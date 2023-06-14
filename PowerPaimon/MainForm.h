#pragma once
#include "Settings.h"
#include "SetupForm.h"
#include <algorithm>


namespace unlockfpsclr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			settings = Settings::Load();

			this->Load += gcnew EventHandler(this, &MainForm::OnLoad);
			this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::OnFormClosing);
			this->Resize += gcnew EventHandler(this, &MainForm::OnResize);
			this->notifyIcon->DoubleClick += gcnew EventHandler(this, &MainForm::OnDoubleClick);

			this->ckbVSync->DataBindings->Add("Checked", settings, "AutoDisableVSync", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbPopupWnd->DataBindings->Add("Checked", settings, "PopupWindow", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbFullscreen->DataBindings->Add("Checked", settings, "Fullscreen", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbCustomRes->DataBindings->Add("Checked", settings, "UseCustomRes", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbStartMinimized->DataBindings->Add("Checked", settings, "StartMinimized", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbAutoClose->DataBindings->Add("Checked", settings, "AutoClose", false, DataSourceUpdateMode::OnPropertyChanged);
			this->ckbPowerSave->DataBindings->Add("Checked", settings, "UsePowerSave", false, DataSourceUpdateMode::OnPropertyChanged);

			this->lbDllList->Format += gcnew ListControlConvertEventHandler(this, &MainForm::OnFormat);

			this->settings = settings;
			this->FormClosing += gcnew FormClosingEventHandler(this, &MainForm::UpdateSettings);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: Settings^ settings;
	private: BackgroundWorker^ backgroundWorker;
	private: System::Windows::Forms::Button^ btnStartGame;

	private: System::Windows::Forms::ToolTip^ ttAutoStart;
	private: System::Windows::Forms::TrackBar^ tbFPS;

	private: System::Windows::Forms::NumericUpDown^ inputFPS;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;



	private: System::Windows::Forms::ToolTip^ ttGamePath;


	private: System::Windows::Forms::NotifyIcon^ notifyIcon;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuNotify;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuExit;
	private: System::Windows::Forms::ToolStripMenuItem^ menuItemAbout;

	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::CheckBox^ ckbAutoStart;
	private: System::Windows::Forms::TabControl^ tabControl;
	private: System::Windows::Forms::TabPage^ tabPageGeneral;
	private: System::Windows::Forms::ComboBox^ comboPriority;
	private: System::Windows::Forms::Label^ labelPriority;
	private: System::Windows::Forms::CheckBox^ ckbPowerSave;
	private: System::Windows::Forms::CheckBox^ ckbAutoClose;
	private: System::Windows::Forms::CheckBox^ ckbStartMinimized;
	private: System::Windows::Forms::CheckBox^ ckbVSync;
	private: System::Windows::Forms::TabPage^ tabPageLaunchOptions;
	private: System::Windows::Forms::NumericUpDown^ monitorNum;
	private: System::Windows::Forms::Label^ labelMonitorNum;
	private: System::Windows::Forms::ComboBox^ comboWindowMode;
	private: System::Windows::Forms::Label^ labelWindowMode;
	private: System::Windows::Forms::Label^ labelDummy;
	private: System::Windows::Forms::NumericUpDown^ customResY;
	private: System::Windows::Forms::NumericUpDown^ customResX;

	private: System::Windows::Forms::CheckBox^ ckbCustomRes;
	private: System::Windows::Forms::CheckBox^ ckbFullscreen;
	private: System::Windows::Forms::CheckBox^ ckbPopupWnd;
	private: System::Windows::Forms::TabPage^ tabPageDLLs;
	private: System::Windows::Forms::Button^ btnDllRemove;
	private: System::Windows::Forms::Button^ btnDllAdd;
	private: System::Windows::Forms::ListBox^ lbDllList;
	private: System::Windows::Forms::Label^ labelDLLMessage;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel4;






	private: System::Windows::Forms::ToolStripMenuItem^ menuItemExit;

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;






	private: System::Windows::Forms::ToolStripMenuItem^ editToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ menuItemSetup;
private: System::Windows::Forms::ToolStripMenuItem^ menuItemLang;
private: System::Windows::Forms::ToolStripMenuItem^ menuItemLangJa;

private: System::Windows::Forms::ToolStripMenuItem^ menuItemLangEn;


private: System::Windows::Forms::ToolStripSeparator^ toolStripMenuItem2;
private: System::Windows::Forms::ToolStripMenuItem^ menuItemLangDefault;

private: System::Windows::Forms::ToolTip^ ttPowerSaving;
private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuConfigure;
private: System::Windows::Forms::ToolTip^ ttMinimize;
private: System::Windows::Forms::ToolTip^ ttAutoExit;






	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->btnStartGame = (gcnew System::Windows::Forms::Button());
			this->ttAutoStart = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->ckbAutoStart = (gcnew System::Windows::Forms::CheckBox());
			this->tbFPS = (gcnew System::Windows::Forms::TrackBar());
			this->inputFPS = (gcnew System::Windows::Forms::NumericUpDown());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemAbout = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemSetup = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemLang = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemLangJa = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuItemLangEn = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->menuItemLangDefault = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ttGamePath = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->contextMenuNotify = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripMenuConfigure = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPageGeneral = (gcnew System::Windows::Forms::TabPage());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->ckbStartMinimized = (gcnew System::Windows::Forms::CheckBox());
			this->ckbAutoClose = (gcnew System::Windows::Forms::CheckBox());
			this->ckbPowerSave = (gcnew System::Windows::Forms::CheckBox());
			this->labelPriority = (gcnew System::Windows::Forms::Label());
			this->comboPriority = (gcnew System::Windows::Forms::ComboBox());
			this->tabPageLaunchOptions = (gcnew System::Windows::Forms::TabPage());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->ckbVSync = (gcnew System::Windows::Forms::CheckBox());
			this->ckbPopupWnd = (gcnew System::Windows::Forms::CheckBox());
			this->ckbFullscreen = (gcnew System::Windows::Forms::CheckBox());
			this->ckbCustomRes = (gcnew System::Windows::Forms::CheckBox());
			this->customResX = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelDummy = (gcnew System::Windows::Forms::Label());
			this->customResY = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelWindowMode = (gcnew System::Windows::Forms::Label());
			this->comboWindowMode = (gcnew System::Windows::Forms::ComboBox());
			this->labelMonitorNum = (gcnew System::Windows::Forms::Label());
			this->monitorNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->tabPageDLLs = (gcnew System::Windows::Forms::TabPage());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->labelDLLMessage = (gcnew System::Windows::Forms::Label());
			this->lbDllList = (gcnew System::Windows::Forms::ListBox());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btnDllAdd = (gcnew System::Windows::Forms::Button());
			this->btnDllRemove = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->ttPowerSaving = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->ttMinimize = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->ttAutoExit = (gcnew System::Windows::Forms::ToolTip(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbFPS))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inputFPS))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->contextMenuNotify->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->tabPageGeneral->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tabPageLaunchOptions->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResX))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->monitorNum))->BeginInit();
			this->tabPageDLLs->SuspendLayout();
			this->flowLayoutPanel3->SuspendLayout();
			this->flowLayoutPanel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnStartGame
			// 
			this->btnStartGame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnStartGame->Location = System::Drawing::Point(286, 333);
			this->btnStartGame->Name = L"btnStartGame";
			this->btnStartGame->Size = System::Drawing::Size(75, 21);
			this->btnStartGame->TabIndex = 0;
			this->btnStartGame->TabStop = false;
			this->btnStartGame->Text = L"Start Game";
			this->btnStartGame->UseVisualStyleBackColor = true;
			this->btnStartGame->Click += gcnew System::EventHandler(this, &MainForm::btnStartGame_Click);
			// 
			// ttAutoStart
			// 
			this->ttAutoStart->AutoPopDelay = 5000;
			this->ttAutoStart->InitialDelay = 1;
			this->ttAutoStart->ReshowDelay = 100;
			// 
			// ckbAutoStart
			// 
			this->ckbAutoStart->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ckbAutoStart->AutoSize = true;
			this->ckbAutoStart->Location = System::Drawing::Point(124, 336);
			this->ckbAutoStart->Name = L"ckbAutoStart";
			this->ckbAutoStart->Size = System::Drawing::Size(156, 16);
			this->ckbAutoStart->TabIndex = 1;
			this->ckbAutoStart->TabStop = false;
			this->ckbAutoStart->Text = L"Start Game Automatically";
			this->ttAutoStart->SetToolTip(this->ckbAutoStart, L"This will take effect on subsequent launch");
			this->ckbAutoStart->UseVisualStyleBackColor = true;
			// 
			// tbFPS
			// 
			this->tbFPS->Cursor = System::Windows::Forms::Cursors::Hand;
			this->tbFPS->Location = System::Drawing::Point(18, 45);
			this->tbFPS->Maximum = 360;
			this->tbFPS->Minimum = 1;
			this->tbFPS->Name = L"tbFPS";
			this->tbFPS->Orientation = System::Windows::Forms::Orientation::Vertical;
			this->tbFPS->Size = System::Drawing::Size(45, 246);
			this->tbFPS->TabIndex = 2;
			this->tbFPS->TabStop = false;
			this->tbFPS->TickFrequency = 30;
			this->tbFPS->TickStyle = System::Windows::Forms::TickStyle::Both;
			this->tbFPS->Value = 120;
			// 
			// inputFPS
			// 
			this->inputFPS->Location = System::Drawing::Point(18, 23);
			this->inputFPS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 360, 0, 0, 0 });
			this->inputFPS->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->inputFPS->Name = L"inputFPS";
			this->inputFPS->Size = System::Drawing::Size(45, 19);
			this->inputFPS->TabIndex = 4;
			this->inputFPS->TabStop = false;
			this->inputFPS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->editToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(375, 24);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->menuItemAbout,
					this->menuItemExit
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// menuItemAbout
			// 
			this->menuItemAbout->Name = L"menuItemAbout";
			this->menuItemAbout->Size = System::Drawing::Size(107, 22);
			this->menuItemAbout->Text = L"About";
			this->menuItemAbout->Click += gcnew System::EventHandler(this, &MainForm::menuItemAbout_Click);
			// 
			// menuItemExit
			// 
			this->menuItemExit->Name = L"menuItemExit";
			this->menuItemExit->Size = System::Drawing::Size(107, 22);
			this->menuItemExit->Text = L"Exit";
			this->menuItemExit->Click += gcnew System::EventHandler(this, &MainForm::menuItemExit_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->menuItemSetup,
					this->menuItemLang
			});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// menuItemSetup
			// 
			this->menuItemSetup->Name = L"menuItemSetup";
			this->menuItemSetup->Size = System::Drawing::Size(126, 22);
			this->menuItemSetup->Text = L"Setup";
			this->menuItemSetup->Click += gcnew System::EventHandler(this, &MainForm::setupMenuItem_Click);
			// 
			// menuItemLang
			// 
			this->menuItemLang->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->menuItemLangJa,
					this->menuItemLangEn, this->toolStripMenuItem2, this->menuItemLangDefault
			});
			this->menuItemLang->Name = L"menuItemLang";
			this->menuItemLang->Size = System::Drawing::Size(126, 22);
			this->menuItemLang->Text = L"Language";
			// 
			// menuItemLangJa
			// 
			this->menuItemLangJa->Name = L"menuItemLangJa";
			this->menuItemLangJa->Size = System::Drawing::Size(153, 22);
			this->menuItemLangJa->Text = L"Japanese";
			// 
			// menuItemLangEn
			// 
			this->menuItemLangEn->Name = L"menuItemLangEn";
			this->menuItemLangEn->Size = System::Drawing::Size(153, 22);
			this->menuItemLangEn->Text = L"English";
			// 
			// toolStripMenuItem2
			// 
			this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
			this->toolStripMenuItem2->Size = System::Drawing::Size(150, 6);
			// 
			// menuItemLangDefault
			// 
			this->menuItemLangDefault->Name = L"menuItemLangDefault";
			this->menuItemLangDefault->Size = System::Drawing::Size(153, 22);
			this->menuItemLangDefault->Text = L"System Default";
			// 
			// ttGamePath
			// 
			this->ttGamePath->AutoPopDelay = 5000;
			this->ttGamePath->InitialDelay = 2;
			this->ttGamePath->ReshowDelay = 100;
			// 
			// notifyIcon
			// 
			this->notifyIcon->BalloonTipIcon = System::Windows::Forms::ToolTipIcon::Info;
			this->notifyIcon->BalloonTipText = L"Minimized to tray";
			this->notifyIcon->BalloonTipTitle = L"PowerPaimon";
			this->notifyIcon->ContextMenuStrip = this->contextMenuNotify;
			this->notifyIcon->Text = L"PowerPaimon";
			this->notifyIcon->Visible = true;
			// 
			// contextMenuNotify
			// 
			this->contextMenuNotify->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuConfigure,
					this->toolStripMenuExit
			});
			this->contextMenuNotify->Name = L"contextMenuNotify";
			this->contextMenuNotify->ShowItemToolTips = false;
			this->contextMenuNotify->Size = System::Drawing::Size(128, 48);
			// 
			// toolStripMenuConfigure
			// 
			this->toolStripMenuConfigure->Name = L"toolStripMenuConfigure";
			this->toolStripMenuConfigure->Size = System::Drawing::Size(127, 22);
			this->toolStripMenuConfigure->Text = L"Configure";
			this->toolStripMenuConfigure->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuConfigure_Click);
			// 
			// toolStripMenuExit
			// 
			this->toolStripMenuExit->Name = L"toolStripMenuExit";
			this->toolStripMenuExit->Size = System::Drawing::Size(127, 22);
			this->toolStripMenuExit->Text = L"Exit";
			this->toolStripMenuExit->Click += gcnew System::EventHandler(this, &MainForm::toolStripMenuExit_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->tbFPS);
			this->groupBox1->Controls->Add(this->inputFPS);
			this->groupBox1->Location = System::Drawing::Point(12, 27);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(80, 300);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"FPS";
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPageGeneral);
			this->tabControl->Controls->Add(this->tabPageLaunchOptions);
			this->tabControl->Controls->Add(this->tabPageDLLs);
			this->tabControl->Location = System::Drawing::Point(98, 27);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(268, 300);
			this->tabControl->TabIndex = 6;
			// 
			// tabPageGeneral
			// 
			this->tabPageGeneral->Controls->Add(this->flowLayoutPanel1);
			this->tabPageGeneral->Location = System::Drawing::Point(4, 22);
			this->tabPageGeneral->Name = L"tabPageGeneral";
			this->tabPageGeneral->Padding = System::Windows::Forms::Padding(3);
			this->tabPageGeneral->Size = System::Drawing::Size(260, 274);
			this->tabPageGeneral->TabIndex = 0;
			this->tabPageGeneral->Text = L"General";
			this->tabPageGeneral->UseVisualStyleBackColor = true;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->ckbStartMinimized);
			this->flowLayoutPanel1->Controls->Add(this->ckbAutoClose);
			this->flowLayoutPanel1->Controls->Add(this->ckbPowerSave);
			this->flowLayoutPanel1->Controls->Add(this->labelPriority);
			this->flowLayoutPanel1->Controls->Add(this->comboPriority);
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Padding = System::Windows::Forms::Padding(5);
			this->flowLayoutPanel1->Size = System::Drawing::Size(260, 274);
			this->flowLayoutPanel1->TabIndex = 7;
			// 
			// ckbStartMinimized
			// 
			this->ckbStartMinimized->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ckbStartMinimized->AutoSize = true;
			this->ckbStartMinimized->Location = System::Drawing::Point(8, 8);
			this->ckbStartMinimized->Name = L"ckbStartMinimized";
			this->ckbStartMinimized->Size = System::Drawing::Size(160, 16);
			this->ckbStartMinimized->TabIndex = 1;
			this->ckbStartMinimized->TabStop = false;
			this->ckbStartMinimized->Text = L"Start Minimized (Unlocker)";
			this->ckbStartMinimized->UseVisualStyleBackColor = true;
			// 
			// ckbAutoClose
			// 
			this->ckbAutoClose->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ckbAutoClose->AutoSize = true;
			this->ckbAutoClose->Location = System::Drawing::Point(8, 30);
			this->ckbAutoClose->Margin = System::Windows::Forms::Padding(3, 3, 100, 3);
			this->ckbAutoClose->Name = L"ckbAutoClose";
			this->ckbAutoClose->Size = System::Drawing::Size(81, 16);
			this->ckbAutoClose->TabIndex = 2;
			this->ckbAutoClose->TabStop = false;
			this->ckbAutoClose->Text = L"Auto Close";
			this->ckbAutoClose->UseVisualStyleBackColor = true;
			// 
			// ckbPowerSave
			// 
			this->ckbPowerSave->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ckbPowerSave->AutoSize = true;
			this->ckbPowerSave->Location = System::Drawing::Point(8, 52);
			this->ckbPowerSave->Margin = System::Windows::Forms::Padding(3, 3, 100, 3);
			this->ckbPowerSave->Name = L"ckbPowerSave";
			this->ckbPowerSave->Size = System::Drawing::Size(93, 16);
			this->ckbPowerSave->TabIndex = 3;
			this->ckbPowerSave->TabStop = false;
			this->ckbPowerSave->Text = L"Power Saving";
			this->ckbPowerSave->UseVisualStyleBackColor = true;
			// 
			// labelPriority
			// 
			this->labelPriority->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelPriority->AutoSize = true;
			this->labelPriority->Location = System::Drawing::Point(8, 78);
			this->labelPriority->Name = L"labelPriority";
			this->labelPriority->Size = System::Drawing::Size(120, 12);
			this->labelPriority->TabIndex = 4;
			this->labelPriority->Text = L"Game Process Priority";
			// 
			// comboPriority
			// 
			this->comboPriority->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->comboPriority->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboPriority->FormattingEnabled = true;
			this->comboPriority->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Realtime", L"High", L"Above Normal", L"Normal",
					L"Below Normal", L"Low"
			});
			this->comboPriority->Location = System::Drawing::Point(134, 74);
			this->comboPriority->Name = L"comboPriority";
			this->comboPriority->Size = System::Drawing::Size(118, 20);
			this->comboPriority->TabIndex = 5;
			this->comboPriority->TabStop = false;
			// 
			// tabPageLaunchOptions
			// 
			this->tabPageLaunchOptions->Controls->Add(this->flowLayoutPanel2);
			this->tabPageLaunchOptions->Location = System::Drawing::Point(4, 22);
			this->tabPageLaunchOptions->Name = L"tabPageLaunchOptions";
			this->tabPageLaunchOptions->Padding = System::Windows::Forms::Padding(3);
			this->tabPageLaunchOptions->Size = System::Drawing::Size(260, 274);
			this->tabPageLaunchOptions->TabIndex = 1;
			this->tabPageLaunchOptions->Text = L"Launch Options";
			this->tabPageLaunchOptions->UseVisualStyleBackColor = true;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->Controls->Add(this->ckbVSync);
			this->flowLayoutPanel2->Controls->Add(this->ckbPopupWnd);
			this->flowLayoutPanel2->Controls->Add(this->ckbFullscreen);
			this->flowLayoutPanel2->Controls->Add(this->ckbCustomRes);
			this->flowLayoutPanel2->Controls->Add(this->customResX);
			this->flowLayoutPanel2->Controls->Add(this->labelDummy);
			this->flowLayoutPanel2->Controls->Add(this->customResY);
			this->flowLayoutPanel2->Controls->Add(this->labelWindowMode);
			this->flowLayoutPanel2->Controls->Add(this->comboWindowMode);
			this->flowLayoutPanel2->Controls->Add(this->labelMonitorNum);
			this->flowLayoutPanel2->Controls->Add(this->monitorNum);
			this->flowLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Padding = System::Windows::Forms::Padding(5);
			this->flowLayoutPanel2->Size = System::Drawing::Size(260, 274);
			this->flowLayoutPanel2->TabIndex = 7;
			// 
			// ckbVSync
			// 
			this->ckbVSync->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ckbVSync->AutoSize = true;
			this->ckbVSync->Location = System::Drawing::Point(8, 8);
			this->ckbVSync->Name = L"ckbVSync";
			this->ckbVSync->Size = System::Drawing::Size(127, 16);
			this->ckbVSync->TabIndex = 0;
			this->ckbVSync->TabStop = false;
			this->ckbVSync->Text = L"Auto Disable VSync";
			this->ckbVSync->UseVisualStyleBackColor = true;
			// 
			// ckbPopupWnd
			// 
			this->ckbPopupWnd->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ckbPopupWnd->AutoSize = true;
			this->ckbPopupWnd->Location = System::Drawing::Point(8, 30);
			this->ckbPopupWnd->Margin = System::Windows::Forms::Padding(3, 3, 100, 3);
			this->ckbPopupWnd->Name = L"ckbPopupWnd";
			this->ckbPopupWnd->Size = System::Drawing::Size(97, 16);
			this->ckbPopupWnd->TabIndex = 0;
			this->ckbPopupWnd->TabStop = false;
			this->ckbPopupWnd->Text = L"Popup Window";
			this->ckbPopupWnd->UseVisualStyleBackColor = true;
			// 
			// ckbFullscreen
			// 
			this->ckbFullscreen->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ckbFullscreen->AutoSize = true;
			this->ckbFullscreen->Location = System::Drawing::Point(8, 52);
			this->ckbFullscreen->Margin = System::Windows::Forms::Padding(3, 3, 100, 3);
			this->ckbFullscreen->Name = L"ckbFullscreen";
			this->ckbFullscreen->Size = System::Drawing::Size(77, 16);
			this->ckbFullscreen->TabIndex = 1;
			this->ckbFullscreen->TabStop = false;
			this->ckbFullscreen->Text = L"Fullscreen";
			this->ckbFullscreen->UseVisualStyleBackColor = true;
			// 
			// ckbCustomRes
			// 
			this->ckbCustomRes->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ckbCustomRes->AutoSize = true;
			this->ckbCustomRes->Location = System::Drawing::Point(8, 75);
			this->ckbCustomRes->Name = L"ckbCustomRes";
			this->ckbCustomRes->Size = System::Drawing::Size(121, 16);
			this->ckbCustomRes->TabIndex = 2;
			this->ckbCustomRes->TabStop = false;
			this->ckbCustomRes->Text = L"Custom Resolution";
			this->ckbCustomRes->UseVisualStyleBackColor = true;
			this->ckbCustomRes->CheckedChanged += gcnew System::EventHandler(this, &MainForm::ckbCustomRes_CheckedChanged);
			// 
			// customResX
			// 
			this->customResX->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->customResX->Location = System::Drawing::Point(135, 74);
			this->customResX->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7680, 0, 0, 0 });
			this->customResX->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			this->customResX->Name = L"customResX";
			this->customResX->Size = System::Drawing::Size(50, 19);
			this->customResX->TabIndex = 4;
			this->customResX->TabStop = false;
			this->customResX->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1920, 0, 0, 0 });
			// 
			// labelDummy
			// 
			this->labelDummy->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelDummy->AutoSize = true;
			this->labelDummy->Location = System::Drawing::Point(188, 77);
			this->labelDummy->Margin = System::Windows::Forms::Padding(0);
			this->labelDummy->Name = L"labelDummy";
			this->labelDummy->Size = System::Drawing::Size(11, 12);
			this->labelDummy->TabIndex = 6;
			this->labelDummy->Text = L"x";
			// 
			// customResY
			// 
			this->customResY->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->customResY->Location = System::Drawing::Point(202, 74);
			this->customResY->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 4320, 0, 0, 0 });
			this->customResY->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 200, 0, 0, 0 });
			this->customResY->Name = L"customResY";
			this->customResY->Size = System::Drawing::Size(50, 19);
			this->customResY->TabIndex = 5;
			this->customResY->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1080, 0, 0, 0 });
			// 
			// labelWindowMode
			// 
			this->labelWindowMode->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelWindowMode->AutoSize = true;
			this->labelWindowMode->Location = System::Drawing::Point(8, 103);
			this->labelWindowMode->Margin = System::Windows::Forms::Padding(3, 0, 47, 0);
			this->labelWindowMode->Name = L"labelWindowMode";
			this->labelWindowMode->Size = System::Drawing::Size(76, 12);
			this->labelWindowMode->TabIndex = 7;
			this->labelWindowMode->Text = L"Window Mode:";
			// 
			// comboWindowMode
			// 
			this->comboWindowMode->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->comboWindowMode->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboWindowMode->FormattingEnabled = true;
			this->comboWindowMode->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"Borderless", L"Exclusive" });
			this->comboWindowMode->Location = System::Drawing::Point(134, 99);
			this->comboWindowMode->Name = L"comboWindowMode";
			this->comboWindowMode->Size = System::Drawing::Size(118, 20);
			this->comboWindowMode->TabIndex = 8;
			this->comboWindowMode->TabStop = false;
			// 
			// labelMonitorNum
			// 
			this->labelMonitorNum->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelMonitorNum->AutoSize = true;
			this->labelMonitorNum->Location = System::Drawing::Point(8, 128);
			this->labelMonitorNum->Margin = System::Windows::Forms::Padding(3, 0, 78, 0);
			this->labelMonitorNum->Name = L"labelMonitorNum";
			this->labelMonitorNum->Size = System::Drawing::Size(45, 12);
			this->labelMonitorNum->TabIndex = 9;
			this->labelMonitorNum->Text = L"Monitor:";
			// 
			// monitorNum
			// 
			this->monitorNum->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->monitorNum->Location = System::Drawing::Point(134, 125);
			this->monitorNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->monitorNum->Name = L"monitorNum";
			this->monitorNum->Size = System::Drawing::Size(118, 19);
			this->monitorNum->TabIndex = 10;
			this->monitorNum->TabStop = false;
			this->monitorNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// tabPageDLLs
			// 
			this->tabPageDLLs->Controls->Add(this->flowLayoutPanel3);
			this->tabPageDLLs->Location = System::Drawing::Point(4, 22);
			this->tabPageDLLs->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
			this->tabPageDLLs->Name = L"tabPageDLLs";
			this->tabPageDLLs->Padding = System::Windows::Forms::Padding(3, 3, 3, 0);
			this->tabPageDLLs->Size = System::Drawing::Size(260, 274);
			this->tabPageDLLs->TabIndex = 2;
			this->tabPageDLLs->Text = L"DLLs";
			this->tabPageDLLs->UseVisualStyleBackColor = true;
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->Controls->Add(this->labelDLLMessage);
			this->flowLayoutPanel3->Controls->Add(this->lbDllList);
			this->flowLayoutPanel3->Controls->Add(this->flowLayoutPanel4);
			this->flowLayoutPanel3->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel3->Margin = System::Windows::Forms::Padding(0);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Padding = System::Windows::Forms::Padding(5);
			this->flowLayoutPanel3->Size = System::Drawing::Size(260, 274);
			this->flowLayoutPanel3->TabIndex = 7;
			// 
			// labelDLLMessage
			// 
			this->labelDLLMessage->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->labelDLLMessage->AutoSize = true;
			this->labelDLLMessage->Location = System::Drawing::Point(8, 5);
			this->labelDLLMessage->Name = L"labelDLLMessage";
			this->labelDLLMessage->Size = System::Drawing::Size(232, 12);
			this->labelDLLMessage->TabIndex = 0;
			this->labelDLLMessage->Text = L"DLLs will be injected in the order of this list";
			// 
			// lbDllList
			// 
			this->lbDllList->FormattingEnabled = true;
			this->lbDllList->ItemHeight = 12;
			this->lbDllList->Location = System::Drawing::Point(8, 20);
			this->lbDllList->Name = L"lbDllList";
			this->lbDllList->Size = System::Drawing::Size(125, 244);
			this->lbDllList->TabIndex = 1;
			this->lbDllList->TabStop = false;
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->Controls->Add(this->btnDllAdd);
			this->flowLayoutPanel4->Controls->Add(this->btnDllRemove);
			this->flowLayoutPanel4->Location = System::Drawing::Point(139, 20);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(113, 100);
			this->flowLayoutPanel4->TabIndex = 4;
			// 
			// btnDllAdd
			// 
			this->btnDllAdd->Location = System::Drawing::Point(3, 3);
			this->btnDllAdd->Name = L"btnDllAdd";
			this->btnDllAdd->Size = System::Drawing::Size(107, 21);
			this->btnDllAdd->TabIndex = 2;
			this->btnDllAdd->TabStop = false;
			this->btnDllAdd->Text = L"Add";
			this->btnDllAdd->UseVisualStyleBackColor = true;
			// 
			// btnDllRemove
			// 
			this->btnDllRemove->Location = System::Drawing::Point(3, 30);
			this->btnDllRemove->Name = L"btnDllRemove";
			this->btnDllRemove->Size = System::Drawing::Size(107, 21);
			this->btnDllRemove->TabIndex = 3;
			this->btnDllRemove->TabStop = false;
			this->btnDllRemove->Text = L"Remove";
			this->btnDllRemove->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(375, 362);
			this->Controls->Add(this->tabControl);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->ckbAutoStart);
			this->Controls->Add(this->btnStartGame);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"PowerPaimon";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tbFPS))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->inputFPS))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->contextMenuNotify->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->tabPageGeneral->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->tabPageLaunchOptions->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->flowLayoutPanel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResX))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->customResY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->monitorNum))->EndInit();
			this->tabPageDLLs->ResumeLayout(false);
			this->flowLayoutPanel3->ResumeLayout(false);
			this->flowLayoutPanel3->PerformLayout();
			this->flowLayoutPanel4->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: Void btnStartGame_Click(Object^ sender, EventArgs^ e);
	private: Void OnLoad(Object^ sender, EventArgs^ e);
	private: Void setupMenuItem_Click(Object^ sender, EventArgs^ e);
	private: Void OnDoWork(Object^ sender, DoWorkEventArgs^ e);
	private: Void OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e);
	private: Void OnResize(Object^ sender, EventArgs^ e);
	private: Void OnDoubleClick(Object^ sender, EventArgs^ e);
	private: Void toolStripMenuExit_Click(Object^ sender, EventArgs^ e);
	private: Void OnFormClosing(Object^ sender, FormClosingEventArgs^ e);
	private: Void menuItemAbout_Click(Object^ sender, EventArgs^ e);
	private: Void UpdateSettings(Object^ sender, FormClosingEventArgs^ e);
	private: Void btnDllRemove_Click(Object^ sender, EventArgs^ e);
	private: Void btnDllAdd_Click(Object^ sender, EventArgs^ e);
	private: Void OnFormat(Object^ sender, ListControlConvertEventArgs^ e);
	private: Void ckbCustomRes_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: Void menuItemExit_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void toolStripMenuConfigure_Click(System::Object^ sender, System::EventArgs^ e);
};
}