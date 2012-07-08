#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([fizz], [0.1], [self@svartalf.info])
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([generator.h])
AM_CONFIG_HEADER([config.h])

# Checks for programs.
CCFLAGS="-std=c99 -pedantic"
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([ev], [ev_run], [], [
	echo "libev is missing. Install libev library"
	exit -1
])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h sys/socket.h arpa/inet.h])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([socket])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
