#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(zcmdsh, 0.0.1, yasu1976@gmail.com)
AC_CONFIG_SRCDIR([apps/zcmdsh.c])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER([config.h])

dnl ------------
dnl Check CFLAGS
dnl ------------
AC_ARG_WITH(cflags,
[  --with-cflags              Set CFLAGS.])

dnl -----------------------------------------
dnl If linkbase specified expand it
dnl -----------------------------------------
if test "x${with_linkbase}" != "x" ; then
  CFLAGS="${with_linkbase}";
else
  CFLAGS="$CFLAGS -O0 -g -Wall";
fi

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for libraries.
AC_CHECK_LIB(m, main)

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([fcntl.h netdb.h netinet/in.h stdlib.h string.h sys/param.h sys/socket.h sys/time.h syslog.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
#AC_FUNC_MALLOC
AC_FUNC_MEMCMP
#AC_FUNC_REALLOC
AC_FUNC_STRFTIME
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([gettimeofday memmove memset strdup strerror strstr])
AC_CONFIG_FILES([Makefile lib/Makefile app/Makefile])
AC_OUTPUT

echo "
srsc configuration
-------------------
version                 : ${VERSION}
compiler                : ${CC}
compiler flags          : ${CFLAGS}
linker flags            : ${LDFLAGS}
link libraries          : ${LIBS}
"


