#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Snake;
//+------------------------------------------------------------------------------------------------------------------+
//|                                                                                                                  |
//+------------------------------------------------------------------------------------------------------------------+
[STAThreadAttribute]
int main() {
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    MyForm form;
    Application::Run(% form);

    return 0;
}
