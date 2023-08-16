/*  This program is another data generator that first connects to the memory mapped file using its name
*   It then connects to the memory mapped file and casts it as a pointer to the shared_data struct
*   Finally it generates random data and writes it to the value2 variable in the shared struct once every 2 seconds
*/

#include <Windows.h>
#include <iostream>
#include "shared_data.h"

int main() {
    
    // Acquire the memory mapped file for writing
    // NOTE: The name given to the memory mapped file in data_gen_a.cpp is used to link up the memory
    HANDLE hFileMapping = OpenFileMappingW(FILE_MAP_WRITE, FALSE, L"MySharedMemory");

    // Attach the memory mapped file to an instance of the SharedData struct in this script
    SharedData* pData = static_cast<SharedData*>(MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, sizeof(SharedData)));

    // Generate random values, and put them in the value2 variable in the shared struct every 2 seconds
    while (true) {
        pData->value2 = rand(); // Update with new value
        std::cout << "Value2: " << pData->value2 << std::endl; // Print the value generated here to the terminal
        Sleep(2000);
    }

    // Again, this never runs, however it would do cleanup if it did run
    UnmapViewOfFile(pData);
    CloseHandle(hFileMapping);

    return 0;
}
