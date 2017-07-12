CC=g++
AR=ar
INCLUDE_DIR=include
CPPFLAGS=-I$(INCLUDE_DIR) -std=gnu++11 -Wpedantic -Wall -Wextra -Werror -O2
LDFLAGS=-L.
ARFLAGS=-cr
SRC=$(wildcard src/*.cpp)
BIN_DIR=bin
STATIC_TARGET=$(BIN_DIR)/libtextpurifier.a
STATIC_DIR=build_static
STATIC_OBJ=$(SRC:src/%.cpp=$(STATIC_DIR)/%.o)
STATIC_DEPS=$(STATIC_OBJ:%.o=%.d)
SHARED_TARGET=$(BIN_DIR)/libtextpurifier.so
SHARED_DIR=build_shared
SHARED_OBJ=$(SRC:src/%.cpp=$(SHARED_DIR)/%.o)
SHARED_DEPS=$(SHARED_OBJ:%.o=%.d)

.PHONY: all static shared doc clean

all: static shared

static: $(STATIC_TARGET)

shared: $(SHARED_TARGET)

$(STATIC_TARGET): $(STATIC_OBJ) | $(BIN_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(SHARED_TARGET): CPPFLAGS+=-fPIC
$(SHARED_TARGET): LDFLAGS+=-shared
$(SHARED_TARGET): $(SHARED_OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

-include $(STATIC_DEPS)
$(STATIC_DIR)/%.o: src/%.cpp | $(STATIC_DIR)
	$(CC) $(CPPFLAGS) -MMD -o $@ -c $<

-include $(SHARED_DEPS)
$(SHARED_DIR)/%.o: src/%.cpp | $(SHARED_DIR)
	$(CC) $(CPPFLAGS) -MMD -o $@ -c $<

$(STATIC_DIR) $(SHARED_DIR):
	@mkdir $@

$(BIN_DIR):
	@mkdir $@

doc:
	@echo "Generating document ..."
	@doxygen 1>/dev/null

clean:
	@rm -rf $(STATIC_DIR) $(SHARED_DIR) $(BIN_DIR)
