CC = gcc
CFLAGS = -pthread -Wall
TARGETS = server client

all: $(TARGETS)

server: ProgramaServer.c ProgStreamer.o ProgEncoder.o
	$(CC) $(CFLAGS) ProgramaServer.c ProgStreamer.o ProgEncoder.o -o servidor

client: ProgramaCliente.c
	$(CC) $(CFLAGS) ProgramaCliente.c -o cliente

ProgStreamer.o: ProgStreamer.c ProgStreamer.h
	$(CC) $(CFLAGS) -c ProgStreamer.c -o ProgStreamer.o

ProgEncoder.o: ProgEncoder.c ProgEncoder.h
	$(CC) $(CFLAGS) -c ProgEncoder.c -o ProgEncoder.o

clean:
	rm -f $(TARGETS) *.o
