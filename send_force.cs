using System;
using System.IO.Pipes;
using System.Text;
using System.Threading;

class Program {
    static void Main() {
        try {
            // Define the named pipe name
            string pipeName = "MyNamedPipe";
            using (NamedPipeClientStream pipeClient = new NamedPipeClientStream(".", pipeName, PipeDirection.Out)) {
                // Connect to the server pipe
                pipeClient.Connect();

                while (true) {
                    // Generate random data
                    byte[] data = GenerateRandomData(20);

                    // Send data to the server
                    pipeClient.Write(data, 0, data.Length);

                    Console.WriteLine("Data sent to the server.");

                    // Sleep for a while before starting the next iteration
                    Thread.Sleep(1000); // Sleep for 1 second (adjust as needed)
                }

                // Close the pipe
                pipeClient.Close();
            }
        } catch (Exception ex) {
            Console.WriteLine("Exception: " + ex.Message);
        }

        Console.ReadLine();
    }

    static byte[] GenerateRandomData(int length) {
        Random rand = new Random();
        byte[] data = new byte[length];
        rand.NextBytes(data);
        return data;
    }
}
