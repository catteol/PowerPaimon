using System.Data;
using System.Globalization;
using System.Reflection;
using System.Reflection.PortableExecutable;
using Microsoft.Extensions.DependencyInjection;
using PowerPaimon.Model;
using PowerPaimon.Properties;
using PowerPaimon.Service;

namespace PowerPaimon
{
    public partial class MainForm : Form
    {
        private Point _windowLocation;
        private Size _windowSize;

        private readonly ConfigService _configService;
        private readonly Config _config;
        private readonly ProcessService _processService;

        public MainForm(
            ConfigService configService,
            ProcessService processService)
        {
            InitializeComponent();
            _configService = configService;
            _config = _configService.Config;
            _processService = processService;
            SetupBindings();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            _configService.Save();
            _processService.OnFormClosing();
            NotifyIconMain.Visible = false;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            UpdateLanguage();
            UpdateControlState();
            this.Text = $"PowerPaimon v{Assembly.GetExecutingAssembly().GetName().Version?.ToString(3)}";

            _windowLocation = Location;
            _windowSize = Size;
            if (_config.AutoStart)
                BtnStartGame_Click(sender, e);
        }

        private void SetupBindings()
        {
            // Main Features
            InputFPS.DataBindings.Add("Value", _config, "FPSTarget", true, DataSourceUpdateMode.OnPropertyChanged);
            SliderFPS.DataBindings.Add("Value", _config, "FPSTarget", true, DataSourceUpdateMode.OnPropertyChanged);
            CBAutoStart.DataBindings.Add("Checked", _config, "AutoStart", true, DataSourceUpdateMode.OnPropertyChanged);

            // General
            CBStartMinimized.DataBindings.Add("Checked", _config, "StartMinimized", true, DataSourceUpdateMode.OnPropertyChanged);
            CBAutoClose.DataBindings.Add("Checked", _config, "AutoClose", true, DataSourceUpdateMode.OnPropertyChanged);
            CBPowerSave.DataBindings.Add("Checked", _config, "UsePowerSave", true, DataSourceUpdateMode.OnPropertyChanged);
            ComboLanguage.DataBindings.Add("SelectedIndex", _config, "Language", true, DataSourceUpdateMode.OnPropertyChanged);

            // Launch Options
            CBPopup.DataBindings.Add("Checked", _config, "PopupWindow", true, DataSourceUpdateMode.OnPropertyChanged);
            CBFullscreen.DataBindings.Add("Checked", _config, "Fullscreen", true, DataSourceUpdateMode.OnPropertyChanged);
            CBCustomRes.DataBindings.Add("Checked", _config, "UseCustomRes", true, DataSourceUpdateMode.OnPropertyChanged);
            InputResX.DataBindings.Add("Value", _config, "CustomResX", true, DataSourceUpdateMode.OnPropertyChanged);
            InputResY.DataBindings.Add("Value", _config, "CustomResY", true, DataSourceUpdateMode.OnPropertyChanged);
            ComboFullscreenMode.DataBindings.Add("SelectedIndex", _config, "IsExclusiveFullscreen", true, DataSourceUpdateMode.OnPropertyChanged);
            InputMonitorNum.DataBindings.Add("Value", _config, "MonitorNum", true, DataSourceUpdateMode.OnPropertyChanged);
            ComboPriority.DataBindings.Add("SelectedIndex", _config, "Priority", true, DataSourceUpdateMode.OnPropertyChanged);
            CBUseMobileUI.DataBindings.Add("Checked", _config, "UseMobileUI", true, DataSourceUpdateMode.OnPropertyChanged);

            // DLLs            
            RefreshDllList();
            CBSuspendLoad.DataBindings.Add("Checked", _config, "SuspendLoad", true, DataSourceUpdateMode.OnPropertyChanged);
        }

        private void SetupMenuItem_Click(object sender, EventArgs e)
        {
            ShowSetupForm();
        }

        private void BtnStartGame_Click(object sender, EventArgs e)
        {
            if (!File.Exists(_config.GamePath))
                ShowSetupForm();

            if (_processService.Start())
                WindowState = FormWindowState.Minimized;
        }

        private static void ShowSetupForm()
        {
            var setupForm = Program.ServiceProvider?.GetRequiredService<SetupForm>();
            setupForm?.ShowDialog();
        }

        private void ExitMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void MainForm_Resize(object sender, EventArgs e)
        {
            if (WindowState == FormWindowState.Minimized)
                NotifyAndHide();
        }

        private void NotifyAndHide()
        {
            NotifyIconMain.Visible = true;
            NotifyIconMain.Text = $@"PowerPaimon (FPS: {_config.FPSTarget})";
            NotifyIconMain.ShowBalloonTip(500);

            ShowInTaskbar = false;
            Hide();
        }

        private void NotifyIconMain_DoubleClick(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Normal;
            ShowInTaskbar = true;
            Show();
            Activate();

            Location = _windowLocation;
            Size = _windowSize;
        }

        private void AboutMenuItem_Click(object sender, EventArgs e)
        {
            var aboutForm = new AboutForm();
            aboutForm.ShowDialog();
        }

        private void RefreshDllList()
        {
            _config.DllList = _config.DllList
                .Where(VerifyDll)
                .ToList();

            ListBoxDlls.Items.Clear();
            ListBoxDlls.Items.AddRange(_config.DllList.ToArray());
        }

        private void UpdateControlState()
        {
            if (_config.PopupWindow) // they can't coexist (?) so disable the other
                _config.Fullscreen = false;

            CBPopup.Enabled = !_config.Fullscreen;
            CBFullscreen.Enabled = !_config.PopupWindow;
            InputResX.Enabled = _config.UseCustomRes;
            InputResY.Enabled = _config.UseCustomRes;
            ComboFullscreenMode.Enabled = _config is { Fullscreen: true, PopupWindow: false };
        }

        private void UpdateLanguage()
        {
            switch (ComboLanguage.SelectedIndex)
            {
                case 0: // English
                    Thread.CurrentThread.CurrentUICulture = new CultureInfo("");
                    break;
                case 1: // Japanese
                    Thread.CurrentThread.CurrentUICulture = new CultureInfo("ja-JP");
                    break;
                case 2: // System Default
                    {
                        switch (CultureInfo.CurrentCulture.IetfLanguageTag)
                        {
                            case "ja-JP":
                                Thread.CurrentThread.CurrentUICulture = new CultureInfo("ja-JP");
                                break;
                            default:
                                Thread.CurrentThread.CurrentUICulture = new CultureInfo("");
                                break;
                        }
                        break;
                    }
            }

            // Main Form
            FileToolStripMenuItem.Text = Resources.File;
            SetupMenuItem.Text = Resources.Setup;
            AboutMenuItem.Text = Resources.About;
            ExitMenuItem.Text = ExitMenuItem2.Text = Resources.Exit;
            TabGeneral.Text = Resources.General;
            TabLaunchOptions.Text = Resources.LaunchOptions;
            CBAutoStart.Text = Resources.AutoStartGame;
            BtnStartGame.Text = Resources.StartGame;

            // General Tab
            CBStartMinimized.Text = Resources.StartMinimized;
            CBAutoClose.Text = Resources.AutoClose;
            CBPowerSave.Text = Resources.PowerSaving;
            LabelLanguage.Text = Resources.Language;

            // Language ComboBox, looks unsmart
            ComboLanguage.SelectedIndexChanged -= LanguageChanged;
            var oldIdx = ComboLanguage.SelectedIndex;
            ComboLanguage.Items.Clear();
            ComboLanguage.Items.AddRange(new object[] { Resources.English, Resources.Japanese, Resources.SystemDefault });
            ComboLanguage.SelectedIndex = oldIdx;
            ComboLanguage.SelectedIndexChanged += LanguageChanged;

            // Launch Options Tab
            CBPopup.Text = Resources.BorderlessWindow;
            groupBoxFullscreen.Text = Resources.Fullscreen;
            CBFullscreen.Text = Resources.Enable;
            LabelWindowMode.Text = Resources.Mode;
            groupBoxCustomResolution.Text = Resources.CustomResolution;
            CBCustomRes.Text = Resources.Enable;
            LabelCustomRes.Text = Resources.Resolution;
            LabelMonitor.Text = Resources.Monitor;
            LabelPriority.Text = Resources.Priority;
            CBUseMobileUI.Text = Resources.UseMobileUI;

            // DLLs Tab
            DLLLabel.Text = Resources.DLLLabelDescription;
            BtnAddDll.Text = Resources.Add;
            BtnRemoveDll.Text = Resources.Remove;
            CBSuspendLoad.Text = Resources.SuspendLoad;
        }

        public void LanguageChanged(object? sender, EventArgs e)
        {
            UpdateLanguage();
        }
        public void LaunchOptionsChanged(object sender, EventArgs e)
        {
            UpdateControlState();
        }

        private void BtnAddDll_Click(object sender, EventArgs e)
        {
            if (DllAddDialog.ShowDialog() != DialogResult.OK)
                return;

            var selectedFiles = DllAddDialog.FileNames.ToList();
            selectedFiles = selectedFiles
                .Where(x => VerifyDll(x) || MessageBox.Show(
                    $@"Invalid File: {Environment.NewLine}{x}{Environment.NewLine}{Environment.NewLine}Only native x64 dlls are supported",
                    @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error) != DialogResult.OK)
                .Where(x => !_config.DllList.Contains(x))
                .ToList();

            _config.DllList.AddRange(selectedFiles);
            RefreshDllList();
        }

        private bool VerifyDll(string fullPath)
        {
            if (!File.Exists(fullPath))
                return false;

            using var fs = new FileStream(fullPath, FileMode.Open, FileAccess.Read);
            using var peReader = new PEReader(fs);

            if (peReader.HasMetadata)
                return false;

            return peReader.PEHeaders.CoffHeader.Machine == Machine.Amd64;
        }

        private void ListBoxDlls_Format(object sender, ListControlConvertEventArgs e)
        {
            e.Value = Path.GetFileName(e.Value as string);
        }

        private void ListBoxDlls_MouseMove(object sender, MouseEventArgs e)
        {
            var index = ListBoxDlls.IndexFromPoint(e.Location);
            if (index == -1)
                return;

            var toolTipText = _config.DllList[index];
            ToolTipMain.SetToolTip(ListBoxDlls, toolTipText);
        }

        private void BtnRemoveDll_Click(object sender, EventArgs e)
        {
            var selectedIndex = ListBoxDlls.SelectedIndex;
            if (selectedIndex == -1)
                return;

            _config.DllList.RemoveAt(selectedIndex);
            RefreshDllList();
        }
    }
}
