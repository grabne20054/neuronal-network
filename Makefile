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

build_train: neuron.o network.o layer.o preprocessing.o
	$(CC) $(CFLAGS) lib/src/train.c build/neuron.o build/network.o build/layer.o build/preprocessing.o -o build/nn-train $(LDFLAGS)


build_predict: neuron.o network.o layer.o preprocessing.o
	$(CC) $(CFLAGS) lib/src/predict.c build/neuron.o build/network.o build/layer.o build/preprocessing.o -o build/nn-predict $(LDFLAGS)

build: build_train build_predict

clean:
	rm -r ./build/*
	rm -r ./networks/*

train: build_train build/nn-train
	build/nn-train $(hlayers) $(e) $(lr) $(train) $(f)

predict: build_predict build/nn-predict
	build/nn-predict $(f)
	