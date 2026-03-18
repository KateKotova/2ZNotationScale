//##############################################################################

//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw
// Файл:     A b o t B o x _ U n i t . с p p
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Описание: информация о разработке программы калькулятора.
//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AboutBox_Unit.h"
#include "Main_Form_Unit.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"


TAboutBox *AboutBox;

//==============================================================================
//  К о н с т р у к т о р   п о   у м о л ч а н и ю .
//------------------------------------------------------------------------------
// Класс:     TAboutBox.
// Описание:  инициализация формы.
// Параметры:
//   AOwner - объект-носитель объекта данного класса.
//------------------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner) :
  // Вызов родительского конструктора.
  TForm(AOwner)
{    }


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  SpeedButton1Click.
// Класс:     TAboutBox.
// Описание:  закрытие формы.
//------------------------------------------------------------------------------
void __fastcall TAboutBox::OK_SpeedButtonClick(TObject *Sender)
{
  Main_Form->About_SpeedButton->Enabled = true;
  // mrOK == 1 - признак закрытия формы.
  AboutBox->ModalResult = 1;
} // TAboutBox::SpeedButton1Click

