/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: b0a40108a1a959eb6d4001b2998e9c63caeada90 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_altay_datachannel_Context___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_altay_datachannel_Context_createPeerConnection, 0, 0, altay\\datachannel\\PeerConnection, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, options, IS_ARRAY, 0, "[]")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_Context_poll, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_Context_setLogLevel, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, level, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(altay_datachannel_Context, __construct);
ZEND_METHOD(altay_datachannel_Context, createPeerConnection);
ZEND_METHOD(altay_datachannel_Context, poll);
ZEND_METHOD(altay_datachannel_Context, setLogLevel);

static const zend_function_entry class_altay_datachannel_Context_methods[] = {
	ZEND_ME(altay_datachannel_Context, __construct, arginfo_class_altay_datachannel_Context___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_Context, createPeerConnection, arginfo_class_altay_datachannel_Context_createPeerConnection, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_Context, poll, arginfo_class_altay_datachannel_Context_poll, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_Context, setLogLevel, arginfo_class_altay_datachannel_Context_setLogLevel, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_altay_datachannel_Context(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "altay\\datachannel", "Context", class_altay_datachannel_Context_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;
#endif

	zval const_EVENT_STATE_value;
	ZVAL_LONG(&const_EVENT_STATE_value, 1);
	zend_string *const_EVENT_STATE_name = zend_string_init_interned("EVENT_STATE", sizeof("EVENT_STATE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_STATE_name, &const_EVENT_STATE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_STATE_name);

	zval const_EVENT_ICE_STATE_value;
	ZVAL_LONG(&const_EVENT_ICE_STATE_value, 2);
	zend_string *const_EVENT_ICE_STATE_name = zend_string_init_interned("EVENT_ICE_STATE", sizeof("EVENT_ICE_STATE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_ICE_STATE_name, &const_EVENT_ICE_STATE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_ICE_STATE_name);

	zval const_EVENT_GATHERING_STATE_value;
	ZVAL_LONG(&const_EVENT_GATHERING_STATE_value, 3);
	zend_string *const_EVENT_GATHERING_STATE_name = zend_string_init_interned("EVENT_GATHERING_STATE", sizeof("EVENT_GATHERING_STATE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_GATHERING_STATE_name, &const_EVENT_GATHERING_STATE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_GATHERING_STATE_name);

	zval const_EVENT_LOCAL_DESCRIPTION_value;
	ZVAL_LONG(&const_EVENT_LOCAL_DESCRIPTION_value, 4);
	zend_string *const_EVENT_LOCAL_DESCRIPTION_name = zend_string_init_interned("EVENT_LOCAL_DESCRIPTION", sizeof("EVENT_LOCAL_DESCRIPTION") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_LOCAL_DESCRIPTION_name, &const_EVENT_LOCAL_DESCRIPTION_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_LOCAL_DESCRIPTION_name);

	zval const_EVENT_LOCAL_CANDIDATE_value;
	ZVAL_LONG(&const_EVENT_LOCAL_CANDIDATE_value, 5);
	zend_string *const_EVENT_LOCAL_CANDIDATE_name = zend_string_init_interned("EVENT_LOCAL_CANDIDATE", sizeof("EVENT_LOCAL_CANDIDATE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_LOCAL_CANDIDATE_name, &const_EVENT_LOCAL_CANDIDATE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_LOCAL_CANDIDATE_name);

	zval const_EVENT_DATA_CHANNEL_value;
	ZVAL_LONG(&const_EVENT_DATA_CHANNEL_value, 6);
	zend_string *const_EVENT_DATA_CHANNEL_name = zend_string_init_interned("EVENT_DATA_CHANNEL", sizeof("EVENT_DATA_CHANNEL") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_DATA_CHANNEL_name, &const_EVENT_DATA_CHANNEL_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_DATA_CHANNEL_name);

	zval const_EVENT_CHANNEL_OPEN_value;
	ZVAL_LONG(&const_EVENT_CHANNEL_OPEN_value, 7);
	zend_string *const_EVENT_CHANNEL_OPEN_name = zend_string_init_interned("EVENT_CHANNEL_OPEN", sizeof("EVENT_CHANNEL_OPEN") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_CHANNEL_OPEN_name, &const_EVENT_CHANNEL_OPEN_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_CHANNEL_OPEN_name);

	zval const_EVENT_CHANNEL_CLOSED_value;
	ZVAL_LONG(&const_EVENT_CHANNEL_CLOSED_value, 8);
	zend_string *const_EVENT_CHANNEL_CLOSED_name = zend_string_init_interned("EVENT_CHANNEL_CLOSED", sizeof("EVENT_CHANNEL_CLOSED") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_CHANNEL_CLOSED_name, &const_EVENT_CHANNEL_CLOSED_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_CHANNEL_CLOSED_name);

	zval const_EVENT_CHANNEL_ERROR_value;
	ZVAL_LONG(&const_EVENT_CHANNEL_ERROR_value, 9);
	zend_string *const_EVENT_CHANNEL_ERROR_name = zend_string_init_interned("EVENT_CHANNEL_ERROR", sizeof("EVENT_CHANNEL_ERROR") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_CHANNEL_ERROR_name, &const_EVENT_CHANNEL_ERROR_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_CHANNEL_ERROR_name);

	zval const_EVENT_MESSAGE_value;
	ZVAL_LONG(&const_EVENT_MESSAGE_value, 10);
	zend_string *const_EVENT_MESSAGE_name = zend_string_init_interned("EVENT_MESSAGE", sizeof("EVENT_MESSAGE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_MESSAGE_name, &const_EVENT_MESSAGE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_MESSAGE_name);

	zval const_EVENT_BUFFERED_AMOUNT_LOW_value;
	ZVAL_LONG(&const_EVENT_BUFFERED_AMOUNT_LOW_value, 11);
	zend_string *const_EVENT_BUFFERED_AMOUNT_LOW_name = zend_string_init_interned("EVENT_BUFFERED_AMOUNT_LOW", sizeof("EVENT_BUFFERED_AMOUNT_LOW") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_BUFFERED_AMOUNT_LOW_name, &const_EVENT_BUFFERED_AMOUNT_LOW_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_BUFFERED_AMOUNT_LOW_name);

	zval const_EVENT_LOG_value;
	ZVAL_LONG(&const_EVENT_LOG_value, 12);
	zend_string *const_EVENT_LOG_name = zend_string_init_interned("EVENT_LOG", sizeof("EVENT_LOG") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_EVENT_LOG_name, &const_EVENT_LOG_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_EVENT_LOG_name);

	zval const_LOG_NONE_value;
	ZVAL_LONG(&const_LOG_NONE_value, 0);
	zend_string *const_LOG_NONE_name = zend_string_init_interned("LOG_NONE", sizeof("LOG_NONE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_LOG_NONE_name, &const_LOG_NONE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_LOG_NONE_name);

	zval const_LOG_FATAL_value;
	ZVAL_LONG(&const_LOG_FATAL_value, 1);
	zend_string *const_LOG_FATAL_name = zend_string_init_interned("LOG_FATAL", sizeof("LOG_FATAL") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_LOG_FATAL_name, &const_LOG_FATAL_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_LOG_FATAL_name);

	zval const_LOG_ERROR_value;
	ZVAL_LONG(&const_LOG_ERROR_value, 2);
	zend_string *const_LOG_ERROR_name = zend_string_init_interned("LOG_ERROR", sizeof("LOG_ERROR") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_LOG_ERROR_name, &const_LOG_ERROR_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_LOG_ERROR_name);

	zval const_LOG_WARNING_value;
	ZVAL_LONG(&const_LOG_WARNING_value, 3);
	zend_string *const_LOG_WARNING_name = zend_string_init_interned("LOG_WARNING", sizeof("LOG_WARNING") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_LOG_WARNING_name, &const_LOG_WARNING_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_LOG_WARNING_name);

	zval const_LOG_INFO_value;
	ZVAL_LONG(&const_LOG_INFO_value, 4);
	zend_string *const_LOG_INFO_name = zend_string_init_interned("LOG_INFO", sizeof("LOG_INFO") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_LOG_INFO_name, &const_LOG_INFO_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_LOG_INFO_name);

	zval const_LOG_DEBUG_value;
	ZVAL_LONG(&const_LOG_DEBUG_value, 5);
	zend_string *const_LOG_DEBUG_name = zend_string_init_interned("LOG_DEBUG", sizeof("LOG_DEBUG") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_LOG_DEBUG_name, &const_LOG_DEBUG_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_LOG_DEBUG_name);

	zval const_LOG_VERBOSE_value;
	ZVAL_LONG(&const_LOG_VERBOSE_value, 6);
	zend_string *const_LOG_VERBOSE_name = zend_string_init_interned("LOG_VERBOSE", sizeof("LOG_VERBOSE") - 1, 1);
	zend_declare_class_constant_ex(class_entry, const_LOG_VERBOSE_name, &const_LOG_VERBOSE_value, ZEND_ACC_PUBLIC, NULL);
	zend_string_release(const_LOG_VERBOSE_name);

	return class_entry;
}
