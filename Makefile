# Top-level Makefile: delegates the real work to src/Makefile

SRC_DIR = src

.PHONY: all clean run

all:
	$(MAKE) -C $(SRC_DIR)

clean:
	$(MAKE) -C $(SRC_DIR) clean

run: all
	./bin/client
