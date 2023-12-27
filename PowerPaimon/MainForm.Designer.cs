using PowerPaimon.Properties;

namespace PowerPaimon
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            OptionsMenuStrip = new MenuStrip();
            FileToolStripMenuItem = new ToolStripMenuItem();
            SetupMenuItem = new ToolStripMenuItem();
            AboutMenuItem = new ToolStripMenuItem();
            MenuItemHr = new ToolStripSeparator();
            ExitMenuItem2 = new ToolStripMenuItem();
            InputFPS = new NumericUpDown();
            SliderFPS = new TrackBar();
            CBAutoStart = new CheckBox();
            BtnStartGame = new Button();
            ToolTipMain = new ToolTip(components);
            CBPowerSave = new CheckBox();
            CBAutoClose = new CheckBox();
            CBStartMinimized = new CheckBox();
            CBSuspendLoad = new CheckBox();
            NotifyIconMain = new NotifyIcon(components);
            ContextNotify = new ContextMenuStrip(components);
            ExitMenuItem = new ToolStripMenuItem();
            TabCtrlSettings = new TabControl();
            TabGeneral = new TabPage();
            LabelLanguage = new Label();
            ComboLanguage = new ComboBox();
            TabLaunchOptions = new TabPage();
            groupBoxCustomResolution = new GroupBox();
            CBCustomRes = new CheckBox();
            LabelCustomRes = new Label();
            InputResX = new NumericUpDown();
            LabelX = new Label();
            InputResY = new NumericUpDown();
            groupBoxFullscreen = new GroupBox();
            CBFullscreen = new CheckBox();
            LabelWindowMode = new Label();
            ComboFullscreenMode = new ComboBox();
            CBUseMobileUI = new CheckBox();
            InputMonitorNum = new NumericUpDown();
            LabelMonitor = new Label();
            CBPopup = new CheckBox();
            ComboPriority = new ComboBox();
            LabelPriority = new Label();
            TabDlls = new TabPage();
            BtnRemoveDll = new Button();
            BtnAddDll = new Button();
            ListBoxDlls = new ListBox();
            DLLLabel = new Label();
            DllAddDialog = new OpenFileDialog();
            FPSGroup = new GroupBox();
            OptionsMenuStrip.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)InputFPS).BeginInit();
            ((System.ComponentModel.ISupportInitialize)SliderFPS).BeginInit();
            ContextNotify.SuspendLayout();
            TabCtrlSettings.SuspendLayout();
            TabGeneral.SuspendLayout();
            TabLaunchOptions.SuspendLayout();
            groupBoxCustomResolution.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)InputResX).BeginInit();
            ((System.ComponentModel.ISupportInitialize)InputResY).BeginInit();
            groupBoxFullscreen.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)InputMonitorNum).BeginInit();
            TabDlls.SuspendLayout();
            FPSGroup.SuspendLayout();
            SuspendLayout();
            // 
            // OptionsMenuStrip
            // 
            OptionsMenuStrip.Items.AddRange(new ToolStripItem[] { FileToolStripMenuItem });
            OptionsMenuStrip.Location = new Point(0, 0);
            OptionsMenuStrip.Name = "OptionsMenuStrip";
            OptionsMenuStrip.Size = new Size(346, 24);
            OptionsMenuStrip.TabIndex = 0;
            OptionsMenuStrip.Text = "OptionsMenuStrip";
            // 
            // FileToolStripMenuItem
            // 
            FileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[] { SetupMenuItem, AboutMenuItem, MenuItemHr, ExitMenuItem2 });
            FileToolStripMenuItem.Name = "FileToolStripMenuItem";
            FileToolStripMenuItem.Size = new Size(37, 20);
            FileToolStripMenuItem.Text = "File";
            // 
            // SetupMenuItem
            // 
            SetupMenuItem.Name = "SetupMenuItem";
            SetupMenuItem.Size = new Size(107, 22);
            SetupMenuItem.Text = "Setup";
            SetupMenuItem.Click += SetupMenuItem_Click;
            // 
            // AboutMenuItem
            // 
            AboutMenuItem.Name = "AboutMenuItem";
            AboutMenuItem.Size = new Size(107, 22);
            AboutMenuItem.Text = "About";
            AboutMenuItem.Click += AboutMenuItem_Click;
            // 
            // MenuItemHr
            // 
            MenuItemHr.Name = "MenuItemHr";
            MenuItemHr.Size = new Size(104, 6);
            // 
            // ExitMenuItem2
            // 
            ExitMenuItem2.Name = "ExitMenuItem2";
            ExitMenuItem2.Size = new Size(107, 22);
            ExitMenuItem2.Text = "Exit";
            ExitMenuItem2.Click += ExitMenuItem_Click;
            // 
            // InputFPS
            // 
            InputFPS.Location = new Point(6, 25);
            InputFPS.Maximum = new decimal(new int[] { 420, 0, 0, 0 });
            InputFPS.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            InputFPS.Name = "InputFPS";
            InputFPS.Size = new Size(45, 23);
            InputFPS.TabIndex = 2;
            InputFPS.TextAlign = HorizontalAlignment.Center;
            InputFPS.Value = new decimal(new int[] { 120, 0, 0, 0 });
            // 
            // SliderFPS
            // 
            SliderFPS.Location = new Point(8, 54);
            SliderFPS.Maximum = 420;
            SliderFPS.Minimum = 1;
            SliderFPS.Name = "SliderFPS";
            SliderFPS.Orientation = Orientation.Vertical;
            SliderFPS.Size = new Size(45, 248);
            SliderFPS.TabIndex = 30;
            SliderFPS.TickFrequency = 60;
            SliderFPS.TickStyle = TickStyle.Both;
            SliderFPS.Value = 120;
            // 
            // CBAutoStart
            // 
            CBAutoStart.AutoSize = true;
            CBAutoStart.Location = new Point(80, 341);
            CBAutoStart.Name = "CBAutoStart";
            CBAutoStart.Size = new Size(161, 19);
            CBAutoStart.TabIndex = 4;
            CBAutoStart.Text = Resources.AutoStartGame;
            ToolTipMain.SetToolTip(CBAutoStart, "This will take effect on subsequent launch");
            CBAutoStart.UseVisualStyleBackColor = true;
            // 
            // BtnStartGame
            // 
            BtnStartGame.Location = new Point(247, 338);
            BtnStartGame.Name = "BtnStartGame";
            BtnStartGame.Size = new Size(85, 23);
            BtnStartGame.TabIndex = 5;
            BtnStartGame.Text = "Start Game";
            BtnStartGame.UseVisualStyleBackColor = true;
            BtnStartGame.Click += BtnStartGame_Click;
            // 
            // CBPowerSave
            // 
            CBPowerSave.AutoSize = true;
            CBPowerSave.Location = new Point(6, 56);
            CBPowerSave.Name = "CBPowerSave";
            CBPowerSave.Size = new Size(97, 19);
            CBPowerSave.TabIndex = 3;
            CBPowerSave.Text = "Power Saving";
            ToolTipMain.SetToolTip(CBPowerSave, "Sets fps to 10 and low process priority upon losing focus (e.g. tabbing out of game)");
            CBPowerSave.UseVisualStyleBackColor = true;
            // 
            // CBAutoClose
            // 
            CBAutoClose.AutoSize = true;
            CBAutoClose.Location = new Point(6, 31);
            CBAutoClose.Name = "CBAutoClose";
            CBAutoClose.Size = new Size(84, 19);
            CBAutoClose.TabIndex = 2;
            CBAutoClose.Text = "Auto Close";
            ToolTipMain.SetToolTip(CBAutoClose, "PowerPaimon will exit upon game closing");
            CBAutoClose.UseVisualStyleBackColor = true;
            // 
            // CBStartMinimized
            // 
            CBStartMinimized.AutoSize = true;
            CBStartMinimized.Location = new Point(6, 6);
            CBStartMinimized.Name = "CBStartMinimized";
            CBStartMinimized.Size = new Size(109, 19);
            CBStartMinimized.TabIndex = 1;
            CBStartMinimized.Text = "Start Minimized";
            ToolTipMain.SetToolTip(CBStartMinimized, "PowerPaimon will minimized to tray on starup");
            CBStartMinimized.UseVisualStyleBackColor = true;
            // 
            // CBSuspendLoad
            // 
            CBSuspendLoad.AutoSize = true;
            CBSuspendLoad.Location = new Point(138, 79);
            CBSuspendLoad.Name = "CBSuspendLoad";
            CBSuspendLoad.Size = new Size(100, 19);
            CBSuspendLoad.TabIndex = 4;
            CBSuspendLoad.Text = "Suspend Load";
            ToolTipMain.SetToolTip(CBSuspendLoad, "This can ensure dll gets loaded before the game starts\r\nIt may not work all the times\r\nUncheck this if the game crashes");
            CBSuspendLoad.UseVisualStyleBackColor = true;
            // 
            // NotifyIconMain
            // 
            NotifyIconMain.BalloonTipIcon = ToolTipIcon.Info;
            NotifyIconMain.BalloonTipText = "Minimized to tray";
            NotifyIconMain.BalloonTipTitle = "PowerPaimon";
            NotifyIconMain.ContextMenuStrip = ContextNotify;
            NotifyIconMain.Icon = (Icon)resources.GetObject("NotifyIconMain.Icon");
            NotifyIconMain.Text = "PowerPaimon";
            NotifyIconMain.Visible = true;
            NotifyIconMain.DoubleClick += NotifyIconMain_DoubleClick;
            // 
            // ContextNotify
            // 
            ContextNotify.Items.AddRange(new ToolStripItem[] { ExitMenuItem });
            ContextNotify.Name = "ContextNotify";
            ContextNotify.Size = new Size(94, 26);
            // 
            // ExitMenuItem
            // 
            ExitMenuItem.Name = "ExitMenuItem";
            ExitMenuItem.Size = new Size(93, 22);
            ExitMenuItem.Text = "Exit";
            ExitMenuItem.Click += ExitMenuItem_Click;
            // 
            // TabCtrlSettings
            // 
            TabCtrlSettings.Controls.Add(TabGeneral);
            TabCtrlSettings.Controls.Add(TabLaunchOptions);
            TabCtrlSettings.Controls.Add(TabDlls);
            TabCtrlSettings.Location = new Point(76, 27);
            TabCtrlSettings.Name = "TabCtrlSettings";
            TabCtrlSettings.SelectedIndex = 0;
            TabCtrlSettings.Size = new Size(260, 308);
            TabCtrlSettings.TabIndex = 1;
            // 
            // TabGeneral
            // 
            TabGeneral.Controls.Add(LabelLanguage);
            TabGeneral.Controls.Add(ComboLanguage);
            TabGeneral.Controls.Add(CBPowerSave);
            TabGeneral.Controls.Add(CBAutoClose);
            TabGeneral.Controls.Add(CBStartMinimized);
            TabGeneral.Location = new Point(4, 24);
            TabGeneral.Name = "TabGeneral";
            TabGeneral.Padding = new Padding(3);
            TabGeneral.Size = new Size(252, 280);
            TabGeneral.TabIndex = 0;
            TabGeneral.Text = "General";
            TabGeneral.UseVisualStyleBackColor = true;
            // 
            // LabelLanguage
            // 
            LabelLanguage.AutoSize = true;
            LabelLanguage.Location = new Point(3, 84);
            LabelLanguage.Name = "LabelLanguage";
            LabelLanguage.Size = new Size(59, 15);
            LabelLanguage.TabIndex = 7;
            LabelLanguage.Text = "Language";
            // 
            // ComboLanguage
            // 
            ComboLanguage.FormattingEnabled = true;
            ComboLanguage.Items.AddRange(new object[] { "English", "Japanese", "System Default" });
            ComboLanguage.Location = new Point(125, 81);
            ComboLanguage.Name = "ComboLanguage";
            ComboLanguage.Size = new Size(121, 23);
            ComboLanguage.TabIndex = 6;
            ComboLanguage.Text = "System Default";
            ComboLanguage.SelectedIndexChanged += LanguageChanged;
            // 
            // TabLaunchOptions
            // 
            TabLaunchOptions.Controls.Add(groupBoxCustomResolution);
            TabLaunchOptions.Controls.Add(groupBoxFullscreen);
            TabLaunchOptions.Controls.Add(CBUseMobileUI);
            TabLaunchOptions.Controls.Add(InputMonitorNum);
            TabLaunchOptions.Controls.Add(LabelMonitor);
            TabLaunchOptions.Controls.Add(CBPopup);
            TabLaunchOptions.Controls.Add(ComboPriority);
            TabLaunchOptions.Controls.Add(LabelPriority);
            TabLaunchOptions.Location = new Point(4, 24);
            TabLaunchOptions.Name = "TabLaunchOptions";
            TabLaunchOptions.Padding = new Padding(3);
            TabLaunchOptions.Size = new Size(252, 280);
            TabLaunchOptions.TabIndex = 1;
            TabLaunchOptions.Text = "Launch Options";
            TabLaunchOptions.UseVisualStyleBackColor = true;
            // 
            // groupBoxCustomResolution
            // 
            groupBoxCustomResolution.Controls.Add(CBCustomRes);
            groupBoxCustomResolution.Controls.Add(LabelCustomRes);
            groupBoxCustomResolution.Controls.Add(InputResX);
            groupBoxCustomResolution.Controls.Add(LabelX);
            groupBoxCustomResolution.Controls.Add(InputResY);
            groupBoxCustomResolution.Location = new Point(6, 108);
            groupBoxCustomResolution.Name = "groupBoxCustomResolution";
            groupBoxCustomResolution.Size = new Size(240, 77);
            groupBoxCustomResolution.TabIndex = 13;
            groupBoxCustomResolution.TabStop = false;
            groupBoxCustomResolution.Text = "Custom Resolution";
            // 
            // CBCustomRes
            // 
            CBCustomRes.AutoSize = true;
            CBCustomRes.Location = new Point(6, 22);
            CBCustomRes.Name = "CBCustomRes";
            CBCustomRes.Size = new Size(61, 19);
            CBCustomRes.TabIndex = 2;
            CBCustomRes.Text = "Enable";
            CBCustomRes.UseVisualStyleBackColor = true;
            CBCustomRes.CheckStateChanged += LaunchOptionsChanged;
            // 
            // LabelCustomRes
            // 
            LabelCustomRes.AutoSize = true;
            LabelCustomRes.Location = new Point(6, 44);
            LabelCustomRes.Name = "LabelCustomRes";
            LabelCustomRes.Size = new Size(69, 15);
            LabelCustomRes.TabIndex = 3;
            LabelCustomRes.Text = "Resolution: ";
            // 
            // InputResX
            // 
            InputResX.Location = new Point(99, 42);
            InputResX.Maximum = new decimal(new int[] { 7680, 0, 0, 0 });
            InputResX.Minimum = new decimal(new int[] { 200, 0, 0, 0 });
            InputResX.Name = "InputResX";
            InputResX.Size = new Size(55, 23);
            InputResX.TabIndex = 4;
            InputResX.Value = new decimal(new int[] { 1920, 0, 0, 0 });
            // 
            // LabelX
            // 
            LabelX.AutoSize = true;
            LabelX.Location = new Point(160, 44);
            LabelX.Name = "LabelX";
            LabelX.Size = new Size(13, 15);
            LabelX.TabIndex = 5;
            LabelX.Text = "x";
            // 
            // InputResY
            // 
            InputResY.Location = new Point(179, 42);
            InputResY.Maximum = new decimal(new int[] { 4320, 0, 0, 0 });
            InputResY.Minimum = new decimal(new int[] { 200, 0, 0, 0 });
            InputResY.Name = "InputResY";
            InputResY.Size = new Size(55, 23);
            InputResY.TabIndex = 6;
            InputResY.Value = new decimal(new int[] { 1080, 0, 0, 0 });
            // 
            // groupBoxFullscreen
            // 
            groupBoxFullscreen.Controls.Add(CBFullscreen);
            groupBoxFullscreen.Controls.Add(LabelWindowMode);
            groupBoxFullscreen.Controls.Add(ComboFullscreenMode);
            groupBoxFullscreen.Location = new Point(6, 31);
            groupBoxFullscreen.Name = "groupBoxFullscreen";
            groupBoxFullscreen.Size = new Size(240, 71);
            groupBoxFullscreen.TabIndex = 12;
            groupBoxFullscreen.TabStop = false;
            groupBoxFullscreen.Text = "Fullscren";
            // 
            // CBFullscreen
            // 
            CBFullscreen.AutoSize = true;
            CBFullscreen.Location = new Point(6, 22);
            CBFullscreen.Name = "CBFullscreen";
            CBFullscreen.Size = new Size(61, 19);
            CBFullscreen.TabIndex = 1;
            CBFullscreen.Text = "Enable";
            CBFullscreen.UseVisualStyleBackColor = true;
            CBFullscreen.CheckStateChanged += LaunchOptionsChanged;
            // 
            // LabelWindowMode
            // 
            LabelWindowMode.AutoSize = true;
            LabelWindowMode.Location = new Point(6, 44);
            LabelWindowMode.Name = "LabelWindowMode";
            LabelWindowMode.Size = new Size(41, 15);
            LabelWindowMode.TabIndex = 7;
            LabelWindowMode.Text = "Mode:";
            // 
            // ComboFullscreenMode
            // 
            ComboFullscreenMode.FormattingEnabled = true;
            ComboFullscreenMode.Items.AddRange(new object[] { "Borderless", "Exclusive" });
            ComboFullscreenMode.Location = new Point(99, 41);
            ComboFullscreenMode.Name = "ComboFullscreenMode";
            ComboFullscreenMode.Size = new Size(135, 23);
            ComboFullscreenMode.TabIndex = 8;
            ComboFullscreenMode.Text = "Borderless";
            // 
            // CBUseMobileUI
            // 
            CBUseMobileUI.AutoSize = true;
            CBUseMobileUI.Location = new Point(6, 251);
            CBUseMobileUI.Name = "CBUseMobileUI";
            CBUseMobileUI.Size = new Size(99, 19);
            CBUseMobileUI.TabIndex = 11;
            CBUseMobileUI.Text = "Use Mobile UI";
            CBUseMobileUI.UseVisualStyleBackColor = true;
            // 
            // InputMonitorNum
            // 
            InputMonitorNum.Location = new Point(111, 191);
            InputMonitorNum.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            InputMonitorNum.Name = "InputMonitorNum";
            InputMonitorNum.Size = new Size(135, 23);
            InputMonitorNum.TabIndex = 10;
            InputMonitorNum.Value = new decimal(new int[] { 1, 0, 0, 0 });
            // 
            // LabelMonitor
            // 
            LabelMonitor.AutoSize = true;
            LabelMonitor.Location = new Point(6, 193);
            LabelMonitor.Name = "LabelMonitor";
            LabelMonitor.Size = new Size(56, 15);
            LabelMonitor.TabIndex = 9;
            LabelMonitor.Text = "Monitor: ";
            // 
            // CBPopup
            // 
            CBPopup.AutoSize = true;
            CBPopup.Location = new Point(6, 6);
            CBPopup.Name = "CBPopup";
            CBPopup.Size = new Size(127, 19);
            CBPopup.TabIndex = 0;
            CBPopup.Text = "Borderless Window";
            CBPopup.UseVisualStyleBackColor = true;
            CBPopup.CheckStateChanged += LaunchOptionsChanged;
            // 
            // ComboPriority
            // 
            ComboPriority.FormattingEnabled = true;
            ComboPriority.Items.AddRange(new object[] { "Realtime", "High", "Above Normal", "Normal", "Below Normal", "Low" });
            ComboPriority.Location = new Point(111, 220);
            ComboPriority.Name = "ComboPriority";
            ComboPriority.Size = new Size(135, 23);
            ComboPriority.TabIndex = 5;
            ComboPriority.Text = "Normal";
            // 
            // LabelPriority
            // 
            LabelPriority.AutoSize = true;
            LabelPriority.Location = new Point(6, 223);
            LabelPriority.Name = "LabelPriority";
            LabelPriority.Size = new Size(91, 15);
            LabelPriority.TabIndex = 4;
            LabelPriority.Text = "Process Priority:";
            // 
            // TabDlls
            // 
            TabDlls.Controls.Add(CBSuspendLoad);
            TabDlls.Controls.Add(BtnRemoveDll);
            TabDlls.Controls.Add(BtnAddDll);
            TabDlls.Controls.Add(ListBoxDlls);
            TabDlls.Controls.Add(DLLLabel);
            TabDlls.Location = new Point(4, 24);
            TabDlls.Name = "TabDlls";
            TabDlls.Padding = new Padding(3);
            TabDlls.Size = new Size(252, 280);
            TabDlls.TabIndex = 2;
            TabDlls.Text = "DLLs";
            TabDlls.UseVisualStyleBackColor = true;
            // 
            // BtnRemoveDll
            // 
            BtnRemoveDll.Location = new Point(132, 50);
            BtnRemoveDll.Name = "BtnRemoveDll";
            BtnRemoveDll.Size = new Size(114, 23);
            BtnRemoveDll.TabIndex = 3;
            BtnRemoveDll.Text = "Remove";
            BtnRemoveDll.UseVisualStyleBackColor = true;
            BtnRemoveDll.Click += BtnRemoveDll_Click;
            // 
            // BtnAddDll
            // 
            BtnAddDll.Location = new Point(132, 21);
            BtnAddDll.Name = "BtnAddDll";
            BtnAddDll.Size = new Size(114, 23);
            BtnAddDll.TabIndex = 2;
            BtnAddDll.Text = "Add";
            BtnAddDll.UseVisualStyleBackColor = true;
            BtnAddDll.Click += BtnAddDll_Click;
            // 
            // ListBoxDlls
            // 
            ListBoxDlls.FormattingEnabled = true;
            ListBoxDlls.ItemHeight = 15;
            ListBoxDlls.Location = new Point(6, 21);
            ListBoxDlls.Name = "ListBoxDlls";
            ListBoxDlls.Size = new Size(120, 244);
            ListBoxDlls.TabIndex = 1;
            ListBoxDlls.Format += ListBoxDlls_Format;
            ListBoxDlls.MouseMove += ListBoxDlls_MouseMove;
            // 
            // DLLLabel
            // 
            DLLLabel.AutoSize = true;
            DLLLabel.Location = new Point(6, 3);
            DLLLabel.Name = "DLLLabel";
            DLLLabel.Size = new Size(232, 15);
            DLLLabel.TabIndex = 0;
            DLLLabel.Text = "DLLs will be injected in the order of this list";
            // 
            // DllAddDialog
            // 
            DllAddDialog.Filter = "DLL (*.dll)|*.dll|All files (*.*)|*.*";
            DllAddDialog.Multiselect = true;
            DllAddDialog.RestoreDirectory = true;
            // 
            // FPSGroup
            // 
            FPSGroup.Controls.Add(SliderFPS);
            FPSGroup.Controls.Add(InputFPS);
            FPSGroup.Location = new Point(12, 27);
            FPSGroup.Name = "FPSGroup";
            FPSGroup.Size = new Size(58, 308);
            FPSGroup.TabIndex = 6;
            FPSGroup.TabStop = false;
            FPSGroup.Text = "FPS";
            // 
            // MainForm
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(346, 368);
            Controls.Add(FPSGroup);
            Controls.Add(BtnStartGame);
            Controls.Add(CBAutoStart);
            Controls.Add(OptionsMenuStrip);
            Controls.Add(TabCtrlSettings);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            Icon = (Icon)resources.GetObject("$this.Icon");
            MainMenuStrip = OptionsMenuStrip;
            MaximizeBox = false;
            Name = "MainForm";
            StartPosition = FormStartPosition.CenterScreen;
            Text = "PowerPaimon";
            FormClosing += MainForm_FormClosing;
            Load += MainForm_Load;
            Resize += MainForm_Resize;
            OptionsMenuStrip.ResumeLayout(false);
            OptionsMenuStrip.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)InputFPS).EndInit();
            ((System.ComponentModel.ISupportInitialize)SliderFPS).EndInit();
            ContextNotify.ResumeLayout(false);
            TabCtrlSettings.ResumeLayout(false);
            TabGeneral.ResumeLayout(false);
            TabGeneral.PerformLayout();
            TabLaunchOptions.ResumeLayout(false);
            TabLaunchOptions.PerformLayout();
            groupBoxCustomResolution.ResumeLayout(false);
            groupBoxCustomResolution.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)InputResX).EndInit();
            ((System.ComponentModel.ISupportInitialize)InputResY).EndInit();
            groupBoxFullscreen.ResumeLayout(false);
            groupBoxFullscreen.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)InputMonitorNum).EndInit();
            TabDlls.ResumeLayout(false);
            TabDlls.PerformLayout();
            FPSGroup.ResumeLayout(false);
            FPSGroup.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private MenuStrip OptionsMenuStrip;
        private ToolStripMenuItem FileToolStripMenuItem;
        private ToolStripMenuItem SetupMenuItem;
        private ToolStripMenuItem AboutMenuItem;
        private NumericUpDown InputFPS;
        private TrackBar SliderFPS;
        private CheckBox CBAutoStart;
        private Button BtnStartGame;
        private ToolTip ToolTipMain;
        private NotifyIcon NotifyIconMain;
        private ContextMenuStrip ContextNotify;
        private ToolStripMenuItem ExitMenuItem;

        private TabControl TabCtrlSettings;
        private TabPage TabGeneral;
        private TabPage TabLaunchOptions;
        private TabPage TabDlls;
        private ComboBox ComboPriority;
        private Label LabelPriority;
        private CheckBox CBPowerSave;
        private CheckBox CBAutoClose;
        private CheckBox CBStartMinimized;
        private NumericUpDown InputResY;
        private Label LabelX;
        private NumericUpDown InputResX;
        private Label LabelCustomRes;
        private CheckBox CBCustomRes;
        private CheckBox CBFullscreen;
        private CheckBox CBPopup;
        private NumericUpDown InputMonitorNum;
        private Label LabelMonitor;
        private ComboBox ComboFullscreenMode;
        private Label LabelWindowMode;
        private Label DLLLabel;
        private ListBox ListBoxDlls;
        private Button BtnRemoveDll;
        private Button BtnAddDll;
        private CheckBox CBSuspendLoad;
        private CheckBox CBUseMobileUI;
        private OpenFileDialog DllAddDialog;
        private GroupBox FPSGroup;
        private ToolStripSeparator MenuItemHr;
        private ToolStripMenuItem ExitMenuItem2;
        private ComboBox ComboLanguage;
        private Label LabelLanguage;
        private GroupBox groupBoxCustomResolution;
        private GroupBox groupBoxFullscreen;
    }
}
