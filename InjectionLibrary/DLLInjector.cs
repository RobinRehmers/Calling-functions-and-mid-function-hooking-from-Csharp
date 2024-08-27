using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace InjectionLibrary
{
    public static class DllInjector
    {
        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr OpenProcess(uint processAccess, bool bInheritHandle, int processId);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out IntPtr lpNumberOfBytesWritten);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, out IntPtr lpThreadId);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern uint WaitForSingleObject(IntPtr hHandle, uint dwMilliseconds);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);

        private const uint PROCESS_CREATE_THREAD = 0x0002;
        private const uint PROCESS_QUERY_INFORMATION = 0x0400;
        private const uint PROCESS_VM_OPERATION = 0x0008;
        private const uint PROCESS_VM_WRITE = 0x0020;
        private const uint PROCESS_VM_READ = 0x0010;
        private const uint MEM_COMMIT = 0x1000;
        private const uint MEM_RESERVE = 0x2000;
        private const uint PAGE_READWRITE = 0x04;
        private const uint INFINITE = 0xFFFFFFFF;

        public static void InjectDll(string dllPath, string processName)
        {
            Process process = null;
            while (process == null)
            {
                process = Process.GetProcessesByName(processName).FirstOrDefault();
                if (process == null)
                {
                    MessageBox.Show("Cant find the games process. Please start 'The Elder Scrolls V: Skyrim' and hit 'OK'.");
                    Thread.Sleep(2000);
                }
            }
            int processId = process.Id;

            IntPtr hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, false, processId);

            if (hProcess == IntPtr.Zero)
            {
                MessageBox.Show("Failed to open target process.");
                return;
            }

            IntPtr allocAddress = VirtualAllocEx(hProcess, IntPtr.Zero, (uint)((dllPath.Length + 1) * Marshal.SizeOf(typeof(char))), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            if (allocAddress == IntPtr.Zero)
            {
                MessageBox.Show("Failed to allocate memory in target process.");
                CloseHandle(hProcess);
                return;
            }

            byte[] bytes = Encoding.Unicode.GetBytes(dllPath);
            if (!WriteProcessMemory(hProcess, allocAddress, bytes, (uint)bytes.Length, out _))
            {
                MessageBox.Show("Failed to write DLL path to target process memory.");
                CloseHandle(hProcess);
                return;
            }

            IntPtr loadLibraryAddress = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryW");
            if (loadLibraryAddress == IntPtr.Zero)
            {
                MessageBox.Show("Failed to get LoadLibraryW address.");
                CloseHandle(hProcess);
                return;
            }

            IntPtr hThread = CreateRemoteThread(hProcess, IntPtr.Zero, 0, loadLibraryAddress, allocAddress, 0, out _);
            if (hThread == IntPtr.Zero)
            {
                MessageBox.Show("Failed to create remote thread in target process.");
                CloseHandle(hProcess);
                return;
            }

            WaitForSingleObject(hThread, INFINITE);

            CloseHandle(hThread);
            CloseHandle(hProcess);

            MessageBox.Show("DLL successfully injected.");
        }
    }
}
