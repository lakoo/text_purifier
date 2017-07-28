AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4
SUBDIRS = src test

if ENABLE_DOXYGEN
SUBDIRS += docs
endif

include_HEADERS = include/text_purifier.h

################################################################################

update_readme:
	@sed -i.bak -E 's/(Text Purifier \()[[:digit:]]+\.[[:digit:]]+\.[[:digit:]]/\1$(VERSION)/' README.md
	@rm README.md.bak

all-local: update_readme

################################################################################

clean-local:
	rm -rf html/
	rm -f *.gcov
