CC = gcc
LIB_DIR = ../../lib_tlpi
BIN_DIR = ../../bin
CFLAGS = -Wall -g -I$(LIB_DIR)
LDFLAGS = -L$(LIB_DIR) -ltlpi
TARGET = $(BIN_DIR)/mycopy

all:
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) copy.c -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
