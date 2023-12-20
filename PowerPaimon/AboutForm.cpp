#include <Windows.h>
#include "AboutForm.h"
#include "MainForm.h"
#include "resource.h"
#include "Util.h"


using namespace System::Diagnostics;

namespace PowerPaimon
{
	Void AboutForm::OnLoad(Object^ sender, EventArgs^ e)
	{
		this->labelTitle->Text = String::Format("{0} v{1}", Util::GetString(IDS_MAIN_TITLE), ProductVersion);
		this->richTextBox1->Text = Util::GetString(IDS_ABOUT_MESSAGE);


	}
	System::Void AboutForm::richTextBox1_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkClickedEventArgs^ e)
	{
		Process::Start(e->LinkText);
	}
	System::Void AboutForm::richTextBox1_Enter(System::Object^ sender, System::EventArgs^ e)
	{
		this->ActiveControl = nullptr;
	}
}
