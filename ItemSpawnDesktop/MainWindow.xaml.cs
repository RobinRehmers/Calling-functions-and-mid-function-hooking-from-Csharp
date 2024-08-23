using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using InjectionLibrary;
using System.IO;
using System;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace ItemSpawnDesktop
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("kernel32.dll")]
        private static extern bool AllocConsole();

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

        [DllImport("DLL_to_inject.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void SpawnItemToInventory(int itemID, int spawnAmount);

        [UnmanagedFunctionPointer(CallingConvention.FastCall)]
        private delegate void MyExportedFunctionDelegate(int itemID, int spawnAmount);

        private int selectedItemID;
        private bool isDllInjected = false;

        public MainWindow()
        {
            InitializeComponent();
            //AllocConsole();
            //string solutionDirectory = Directory.GetParent(Directory.GetParent(Directory.GetParent(Directory.GetParent(Directory.GetParent(AppDomain.CurrentDomain.BaseDirectory).FullName).FullName).FullName).FullName).FullName;
            //string dllPath = System.IO.Path.Combine(solutionDirectory, @"x64\Debug\DLL_to_inject.dll");
            //DllInjector.InjectDll(dllPath, "SkyrimSE");
            //isDllInjected = true;
        }

        private void btnSword_Click(object sender, RoutedEventArgs e)
        {
            selectedItemID = 0xBE202;
            ShowSpawnControls();
        }

        private void btnBow_Click(object sender, RoutedEventArgs e)
        {
            selectedItemID = 0xBF405;
            ShowSpawnControls();
        }

        private void ShowSpawnControls()
        {
            txtSpawnAmount.Visibility = Visibility.Visible;
            btnSpawnIt.Visibility = Visibility.Visible;
        }

        private void btnSpawnIt_Click(object sender, RoutedEventArgs e)
        {
            int spawnAmount;
            if (int.TryParse(txtSpawnAmount.Text, out spawnAmount))
            {
                if (!isDllInjected)
                {
                    string solutionDirectory = Directory.GetParent(Directory.GetParent(Directory.GetParent(Directory.GetParent(Directory.GetParent(AppDomain.CurrentDomain.BaseDirectory).FullName).FullName).FullName).FullName).FullName;
                    string dllPath = System.IO.Path.Combine(solutionDirectory, @"x64\Debug\DLL_to_inject.dll");

                    DllInjector.InjectDll(dllPath, "SkyrimSE");

                    isDllInjected = true;
                }

            }
            else
            {
                MessageBox.Show("Please enter a valid number for spawn amount.");
            }
            Console.ReadLine();
        }     
    }
}