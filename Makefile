CC=gcc
CFLAGS=-Wall
LDFLAGS=-lz
SOURCES=aes.c tools.c sha1.c blsunpack.c
EXECUTABLE=blsunpack
all:
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $(EXECUTABLE)
clean:
	rm -rf $(EXECUTABLE)