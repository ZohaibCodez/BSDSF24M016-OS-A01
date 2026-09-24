# src/Makefile: compiles sources into objects and links bin/client

CC      = gcc
CFLAGS  = -Wall -Wextra -g -I../include

OBJ_DIR = ../obj
BIN_DIR = ../bin
INC_DIR = ../include

TARGET  = $(BIN_DIR)/client
SRCS    = main.c mystrfunctions.c myfilefunctions.c
OBJECTS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
HEADERS = $(wildcard $(INC_DIR)/*.h)

.PHONY: all clean

all: $(TARGET)

# Linking rule: build the executable from all object files
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Pattern rule: how to turn any .c into a .o
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
