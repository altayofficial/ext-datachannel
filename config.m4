PHP_ARG_WITH([datachannel],
  [for datachannel support],
  [AS_HELP_STRING([--with-datachannel=DIR],
    [Include datachannel support. DIR is the prefix libdatachannel, libjuice and libusrsctp were installed to])],
  [no])

if test "$PHP_DATACHANNEL" != "no"; then
  PHP_REQUIRE_CXX()

  if test "$PHP_DATACHANNEL" = "yes" || test ! -f "$PHP_DATACHANNEL/include/rtc/rtc.hpp"; then
    AC_MSG_ERROR([--with-datachannel needs the prefix libdatachannel was installed to])
  fi

  DATACHANNEL_LIBDIR=""
  for dir in lib64 lib; do
    if test -f "$PHP_DATACHANNEL/$dir/libdatachannel.a"; then
      DATACHANNEL_LIBDIR="$PHP_DATACHANNEL/$dir"
      break
    fi
  done
  if test -z "$DATACHANNEL_LIBDIR"; then
    AC_MSG_ERROR([static libdatachannel not found in $PHP_DATACHANNEL])
  fi

  PHP_ADD_INCLUDE([$PHP_DATACHANNEL/include])
  dnl these prepend, so they go in reverse: libdatachannel needs juice and usrsctp, which need openssl.
  dnl only the static archives are installed there, so the linker can't pick anything else
  PHP_SETUP_OPENSSL([DATACHANNEL_SHARED_LIBADD], [], [AC_MSG_ERROR([OpenSSL not found])])
  PHP_ADD_LIBRARY([pthread], 1, DATACHANNEL_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH([usrsctp], [$DATACHANNEL_LIBDIR], DATACHANNEL_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH([juice], [$DATACHANNEL_LIBDIR], DATACHANNEL_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH([datachannel], [$DATACHANNEL_LIBDIR], DATACHANNEL_SHARED_LIBADD)
  PHP_SUBST([DATACHANNEL_SHARED_LIBADD])

  AC_DEFINE([RTC_STATIC], [1], [libdatachannel is linked statically])

  dnl the 6th parameter here is required for C++ shared extensions
  PHP_NEW_EXTENSION(datachannel, datachannel.cpp classes/Context.cpp classes/PeerConnection.cpp classes/DataChannel.cpp, $ext_shared,,-std=c++20 -Wall -Werror -DRTC_STATIC=1, yes)
  PHP_ADD_BUILD_DIR($ext_builddir/classes, 1)
fi
