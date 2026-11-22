#include <limits>

#include "Common.h"
#include "../ZendUtil.h"

extern "C" {
#include "zend_exceptions.h"
#include "../stubs/Context_arginfo.h"
}

typedef struct _context_obj {
	std::shared_ptr<EventQueue> queue;
	zend_long nextPeerId;
	zend_object std;
} context_obj;

static zend_class_entry* context_ce;
static zend_object_handlers context_handlers;

static inline context_obj* fetch_context(zend_object* object) {
	return fetch_from_zend_object<context_obj>(object);
}

/* log lines */

//the logger is process wide, so its lines don't belong to any one context. Keep a bounded backlog in case nobody
//polls for a while, a stuck thread shouldn't turn into unbounded memory
static constexpr size_t MAX_LOG_BACKLOG = 4096;
static std::mutex log_mutex;
static std::deque<QueuedEvent> log_backlog;

static void log_callback(rtc::LogLevel level, std::string message) {
	QueuedEvent event{EVENT_LOG};
	event.number = (zend_long)level;
	event.hasText = true;
	event.text = std::move(message);

	std::lock_guard<std::mutex> lock(log_mutex);
	if (log_backlog.size() >= MAX_LOG_BACKLOG) {
		log_backlog.pop_front();
	}
	log_backlog.push_back(std::move(event));
}

void log_queue_drain(std::deque<QueuedEvent>& into) {
	std::lock_guard<std::mutex> lock(log_mutex);
	while (!log_backlog.empty()) {
		into.push_back(std::move(log_backlog.front()));
		log_backlog.pop_front();
	}
}

/* object handlers */

static zend_object* context_new(zend_class_entry* ce) {
	auto object = alloc_custom_zend_object<context_obj>(ce, &context_handlers);
	new (&object->queue) std::shared_ptr<EventQueue>(std::make_shared<EventQueue>());
	object->nextPeerId = 1;
	return &object->std;
}

static void context_free(zend_object* std) {
	auto object = fetch_context(std);
	object->queue.~shared_ptr();
	zend_object_std_dtor(std);
}

/* option parsing */

static bool read_bool(zval* value, const char* name, bool& out) {
	if (Z_TYPE_P(value) != IS_TRUE && Z_TYPE_P(value) != IS_FALSE) {
		zend_type_error("Option \"%s\" must be of type bool, %s given", name, zend_zval_type_name(value));
		return false;
	}
	out = Z_TYPE_P(value) == IS_TRUE;
	return true;
}

static bool read_string(zval* value, const char* name, std::string& out) {
	if (Z_TYPE_P(value) != IS_STRING) {
		zend_type_error("Option \"%s\" must be of type string, %s given", name, zend_zval_type_name(value));
		return false;
	}
	out.assign(Z_STRVAL_P(value), Z_STRLEN_P(value));
	return true;
}

static bool read_int(zval* value, const char* name, zend_long min, zend_long max, zend_long& out) {
	if (Z_TYPE_P(value) != IS_LONG) {
		zend_type_error("Option \"%s\" must be of type int, %s given", name, zend_zval_type_name(value));
		return false;
	}
	if (Z_LVAL_P(value) < min || Z_LVAL_P(value) > max) {
		zend_value_error("Option \"%s\" must be between " ZEND_LONG_FMT " and " ZEND_LONG_FMT, name, min, max);
		return false;
	}
	out = Z_LVAL_P(value);
	return true;
}

static bool parse_configuration(HashTable* options, rtc::Configuration& config) {
	zend_string* key;
	zval* value;
	ZEND_HASH_FOREACH_STR_KEY_VAL(options, key, value) {
		if (key == nullptr) {
			zend_value_error("Options must be keyed by name");
			return false;
		}
		ZVAL_DEREF(value);
		const char* name = ZSTR_VAL(key);
		std::string text;
		zend_long number = 0;
		bool flag = false;

		if (zend_string_equals_literal(key, "iceServers")) {
			if (Z_TYPE_P(value) != IS_ARRAY) {
				zend_type_error("Option \"iceServers\" must be of type array, %s given", zend_zval_type_name(value));
				return false;
			}
			zval* server;
			ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(value), server) {
				ZVAL_DEREF(server);
				if (!read_string(server, "iceServers", text)) {
					return false;
				}
				try {
					config.iceServers.emplace_back(text);
				} catch (const std::exception& e) {
					zend_value_error("Invalid ICE server \"%s\": %s", text.c_str(), e.what());
					return false;
				}
			} ZEND_HASH_FOREACH_END();
		} else if (zend_string_equals_literal(key, "bindAddress")) {
			if (!read_string(value, name, text)) return false;
			config.bindAddress = text;
		} else if (zend_string_equals_literal(key, "portRangeBegin")) {
			if (!read_int(value, name, 1, 65535, number)) return false;
			config.portRangeBegin = (uint16_t)number;
		} else if (zend_string_equals_literal(key, "portRangeEnd")) {
			if (!read_int(value, name, 1, 65535, number)) return false;
			config.portRangeEnd = (uint16_t)number;
		} else if (zend_string_equals_literal(key, "enableIceUdpMux")) {
			if (!read_bool(value, name, flag)) return false;
			config.enableIceUdpMux = flag;
		} else if (zend_string_equals_literal(key, "enableIceTcp")) {
			if (!read_bool(value, name, flag)) return false;
			config.enableIceTcp = flag;
		} else if (zend_string_equals_literal(key, "relayOnly")) {
			if (!read_bool(value, name, flag)) return false;
			config.iceTransportPolicy = flag ? rtc::TransportPolicy::Relay : rtc::TransportPolicy::All;
		} else if (zend_string_equals_literal(key, "disableAutoNegotiation")) {
			if (!read_bool(value, name, flag)) return false;
			config.disableAutoNegotiation = flag;
		} else if (zend_string_equals_literal(key, "certificatePemFile")) {
			if (!read_string(value, name, text)) return false;
			config.certificatePemFile = text;
		} else if (zend_string_equals_literal(key, "keyPemFile")) {
			if (!read_string(value, name, text)) return false;
			config.keyPemFile = text;
		} else if (zend_string_equals_literal(key, "keyPemPass")) {
			if (!read_string(value, name, text)) return false;
			config.keyPemPass = text;
		} else if (zend_string_equals_literal(key, "maxMessageSize")) {
			if (!read_int(value, name, 1, std::numeric_limits<int32_t>::max(), number)) return false;
			config.maxMessageSize = (size_t)number;
		} else if (zend_string_equals_literal(key, "mtu")) {
			if (!read_int(value, name, 576, 65535, number)) return false;
			config.mtu = (size_t)number;
		} else {
			zend_value_error("Unknown option \"%s\"", name);
			return false;
		}
	} ZEND_HASH_FOREACH_END();

	if (config.portRangeBegin > config.portRangeEnd) {
		zend_value_error("Option \"portRangeBegin\" must not be greater than \"portRangeEnd\"");
		return false;
	}
	return true;
}

/* callbacks, these run on libdatachannel's threads */

static void attach_peer_callbacks(const std::shared_ptr<rtc::PeerConnection>& connection, const std::shared_ptr<EventQueue>& queue, zend_long peerId) {
	std::weak_ptr<EventQueue> weak = queue;

	connection->onStateChange([weak, peerId](rtc::PeerConnection::State state) {
		if (auto q = weak.lock()) {
			QueuedEvent event{EVENT_STATE, peerId};
			event.number = (zend_long)state;
			q->push(std::move(event));
		}
	});
	connection->onIceStateChange([weak, peerId](rtc::PeerConnection::IceState state) {
		if (auto q = weak.lock()) {
			QueuedEvent event{EVENT_ICE_STATE, peerId};
			event.number = (zend_long)state;
			q->push(std::move(event));
		}
	});
	connection->onGatheringStateChange([weak, peerId](rtc::PeerConnection::GatheringState state) {
		if (auto q = weak.lock()) {
			QueuedEvent event{EVENT_GATHERING_STATE, peerId};
			event.number = (zend_long)state;
			q->push(std::move(event));
		}
	});
	connection->onLocalDescription([weak, peerId](rtc::Description description) {
		if (auto q = weak.lock()) {
			QueuedEvent event{EVENT_LOCAL_DESCRIPTION, peerId};
			event.hasText = true;
			event.text = std::string(description);
			event.extra = description.typeString();
			q->push(std::move(event));
		}
	});
	connection->onLocalCandidate([weak, peerId](rtc::Candidate candidate) {
		if (auto q = weak.lock()) {
			QueuedEvent event{EVENT_LOCAL_CANDIDATE, peerId};
			event.hasText = true;
			event.text = candidate.candidate();
			event.extra = candidate.mid();
			q->push(std::move(event));
		}
	});
	connection->onDataChannel([weak, peerId](std::shared_ptr<rtc::DataChannel> channel) {
		if (auto q = weak.lock()) {
			//callbacks go on before this returns, anything the channel receives before that is held by the library
			zend_long channelId = q->nextChannelId++;
			data_channel_attach(channel, q, peerId, channelId);
			QueuedEvent event{EVENT_DATA_CHANNEL, peerId, channelId};
			event.channel = std::move(channel);
			q->push(std::move(event));
		}
	});
}

/* methods */

#define CONTEXT_THIS() fetch_context(Z_OBJ_P(ZEND_THIS))

ZEND_METHOD(altay_datachannel_Context, __construct) {
	ZEND_PARSE_PARAMETERS_NONE();
}

ZEND_METHOD(altay_datachannel_Context, createPeerConnection) {
	HashTable* options = nullptr;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY_HT(options)
	ZEND_PARSE_PARAMETERS_END();

	rtc::Configuration config;
	if (options != nullptr && !parse_configuration(options, config)) {
		RETURN_THROWS();
	}

	auto context = CONTEXT_THIS();
	zend_long peerId = context->nextPeerId++;

	DATACHANNEL_TRY
		auto connection = std::make_shared<rtc::PeerConnection>(std::move(config));
		attach_peer_callbacks(connection, context->queue, peerId);
		peer_connection_create(return_value, std::move(connection), context->queue, peerId);
	DATACHANNEL_CATCH
}

ZEND_METHOD(altay_datachannel_Context, poll) {
	ZEND_PARSE_PARAMETERS_NONE();

	auto context = CONTEXT_THIS();
	std::deque<QueuedEvent> events = context->queue->drain();
	log_queue_drain(events);

	array_init_size(return_value, (uint32_t)events.size());
	for (auto& event : events) {
		zval entry, value, extra;
		array_init_size(&entry, 5);
		add_next_index_long(&entry, event.type);
		add_next_index_long(&entry, event.peerId);
		add_next_index_long(&entry, event.channelId);

		ZVAL_NULL(&extra);
		switch (event.type) {
			case EVENT_DATA_CHANNEL:
				data_channel_create(&value, std::move(event.channel), event.channelId, event.peerId);
				break;
			case EVENT_LOCAL_DESCRIPTION:
			case EVENT_LOCAL_CANDIDATE:
				ZVAL_STRINGL(&value, event.text.data(), event.text.size());
				ZVAL_STRINGL(&extra, event.extra.data(), event.extra.size());
				break;
			case EVENT_MESSAGE:
				ZVAL_STRINGL(&value, event.text.data(), event.text.size());
				ZVAL_BOOL(&extra, event.number != 0);
				break;
			case EVENT_LOG:
				ZVAL_STRINGL(&value, event.text.data(), event.text.size());
				ZVAL_LONG(&extra, event.number);
				break;
			default:
				if (event.hasText) {
					ZVAL_STRINGL(&value, event.text.data(), event.text.size());
				} else {
					ZVAL_LONG(&value, event.number);
				}
				break;
		}
		add_next_index_zval(&entry, &value);
		add_next_index_zval(&entry, &extra);
		add_next_index_zval(return_value, &entry);
	}
}

ZEND_METHOD(altay_datachannel_Context, setLogLevel) {
	zend_long level;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(level)
	ZEND_PARSE_PARAMETERS_END();

	if (level < (zend_long)rtc::LogLevel::None || level > (zend_long)rtc::LogLevel::Verbose) {
		zend_argument_value_error(1, "must be one of the Context::LOG_* constants");
		RETURN_THROWS();
	}

	//later calls swap the callback and change the level, so always hand ours over or logging goes back to stdout
	rtc::InitLogger((rtc::LogLevel)level, log_callback);
}

void init_class_Context() {
	context_ce = register_class_altay_datachannel_Context();
	context_ce->create_object = context_new;

	memcpy(&context_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	context_handlers.offset = XtOffsetOf(context_obj, std);
	context_handlers.free_obj = context_free;
	context_handlers.clone_obj = nullptr;
}
