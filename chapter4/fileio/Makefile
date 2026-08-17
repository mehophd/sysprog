CC = gcc
LIB_DIR = ../../lib_tlpi
BIN_DIR = ../../bin
CFLAGS = -Wall -g -I$(LIB_DIR)
LDFLAGS = -L$(LIB_DIR) -ltlpi

all:
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) seek_io.c -o $(BIN_DIR)/seek_io $(LDFLAGS)
	$(CC) $(CFLAGS) copy.c -o $(BIN_DIR)/copy $(LDFLAGS)

clean:
	rm -f $(BIN_DIR)/seek_io
	rm -f $(BIN_DIR)/copy
