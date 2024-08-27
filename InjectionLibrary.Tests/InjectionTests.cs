using System.IO.Pipes;
using Xunit;
using InjectionLibrary;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using System.Security.AccessControl;
using System.Security.Principal;

namespace InjectionLibrary.Tests
{
    public class InjectionTests
    {
        private const string ProcessName = "SkyrimSE";
        private const string DllName = "DLL_to_inject.dll";
        private const string PipeName = "SkyrimPipe";
        private static bool isDllInjected = false;

        public InjectionTests()
        {
            if (!isDllInjected)
            {
                string outputDirectory = AppDomain.CurrentDomain.BaseDirectory;
                string dllPath = Path.Combine(outputDirectory, DllName);

                if (!File.Exists(dllPath))
                {
                    throw new FileNotFoundException($"DLL not found at path: {dllPath}");
                }

                Environment.SetEnvironmentVariable("IS_TEST_EXECUTION", "true");

                DllInjector.InjectDll(dllPath, ProcessName);
                isDllInjected = true;
            }
        }

        [Fact]
        public void TestDllInjection()
        {
            bool isDllInjected = IsDllInjected(ProcessName, DllName);
            Assert.True(isDllInjected);
        }

        private bool IsDllInjected(string processName, string dllName)
        {
            var process = Process.GetProcessesByName(processName).FirstOrDefault();
            if (process == null)
                return false;

            foreach (ProcessModule module in process.Modules)
            {
                if (module.ModuleName.Equals(dllName, StringComparison.OrdinalIgnoreCase))
                {
                    return true;
                }
            }
            return false;
        }

        [Fact]
        public void TestPipeConnection()
        {
            SpawnRequest.InitializePipeClient();

            Assert.NotNull(SpawnRequest.pipeClient);
            Assert.True(SpawnRequest.pipeClient.IsConnected);
        }
    }
}
