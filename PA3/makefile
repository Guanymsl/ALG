CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv

all: bin/cb
	@echo -n ""

bin/cb: main_opt.o cycle_breaking.o lib/libtm_usage.a
	$(CC) main_opt.o cycle_breaking.o lib/libtm_usage.a -o bin/cb

main_opt.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp -o main_opt.o

cycle_breaking.o: src/cycle_breaking.cpp src/cycle_breaking.h
	$(CC) $(CFLAGS) src/cycle_breaking.cpp -o cycle_breaking.o

lib: lib/libtm_usage.a

lib/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<

tm_usage.o: lib/tm_usage.cpp lib/tm_usage.h
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o lib/*.a lib/*.o bin/*
