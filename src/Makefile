# src/Makefile: builds static and dynamic libraries, and a client for each

CC        = gcc
CFLAGS    = -Wall -Wextra -g -I../include
PICFLAGS  = -fPIC
AR        = ar
ARFLAGS   = rcs
RANLIB    = ranlib

OBJ_DIR   = ../obj
BIN_DIR   = ../bin
LIB_DIR   = ../lib
INC_DIR   = ../include

LIB_NAME       = myutils
STATIC_LIB     = $(LIB_DIR)/lib$(LIB_NAME).a
DYNAMIC_LIB    = $(LIB_DIR)/lib$(LIB_NAME).so
STATIC_TARGET  = $(BIN_DIR)/client_static
DYNAMIC_TARGET = $(BIN_DIR)/client_dynamic

LIB_SRCS = mystrfunctions.c myfilefunctions.c
LIB_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))
MAIN_OBJ = $(OBJ_DIR)/main.o
HEADERS  = $(wildcard $(INC_DIR)/*.h)

.PHONY: all static dynamic clean

all: static dynamic

static: $(STATIC_TARGET)

dynamic: $(DYNAMIC_TARGET)

# Library objects are compiled as position-independent code
$(LIB_OBJS): CFLAGS += $(PICFLAGS)

# Static library: archive of object files
$(STATIC_LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

# Dynamic library: shared object
$(DYNAMIC_LIB): $(LIB_OBJS)
	$(CC) -shared $^ -o $@

# Static client: -l:libmyutils.a forces the .a even when the .so exists
$(STATIC_TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l:lib$(LIB_NAME).a -o $@

# Dynamic client: -lmyutils picks libmyutils.so
$(DYNAMIC_TARGET): $(MAIN_OBJ) $(DYNAMIC_LIB)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $@

# Pattern rule: any .c to .o
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(STATIC_LIB) $(DYNAMIC_LIB) $(STATIC_TARGET) $(DYNAMIC_TARGET)
