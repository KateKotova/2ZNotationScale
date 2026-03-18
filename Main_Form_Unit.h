//##############################################################################

//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw
// Файл:     M a i n _ F o r m _ U n i t . h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Описание: содержание элементов главной формы-примера
//           реализации перспективной библиотеки систем счисления.
//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw

#ifndef Main_Form_UnitH
#define Main_Form_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>

//---------------------------------------------------------------------------
// Класс: главна¤ форма.
class TMain_Form : public TForm
{
__published:	// IDE-managed Components
        TMaskEdit *MaskEdit;
        TComboBox *Notation_Scale_ComboBox;

        TSpeedButton *ZEROIZE_SpeedButton;
        TSpeedButton *BACKSPACE_SpeedButton;
        TSpeedButton *ADDING_SpeedButton;
        TSpeedButton *SUBTRACTION_SpeedButton;
        TSpeedButton *MULTIPLYING_SpeedButton;
        TSpeedButton *DIVISION_SpeedButton;
        TSpeedButton *EQUALITY_SpeedButton;

        TSpeedButton *Sign_SpeedButton;
        
        TSpeedButton *SpeedButton0;  TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;  TSpeedButton *SpeedButton3;
        TSpeedButton *SpeedButton4;  TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton6;  TSpeedButton *SpeedButton7;
        TSpeedButton *SpeedButton8;  TSpeedButton *SpeedButton9;
        TSpeedButton *SpeedButton10; TSpeedButton *SpeedButton11;
        TSpeedButton *SpeedButton12; TSpeedButton *SpeedButton13;
        TSpeedButton *SpeedButton14; TSpeedButton *SpeedButton15;
        TSpeedButton *SpeedButton16; TSpeedButton *SpeedButton17;
        TSpeedButton *SpeedButton18; TSpeedButton *SpeedButton19;
        TSpeedButton *SpeedButton20; TSpeedButton *SpeedButton21;
        TSpeedButton *SpeedButton22; TSpeedButton *SpeedButton23;
        TSpeedButton *SpeedButton24; TSpeedButton *SpeedButton25;
        TSpeedButton *SpeedButton26; TSpeedButton *SpeedButton27;
        TSpeedButton *SpeedButton28; TSpeedButton *SpeedButton29;
        TSpeedButton *SpeedButton30; TSpeedButton *SpeedButton31;
        TSpeedButton *SpeedButton32; TSpeedButton *SpeedButton33;
        TSpeedButton *SpeedButton34;

        TPanel *Figures_Panel;
        TPanel *Options_Panel;

        TImage *Figures_Image;
        TImage *Operations_Image;

        TBevel *Bevel1;
        TBevel *Bevel2;
        TBevel *Bevel3;
        TBevel *Bevel4;
        TBevel *Bevel5;
        TPanel *Information_Panel;
        TBevel *Bevel6;
        TImage *Information_Image;
        TSpeedButton *Help_SpeedButton;
        TSpeedButton *About_SpeedButton;

        // Функция: ввод символа алфавита или операции с клавиатуры.
        void __fastcall MaskEditKeyPress(TObject *Sender, char &Key);
        
        // Функция: оздание формы.
        void __fastcall FormCreate(TObject *Sender);

        // Функция: изменение системы счислени¤.
        void __fastcall Notation_Scale_ComboBoxChange(TObject *Sender);

        // Функции: выполнение операций.
        // Функции: равенство, обнуление, удаление последнего символа строки.
        void __fastcall EQUALITY_SpeedButtonClick(TObject *Sender);
        void __fastcall ZEROIZE_SpeedButtonClick(TObject *Sender);
        void __fastcall BACKSPACE_SpeedButtonClick(TObject *Sender);

        // Функции: сложение, вычитание, умножение, деление.
        void __fastcall Sign_SpeedButtonClick(TObject *Sender);
        void __fastcall ADDING_SpeedButtonClick(TObject *Sender);
        void __fastcall SUBTRACTION_SpeedButtonClick(TObject *Sender);
        void __fastcall MULTIPLYING_SpeedButtonClick(TObject *Sender);
        void __fastcall DIVISION_SpeedButtonClick(TObject *Sender);

        // Функции: ввод цифры из алфавитов всех систем счислени¤.
        void __fastcall SpeedButton0Click(TObject  *Sender);
        void __fastcall SpeedButton1Click(TObject  *Sender);
        void __fastcall SpeedButton2Click(TObject  *Sender);
        void __fastcall SpeedButton3Click(TObject  *Sender);
        void __fastcall SpeedButton4Click(TObject  *Sender);
        void __fastcall SpeedButton5Click(TObject  *Sender);
        void __fastcall SpeedButton6Click(TObject  *Sender);
        void __fastcall SpeedButton7Click(TObject  *Sender);
        void __fastcall SpeedButton8Click(TObject  *Sender);
        void __fastcall SpeedButton9Click(TObject  *Sender);
        void __fastcall SpeedButton11Click(TObject *Sender);
        void __fastcall SpeedButton12Click(TObject *Sender);
        void __fastcall SpeedButton13Click(TObject *Sender);
        void __fastcall SpeedButton14Click(TObject *Sender);
        void __fastcall SpeedButton15Click(TObject *Sender);
        void __fastcall SpeedButton16Click(TObject *Sender);
        void __fastcall SpeedButton17Click(TObject *Sender);
        void __fastcall SpeedButton18Click(TObject *Sender);
        void __fastcall SpeedButton19Click(TObject *Sender);
        void __fastcall SpeedButton21Click(TObject *Sender);
        void __fastcall SpeedButton22Click(TObject *Sender);
        void __fastcall SpeedButton23Click(TObject *Sender);
        void __fastcall SpeedButton24Click(TObject *Sender);
        void __fastcall SpeedButton25Click(TObject *Sender);
        void __fastcall SpeedButton26Click(TObject *Sender);
        void __fastcall SpeedButton27Click(TObject *Sender);
        void __fastcall SpeedButton28Click(TObject *Sender);
        void __fastcall SpeedButton29Click(TObject *Sender);
        void __fastcall SpeedButton30Click(TObject *Sender);
        void __fastcall SpeedButton31Click(TObject *Sender);
        void __fastcall SpeedButton32Click(TObject *Sender);
        void __fastcall SpeedButton33Click(TObject *Sender);
        void __fastcall SpeedButton34Click(TObject *Sender);
        void __fastcall SpeedButton10Click(TObject *Sender);
        void __fastcall SpeedButton20Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall About_SpeedButtonClick(TObject *Sender);
        void __fastcall Help_SpeedButtonClick(TObject *Sender);

private:	// User declarations

public:		// User declarations
        __fastcall TMain_Form(TComponent* Owner);

        // Функция: получение длины числа, записанного в строке
        // маскированного пол¤ без учЄта символа, занимаемого знаком.
        unsigned char __fastcall fn_uch_Get_MaskEdit_Text_Number_Length();

        // Функция: установка доступности кнопки в зависимости от того,
        // входит ли их символы в алфавит текущей системы счислени¤.
        bool __fastcall fn_b_Set_SpeedButton_Enable(TSpeedButton *SpeedButton);

        // Функция: установка доступности всех кнопки в зависимости от того,
        // входит ли их символы в алфавит текущей системы счислени¤.
        void __fastcall fn_Set_SpeedButtons_Enable();

        // Функция: нажатие на кнопку,
        // фнкция которой определ¤етс¤ свойством Tag.
        void __fastcall SpeedButtonClick(TSpeedButton *SpeedButton);

}; // TMain_Form

//---------------------------------------------------------------------------
// Внешняя переменная: объект класса главной формы.
extern PACKAGE TMain_Form *Main_Form;
//---------------------------------------------------------------------------
#endif


