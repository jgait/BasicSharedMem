# BasicSharedMem
A three-process Windows shared memory example

`data_gen_a.cpp` and `data_gen_b.cpp` create random data and load it into shared memory
A third process, `data_display.cpp`, then reads the data and prints it to the terminal

## Use
1. Compile with g++
2. Run the executables in three separate terminals (`data_gen_a.cpp` must be started first)
