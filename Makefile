CC=gcc
CFLAGS=-Wall -Wextra -I./lib/include
LDFLAGS=-lm

neuron.o: lib/src/neuron.c lib/include/neuron.h 
	$(CC) $(CFLAGS) -c lib/src/neuron.c -o build/neuron.o

network.o: lib/src/network.c lib/include/neuron.h
	$(CC) $(CFLAGS) -c lib/src/network.c -o build/network.o

build: neuron.o network.o
	$(CC) $(CFLAGS) lib/src/main.c build/neuron.o build/network.o -o build/main.o $(LDFLAGS)

clean:
	rm -r ./build/*

run: build
	build/main.o
	