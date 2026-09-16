CC=gcc
CFLAGS=-Wall -Wextra -I./lib/include
LDFLAGS=-lm

neuron.o: lib/src/neuron.c lib/include/neuron.h 
	$(CC) $(CFLAGS) -c lib/src/neuron.c -o build/neuron.o

network.o: lib/src/network.c lib/include/neuron.h
	$(CC) $(CFLAGS) -c lib/src/network.c -o build/network.o

layer.o: lib/src/layer.c lib/include/layer.h
	$(CC) $(CFLAGS) -c lib/src/layer.c -o build/layer.o

preprocessing.o: lib/src/preprocessing.c lib/include/preprocessing.h
	$(CC) $(CFLAGS) -c lib/src/preprocessing.c -o build/preprocessing.o

build: neuron.o network.o layer.o preprocessing.o
	$(CC) $(CFLAGS) lib/src/main.c build/neuron.o build/network.o build/layer.o build/preprocessing.o -o build/main.o $(LDFLAGS)

clean:
	rm -r ./build/*

run: build build/main.o
	build/main.o $(hlayers) $(e) $(lr) $(train) $(f)
	