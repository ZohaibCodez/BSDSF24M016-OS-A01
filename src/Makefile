# src/Makefile: builds libmyutils.a and links bin/client_static against it

CC       = gcc
CFLAGS   = -Wall -Wextra -g -I../include
AR       = ar
ARFLAGS  = rcs
RANLIB   = ranlib

OBJ_DIR  = ../obj
BIN_DIR  = ../bin
LIB_DIR  = ../lib
INC_DIR  = ../include

LIB_NAME   = myutils
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
TARGET     = $(BIN_DIR)/client_static

LIB_SRCS = mystrfunctions.c myfilefunctions.c
LIB_OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRCS))
MAIN_OBJ = $(OBJ_DIR)/main.o
HEADERS  = $(wildcard $(INC_DIR)/*.h)

.PHONY: all clean

all: $(TARGET)

# Step 1: bundle library object files into a static archive
$(STATIC_LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
	$(RANLIB) $@

# Step 2: link main.o against the static library
$(TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $@

# Pattern rule: any .c to .o
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(STATIC_LIB) $(TARGET)
