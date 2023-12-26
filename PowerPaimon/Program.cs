using Microsoft.Extensions.DependencyInjection;
using System.Runtime.InteropServices;
using PowerPaimon.Service;
using PowerPaimon.Utility;

namespace PowerPaimon
{
    internal static class Program
    {
        private static IntPtr MutexHandle = IntPtr.Zero;
        public static IServiceProvider ServiceProvider { get; private set; }

        [STAThread]
        static void Main()
        {
            MutexHandle = Native.CreateMutex(IntPtr.Zero, true, @"PowerPaimon");
            if (Marshal.GetLastWin32Error() == 183)
            {
                MessageBox.Show(@"Another PowerPaimon is already running.", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            
            var services = new ServiceCollection();
            services.AddTransient<MainForm>();
            services.AddTransient<SettingsForm>();
            services.AddTransient<SetupForm>();
            services.AddSingleton<ConfigService>();
            services.AddSingleton<ProcessService>();

            ServiceProvider = services.BuildServiceProvider();

            ApplicationConfiguration.Initialize();
            Application.Run(ServiceProvider.GetRequiredService<MainForm>());
        }


    }
}