/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: e51c7ff0a9885145308892f14e02fc6467e780fd */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_altay_datachannel_PeerConnection___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_getId, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_setRemoteDescription, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, sdp, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, type, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_setLocalDescription, 0, 0, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, type, IS_STRING, 0, "\"\"")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_getLocalDescription, 0, 0, IS_STRING, 1)
ZEND_END_ARG_INFO()

#define arginfo_class_altay_datachannel_PeerConnection_getLocalDescriptionType arginfo_class_altay_datachannel_PeerConnection_getLocalDescription

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_addRemoteCandidate, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, candidate, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, mid, IS_STRING, 0, "\"0\"")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_createDataChannel, 0, 1, altay\\datachannel\\DataChannel, 0)
	ZEND_ARG_TYPE_INFO(0, label, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

#define arginfo_class_altay_datachannel_PeerConnection_getState arginfo_class_altay_datachannel_PeerConnection_getId

#define arginfo_class_altay_datachannel_PeerConnection_getIceState arginfo_class_altay_datachannel_PeerConnection_getId

#define arginfo_class_altay_datachannel_PeerConnection_getGatheringState arginfo_class_altay_datachannel_PeerConnection_getId

#define arginfo_class_altay_datachannel_PeerConnection_getCloseReason arginfo_class_altay_datachannel_PeerConnection_getId

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_getRtt, 0, 0, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_getSctpStats, 0, 0, IS_ARRAY, 1)
ZEND_END_ARG_INFO()

#define arginfo_class_altay_datachannel_PeerConnection_getRemoteFingerprint arginfo_class_altay_datachannel_PeerConnection_getLocalDescription

#define arginfo_class_altay_datachannel_PeerConnection_getSelectedCandidatePair arginfo_class_altay_datachannel_PeerConnection_getSctpStats

#define arginfo_class_altay_datachannel_PeerConnection_getRemoteMaxMessageSize arginfo_class_altay_datachannel_PeerConnection_getId

#define arginfo_class_altay_datachannel_PeerConnection_getBytesSent arginfo_class_altay_datachannel_PeerConnection_getId

#define arginfo_class_altay_datachannel_PeerConnection_getBytesReceived arginfo_class_altay_datachannel_PeerConnection_getId

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_PeerConnection_close, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(altay_datachannel_PeerConnection, __construct);
ZEND_METHOD(altay_datachannel_PeerConnection, getId);
ZEND_METHOD(altay_datachannel_PeerConnection, setRemoteDescription);
ZEND_METHOD(altay_datachannel_PeerConnection, setLocalDescription);
ZEND_METHOD(altay_datachannel_PeerConnection, getLocalDescription);
ZEND_METHOD(altay_datachannel_PeerConnection, getLocalDescriptionType);
ZEND_METHOD(altay_datachannel_PeerConnection, addRemoteCandidate);
ZEND_METHOD(altay_datachannel_PeerConnection, createDataChannel);
ZEND_METHOD(altay_datachannel_PeerConnection, getState);
ZEND_METHOD(altay_datachannel_PeerConnection, getIceState);
ZEND_METHOD(altay_datachannel_PeerConnection, getGatheringState);
ZEND_METHOD(altay_datachannel_PeerConnection, getCloseReason);
ZEND_METHOD(altay_datachannel_PeerConnection, getRtt);
ZEND_METHOD(altay_datachannel_PeerConnection, getSctpStats);
ZEND_METHOD(altay_datachannel_PeerConnection, getRemoteFingerprint);
ZEND_METHOD(altay_datachannel_PeerConnection, getSelectedCandidatePair);
ZEND_METHOD(altay_datachannel_PeerConnection, getRemoteMaxMessageSize);
ZEND_METHOD(altay_datachannel_PeerConnection, getBytesSent);
ZEND_METHOD(altay_datachannel_PeerConnection, getBytesReceived);
ZEND_METHOD(altay_datachannel_PeerConnection, close);

static const zend_function_entry class_altay_datachannel_PeerConnection_methods[] = {
	ZEND_ME(altay_datachannel_PeerConnection, __construct, arginfo_class_altay_datachannel_PeerConnection___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(altay_datachannel_PeerConnection, getId, arginfo_class_altay_datachannel_PeerConnection_getId, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, setRemoteDescription, arginfo_class_altay_datachannel_PeerConnection_setRemoteDescription, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, setLocalDescription, arginfo_class_altay_datachannel_PeerConnection_setLocalDescription, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getLocalDescription, arginfo_class_altay_datachannel_PeerConnection_getLocalDescription, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getLocalDescriptionType, arginfo_class_altay_datachannel_PeerConnection_getLocalDescriptionType, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, addRemoteCandidate, arginfo_class_altay_datachannel_PeerConnection_addRemoteCandidate, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, createDataChannel, arginfo_class_altay_datachannel_PeerConnection_createDataChannel, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getState, arginfo_class_altay_datachannel_PeerConnection_getState, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getIceState, arginfo_class_altay_datachannel_PeerConnection_getIceState, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getGatheringState, arginfo_class_altay_datachannel_PeerConnection_getGatheringState, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getCloseReason, arginfo_class_altay_datachannel_PeerConnection_getCloseReason, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getRtt, arginfo_class_altay_datachannel_PeerConnection_getRtt, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getSctpStats, arginfo_class_altay_datachannel_PeerConnection_getSctpStats, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getRemoteFingerprint, arginfo_class_altay_datachannel_PeerConnection_getRemoteFingerprint, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getSelectedCandidatePair, arginfo_class_altay_datachannel_PeerConnection_getSelectedCandidatePair, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getRemoteMaxMessageSize, arginfo_class_altay_datachannel_PeerConnection_getRemoteMaxMessageSize, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getBytesSent, arginfo_class_altay_datachannel_PeerConnection_getBytesSent, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, getBytesReceived, arginfo_class_altay_datachannel_PeerConnection_getBytesReceived, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_PeerConnection, close, arginfo_class_altay_datachannel_PeerConnection_close, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_altay_datachannel_PeerConnection(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "altay\\datachannel", "PeerConnection", class_altay_datachannel_PeerConnection_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;
#endif

	zval const_STATE_NEW_value;
	ZVAL_LONG(&const_STATE_NEW_value, 0);
	zend_string *const_STATE_NEW_name = zend_string_init_interned("STATE_NEW", sizeof("STATE_NEW") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_STATE_NEW_name, &const_STATE_NEW_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_STATE_NEW_name);

	zval const_STATE_CONNECTING_value;
	ZVAL_LONG(&const_STATE_CONNECTING_value, 1);
	zend_string *const_STATE_CONNECTING_name = zend_string_init_interned("STATE_CONNECTING", sizeof("STATE_CONNECTING") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_STATE_CONNECTING_name, &const_STATE_CONNECTING_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_STATE_CONNECTING_name);

	zval const_STATE_CONNECTED_value;
	ZVAL_LONG(&const_STATE_CONNECTED_value, 2);
	zend_string *const_STATE_CONNECTED_name = zend_string_init_interned("STATE_CONNECTED", sizeof("STATE_CONNECTED") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_STATE_CONNECTED_name, &const_STATE_CONNECTED_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_STATE_CONNECTED_name);

	zval const_STATE_DISCONNECTED_value;
	ZVAL_LONG(&const_STATE_DISCONNECTED_value, 3);
	zend_string *const_STATE_DISCONNECTED_name = zend_string_init_interned("STATE_DISCONNECTED", sizeof("STATE_DISCONNECTED") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_STATE_DISCONNECTED_name, &const_STATE_DISCONNECTED_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_STATE_DISCONNECTED_name);

	zval const_STATE_FAILED_value;
	ZVAL_LONG(&const_STATE_FAILED_value, 4);
	zend_string *const_STATE_FAILED_name = zend_string_init_interned("STATE_FAILED", sizeof("STATE_FAILED") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_STATE_FAILED_name, &const_STATE_FAILED_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_STATE_FAILED_name);

	zval const_STATE_CLOSED_value;
	ZVAL_LONG(&const_STATE_CLOSED_value, 5);
	zend_string *const_STATE_CLOSED_name = zend_string_init_interned("STATE_CLOSED", sizeof("STATE_CLOSED") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_STATE_CLOSED_name, &const_STATE_CLOSED_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_STATE_CLOSED_name);

	zval const_GATHERING_NEW_value;
	ZVAL_LONG(&const_GATHERING_NEW_value, 0);
	zend_string *const_GATHERING_NEW_name = zend_string_init_interned("GATHERING_NEW", sizeof("GATHERING_NEW") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_GATHERING_NEW_name, &const_GATHERING_NEW_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_GATHERING_NEW_name);

	zval const_GATHERING_IN_PROGRESS_value;
	ZVAL_LONG(&const_GATHERING_IN_PROGRESS_value, 1);
	zend_string *const_GATHERING_IN_PROGRESS_name = zend_string_init_interned("GATHERING_IN_PROGRESS", sizeof("GATHERING_IN_PROGRESS") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_GATHERING_IN_PROGRESS_name, &const_GATHERING_IN_PROGRESS_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_GATHERING_IN_PROGRESS_name);

	zval const_GATHERING_COMPLETE_value;
	ZVAL_LONG(&const_GATHERING_COMPLETE_value, 2);
	zend_string *const_GATHERING_COMPLETE_name = zend_string_init_interned("GATHERING_COMPLETE", sizeof("GATHERING_COMPLETE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_GATHERING_COMPLETE_name, &const_GATHERING_COMPLETE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_GATHERING_COMPLETE_name);

	zval const_CLOSE_REASON_NONE_value;
	ZVAL_LONG(&const_CLOSE_REASON_NONE_value, 0);
	zend_string *const_CLOSE_REASON_NONE_name = zend_string_init_interned("CLOSE_REASON_NONE", sizeof("CLOSE_REASON_NONE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_CLOSE_REASON_NONE_name, &const_CLOSE_REASON_NONE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_CLOSE_REASON_NONE_name);

	zval const_CLOSE_REASON_LOCAL_value;
	ZVAL_LONG(&const_CLOSE_REASON_LOCAL_value, 1);
	zend_string *const_CLOSE_REASON_LOCAL_name = zend_string_init_interned("CLOSE_REASON_LOCAL", sizeof("CLOSE_REASON_LOCAL") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_CLOSE_REASON_LOCAL_name, &const_CLOSE_REASON_LOCAL_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_CLOSE_REASON_LOCAL_name);

	zval const_CLOSE_REASON_REMOTE_SHUTDOWN_value;
	ZVAL_LONG(&const_CLOSE_REASON_REMOTE_SHUTDOWN_value, 2);
	zend_string *const_CLOSE_REASON_REMOTE_SHUTDOWN_name = zend_string_init_interned("CLOSE_REASON_REMOTE_SHUTDOWN", sizeof("CLOSE_REASON_REMOTE_SHUTDOWN") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_CLOSE_REASON_REMOTE_SHUTDOWN_name, &const_CLOSE_REASON_REMOTE_SHUTDOWN_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_CLOSE_REASON_REMOTE_SHUTDOWN_name);

	zval const_CLOSE_REASON_REMOTE_ABORT_value;
	ZVAL_LONG(&const_CLOSE_REASON_REMOTE_ABORT_value, 3);
	zend_string *const_CLOSE_REASON_REMOTE_ABORT_name = zend_string_init_interned("CLOSE_REASON_REMOTE_ABORT", sizeof("CLOSE_REASON_REMOTE_ABORT") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_CLOSE_REASON_REMOTE_ABORT_name, &const_CLOSE_REASON_REMOTE_ABORT_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_CLOSE_REASON_REMOTE_ABORT_name);

	zval const_CLOSE_REASON_SCTP_TIMEOUT_value;
	ZVAL_LONG(&const_CLOSE_REASON_SCTP_TIMEOUT_value, 4);
	zend_string *const_CLOSE_REASON_SCTP_TIMEOUT_name = zend_string_init_interned("CLOSE_REASON_SCTP_TIMEOUT", sizeof("CLOSE_REASON_SCTP_TIMEOUT") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_CLOSE_REASON_SCTP_TIMEOUT_name, &const_CLOSE_REASON_SCTP_TIMEOUT_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_CLOSE_REASON_SCTP_TIMEOUT_name);

	zval const_CLOSE_REASON_ICE_FAILED_value;
	ZVAL_LONG(&const_CLOSE_REASON_ICE_FAILED_value, 5);
	zend_string *const_CLOSE_REASON_ICE_FAILED_name = zend_string_init_interned("CLOSE_REASON_ICE_FAILED", sizeof("CLOSE_REASON_ICE_FAILED") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_CLOSE_REASON_ICE_FAILED_name, &const_CLOSE_REASON_ICE_FAILED_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_CLOSE_REASON_ICE_FAILED_name);

	zval const_CLOSE_REASON_TRANSPORT_FAILED_value;
	ZVAL_LONG(&const_CLOSE_REASON_TRANSPORT_FAILED_value, 6);
	zend_string *const_CLOSE_REASON_TRANSPORT_FAILED_name = zend_string_init_interned("CLOSE_REASON_TRANSPORT_FAILED", sizeof("CLOSE_REASON_TRANSPORT_FAILED") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_CLOSE_REASON_TRANSPORT_FAILED_name, &const_CLOSE_REASON_TRANSPORT_FAILED_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_CLOSE_REASON_TRANSPORT_FAILED_name);

	return class_entry;
}
