#include <cstddef>

#include "Common.h"
#include "../ZendUtil.h"

extern "C" {
#include "zend_exceptions.h"
#include "../stubs/DataChannel_arginfo.h"
}

zend_class_entry* data_channel_ce;
static zend_object_handlers data_channel_handlers;

static inline data_channel_obj* fetch_channel(zend_object* object) {
	return fetch_from_zend_object<data_channel_obj>(object);
}

static zend_object* data_channel_new(zend_class_entry* ce) {
	auto object = alloc_custom_zend_object<data_channel_obj>(ce, &data_channel_handlers);
	new (&object->channel) std::shared_ptr<rtc::DataChannel>();
	object->id = 0;
	object->peerId = 0;
	return &object->std;
}

static void data_channel_free(zend_object* std) {
	auto object = fetch_channel(std);
	object->channel.~shared_ptr();
	zend_object_std_dtor(std);
}

void data_channel_create(zval* return_value, std::shared_ptr<rtc::DataChannel> channel, zend_long id, zend_long peerId) {
	object_init_ex(return_value, data_channel_ce);
	auto object = fetch_channel(Z_OBJ_P(return_value));
	object->channel = std::move(channel);
	object->id = id;
	object->peerId = peerId;
}

//runs on whichever thread hands us the channel. Only IDs and the queue are captured, never the channel itself, or
//it would keep itself alive through its own callbacks
void data_channel_attach(const std::shared_ptr<rtc::DataChannel>& channel, const std::shared_ptr<EventQueue>& queue, zend_long peerId, zend_long channelId) {
	std::weak_ptr<EventQueue> weak = queue;

	channel->onOpen([weak, peerId, channelId]() {
		if (auto q = weak.lock()) {
			q->push(QueuedEvent{EVENT_CHANNEL_OPEN, peerId, channelId});
		}
	});
	channel->onClosed([weak, peerId, channelId]() {
		if (auto q = weak.lock()) {
			q->push(QueuedEvent{EVENT_CHANNEL_CLOSED, peerId, channelId});
		}
	});
	channel->onError([weak, peerId, channelId](std::string error) {
		if (auto q = weak.lock()) {
			QueuedEvent event{EVENT_CHANNEL_ERROR, peerId, channelId};
			event.hasText = true;
			event.text = std::move(error);
			q->push(std::move(event));
		}
	});
	channel->onMessage(
		[weak, peerId, channelId](rtc::binary data) {
			if (auto q = weak.lock()) {
				QueuedEvent event{EVENT_MESSAGE, peerId, channelId};
				event.hasText = true;
				event.text.assign(reinterpret_cast<const char*>(data.data()), data.size());
				q->push(std::move(event));
			}
		},
		[weak, peerId, channelId](std::string data) {
			if (auto q = weak.lock()) {
				QueuedEvent event{EVENT_MESSAGE, peerId, channelId};
				event.hasText = true;
				event.number = 1;
				event.text = std::move(data);
				q->push(std::move(event));
			}
		}
	);
	channel->onBufferedAmountLow([weak, peerId, channelId]() {
		if (auto q = weak.lock()) {
			q->push(QueuedEvent{EVENT_BUFFERED_AMOUNT_LOW, peerId, channelId});
		}
	});
}

static data_channel_obj* fetch_this(zval* self) {
	auto object = fetch_channel(Z_OBJ_P(self));
	if (UNEXPECTED(!object->channel)) {
		zend_throw_error(NULL, "This DataChannel was not created by a PeerConnection");
		return nullptr;
	}
	return object;
}

#define CHANNEL_THIS() \
	auto object = fetch_this(ZEND_THIS); \
	if (object == nullptr) { \
		RETURN_THROWS(); \
	} \
	auto& channel = object->channel;

ZEND_METHOD(altay_datachannel_DataChannel, __construct) {
	//NOOP, only PeerConnection and Context create these
}

ZEND_METHOD(altay_datachannel_DataChannel, getId) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	(void)channel;
	RETURN_LONG(object->id);
}

ZEND_METHOD(altay_datachannel_DataChannel, getPeerConnectionId) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	(void)channel;
	RETURN_LONG(object->peerId);
}

ZEND_METHOD(altay_datachannel_DataChannel, getLabel) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	std::string label = channel->label();
	RETURN_STRINGL(label.data(), label.size());
}

ZEND_METHOD(altay_datachannel_DataChannel, getStream) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	auto stream = channel->stream();
	if (!stream) {
		RETURN_NULL();
	}
	RETURN_LONG(*stream);
}

ZEND_METHOD(altay_datachannel_DataChannel, isOpen) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	RETURN_BOOL(channel->isOpen());
}

ZEND_METHOD(altay_datachannel_DataChannel, isClosed) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	RETURN_BOOL(channel->isClosed());
}

ZEND_METHOD(altay_datachannel_DataChannel, send) {
	zend_string* data;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STR(data)
	ZEND_PARSE_PARAMETERS_END();
	CHANNEL_THIS();

	DATACHANNEL_TRY
		RETURN_BOOL(channel->send(reinterpret_cast<const std::byte*>(ZSTR_VAL(data)), ZSTR_LEN(data)));
	DATACHANNEL_CATCH
}

ZEND_METHOD(altay_datachannel_DataChannel, getBufferedAmount) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	RETURN_LONG((zend_long)channel->bufferedAmount());
}

ZEND_METHOD(altay_datachannel_DataChannel, setBufferedAmountLowThreshold) {
	zend_long amount;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(amount)
	ZEND_PARSE_PARAMETERS_END();
	CHANNEL_THIS();

	if (amount < 0) {
		zend_argument_value_error(1, "must be greater than or equal to 0");
		RETURN_THROWS();
	}
	channel->setBufferedAmountLowThreshold((size_t)amount);
}

ZEND_METHOD(altay_datachannel_DataChannel, getMaxMessageSize) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();
	RETURN_LONG((zend_long)channel->maxMessageSize());
}

ZEND_METHOD(altay_datachannel_DataChannel, close) {
	ZEND_PARSE_PARAMETERS_NONE();
	CHANNEL_THIS();

	DATACHANNEL_TRY
		channel->close();
	DATACHANNEL_CATCH
}

void init_class_DataChannel() {
	data_channel_ce = register_class_altay_datachannel_DataChannel();
	data_channel_ce->create_object = data_channel_new;

	memcpy(&data_channel_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	data_channel_handlers.offset = XtOffsetOf(data_channel_obj, std);
	data_channel_handlers.free_obj = data_channel_free;
	data_channel_handlers.clone_obj = nullptr;
}
