#include <Windows.h>
#include "SetupForm.h"
#include "Managed.h"
#include "resource.h"
#include "Util.h"

using namespace System::Threading;
using namespace System::Windows::Forms;

namespace PowerPaimon
{

    Void SetupForm::OnFormClosing(Object^ sender, FormClosingEventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(settings->GamePath))
            Application::Exit();
    }

    Void SetupForm::btnBrowse_Click(Object^ sender, EventArgs^ e)
    {
        auto dialog = gcnew OpenFileDialog();
        dialog->Filter = "Process (*.exe)|*.exe|All files (*.*)|*.*";
        dialog->FilterIndex = 0;
        dialog->RestoreDirectory = true;

        if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {
            auto selectedFile = dialog->FileName;
            auto directory = Path::GetDirectoryName(selectedFile);
            
            if (!selectedFile->Contains("GenshinImpact.exe") && !selectedFile->Contains("YuanShen.exe"))
            {
                MessageBox::Show(Util::GetString(IDS_SETUP_DIALOG_BADEXE), Util::GetString(IDS_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (!File::Exists(directory + "\\UnityPlayer.dll"))
            {
                MessageBox::Show(Util::GetString(IDS_SETUP_DIALOG_WRONGPLACE), Util::GetString(IDS_ERROR), MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (backgroundWorker)
                backgroundWorker->CancelAsync();
            settings->GamePath = selectedFile;
            settings->Save();
            this->Close();
        }

    }

    Void SetupForm::OnProcessFound(String^ processPath)
    {
        settings->GamePath = processPath;
        settings->Save();
        this->Close();
    }

    Void SetupForm::OnDoWork(Object^ sender, DoWorkEventArgs^ e)
    {
        auto worker = safe_cast<BackgroundWorker^>(sender);
        while (!worker->CancellationPending)
        {
            auto path = Managed::TryGetGamePath();
            if (!String::IsNullOrWhiteSpace(path))
            {
                settings->GamePath = path;
                settings->Save();
                worker->ReportProgress(100);
                break;
            }

            Thread::Sleep(200);
        }
        
    }

    Void SetupForm::OnProgressChanged(Object^ sender, ProgressChangedEventArgs^ e)
    {
        auto object = e->UserState;
        auto percentage = e->ProgressPercentage;
        if (percentage == 100)
            this->Close();
    }

    Void SetupForm::OnLoad(Object^ sender, EventArgs^ e)
    {
        this->Text = Util::GetString(IDS_SETUP_TITLE);
        btnConfirm->Text = Util::GetString(IDS_CONFIRM);
        btnBrowse->Text = Util::GetString(IDS_BROWSE);

        auto result = Managed::TryResolveGamePath();
        if (result->Count)
        {
            btnConfirm->Visible = true;
            //btnBrowse->Visible = false;
            labelResult->Text = String::Format(Util::GetString(IDS_SETUP_LBRESULT_FOUND), result->Count);
            labelResult->ForeColor = Color::Green;
            labelSelectInstance->Text = Util::GetString(IDS_SETUP_LBSELECT_FOUND);
            comboBoxSelectInst->Visible = true;
            comboBoxSelectInst->Items->AddRange(result->ToArray());
            comboBoxSelectInst->SelectedIndex = 0;
            if (!String::IsNullOrWhiteSpace(settings->GamePath))
                comboBoxSelectInst->SelectedIndex = result->IndexOf(settings->GamePath);
        }
        else
        {
            btnConfirm->Visible = false;
            //btnBrowse->Visible = true;
            labelResult->Text = Util::GetString(IDS_SETUP_LBRESULT_NOTFOUND);
            labelResult->ForeColor = Color::Red;
            labelSelectInstance->Text = Util::GetString(IDS_SETUP_LBSELECT_NOTFOUND);
            comboBoxSelectInst->Visible = false;

            backgroundWorker = gcnew BackgroundWorker();
            backgroundWorker->WorkerReportsProgress = true;
            backgroundWorker->WorkerSupportsCancellation = true;
            backgroundWorker->DoWork += gcnew DoWorkEventHandler(this, &SetupForm::OnDoWork);
            backgroundWorker->ProgressChanged += gcnew ProgressChangedEventHandler(this, &SetupForm::OnProgressChanged);
            backgroundWorker->RunWorkerAsync();
        }
    }

    Void SetupForm::btnConfirm_Click(Object^ sender, EventArgs^ e)
    {
        settings->GamePath = safe_cast<String^>(comboBoxSelectInst->Items[comboBoxSelectInst->SelectedIndex]);
        settings->Save();
        this->Close();
    }
}
