# Top-level Makefile: delegates the real work to src/Makefile

SRC_DIR = src
LIB_DIR = $(CURDIR)/lib

.PHONY: all static dynamic clean run run-dynamic

all:
	$(MAKE) -C $(SRC_DIR)

static:
	$(MAKE) -C $(SRC_DIR) static

dynamic:
	$(MAKE) -C $(SRC_DIR) dynamic

clean:
	$(MAKE) -C $(SRC_DIR) clean

run: static
	./bin/client_static

run-dynamic: dynamic
	LD_LIBRARY_PATH=$(LIB_DIR) ./bin/client_dynamic
