AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src

include_HEADERS = include/text_purifier.h

.PHONY: cppcheck
cppcheck:
	cppcheck -I include -i test --quiet --force --std=c++11 --enable=all --error-exitcode=1 --suppress=missingIncludeSystem $(top_srcdir)
