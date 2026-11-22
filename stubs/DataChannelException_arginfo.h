/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 5ebde1454c8a45f714a9a67019cb773d899a7150 */

static zend_class_entry *register_class_altay_datachannel_DataChannelException(zend_class_entry *class_entry_RuntimeException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "altay\\datachannel", "DataChannelException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_RuntimeException, 0);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_RuntimeException);
#endif

	return class_entry;
}
