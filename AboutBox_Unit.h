//##############################################################################

//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw
// Файл:     A b o t B o x _ U n i t . h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Описание: информация о разработке программы калькулятора.
//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw

//----------------------------------------------------------------------------
#ifndef AboutBox_UnitH
#define AboutBox_UnitH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TImage *ProgramIcon;
        TLabel *ProductName_Label;
        TLabel *Discribe_Label_1;
        TLabel *Discribe_Label_2;
        TLabel *Author_Label;
        TLabel *Discribe_Label_3;
        TPanel *OK_Panel;
        TSpeedButton *OK_SpeedButton;
        void __fastcall OK_SpeedButtonClick(TObject *Sender);
private:
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
