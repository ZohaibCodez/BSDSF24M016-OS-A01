# Top-level Makefile: delegates builds to src/Makefile, handles install

SRC_DIR  = src
LIB_DIR  = $(CURDIR)/lib
MAN_SRC  = man

PREFIX   = /usr/local
BINDIR   = $(PREFIX)/bin
MANDIR   = $(PREFIX)/share/man

INSTALL  = install
PROGRAM  = client

.PHONY: all static dynamic clean run run-dynamic install uninstall

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

install: static
	$(INSTALL) -d $(BINDIR) $(MANDIR)/man1 $(MANDIR)/man3
	$(INSTALL) -m 755 bin/client_static $(BINDIR)/$(PROGRAM)
	$(INSTALL) -m 644 $(MAN_SRC)/man1/*.1 $(MANDIR)/man1
	$(INSTALL) -m 644 $(MAN_SRC)/man3/*.3 $(MANDIR)/man3
	-mandb -q
	@echo "Installed $(PROGRAM) to $(BINDIR) and man pages to $(MANDIR)"

uninstall:
	rm -f $(BINDIR)/$(PROGRAM)
	rm -f $(addprefix $(MANDIR)/man1/,$(notdir $(wildcard $(MAN_SRC)/man1/*.1)))
	rm -f $(addprefix $(MANDIR)/man3/,$(notdir $(wildcard $(MAN_SRC)/man3/*.3)))
	-mandb -q
	@echo "Uninstalled $(PROGRAM) and its man pages"
