CC = g++
CFLAGS = -std=c++11 -Wall

.PHONY: all clean

all: data_gen_a.exe data_gen_b.exe data_display.exe

data_gen_a.exe: data_gen_a.cpp shared_data.h
	$(CC) $(CFLAGS) -o $@ $<

data_gen_b.exe: data_gen_b.cpp shared_data.h
	$(CC) $(CFLAGS) -o $@ $<

data_display.exe: data_display.cpp shared_data.h
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f data_gen_a.exe data_gen_b.exe data_display.exe
