lib_LTLIBRARIES = libtextpurifier.la

AM_CXXFLAGS = -I$(top_srcdir)/include -Wpedantic -Wall -Wextra -Werror

libtextpurifier_la_SOURCES = \
	char_node.cpp \
	filter_list.cpp \
	string_utils.cpp \
	text_purifier.cpp

################################################################################

check_LTLIBRARIES = libtextpurifier.gcov.la

libtextpurifier_gcov_la_CXXFLAGS = ${AM_CXXFLAGS} -ftest-coverage -fprofile-arcs
libtextpurifier_gcov_la_LDFLAGS = -ftest-coverage -fprofile-arcs

libtextpurifier_gcov_la_SOURCES = ${libtextpurifier_la_SOURCES}

################################################################################

clean-local:
	rm -f *.gcda *.gcno *.gcov
