/*  This program is the data reader/display and is as a proof of concept for how a logger or GUI might work
*   First it mounts the memory mapped file by name and casts it to a shared data struct
*   Then, in a loop, it reads and prints the values in value1 and value2 as they are updated by data_gen_a.cpp and data_gen_b.cpp 
*/

#include <Windows.h>
#include <iostream>
#include "shared_data.h"

int main() {
    // Mount the memory mapped file by name with read permissions
    HANDLE hFileMapping = OpenFileMappingW(FILE_MAP_READ, FALSE, L"MySharedMemory");

    // link the memory mapped file to a local struct
    SharedData* pData = static_cast<SharedData*>(MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, sizeof(SharedData)));

    // Read the values and print them out every 3 seconds, one could also save to a file or push to a GUI
    while (true) {
        // Read and display data
        std::cout << "Value 1: " << pData->value1 << std::endl;
        std::cout << "Value 2: " << pData->value2 << std::endl;
        // Read and display other data as needed

        Sleep(10);
    }

    // Do cleanup
    UnmapViewOfFile(pData);
    CloseHandle(hFileMapping);

    return 0;
}
