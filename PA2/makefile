CC = g++
CFLAGS = -c

all: bin/mps
	@echo -n ""

bin/mps: main_opt.o max_planar_subset.o
	$(CC) main_opt.o max_planar_subset.o -o bin/mps

main_opt.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o main_opt.o

max_planar_subset.o: src/max_planar_subset.cpp src/max_planar_subset.h
	$(CC) $(CFLAGS) src/max_planar_subset.cpp -o max_planar_subset.o

clean:
	rm -rf *.o bin/*
