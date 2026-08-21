CC = gcc
LIB_DIR = ../../lib_tlpi
BIN_DIR = ../../bin
CFLAGS = -Wall -g -I$(LIB_DIR)
LDFLAGS = -L$(LIB_DIR) -ltlpi

all:
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) tee.c -o $(BIN_DIR)/tee $(LDFLAGS)
	$(CC) $(CFLAGS) copyhole.c -o $(BIN_DIR)/copyhole $(LDFLAGS)

clean:
	rm -f $(BIN_DIR)/tee
	rm -f $(BIN_DIR)/copyhole