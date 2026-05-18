#include "pch.h"
#include "MainWin.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    SwarmGUI::MainWin form;
    Application::Run(% form);

    return 0;
}