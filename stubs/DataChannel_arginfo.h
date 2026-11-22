/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 582aceb2db9a38bb25e5f3b81de8d86699dfe78e */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_altay_datachannel_DataChannel___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_DataChannel_getId, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_altay_datachannel_DataChannel_getPeerConnectionId arginfo_class_altay_datachannel_DataChannel_getId

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_DataChannel_getLabel, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_DataChannel_getStream, 0, 0, IS_LONG, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_DataChannel_isOpen, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_altay_datachannel_DataChannel_isClosed arginfo_class_altay_datachannel_DataChannel_isOpen

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_DataChannel_send, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_altay_datachannel_DataChannel_getBufferedAmount arginfo_class_altay_datachannel_DataChannel_getId

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_DataChannel_setBufferedAmountLowThreshold, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, amount, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_altay_datachannel_DataChannel_getMaxMessageSize arginfo_class_altay_datachannel_DataChannel_getId

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_altay_datachannel_DataChannel_close, 0, 0, IS_VOID, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(altay_datachannel_DataChannel, __construct);
ZEND_METHOD(altay_datachannel_DataChannel, getId);
ZEND_METHOD(altay_datachannel_DataChannel, getPeerConnectionId);
ZEND_METHOD(altay_datachannel_DataChannel, getLabel);
ZEND_METHOD(altay_datachannel_DataChannel, getStream);
ZEND_METHOD(altay_datachannel_DataChannel, isOpen);
ZEND_METHOD(altay_datachannel_DataChannel, isClosed);
ZEND_METHOD(altay_datachannel_DataChannel, send);
ZEND_METHOD(altay_datachannel_DataChannel, getBufferedAmount);
ZEND_METHOD(altay_datachannel_DataChannel, setBufferedAmountLowThreshold);
ZEND_METHOD(altay_datachannel_DataChannel, getMaxMessageSize);
ZEND_METHOD(altay_datachannel_DataChannel, close);

static const zend_function_entry class_altay_datachannel_DataChannel_methods[] = {
	ZEND_ME(altay_datachannel_DataChannel, __construct, arginfo_class_altay_datachannel_DataChannel___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(altay_datachannel_DataChannel, getId, arginfo_class_altay_datachannel_DataChannel_getId, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, getPeerConnectionId, arginfo_class_altay_datachannel_DataChannel_getPeerConnectionId, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, getLabel, arginfo_class_altay_datachannel_DataChannel_getLabel, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, getStream, arginfo_class_altay_datachannel_DataChannel_getStream, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, isOpen, arginfo_class_altay_datachannel_DataChannel_isOpen, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, isClosed, arginfo_class_altay_datachannel_DataChannel_isClosed, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, send, arginfo_class_altay_datachannel_DataChannel_send, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, getBufferedAmount, arginfo_class_altay_datachannel_DataChannel_getBufferedAmount, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, setBufferedAmountLowThreshold, arginfo_class_altay_datachannel_DataChannel_setBufferedAmountLowThreshold, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, getMaxMessageSize, arginfo_class_altay_datachannel_DataChannel_getMaxMessageSize, ZEND_ACC_PUBLIC)
	ZEND_ME(altay_datachannel_DataChannel, close, arginfo_class_altay_datachannel_DataChannel_close, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_altay_datachannel_DataChannel(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "altay\\datachannel", "DataChannel", class_altay_datachannel_DataChannel_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;
#endif

	return class_entry;
}
