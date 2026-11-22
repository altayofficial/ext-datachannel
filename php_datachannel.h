/* datachannel extension for PHP */

#ifndef PHP_DATACHANNEL_H
# define PHP_DATACHANNEL_H

extern zend_module_entry datachannel_module_entry;
# define phpext_datachannel_ptr &datachannel_module_entry

# define PHP_DATACHANNEL_VERSION "0.1.1"

# if defined(ZTS) && defined(COMPILE_DL_DATACHANNEL)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_DATACHANNEL_H */
