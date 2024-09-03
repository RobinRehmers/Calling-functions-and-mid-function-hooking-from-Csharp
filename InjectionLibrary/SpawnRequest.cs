using System;
using System.IO.Pipes;
using System.IO;
using System.Windows;

namespace InjectionLibrary
{
    public class SpawnRequest
    {
        private static SpawnRequest _instance;
        private static readonly object _lock = new object();
        public NamedPipeClientStream PipeClient { get; private set; }
        private StreamWriter _sw;

        private SpawnRequest()
        {
            InitializePipeClient();
        }

        public static SpawnRequest Instance
        {
            get
            {
                if (_instance == null)
                {
                    lock (_lock)
                    {
                        if (_instance == null)
                        {
                            _instance = new SpawnRequest();
                        }
                    }
                }
                return _instance;
            }
        }

        private void InitializePipeClient()
        {
            PipeClient = new NamedPipeClientStream(".", "SkyrimPipe", PipeDirection.Out);
            try
            {
                PipeClient.Connect();
                _sw = new StreamWriter(PipeClient);
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to connect to pipe: {ex.Message}");
            }
        }

        public void SendSpawnRequest(int itemID, int spawnAmount)
        {
            try
            {
                if (PipeClient.IsConnected)
                {
                    _sw.WriteLine($"{itemID} {spawnAmount}");
                    _sw.Flush();
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
    }
}
