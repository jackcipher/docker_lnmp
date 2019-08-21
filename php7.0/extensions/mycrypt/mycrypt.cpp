/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */
extern "C" {
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
}
#include "php_mycrypt.h"
#include "ef_aes.h"
#include "ef_base64.h"
#include "time.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;
/* If you declare any globals in php_mycrypt.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(mycrypt)
*/

/* True global resources - no need for thread safety here */
static int le_mycrypt;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("mycrypt.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_mycrypt_globals, mycrypt_globals)
    STD_PHP_INI_ENTRY("mycrypt.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_mycrypt_globals, mycrypt_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_mycrypt_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_mycrypt_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "mycrypt", arg);
	RETURN_STRINGL(strg, len);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

static int split(const std::string& str, std::vector<std::string>& ret_, 
		std::string sep)
{
	    if (str.empty())
	    {
		return 0;
	    }

	    std::string tmp;
	    std::string::size_type pos_begin = str.find_first_not_of(sep);
	    std::string::size_type comma_pos = 0;

	    while (pos_begin != std::string::npos)
	    {
		comma_pos = str.find(sep, pos_begin);
		if (comma_pos != std::string::npos)
		{
		    tmp = str.substr(pos_begin, comma_pos - pos_begin);
		    pos_begin = comma_pos + sep.length();
		}
		else
		{
		    tmp = str.substr(pos_begin);
		    pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
		    ret_.push_back(tmp);
		    tmp.clear();
		}
	    }
	    return 0;

}

PHP_FUNCTION(mydec)
{
    char *strarg = NULL;
    int strarg_len;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &strarg, &strarg_len) == FAILURE) {
        RETURN_LONG(-1);
    }
   
    string decstr = base64_decode(strarg);
    vector<string> vstr;
    split(decstr, vstr, "&");
    if (vstr.size() < 3) {
		RETURN_LONG(-1);
	}
    if (abs(time(NULL) - atoi(vstr[0].data())) > 10) {
        RETURN_LONG(-2);
    }
    string rawbody;
    if (aes_decrypt(base64_decode(vstr[2]), vstr[0], rawbody) < 0) {
        RETURN_LONG(-3);
    }
    RETURN_STRINGL(rawbody.data(), rawbody.size());
}

PHP_FUNCTION(myenc)
{
	zval *zv;
	
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &zv) == FAILURE) {
        RETURN_LONG(-1);
    }
   
    stringstream ss;
    time_t tm = time(NULL);
    ss << tm;
    srand(tm);
    string encbody;
    zend_string* val = zval_get_string(zv);
    if (aes_encrypt(val->val, val->len, ss.str(), encbody) < 0) {
        RETURN_LONG(-2);
    }
    ss << "&" << rand() << "&" << base64_encode(encbody);
    string finalstr = base64_encode(ss.str());
    RETURN_STRINGL(finalstr.data(), finalstr.size());
}
/* {{{ php_mycrypt_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_mycrypt_init_globals(zend_mycrypt_globals *mycrypt_globals)
{
	mycrypt_globals->global_value = 0;
	mycrypt_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(mycrypt)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(mycrypt)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(mycrypt)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(mycrypt)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(mycrypt)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "mycrypt support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ mycrypt_functions[]
 *
 * Every user visible function must have an entry in mycrypt_functions[].
 */
const zend_function_entry mycrypt_functions[] = {
	PHP_FE(confirm_mycrypt_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(myenc, NULL)
	PHP_FE(mydec, NULL)
	PHP_FE_END	/* Must be the last line in mycrypt_functions[] */
};
/* }}} */

/* {{{ mycrypt_module_entry
 */
zend_module_entry mycrypt_module_entry = {
	STANDARD_MODULE_HEADER,
	"mycrypt",
	mycrypt_functions,
	PHP_MINIT(mycrypt),
	PHP_MSHUTDOWN(mycrypt),
	PHP_RINIT(mycrypt),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(mycrypt),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(mycrypt),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1",
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_MYCRYPT
ZEND_GET_MODULE(mycrypt)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */