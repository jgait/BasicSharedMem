#include <iostream>
#include <windows.h>

int main() {
    // Define the named pipe name (using ANSI string)
    LPCSTR pipeName = "\\\\.\\pipe\\MyNamedPipe";

        // Create the named pipe
        HANDLE hPipe;
        hPipe = CreateNamedPipeA(
            pipeName, // Use CreateNamedPipeA for ANSI strings
            PIPE_ACCESS_INBOUND,  // Server is read-only
            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
            1,                    // Number of instances
            0,                    // Output buffer size
            0,                    // Input buffer size
            0,                    // Default timeout (0 means blocking)
            NULL
        );

        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Failed to create named pipe. Error code: " << GetLastError() << std::endl;
            return 1;
        }

        std::cout << "Waiting for a client to connect..." << std::endl;

        // Wait for a client to connect
        if (ConnectNamedPipe(hPipe, NULL)) {
            std::cout << "Client connected. Receiving data..." << std::endl;

            while (true) {           
                // Receive data from the client
                char data[20];
                DWORD bytesRead;
                if (ReadFile(hPipe, data, sizeof(data), &bytesRead, NULL)) {
                    std::cout << "Received " << bytesRead << " bytes of data." << std::endl;

                    // Process the received data here
                    for (int i = 0; i < int(bytesRead); ++i) {
                        std::cout << static_cast<int>(data[i]) << " ";
                        if ((i + 1) % 16 == 0) std::cout << std::endl;
                    }
                    std::cout << std::endl;

                } else {
                    std::cerr << "Failed to read data from the pipe. Error code: " << GetLastError() << std::endl;
                }
            }
            
            // Disconnect from the client
            DisconnectNamedPipe(hPipe);
        } else {
            std::cerr << "Failed to connect to the client. Error code: " << GetLastError() << std::endl;
        }

        // Close the pipe handle
        CloseHandle(hPipe);

    return 0;
}
