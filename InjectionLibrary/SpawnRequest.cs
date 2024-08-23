using System;
using System.IO.Pipes;
using System.IO;

namespace InjectionLibrary
{
    public class SpawnRequest
    {
        public static void SendSpawnRequest(int itemID, int spawnAmount)
        {
            try
            {
                using (NamedPipeClientStream pipeClient = new NamedPipeClientStream(".", "SpawnPipe", PipeDirection.Out))
                {                  
                    pipeClient.Connect(2000);

                    using (StreamWriter sw = new StreamWriter(pipeClient))
                    {
                        sw.WriteLine($"{itemID} {spawnAmount}");
                        sw.Flush();
                    }
                }
            }
            catch (TimeoutException ex)
            {
                Console.WriteLine("Timeout beim Verbindungsaufbau zum Pipe-Server: " + ex.Message);
            }
            catch (IOException ex)
            {
                Console.WriteLine("Ein IO-Fehler ist aufgetreten: " + ex.Message);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Ein unerwarteter Fehler ist aufgetreten: " + ex.Message);
            }
        }
    }
}
