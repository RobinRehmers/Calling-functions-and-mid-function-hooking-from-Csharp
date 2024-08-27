using System;
using System.IO.Pipes;
using System.IO;
using System.Windows;

namespace InjectionLibrary
{
    public class SpawnRequest
    {
        public static NamedPipeClientStream pipeClient;
        private static StreamWriter sw;

        public static void SendSpawnRequest(int itemID, int spawnAmount)
        {
            try
            {
                if (pipeClient.IsConnected)
                {
                    sw.WriteLine($"{itemID} {spawnAmount}");
                    sw.Flush();
                }
                else
                {
                    MessageBox.Show("Pipe is not connected.");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error communicating with pipe: {ex.Message}");
            }
        }

        public static void InitializePipeClient()
        {
            pipeClient = new NamedPipeClientStream(".", "SkyrimPipe", PipeDirection.Out);
            try
            {
                pipeClient.Connect();
                sw = new StreamWriter(pipeClient);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to connect to pipe: {ex.Message}");
            }
        }
    }
}
