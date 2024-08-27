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
    public partial class MainWindow : Window
    {
        private int selectedItemID;

        public MainWindow()
        {
            InitializeComponent();
            if (Environment.GetEnvironmentVariable("IS_TEST_EXECUTION") != "true")
            {
                string solutionDirectory = GetSolutionDirectory();
                string dllPath = System.IO.Path.Combine(solutionDirectory, @"x64\Debug\DLL_to_inject.dll");

                if (!File.Exists(dllPath))
                {
                    throw new FileNotFoundException($"DLL not found at path: {dllPath}");
                }

                DllInjector.InjectDll(dllPath, "SkyrimSE");

                SpawnRequest.InitializePipeClient();
            }
        }

        private string GetSolutionDirectory()
        {
            DirectoryInfo directory = new DirectoryInfo(AppDomain.CurrentDomain.BaseDirectory);
            while (directory != null && !directory.GetFiles("*.sln").Any())
            {
                directory = directory.Parent;
            }
            if (directory == null)
            {
                throw new DirectoryNotFoundException("Solution directory not found.");
            }
            return directory.FullName;
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
                SpawnRequest.SendSpawnRequest(selectedItemID, spawnAmount);
            }
            else
            {
                MessageBox.Show("Please enter a valid number for spawn amount.");
            }
        }

        private void txtSpawnAmount_PreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            e.Handled = !IsTextAllowed(e.Text);
        }

        private static bool IsTextAllowed(string text)
        {
            return text.All(char.IsDigit);
        }
    }
}