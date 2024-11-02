CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv

all: bin/mps
	@echo -n ""

bin/mps: main_opt.o max_planar_subset.o lib/libtm_usage.a
	$(CC) main_opt.o max_planar_subset.o lib/libtm_usage.a -o bin/mps

main_opt.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o main_opt.o

max_planar_subset.o: src/max_planar_subset.cpp src/max_planar_subset.h
	$(CC) $(CFLAGS) src/max_planar_subset.cpp -o max_planar_subset.o

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<

tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o lib/*.a lib/*.o bin/*
