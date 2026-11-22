#include <chrono>

#include "Common.h"
#include "../ZendUtil.h"

extern "C" {
#include "zend_exceptions.h"
#include "../stubs/PeerConnection_arginfo.h"
}

zend_class_entry* peer_connection_ce;
static zend_object_handlers peer_connection_handlers;

static inline peer_connection_obj* fetch_peer(zend_object* object) {
	return fetch_from_zend_object<peer_connection_obj>(object);
}

static zend_object* peer_connection_new(zend_class_entry* ce) {
	auto object = alloc_custom_zend_object<peer_connection_obj>(ce, &peer_connection_handlers);
	new (&object->connection) std::shared_ptr<rtc::PeerConnection>();
	new (&object->queue) std::shared_ptr<EventQueue>();
	object->id = 0;
	return &object->std;
}

static void peer_connection_free(zend_object* std) {
	auto object = fetch_peer(std);
	if (object->connection) {
		try {
			object->connection->close();
		} catch (const std::exception&) {
			//nothing useful to do with this while the object is going away
		}
	}
	object->connection.~shared_ptr();
	object->queue.~shared_ptr();
	zend_object_std_dtor(std);
}

void peer_connection_create(zval* return_value, std::shared_ptr<rtc::PeerConnection> connection, std::shared_ptr<EventQueue> queue, zend_long id) {
	object_init_ex(return_value, peer_connection_ce);
	auto object = fetch_peer(Z_OBJ_P(return_value));
	object->connection = std::move(connection);
	object->queue = std::move(queue);
	object->id = id;
}

static peer_connection_obj* fetch_this(zval* self) {
	auto object = fetch_peer(Z_OBJ_P(self));
	if (UNEXPECTED(!object->connection)) {
		zend_throw_error(NULL, "This PeerConnection was not created by a Context");
		return nullptr;
	}
	return object;
}

#define PEER_THIS() \
	auto peer = fetch_this(ZEND_THIS); \
	if (peer == nullptr) { \
		RETURN_THROWS(); \
	} \
	auto& connection = peer->connection;

ZEND_METHOD(altay_datachannel_PeerConnection, __construct) {
	//NOOP, only Context creates these
}

ZEND_METHOD(altay_datachannel_PeerConnection, getId) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	(void)connection;
	RETURN_LONG(peer->id);
}

ZEND_METHOD(altay_datachannel_PeerConnection, setRemoteDescription) {
	zend_string* sdp;
	zend_string* type;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(sdp)
		Z_PARAM_STR(type)
	ZEND_PARSE_PARAMETERS_END();
	PEER_THIS();

	DATACHANNEL_TRY
		connection->setRemoteDescription(rtc::Description(std::string(ZSTR_VAL(sdp), ZSTR_LEN(sdp)), std::string(ZSTR_VAL(type), ZSTR_LEN(type))));
	DATACHANNEL_CATCH
}

ZEND_METHOD(altay_datachannel_PeerConnection, setLocalDescription) {
	zend_string* type = nullptr;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(type)
	ZEND_PARSE_PARAMETERS_END();
	PEER_THIS();

	DATACHANNEL_TRY
		rtc::Description::Type descriptionType = rtc::Description::Type::Unspec;
		if (type != nullptr && ZSTR_LEN(type) > 0) {
			if (zend_string_equals_literal(type, "offer")) {
				descriptionType = rtc::Description::Type::Offer;
			} else if (zend_string_equals_literal(type, "answer")) {
				descriptionType = rtc::Description::Type::Answer;
			} else if (zend_string_equals_literal(type, "pranswer")) {
				descriptionType = rtc::Description::Type::Pranswer;
			} else if (zend_string_equals_literal(type, "rollback")) {
				descriptionType = rtc::Description::Type::Rollback;
			} else {
				zend_argument_value_error(1, "must be \"\", \"offer\", \"answer\", \"pranswer\" or \"rollback\"");
				RETURN_THROWS();
			}
		}
		connection->setLocalDescription(descriptionType);
	DATACHANNEL_CATCH
}

ZEND_METHOD(altay_datachannel_PeerConnection, getLocalDescription) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();

	auto description = connection->localDescription();
	if (!description) {
		RETURN_NULL();
	}
	std::string sdp(*description);
	RETURN_STRINGL(sdp.data(), sdp.size());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getLocalDescriptionType) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();

	auto description = connection->localDescription();
	if (!description) {
		RETURN_NULL();
	}
	std::string type = description->typeString();
	RETURN_STRINGL(type.data(), type.size());
}

ZEND_METHOD(altay_datachannel_PeerConnection, addRemoteCandidate) {
	zend_string* candidate;
	zend_string* mid = nullptr;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(candidate)
		Z_PARAM_OPTIONAL
		Z_PARAM_STR(mid)
	ZEND_PARSE_PARAMETERS_END();
	PEER_THIS();

	DATACHANNEL_TRY
		connection->addRemoteCandidate(rtc::Candidate(
			std::string(ZSTR_VAL(candidate), ZSTR_LEN(candidate)),
			mid != nullptr ? std::string(ZSTR_VAL(mid), ZSTR_LEN(mid)) : std::string("0")
		));
	DATACHANNEL_CATCH
}

ZEND_METHOD(altay_datachannel_PeerConnection, createDataChannel) {
	zend_string* label;
	HashTable* options = nullptr;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STR(label)
		Z_PARAM_OPTIONAL
		Z_PARAM_ARRAY_HT(options)
	ZEND_PARSE_PARAMETERS_END();
	PEER_THIS();

	rtc::DataChannelInit init;
	if (options != nullptr) {
		zend_string* key;
		zval* value;
		ZEND_HASH_FOREACH_STR_KEY_VAL(options, key, value) {
			ZVAL_DEREF(value);
			if (key == nullptr) {
				zend_argument_value_error(2, "must be keyed by option name");
				RETURN_THROWS();
			}
			if (zend_string_equals_literal(key, "unordered") || zend_string_equals_literal(key, "negotiated")) {
				if (Z_TYPE_P(value) != IS_TRUE && Z_TYPE_P(value) != IS_FALSE) {
					zend_type_error("Option \"%s\" must be of type bool, %s given", ZSTR_VAL(key), zend_zval_type_name(value));
					RETURN_THROWS();
				}
				if (zend_string_equals_literal(key, "unordered")) {
					init.reliability.unordered = Z_TYPE_P(value) == IS_TRUE;
				} else {
					init.negotiated = Z_TYPE_P(value) == IS_TRUE;
				}
			} else if (zend_string_equals_literal(key, "maxRetransmits") || zend_string_equals_literal(key, "maxPacketLifeTime") || zend_string_equals_literal(key, "stream")) {
				if (Z_TYPE_P(value) != IS_LONG || Z_LVAL_P(value) < 0 || Z_LVAL_P(value) > 65535) {
					zend_value_error("Option \"%s\" must be an int between 0 and 65535", ZSTR_VAL(key));
					RETURN_THROWS();
				}
				if (zend_string_equals_literal(key, "maxRetransmits")) {
					init.reliability.maxRetransmits = (unsigned int)Z_LVAL_P(value);
				} else if (zend_string_equals_literal(key, "maxPacketLifeTime")) {
					init.reliability.maxPacketLifeTime = std::chrono::milliseconds(Z_LVAL_P(value));
				} else {
					init.id = (uint16_t)Z_LVAL_P(value);
				}
			} else if (zend_string_equals_literal(key, "protocol")) {
				if (Z_TYPE_P(value) != IS_STRING) {
					zend_type_error("Option \"protocol\" must be of type string, %s given", zend_zval_type_name(value));
					RETURN_THROWS();
				}
				init.protocol = std::string(Z_STRVAL_P(value), Z_STRLEN_P(value));
			} else {
				zend_value_error("Unknown option \"%s\"", ZSTR_VAL(key));
				RETURN_THROWS();
			}
		} ZEND_HASH_FOREACH_END();
		if (init.reliability.maxRetransmits && init.reliability.maxPacketLifeTime) {
			zend_value_error("Options \"maxRetransmits\" and \"maxPacketLifeTime\" can't be used together");
			RETURN_THROWS();
		}
	}

	DATACHANNEL_TRY
		auto channel = connection->createDataChannel(std::string(ZSTR_VAL(label), ZSTR_LEN(label)), std::move(init));
		zend_long channelId = peer->queue->nextChannelId++;
		data_channel_attach(channel, peer->queue, peer->id, channelId);
		data_channel_create(return_value, std::move(channel), channelId, peer->id);
	DATACHANNEL_CATCH
}

ZEND_METHOD(altay_datachannel_PeerConnection, getState) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	RETURN_LONG((zend_long)connection->state());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getIceState) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	RETURN_LONG((zend_long)connection->iceState());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getGatheringState) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	RETURN_LONG((zend_long)connection->gatheringState());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getCloseReason) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	RETURN_LONG((zend_long)connection->closeReason());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getRtt) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();

	auto rtt = connection->rtt();
	if (!rtt) {
		RETURN_NULL();
	}
	RETURN_LONG((zend_long)rtt->count());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getSctpStats) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();

	auto stats = connection->sctpStats();
	if (!stats) {
		RETURN_NULL();
	}
	array_init_size(return_value, 7);
	add_assoc_long(return_value, "rtt", (zend_long)stats->rtt.count());
	add_assoc_long(return_value, "rto", (zend_long)stats->rto.count());
	add_assoc_long(return_value, "congestionWindow", (zend_long)stats->congestionWindow);
	add_assoc_long(return_value, "peerReceiveWindow", (zend_long)stats->peerReceiveWindow);
	add_assoc_long(return_value, "unackedChunks", (zend_long)stats->unackedChunks);
	add_assoc_long(return_value, "pendingChunks", (zend_long)stats->pendingChunks);
	add_assoc_long(return_value, "dataTimeouts", (zend_long)stats->dataTimeouts);
}

ZEND_METHOD(altay_datachannel_PeerConnection, getRemoteFingerprint) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();

	DATACHANNEL_TRY
		auto fingerprint = connection->remoteFingerprint();
		if (!fingerprint.isValid()) {
			RETURN_NULL();
		}
		std::string formatted = rtc::CertificateFingerprint::AlgorithmIdentifier(fingerprint.algorithm) + " " + fingerprint.value;
		RETURN_STRINGL(formatted.data(), formatted.size());
	DATACHANNEL_CATCH
}

static void candidate_to_array(zval* out, const rtc::Candidate& candidate) {
	static const char* const TYPES[] = {"unknown", "host", "srflx", "prflx", "relay"};
	auto type = (size_t)candidate.type();

	array_init_size(out, 3);
	auto address = candidate.address();
	if (address) {
		add_next_index_stringl(out, address->data(), address->size());
	} else {
		add_next_index_stringl(out, "", 0);
	}
	add_next_index_long(out, candidate.port().value_or(0));
	add_next_index_string(out, type < sizeof(TYPES) / sizeof(TYPES[0]) ? TYPES[type] : "unknown");
}

ZEND_METHOD(altay_datachannel_PeerConnection, getSelectedCandidatePair) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();

	rtc::Candidate local, remote;
	if (!connection->getSelectedCandidatePair(&local, &remote)) {
		RETURN_NULL();
	}
	zval localArray, remoteArray;
	candidate_to_array(&localArray, local);
	candidate_to_array(&remoteArray, remote);
	array_init_size(return_value, 2);
	add_assoc_zval(return_value, "local", &localArray);
	add_assoc_zval(return_value, "remote", &remoteArray);
}

ZEND_METHOD(altay_datachannel_PeerConnection, getRemoteMaxMessageSize) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	RETURN_LONG((zend_long)connection->remoteMaxMessageSize());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getBytesSent) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	RETURN_LONG((zend_long)connection->bytesSent());
}

ZEND_METHOD(altay_datachannel_PeerConnection, getBytesReceived) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();
	RETURN_LONG((zend_long)connection->bytesReceived());
}

ZEND_METHOD(altay_datachannel_PeerConnection, close) {
	ZEND_PARSE_PARAMETERS_NONE();
	PEER_THIS();

	DATACHANNEL_TRY
		connection->close();
	DATACHANNEL_CATCH
}

void init_class_PeerConnection() {
	peer_connection_ce = register_class_altay_datachannel_PeerConnection();
	peer_connection_ce->create_object = peer_connection_new;

	memcpy(&peer_connection_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	peer_connection_handlers.offset = XtOffsetOf(peer_connection_obj, std);
	peer_connection_handlers.free_obj = peer_connection_free;
	peer_connection_handlers.clone_obj = nullptr;
}
