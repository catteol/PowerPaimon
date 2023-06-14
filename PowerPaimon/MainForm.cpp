#include "Unmanaged.h"
#include "MainForm.h"
#include "AboutForm.h"
#include "Managed.h"
#include "resource.h"
#include "Util.h"
#include <unordered_map>

#define MUTEX_NAME "GenshinFPSUnlocker"

using namespace System;
using namespace System::Reflection;
using namespace System::Windows::Forms;
using namespace System::Text::Json;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Runtime::InteropServices;

static const std::unordered_map<std::string, LPCSTR> dependencies = {
	{"Microsoft.Bcl.AsyncInterfaces.dll", MAKEINTRESOURCEA(IDR_DLL1)},
	{"System.Buffers.dll", MAKEINTRESOURCEA(IDR_DLL2)},
	{"System.Memory.dll", MAKEINTRESOURCEA(IDR_DLL3)},
	{"System.Numerics.Vectors.dll", MAKEINTRESOURCEA(IDR_DLL4)},
	{"System.Runtime.CompilerServices.Unsafe.dll", MAKEINTRESOURCEA(IDR_DLL5)},
	{"System.Text.Encodings.Web.dll", MAKEINTRESOURCEA(IDR_DLL6)},
	{"System.Text.Json.dll", MAKEINTRESOURCEA(IDR_DLL7)},
	{"System.Threading.Tasks.Extensions.dll", MAKEINTRESOURCEA(IDR_DLL8)}
};

void Run()
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	unlockfpsclr::MainForm mainForm;
	Application::Run(% mainForm);
}

Assembly^ OnAssemblyResolve(Object^ sender, ResolveEventArgs^ args)
{
	/*
		resolve dependencies through cpp resource
		the goal is to have a single file application
		kinda ugly but it works idc

		an easier way is to use vmprotect to bundle
		dependency assemblies, but ppl be skeptical about
		binaries processed through vmp, so I didn't use that

		for some reason vmprotect adds significant amount of il code
		even if there aren't any protection enabled

		ILMerge and ILRepack doesn't want to work with c++/cli
		if anyone knows an easier way to bundle assemblies, lmk
	*/

	Assembly^ assembly = nullptr;
	auto assemblyName = gcnew AssemblyName(args->Name);
	auto nativeString = static_cast<LPSTR>(static_cast<PVOID>(Marshal::StringToHGlobalAnsi(assemblyName->Name + ".dll")));

	auto resId = dependencies.find(nativeString);
	if (resId != dependencies.end())
	{
		auto rsrc = FindResourceA(nullptr, resId->second, "DLL");
		auto size = SizeofResource(nullptr, rsrc);
		auto rsrcData = LoadResource(nullptr, rsrc);
		auto pData = LockResource(rsrcData);
		if (pData)
		{
			array<BYTE>^ rawBytes = gcnew array<BYTE>(size);
			Marshal::Copy(static_cast<IntPtr>(pData), rawBytes, 0, size);
			assembly = Assembly::Load(rawBytes);
		}
	}

	Marshal::FreeHGlobal(static_cast<IntPtr>(nativeString));

	return assembly;
}

int main(array<String^>^ args)
{
	HANDLE hMutex = OpenMutexA(MUTEX_ALL_ACCESS, FALSE, MUTEX_NAME);
	if (hMutex)
		return 0;

	hMutex = CreateMutexA(nullptr, FALSE, MUTEX_NAME);

	AppDomain::CurrentDomain->AssemblyResolve += gcnew ResolveEventHandler(&OnAssemblyResolve);

	// check to see if the unlocker is placed with the game
	if (File::Exists("UnityPlayer.dll") && (File::Exists("GenshinImpact.exe") || File::Exists("YuanShen.exe")))
	{
		MessageBox::Show("Do not place unlocker in the same folder as the game", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		goto Exit;
	}

	auto thread = gcnew Thread(gcnew ThreadStart(Run));
	thread->SetApartmentState(ApartmentState::STA); // Single-Threaded Apartment required for file browse
	thread->Start();
	thread->Join();

Exit:
	ReleaseMutex(hMutex);
	return 0;
}

namespace unlockfpsclr
{
	Void MainForm::btnStartGame_Click(Object^ sender, EventArgs^ e)
	{
		// minimize the unlocker if create process was successful
		if (Managed::StartGame(settings))
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
	}

	Void MainForm::OnLoad(Object^ sender, EventArgs^ e)
	{
		// Initialize UI
		this->Text = String::Format("{0} v{1}", Util::GetString(IDS_MAIN_TITLE), ProductVersion);
		this->fileToolStripMenuItem->Text = Util::GetString(IDS_MAIN_MENU_FILE);
		this->menuItemAbout->Text = Util::GetString(IDS_MAIN_MENU_ABOUT);
		this->menuItemExit->Text = Util::GetString(IDS_EXIT);
		this->editToolStripMenuItem->Text = Util::GetString(IDS_MAIN_MENU_EDIT);
		this->menuItemSetup->Text = Util::GetString(IDS_MAIN_MENU_SETUP);
		this->menuItemLang->Text = Util::GetString(IDS_MAIN_MENU_LANG);
		this->menuItemLangJa->Text = Util::GetString(IDS_MAIN_MENU_LANG_JA);
		this->menuItemLangEn->Text = Util::GetString(IDS_MAIN_MENU_LANG_EN);
		this->menuItemLangDefault->Text = Util::GetString(IDS_MAIN_MENU_LANG_DEFAULT);

		this->tabPageGeneral->Text = Util::GetString(IDS_MAIN_TAB_GENERAL);
		this->tabPageLaunchOptions->Text = Util::GetString(IDS_MAIN_TAB_OPT);
		this->tabPageDLLs->Text = Util::GetString(IDS_MAIN_TAB_DLL);

		this->ckbStartMinimized->Text = Util::GetString(IDS_MAIN_CHK_MINIMIZE);
		this->ckbAutoClose->Text = Util::GetString(IDS_MAIN_CHK_AUTOEXIT);
		this->ckbPowerSave->Text = Util::GetString(IDS_MAIN_CHK_PWRSAVE);
		this->labelPriority->Text = Util::GetString(IDS_MAIN_DRD_PROCPRIORITY);

		this->ckbVSync->Text = Util::GetString(IDS_MAIN_CHK_VSYNC);
		this->ckbPopupWnd->Text = Util::GetString(IDS_MAIN_CHK_POPUP);
		this->ckbFullscreen->Text = Util::GetString(IDS_MAIN_CHK_FULLSCREEN);
		this->ckbCustomRes->Text = Util::GetString(IDS_MAIN_CHK_CUSTOMRES);
		this->labelWindowMode->Text = Util::GetString(IDS_MAIN_LB_WINMODE);
		this->labelMonitorNum->Text = Util::GetString(IDS_MAIN_LB_MONITOR);

		this->labelDLLMessage->Text = Util::GetString(IDS_MAIN_LB_DLLCAP);
		this->btnDllAdd->Text = Util::GetString(IDS_MAIN_BTN_ADD);
		this->btnDllRemove->Text = Util::GetString(IDS_MAIN_BTN_REMOVE);

		this->ckbAutoStart->Text = Util::GetString(IDS_MAIN_CHK_AUTOLAUNCH);
		this->btnStartGame->Text = Util::GetString(IDS_MAIN_BTN_LAUNCH);

		this->notifyIcon->BalloonTipTitle = Util::GetString(IDS_MAIN_TITLE);
		this->notifyIcon->BalloonTipText = Util::GetString(IDS_NOTIFY_MINIMIZE_MSG);

		this->toolStripMenuConfigure->Text = Util::GetString(IDS_CONFIGURE);
		this->toolStripMenuExit->Text = Util::GetString(IDS_EXIT);

		this->ttAutoStart->SetToolTip(this->ckbAutoStart, Util::GetString(IDS_MAIN_TT_AUTOLAUNCH));
		this->ttPowerSaving->SetToolTip(this->ckbPowerSave, Util::GetString(IDS_MAIN_TT_PWRSAVE));
		this->ttMinimize->SetToolTip(this->ckbStartMinimized, Util::GetString(IDS_MAIN_TT_MINIMIZE));
		this->ttAutoExit->SetToolTip(this->ckbAutoClose, Util::GetString(IDS_MAIN_TT_AUTOEXIT));

		auto hIcon = (HICON)LoadImageA(GetModuleHandleA(nullptr), MAKEINTRESOURCEA(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
		this->Icon = System::Drawing::Icon::FromHandle(static_cast<IntPtr>(hIcon));
		notifyIcon->Icon = this->Icon;
		//DestroyIcon(hIcon);

		// start setup dialog if game path is invalid in config
		if (String::IsNullOrWhiteSpace(settings->GamePath) || !File::Exists(settings->GamePath))
			(gcnew SetupForm(settings))->ShowDialog();

		settings->FPSTarget = std::clamp(settings->FPSTarget, tbFPS->Minimum, tbFPS->Maximum); // sanitize

		ckbAutoStart->DataBindings->Add("Checked", settings, "AutoStart");
		tbFPS->DataBindings->Add("Value", settings, "FPSTarget", false, DataSourceUpdateMode::OnPropertyChanged);
		inputFPS->DataBindings->Add("Value", settings, "FPSTarget", false, DataSourceUpdateMode::OnPropertyChanged);

		if (settings->StartMinimized)
			this->WindowState = System::Windows::Forms::FormWindowState::Minimized;

		if (settings->AutoStart)
			Managed::StartGame(settings);

		this->Focus();

		// create a thread for applying fps value
		backgroundWorker = gcnew BackgroundWorker();
		backgroundWorker->WorkerReportsProgress = true;
		backgroundWorker->WorkerSupportsCancellation = true;
		backgroundWorker->DoWork += gcnew DoWorkEventHandler(this, &MainForm::OnDoWork);
		backgroundWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &MainForm::OnProgressChanged);
		backgroundWorker->RunWorkerAsync();

		// Settings
		monitorNum->Maximum = GetSystemMetrics(SM_CMONITORS); // get maximum monitor count
		customResX->Value = Convert::ToDecimal(std::clamp(settings->CustomResX, Convert::ToInt32(customResX->Minimum), Convert::ToInt32(customResX->Maximum))); // sanitization
		customResY->Value = Convert::ToDecimal(std::clamp(settings->CustomResY, Convert::ToInt32(customResY->Minimum), Convert::ToInt32(customResY->Maximum))); // sanitization
		monitorNum->Value = Convert::ToDecimal(std::clamp(settings->MonitorNum, Convert::ToInt32(monitorNum->Minimum), Convert::ToInt32(monitorNum->Maximum))); // sanitization
		comboWindowMode->SelectedIndex = Convert::ToInt32(settings->IsExclusiveFullscreen);
		comboPriority->SelectedIndex = std::clamp(settings->Priority, -1, comboPriority->Items->Count);
		lbDllList->Items->AddRange(settings->DllList->ToArray());
		ckbCustomRes_CheckedChanged(nullptr, nullptr);
	}

	Void MainForm::setupMenuItem_Click(Object^ sender, EventArgs^ e)
	{
		auto form = gcnew SetupForm(settings);
		form->ShowDialog();
	}

	Void MainForm::OnDoWork(Object^ sender, DoWorkEventArgs^ e)
	{
		auto worker = safe_cast<BackgroundWorker^>(sender);
		while (!worker->CancellationPending)
		{
			Thread::Sleep(200);
			if (!Unmanaged::IsGameRunning())
				continue;

			// setup pointer to fps value and vsync value
			if (!Unmanaged::SetupData())
				continue;

			Managed::InjectDLLs(settings->DllList);

			while (!worker->CancellationPending)
			{
				Unmanaged::ApplyFPS(settings->FPSTarget, settings->UsePowerSave);
				Unmanaged::ApplyVSync(settings->AutoDisableVSync);

				if (!Unmanaged::IsGameRunning())
					break;

				Thread::Sleep(1000);
			}

			// ProgressChangedEvent will be dispatched on call to ReportProgress
			// this is needed because any changes to form control need to be done on the thread created it
			// and this method runs on a seperate thread
			if (settings->AutoClose)
				worker->ReportProgress(100);
			else
				worker->ReportProgress(10);

		}

	}

	Void MainForm::OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e)
	{
		auto progress = e->ProgressPercentage;
		if (progress == 100)
			Application::Exit();
		if (progress == 10)
			OnDoubleClick(nullptr, nullptr); // restore window
	}

	Void MainForm::OnResize(Object^ sender, EventArgs^ e)
	{
		if (this->WindowState == FormWindowState::Minimized)
		{
			// tray icon visibility and tooltip
			notifyIcon->Visible = true;
			notifyIcon->Text = String::Format("{0} (FPS: {1})", Util::GetString(IDS_MAIN_TITLE), settings->FPSTarget);

			// only show wintoast notification once
			static bool once = false;
			if (!once)
			{
				notifyIcon->ShowBalloonTip(500);
				once = true;
			}

			// hide app icon in taskbar
			this->ShowInTaskbar = false;
		}
	}

	Void MainForm::OnDoubleClick(Object^ sender, EventArgs^ e)
	{
		// restores window and taskbar icon
		this->WindowState = FormWindowState::Normal;
		this->ShowInTaskbar = true;
		this->Activate();
		//notifyIcon->Visible = false;
	}

	Void MainForm::menuItemAbout_Click(Object^ sender, EventArgs^ e)
	{
		auto form = gcnew AboutForm();
		form->ShowDialog();
	}

	Void MainForm::UpdateSettings(System::Object^ sender, FormClosingEventArgs^ e)
	{
		// update settings and write to file

		settings->CustomResX = Convert::ToInt32(customResX->Value);
		settings->CustomResY = Convert::ToInt32(customResY->Value);
		settings->MonitorNum = Convert::ToInt32(monitorNum->Value);
		settings->IsExclusiveFullscreen = comboWindowMode->SelectedIndex == 1;
		settings->Priority = comboPriority->SelectedIndex;

		settings->Save();
		lbDllList->Items->Clear();
	}

	System::Void MainForm::MainForm_Deactivate(System::Object^ sender, System::EventArgs^ e)
	{
		UpdateSettings(sender, nullptr);
	}

	Void MainForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
	{
		// save on exit
		settings->Save();
		notifyIcon->Visible = false;
	}

	Void MainForm::exit_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}

	Void MainForm::btnDllRemove_Click(Object^ sender, EventArgs^ e)
	{
		auto index = lbDllList->SelectedIndex;
		if (index >= 0)
		{
			// if nothing goes wrong...
			// the size of these two list should be the same
			settings->DllList->RemoveAt(index);
			lbDllList->Items->RemoveAt(index);
		}
	}

	Void MainForm::btnDllAdd_Click(Object^ sender, EventArgs^ e)
	{
		auto dialog = gcnew OpenFileDialog();
		dialog->Filter = "DLL (*.dll)|*.dll|All files (*.*)|*.*";
		dialog->FilterIndex = 0;
		dialog->RestoreDirectory = true;

		if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			auto selectedFile = dialog->FileName;
			auto fileName = Path::GetFileName(selectedFile);

			if (auto index = lbDllList->Items->IndexOf(selectedFile); index >= 0)
			{
				lbDllList->SelectedIndex = index;
				MessageBox::Show("File already in list", "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
				return;
			}

			// read and validate pe header
			auto fileStream = File::OpenRead(selectedFile);
			auto rawBytes = gcnew array<uint8_t>(0x1000);
			fileStream->Read(rawBytes, 0, 0x1000);
			pin_ptr<Byte> pinned = &rawBytes[0];
			if (!Unmanaged::VerifyDLL((PVOID)pinned))
			{
				MessageBox::Show("Invalid File\nThe DLL is either corrupted or 32-bit\nOnly 64-bit DLLs are supported", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			settings->DllList->Add(selectedFile);
			lbDllList->Items->Add(selectedFile);
		}

	}

	Void MainForm::OnFormat(Object^ sender, ListControlConvertEventArgs^ e)
	{
		// formatting for dll list box
		e->Value = Path::GetFileName(safe_cast<String^>(e->Value));
	}

	Void MainForm::ckbCustomRes_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		if (!this->ckbCustomRes->Checked)
		{
			this->customResX->Enabled = false;
			this->labelDummy->Enabled = false;
			this->customResY->Enabled = false;
		}
		else
		{
			this->customResX->Enabled = true;
			this->labelDummy->Enabled = true;
			this->customResY->Enabled = true;
		}
	}
	
	System::Void MainForm::toolStripMenuConfigure_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->WindowState = FormWindowState::Normal;
	}
}