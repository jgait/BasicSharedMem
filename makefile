CC = g++
CFLAGS = -std=c++11 -Wall
CSC = /c/Windows/Microsoft.NET/Framework/v4.0.30319/csc.exe

.PHONY: all clean csc cleanCsc

all: data_gen_a.exe data_gen_b.exe data_display.exe

csc: recieve_force.exe send_force.exe

data_gen_a.exe: data_gen_a.cpp shared_data.h
	$(CC) $(CFLAGS) -o $@ $<

data_gen_b.exe: data_gen_b.cpp shared_data.h
	$(CC) $(CFLAGS) -o $@ $<

data_display.exe: data_display.cpp shared_data.h
	$(CC) $(CFLAGS) -o $@ $<

recieve_force.exe: recieve_force.cpp
	$(CC) $(CFLAGS) -o $@ $<

send_force.exe: send_force.cs
	$(CSC) $<

clean:
	rm -f data_gen_a.exe data_gen_b.exe data_display.exe

cleanCsc:
	rm -f recieve_force.exe send_force.exe
