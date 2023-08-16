/*  This program is a data generator that is a sort of proof of concept for how a process that interacts with sensors would run
*   It first handles the intial allocation of the named memory mapped file (The shared memory) 
*   It then links to the memory mapped file and casts it as a struct as defined in shared_data.h
*   Finally it starts writing random values to the value1 variable in the shared memory once every second
*/

#include <Windows.h>
#include <iostream>
#include "shared_data.h" // Critical inclusion to give access to the shared data struct that is used as a "template" for the shared memory

int main() {
    
    /*  Allocate the Memory Mapped File

    *   Here we make the named memory mapped file that we will interface with
    *   This needs to happen before any process can connect to it, so this program needs to launch first
    *       
    *   NOTE: The SharedData struct is the thing that defines the structure of our shared memory and is defined in shared_data.h
    */
    HANDLE hFileMapping = CreateFileMappingW( INVALID_HANDLE_VALUE, 
                                              nullptr, 
                                              PAGE_READWRITE, 
                                              0, 
                                              sizeof(SharedData), // Set the size of the memory mapped file so it can hold our data
                                              L"MySharedMemory"); 


    // Mount the memory mapped file as a pointer to a SharedData type struct. In this file we mount it via the HANDLE created above named hFileMapping
    SharedData* pData = static_cast<SharedData*>(MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, sizeof(SharedData)));

    // Run an infinite loop where we generate a random value and load it into the value1 slot in the shared struct every second
    while (true) {
        pData->value1 = rand() % 100; // Update with new value
        std::cout << "Value1: " << pData->value1 << std::endl; // Print the value generated here to the terminal
        Sleep(1000); // Wait for a second
    }

    // This never runs, but if we break from the loop, we would do some clean up before leaving
    UnmapViewOfFile(pData);
    CloseHandle(hFileMapping);

    return 0;
}
