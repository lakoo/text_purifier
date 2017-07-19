CC=g++
AR=ar
CHECK=cppcheck
INSTALL=install
INCLUDE_DIR=include
CPPFLAGS=-I$(INCLUDE_DIR) -std=gnu++11 -Wpedantic -Wall -Wextra -Werror -O2
LDFLAGS=
ARFLAGS=-rcs
CHECKFLAGS=-I $(INCLUDE_DIR) -i test --quiet --force --std=c++11 --enable=all --error-exitcode=1 --suppress=missingIncludeSystem
INCLUDE=$(wildcard $(INCLUDE_DIR)/*.h)
SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.cpp)
BIN_DIR=bin
STATIC_TARGET=$(BIN_DIR)/libtextpurifier.a
STATIC_DIR=build_static
STATIC_OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(STATIC_DIR)/%.o)
STATIC_DEPS=$(STATIC_OBJ:%.o=%.d)
SHARED_TARGET=$(BIN_DIR)/libtextpurifier.so
SHARED_DIR=build_shared
SHARED_OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(SHARED_DIR)/%.o)
SHARED_DEPS=$(SHARED_OBJ:%.o=%.d)
PREFIX?=/usr/local

.PHONY: all static shared install uninstall doc clean

all: static shared

static: $(STATIC_TARGET)

shared: $(SHARED_TARGET)

$(STATIC_TARGET): $(STATIC_OBJ) | $(BIN_DIR)
	$(CHECK) $(CHECKFLAGS) .
	$(AR) $(ARFLAGS) $@ $^

$(SHARED_TARGET): CPPFLAGS+=-fPIC
$(SHARED_TARGET): LDFLAGS+=-shared
$(SHARED_TARGET): $(SHARED_OBJ) | $(BIN_DIR)
	$(CHECK) $(CHECKFLAGS) .
	$(CC) -o $@ $(LDFLAGS) $^

-include $(STATIC_DEPS)
$(STATIC_DIR)/%.o: $(SRC_DIR)/%.cpp | $(STATIC_DIR)
	$(CC) $(CPPFLAGS) -MMD -o $@ -c $<

-include $(SHARED_DEPS)
$(SHARED_DIR)/%.o: $(SRC_DIR)/%.cpp | $(SHARED_DIR)
	$(CC) $(CPPFLAGS) -MMD -o $@ -c $<

$(STATIC_DIR) $(SHARED_DIR) $(BIN_DIR):
	@mkdir $@

install:
	@if [ -f "$(STATIC_TARGET)" ]; then \
		echo "Installing $(STATIC_TARGET) ..."; \
		$(INSTALL) $(STATIC_TARGET) $(PREFIX)/lib; \
	fi
	@if [ -f "$(SHARED_TARGET)" ]; then \
		echo "Installing $(SHARED_TARGET) ..."; \
		$(INSTALL) $(SHARED_TARGET) $(PREFIX)/lib; \
	fi
	@if [ -f "$(STATIC_TARGET)" ] || [ -f "$(SHARED_TARGET)" ]; then \
		echo "Installing headers ..."; \
		$(INSTALL) $(INCLUDE) $(PREFIX)/include; \
	fi

uninstall:
	@echo "Uninstalling ..."
	@rm -f $(STATIC_TARGET:$(BIN_DIR)/%=$(PREFIX)/lib/%)
	@rm -f $(SHARED_TARGET:$(BIN_DIR)/%=$(PREFIX)/lib/%)
	@rm -f $(INCLUDE:$(INCLUDE_DIR)/%.h=$(PREFIX)/include/%.h)

doc:
	@echo "Generating document ..."
	@doxygen 1>/dev/null

clean:
	@rm -rf $(STATIC_DIR) $(SHARED_DIR) $(BIN_DIR)
