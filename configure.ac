#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([textpurifier], [0.8.7], [aludirk@lakoo.com], [textpurifier], [https://github.com/lakoo/text_purifier])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])
LT_INIT
AC_ENABLE_SHARED
AC_ENABLE_STATIC

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

# Checks for libraries.
AC_CHECK_LIB([cppunit], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([memset setlocale])

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT
