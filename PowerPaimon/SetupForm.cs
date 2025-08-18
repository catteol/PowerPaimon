using System.Data;
using System.Text;
using Microsoft.Win32;
using PowerPaimon.Model;
using PowerPaimon.Properties;
using PowerPaimon.Service;
using PowerPaimon.Utility;

namespace PowerPaimon
{
    public partial class SetupForm : Form
    {
        private CancellationTokenSource _cts;

        private readonly ConfigService _configService;
        private readonly Config _config;

        public SetupForm(ConfigService configService)
        {
            InitializeComponent();
            _configService = configService;
            _config = _configService.Config;
            _cts = new();
        }

        private void SetupForm_Load(object sender, EventArgs e)
        {
            UpdateLanguage();

            Task.Run(PollProcess, _cts.Token);

            LabelCurrentPath.Text = $"{Resources.CurrentPath}:\n" + $@"{_config.GamePath}";
            LabelResult.Text = @"Searching...";
            LabelResult.ForeColor = Color.Orange;
            Task.Run(SearchGamePath, _cts.Token);
        }

        private void SetupForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            _cts.Cancel();
            _configService.Save();
        }

        private async Task PollProcess()
        {
            // System.Diagnostics.Process will throw access denied
            // use native win32 api instead

            while (!_cts.Token.IsCancellationRequested)
            {
                await Task.Delay(1000);
                IntPtr windowHandle = IntPtr.Zero;
                IntPtr processHandle = IntPtr.Zero;
                string processPath = string.Empty;

                Native.EnumWindows((hWnd, lParam) =>
                {
                    const int maxCount = 256;
                    StringBuilder sb = new StringBuilder(maxCount);

                    Native.GetClassName(hWnd, sb, maxCount);
                    if (sb.ToString() == "UnityWndClass")
                    {
                        Native.GetWindowThreadProcessId(hWnd, out var pid);
                        processHandle = Native.OpenProcess(
                            ProcessAccess.QUERY_LIMITED_INFORMATION |
                            ProcessAccess.TERMINATE |
                            StandardAccess.SYNCHRONIZE, false, pid);
                        var foundPath = ProcessUtils.GetProcessPath(processHandle);
                        if (!foundPath.Contains("YuanShen.exe") && !foundPath.Contains("GenshinImpact.exe"))
                            return true;

                        windowHandle = hWnd;
                        processPath = foundPath;
                        return false;
                    }

                    return true;
                }, IntPtr.Zero);

                if (windowHandle == IntPtr.Zero)
                    continue;

                Native.TerminateProcess(processHandle, 0);
                Native.CloseHandle(processHandle);

                if (string.IsNullOrEmpty(processPath))
                {
                    MessageBox.Show(@"Failed to find process path{Environment.NewLine}Please use ""Browse"" instead", @"Error",
                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                MessageBox.Show(this, string.Format(Resources.GameDetectedLabel, processPath), @"Success", MessageBoxButtons.OK,
                    MessageBoxIcon.Information);

                _config.GamePath = processPath;
                Invoke(Close);
            }

        }

        private void SearchGamePath()
        {
            using var hypGlobal = Registry.CurrentUser.OpenSubKey(@"SOFTWARE\Cognosphere\HYP\1_1\hk4e_global");
            using var hypCn = Registry.CurrentUser.OpenSubKey(@"SOFTWARE\miHoYo\HYP\1_1\hk4e_cn");

            List<string> gamePaths = new();

            var installPathGlobal = hypGlobal?.GetValue("GameInstallPath") as string;
            var installPathCn = hypCn?.GetValue("GameInstallPath") as string;

            if (installPathGlobal != null)
            {
                var path = Path.Combine(installPathGlobal, "GenshinImpact.exe");
                gamePaths.Add(path.Replace('/', '\\'));
            }

            if (installPathCn != null)
            {
                var path = Path.Combine(installPathCn, "YuanShen.exe");
                gamePaths.Add(path.Replace('/', '\\'));
            }

            Invoke(() =>
            {
                LabelResult.ForeColor = gamePaths.Count > 0 ? Color.Green : Color.Red;
                LabelResult.Text = string.Format(Resources.GameFoundLabel, gamePaths.Count);
                ComboResult.Items.AddRange(gamePaths.ToArray());
                if (gamePaths.Count > 0)
                    ComboResult.SelectedIndex = 0;
            });
        }

        private void BtnBrowse_Click(object sender, EventArgs e)
        {
            if (BrowseDialog.ShowDialog() != DialogResult.OK)
                return;

            var selectedFile = BrowseDialog.FileName;
            var fileName = Path.GetFileNameWithoutExtension(selectedFile);
            var directory = Path.GetDirectoryName(selectedFile) ?? "";

            if (fileName != "GenshinImpact" && fileName != "YuanShen")
            {
                MessageBox.Show(
                    $@"Please select the game exe{Environment.NewLine}GenshinImpact.exe or YuanShen.exe",
                    @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            var dataDir = Path.Combine(directory, $"{fileName}_Data");
            if (!Directory.Exists(dataDir))
            {
                MessageBox.Show(@"That's not the right place", @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            _config.GamePath = selectedFile;
            Close();
        }

        private void BtnConfirm_Click(object sender, EventArgs e)
        {
            var selectedPath = (string?)ComboResult.SelectedItem;
            if (string.IsNullOrEmpty(selectedPath))
                return;

            _config.GamePath = selectedPath;
            Close();
        }

        private void UpdateLanguage()
        {
            // Setup Form
            LabelCurrentPath.Text = Resources.CurrentPath;
            LabelResult.Text = Resources.SetupHint;
            LabelSelect.Text = Resources.SelectPath;
            LabelHint.Text = Resources.SetupHint;
            BtnBrowse.Text = Resources.Browse;
            BtnConfirm.Text = Resources.Confirm;
        }
    }
}
