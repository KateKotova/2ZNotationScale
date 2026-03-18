//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Main_Form.res");
USEFORM("Main_Form_Unit.cpp", Main_Form);
USEUNIT("Notation_Scales_Unit.cpp");
USEFORM("AboutBox_Unit.cpp", AboutBox);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "2-Z : + - * /";
                 Application->HelpFile = "HELP_CALCULATOR.HLP";
                 Application->CreateForm(__classid(TMain_Form), &Main_Form);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
