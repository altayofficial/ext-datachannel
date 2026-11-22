/* datachannel extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <chrono>

#include "classes/Common.h"

extern "C" {
#include "ext/standard/info.h"
#include "ext/spl/spl_exceptions.h"
#include "php_datachannel.h"
#include "stubs/DataChannelException_arginfo.h"
}

zend_class_entry* datachannel_exception_ce;

PHP_MINFO_FUNCTION(datachannel)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "datachannel support", "enabled");
	php_info_print_table_row(2, "Version", PHP_DATACHANNEL_VERSION);
	php_info_print_table_row(2, "libdatachannel", RTC_VERSION);
	php_info_print_table_end();
}

PHP_RINIT_FUNCTION(datachannel)
{
#if defined(ZTS) && defined(COMPILE_DL_DATACHANNEL)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_MINIT_FUNCTION(datachannel)
{
	datachannel_exception_ce = register_class_altay_datachannel_DataChannelException(spl_ce_RuntimeException);
	init_class_Context();
	init_class_PeerConnection();
	init_class_DataChannel();

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(datachannel)
{
	//every peer connection is gone by now, this only waits for libdatachannel's own threads. Don't hang the process
	//forever if one of them is stuck though
	rtc::Cleanup().wait_for(std::chrono::seconds(5));

	return SUCCESS;
}

static const zend_module_dep module_dependencies[] = {
	ZEND_MOD_REQUIRED("spl")
	ZEND_MOD_END
};

zend_module_entry datachannel_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	module_dependencies,
	"datachannel",
	NULL, /* functions */
	PHP_MINIT(datachannel),
	PHP_MSHUTDOWN(datachannel),
	PHP_RINIT(datachannel),
	NULL, /* RSHUTDOWN */
	PHP_MINFO(datachannel),
	PHP_DATACHANNEL_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_DATACHANNEL
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(datachannel)
#endif
