dnl $Id$
dnl config.m4 for extension mycrypt

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(mycrypt, for mycrypt support,
dnl Make sure that the comment is aligned:
dnl [  --with-mycrypt             Include mycrypt support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(mycrypt, whether to enable mycrypt support,
Make sure that the comment is aligned:
[  --enable-mycrypt           Enable mycrypt support])

if test "$PHP_MYCRYPT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mycrypt -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mycrypt.h"  # you most likely want to change this
  dnl if test -r $PHP_MYCRYPT/$SEARCH_FOR; then # path given as parameter
  dnl   MYCRYPT_DIR=$PHP_MYCRYPT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mycrypt files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MYCRYPT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MYCRYPT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mycrypt distribution])
  dnl fi

  dnl # --with-mycrypt -> add include path
  dnl PHP_ADD_INCLUDE($MYCRYPT_DIR/include)

  dnl # --with-mycrypt -> check for lib and symbol presence
  dnl LIBNAME=mycrypt # you may want to change this
  dnl LIBSYMBOL=mycrypt # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MYCRYPT_DIR/lib, MYCRYPT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MYCRYPTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mycrypt lib version or lib not found])
  dnl ],[
  dnl   -L$MYCRYPT_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MYCRYPT_SHARED_LIBADD)
  PHP_REQUIRE_CXX()
  PHP_ADD_LIBRARY(stdc++, "", EXTRA_LDFLAGS)
  CPPFILE="mycrypt.cpp ef_aes.cpp ef_base64.cpp ef_md5.cpp ef_hex.cpp rijndael-alg-fst.cpp rijndael-api-fst.cpp"
  PHP_NEW_EXTENSION(mycrypt, $CPPFILE, $ext_shared)
fi
