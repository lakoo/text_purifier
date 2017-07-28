AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src test

if ENABLE_DOXYGEN
SUBDIRS += docs
endif

include_HEADERS = include/text_purifier.h

################################################################################

clean-local:
	rm -rf html/
	rm -f *.gcov
