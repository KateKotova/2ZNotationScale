//##############################################################################

//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw
// Файл:     M a i n _ F o r m _ U n i t . с p p
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Описание: маханизмы элементов главной формы-примера
//           реализация перспективной библиотеки систем счисления.
//mwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmwmw

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Main_Form_Unit.h"
#include "Notation_Scales_Unit.h"
#include "AboutBox_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


//------------------------------------------------------------------------------
// Глобальная переменная: главная форма.
TMain_Form *Main_Form;

//==============================================================================
//  К о н с т р у к т о р   п о   у м о л ч а н и ю .
//------------------------------------------------------------------------------
// Класс:     TMain_Form.
// Описание:  инициализация формы.
// Параметры:
//   Owner - объект-носитель объекта данного класса.
//------------------------------------------------------------------------------
__fastcall TMain_Form :: TMain_Form(TComponent* Owner) :
  // Вызов родительского конструктора.
  TForm(Owner)
{    }


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  fn_uch_Get_MaskEdit_Text_Number_Length.
// Класс:     TMain_Form.
// Описание:  получение длины числа, записанного в строке маскированного поля
//            без учёта символа, занимаемого знаком.
//------------------------------------------------------------------------------
unsigned char __fastcall TMain_Form :: fn_uch_Get_MaskEdit_Text_Number_Length()
{
  // Если в начале строки есть минус. то возвращается длина строки,
  // на один символ меньшая действительной, иначе возвращается
  // действительна ядлина строки.
  if (MaskEdit->Text[1] == ch_Minus)
    return (MaskEdit->Text.Length() - 1);
  else
    return MaskEdit->Text.Length();
} // TMain_Form :: fn_uch_Get_MaskEdit_Text_Number_Length


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  FormCreate.
// Класс:     TMain_Form.
// Описание:  создание формы.
// Параметры:
//   Sender - объект вызова функции.
//------------------------------------------------------------------------------
void __fastcall TMain_Form :: FormCreate(TObject *Sender)
{
  Application->Icon = Main_Form->Icon;
  // Выделение динамической памяти под максимальный порядока числа.
  fn_P_t_Cl_Maximum_Notation_Scale_Number_Order_New();
} // TMain_Form :: FormCreate


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  FormClose.
// Класс:     TMain_Form.
// Описание:  закрытие формы.
// Параметры:
//   Sender - объект вызова функции.
//------------------------------------------------------------------------------
void __fastcall TMain_Form::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // Освобождение памяти из-под максимального порядка.
  delete P_t_Cl_Maximum_Notation_Scale_Number_Order;
  // Указатель ссылается в никуда.
  P_t_Cl_Maximum_Notation_Scale_Number_Order = NULL;

  // Приз удчаном завершении программы, форма закрывается.
  if (CloseQuery())
    Application->Terminate();
} // TMain_Form::FormClose


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  MaskEditKeyPress.
// Класс:     TMain_Form.
// Описание:  ввод символа алфавита или операции с клавиатуры.
// Параметры:
//   Sender - объект высова функции.
//   Key    - символ введённый с клавиатуры.
//------------------------------------------------------------------------------
void __fastcall TMain_Form :: MaskEditKeyPress(TObject *Sender, char &Key)
{
  // Если символ ввода - цифра из алфавита текущей системы счисления,
  // то проводится попытка записи её в строку поля вывода,
  // иниче генерируется операция.
  if (P_t_Cl_Maximum_Notation_Scale_Number_Order->
        F_P_t_Cl_Notation_Scale->pr_t_se_ch_Figures.Contains(Key))
  {
    // Приведение символа к верхнему регистру.
    Key = AnsiUpperCase(Key)[1];

    // Если заданный символ входит во множество симальных представлений
    // цифр алфавита текущей системы счисления и в строке есть место
    // для вставки символа (строка не достигла длины максимального числа
    // в данной системе счисления), то он вставляется в конец строки,
    // или же вводится новое число, для которого записывается первый символ,
    if (P_t_Cl_Maximum_Notation_Scale_Number_Order->
          F_P_t_Cl_Notation_Scale->pr_t_se_ch_Figures.Contains(Key) &&
        ((fn_uch_Get_MaskEdit_Text_Number_Length() <
          P_t_Cl_Maximum_Notation_Scale_Number_Order->F_P_t_Cl_Notation_Scale->
            pr_uch_Number_Order_Length) ||
          b_Input_Firt_Key))
    {
      // Если вводится первый символ нового числа, то строка опустошается.
      if (b_Input_Firt_Key)
      {
        MaskEdit->Text = "";
        b_Input_Firt_Key = false;
      } // if

      // Число не должно содержать ведущие нули.
      if (MaskEdit->Text == '0')
        MaskEdit->Text = Key;

      else
        // Вставка символа в конец строки.
        MaskEdit->Text = MaskEdit->Text + Key;
    } // if

    // Возврат из функции.
    return;
  } // if

  // Проверка текущей операции
  switch (Key)
  {
    // Унарные операции.
    // Нажат <BackSpace>.
    case '\b' :
      // Если длина числа, записанного в строке маскированного поля
      // без учёта символа, занимаемого знаком, равна одному,
      // то это значит, что удаляется последний единственный
      // значащий разряд число, то есть число обнуляется.
      // Число обнуляется также, если в строке вывода
      // содержится сообщение об ошибке.
       if ((fn_uch_Get_MaskEdit_Text_Number_Length() == 1) ||
           (MaskEdit->Text.UpperCase() ==
            as_Overflow_Error_String.UpperCase())          ||
           (MaskEdit->Text.UpperCase() ==
            as_Maximum_Excess_Error_String.UpperCase()))
        MaskEdit->Text = '0';

      // Иначе удаляется последний символ с конца - строка усекается.
      else
        MaskEdit->Text = MaskEdit->Text.SetLength(MaskEdit->Text.Length() - 1);
    break;

    // Нажато <Delete>.
    case '.' :
      // Выполнение операции обнуления.
      MaskEdit->Text = '0';
    break;

    // Бинарные операции и операция равенства.
    default:
    {
      // Выполняется предыдущая операция.
      switch (ch_Current_Operation_Type_Key)
      {
        // Нажат <Enter> или '='.
        case '\r': ch_Current_Operation_Type_Key = '=';
        case '=' : 
          // Выполнение операции равенства.
          MaskEdit->Text =
            fn_as_Calculator_Operation(i_EQUALITY, MaskEdit->Text,
                                       t_en_i_Current_Notation_Scale_Base);
        break;


        // Нажат '+'.
        case '+' :
          // Выполнение операции cложения.
          MaskEdit->Text =
            fn_as_Calculator_Operation(i_ADDING, MaskEdit->Text,
                                       t_en_i_Current_Notation_Scale_Base);
        break;

        // Нажат '-'.
        case '-' :
          // Выполнение операции вычитания.
          MaskEdit->Text =
            fn_as_Calculator_Operation(i_SUBTRACTION, MaskEdit->Text,
                                       t_en_i_Current_Notation_Scale_Base);
        break;

        // Нажат '*'.
        case '*':
          // Выполнение операции умножения.
          MaskEdit->Text =
            fn_as_Calculator_Operation(i_MULTIPLYING, MaskEdit->Text,
                                       t_en_i_Current_Notation_Scale_Base);
        break;

        // Нажат '/'.
        case '/':
          // Выполнение операции деления.
          MaskEdit->Text =
            fn_as_Calculator_Operation(i_DIVISION, MaskEdit->Text,
                                       t_en_i_Current_Notation_Scale_Base);
        break;

        default: ;
      } // switch (ch_Current_Operation_Type_Key)

    // Запоминается новая операция как текущая.
    ch_Current_Operation_Type_Key = Key;
    } // default
  } // switch (Key)
} // TMain_Form :: MaskEditKeyPress


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  fn_Set_SpeedButton_Enable.
// Класс:     TMain_Form.
// Описание:  установка доступности кнопки в зависимости от того,
//            входит ли их символы в алфавит текущей системы счисления,
//            основываясь на свойстве Tag, куда автор программы записал
//            числовые эквиваленты отображаемых цифр,
//            так для алфавита всех систем счисления
//            от двоичной до тридцати пятиричной в Tag записаны номера кнопок
//            от нуля до тридцати черырёх.
// Параметры:
//   SpeedButton - текщая кнопка.
// Результат: ответ на вопрос: определена ли кнопка как доступная.
//------------------------------------------------------------------------------
bool __fastcall TMain_Form :: fn_b_Set_SpeedButton_Enable
  (TSpeedButton *SpeedButton)
{
  if (SpeedButton->Tag < t_en_i_Current_Notation_Scale_Base)
    SpeedButton->Enabled = true;
  else
    SpeedButton->Enabled = false;

  // Возврат прзнака доступности текущей кнопки.
  return SpeedButton->Enabled;
} // TMain_Form :: fn_b_Set_SpeedButton_Enable


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  fn_Set_SpeedButtons_Enable.
// Класс:     TMain_Form.
// Описание:  установка доступности всех кнопки в зависимости от того,
//            входит ли их символы в алфавит текущей системы счисления.
//------------------------------------------------------------------------------
void __fastcall TMain_Form :: fn_Set_SpeedButtons_Enable()
{
  // Проверка каждой кнопки.
  fn_b_Set_SpeedButton_Enable(SpeedButton2);
  fn_b_Set_SpeedButton_Enable(SpeedButton3);
  fn_b_Set_SpeedButton_Enable(SpeedButton4);
  fn_b_Set_SpeedButton_Enable(SpeedButton5);
  fn_b_Set_SpeedButton_Enable(SpeedButton6);
  fn_b_Set_SpeedButton_Enable(SpeedButton7);
  fn_b_Set_SpeedButton_Enable(SpeedButton8);
  fn_b_Set_SpeedButton_Enable(SpeedButton9);
  fn_b_Set_SpeedButton_Enable(SpeedButton10);
  fn_b_Set_SpeedButton_Enable(SpeedButton11);
  fn_b_Set_SpeedButton_Enable(SpeedButton12);
  fn_b_Set_SpeedButton_Enable(SpeedButton13);
  fn_b_Set_SpeedButton_Enable(SpeedButton14);
  fn_b_Set_SpeedButton_Enable(SpeedButton15);
  fn_b_Set_SpeedButton_Enable(SpeedButton16);
  fn_b_Set_SpeedButton_Enable(SpeedButton17);
  fn_b_Set_SpeedButton_Enable(SpeedButton18);
  fn_b_Set_SpeedButton_Enable(SpeedButton19);
  fn_b_Set_SpeedButton_Enable(SpeedButton20);
  fn_b_Set_SpeedButton_Enable(SpeedButton21);
  fn_b_Set_SpeedButton_Enable(SpeedButton22);
  fn_b_Set_SpeedButton_Enable(SpeedButton23);
  fn_b_Set_SpeedButton_Enable(SpeedButton24);
  fn_b_Set_SpeedButton_Enable(SpeedButton25);
  fn_b_Set_SpeedButton_Enable(SpeedButton26);
  fn_b_Set_SpeedButton_Enable(SpeedButton27);
  fn_b_Set_SpeedButton_Enable(SpeedButton28);
  fn_b_Set_SpeedButton_Enable(SpeedButton29);
  fn_b_Set_SpeedButton_Enable(SpeedButton30);
  fn_b_Set_SpeedButton_Enable(SpeedButton31);
  fn_b_Set_SpeedButton_Enable(SpeedButton32);
  fn_b_Set_SpeedButton_Enable(SpeedButton33);
  fn_b_Set_SpeedButton_Enable(SpeedButton34);
} // TMain_Form :: fn_Set_SpeedButtons_Enable


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  Notation_Scale_ComboBoxChange.
// Класс:     TMain_Form.
// Описание:  изменение системы счисления.
// Параметры:
//   Sender - объект высова функции.
//------------------------------------------------------------------------------
void __fastcall TMain_Form :: Notation_Scale_ComboBoxChange(TObject *Sender)
{
  // Число из поля системы счисления.
  unsigned char uch_Notation_Scale_ComboBox_Text_Number;

  // Заголовок вывода сообщения об ошибке.
  char *as_Error_MessageBox_Title = " Ошибка ввода!\0";

  try
  {
    // Перевод строки, где удаляются ведущие и завершающие пробелы в число.
    uch_Notation_Scale_ComboBox_Text_Number =
      StrToInt(Notation_Scale_ComboBox->Text.Trim());

    if (uch_Notation_Scale_ComboBox_Text_Number < 2)
    {
      uch_Notation_Scale_ComboBox_Text_Number = 2;
      Notation_Scale_ComboBox->Text = " 2";

      Application->MessageBox
        ("Основание системы счисления, меньшее минимального, исправлено!\0",
         as_Error_MessageBox_Title, MB_OK + MB_ICONWARNING);
    } // if

    else
      if (uch_Notation_Scale_ComboBox_Text_Number > uch_All_Figures_Number - 1)
      {
        uch_Notation_Scale_ComboBox_Text_Number = uch_All_Figures_Number - 1;
        Notation_Scale_ComboBox->Text = IntToStr(uch_All_Figures_Number - 1);

        Application->MessageBox
          ("Основание системы счисления, большее максимального, исправлено!\0",
           as_Error_MessageBox_Title, MB_OK + MB_ICONWARNING);
      } // if
  } // try

  // Перехват всех исключений.
  catch(...)
  {
    uch_Notation_Scale_ComboBox_Text_Number = 10;
    Notation_Scale_ComboBox->Text = "10";
      
    Application->MessageBox
      ("Некорректное основание системы счисления исправлено!\0",
       as_Error_MessageBox_Title, MB_OK + MB_ICONWARNING);
  } // catch(EConvertError&)

  // Проведелние операции перевода в другую систему счисления:
  // новая система счисления извлекается из строки поля,
  // где удаляется ведущий пробел.
  MaskEdit->Text =
    fn_as_Calculator_Operation
      (i_SET_NOTATION_SCALE,
       MaskEdit->Text, (T_en_i_Figure) uch_Notation_Scale_ComboBox_Text_Number);

  // Установка доступности всех кнопки в зависимости от того,
  // входит ли их символы в алфавит текущей системы счисления.
  fn_Set_SpeedButtons_Enable();

  // Если будет вводиться число, то оно будет новым, значит,
  // оно будет начинаться с первого символа.
  b_Input_Firt_Key = true;
} // TMain_Form :: Notation_Scale_ComboBoxChange


//==============================================================================
// Ф у н к ц и я.
//------------------------------------------------------------------------------
// Название:  Notation_Scale_ComboBoxChange.
// Класс:     TMain_Form.
// Описание:  нажатие на кнопку, фнкция которой определяется свойством Tag.
// Параметры:
//   SpeedButton - текущая нажатая кнопка.
//------------------------------------------------------------------------------
void __fastcall TMain_Form :: SpeedButtonClick(TSpeedButton *SpeedButton)
{
  // Символ, инициализирующий выполнение операции данной кнопки.
  char ch_SpeedButton_Key;

  // Проверка свойства Tag кнопки.
  switch (SpeedButton->Tag)
  {
    // Равенство, обнуление, удаление последнего символа строки.
    // После генерирования этих операций будет вводиться
    // первый символ нового числа.
    case 200 : ch_SpeedButton_Key = '\r'; b_Input_Firt_Key = true; break;
    case 201 : ch_SpeedButton_Key = '.';  b_Input_Firt_Key = true; break;
    case 202 : ch_SpeedButton_Key = '\b'; b_Input_Firt_Key = true; break;

    // Сложение, вычитание, умножение, деление.
    case 101 : ch_SpeedButton_Key = '+';  b_Input_Firt_Key = true; break;
    case 102 : ch_SpeedButton_Key = '-';  b_Input_Firt_Key = true; break;
    case 103 : ch_SpeedButton_Key = '*';  b_Input_Firt_Key = true; break;
    case 104 : ch_SpeedButton_Key = '/';  b_Input_Firt_Key = true; break;

    // Цифры из алфавитов всех систем счисления.
    case   0 : ch_SpeedButton_Key = '0';  break;
    case   1 : ch_SpeedButton_Key = '1';  break;
    case   2 : ch_SpeedButton_Key = '2';  break;
    case   3 : ch_SpeedButton_Key = '3';  break;
    case   4 : ch_SpeedButton_Key = '4';  break;
    case   5 : ch_SpeedButton_Key = '5';  break;
    case   6 : ch_SpeedButton_Key = '6';  break;
    case   7 : ch_SpeedButton_Key = '7';  break;
    case   8 : ch_SpeedButton_Key = '8';  break;
    case   9 : ch_SpeedButton_Key = '9';  break;
    case  10 : ch_SpeedButton_Key = 'A';  break;
    case  11 : ch_SpeedButton_Key = 'B';  break;
    case  12 : ch_SpeedButton_Key = 'C';  break;
    case  13 : ch_SpeedButton_Key = 'D';  break;
    case  14 : ch_SpeedButton_Key = 'E';  break;
    case  15 : ch_SpeedButton_Key = 'F';  break;
    case  16 : ch_SpeedButton_Key = 'G';  break;
    case  17 : ch_SpeedButton_Key = 'H';  break;
    case  18 : ch_SpeedButton_Key = 'I';  break;
    case  19 : ch_SpeedButton_Key = 'J';  break;
    case  20 : ch_SpeedButton_Key = 'K';  break;
    case  21 : ch_SpeedButton_Key = 'L';  break;
    case  22 : ch_SpeedButton_Key = 'M';  break;
    case  23 : ch_SpeedButton_Key = 'N';  break;
    case  24 : ch_SpeedButton_Key = 'O';  break;
    case  25 : ch_SpeedButton_Key = 'P';  break;
    case  26 : ch_SpeedButton_Key = 'Q';  break;
    case  27 : ch_SpeedButton_Key = 'R';  break;
    case  28 : ch_SpeedButton_Key = 'S';  break;
    case  29 : ch_SpeedButton_Key = 'T';  break;
    case  30 : ch_SpeedButton_Key = 'U';  break;
    case  31 : ch_SpeedButton_Key = 'V';  break;
    case  32 : ch_SpeedButton_Key = 'W';  break;
    case  33 : ch_SpeedButton_Key = 'X';  break;
    case  34 : ch_SpeedButton_Key = 'Y';  break;

    // Ранее не упомянутая операция смены знака.
    case 100 :
    {
      // Если строка не содержит нуль или сообщение об ошибке,
      // то знак учитывается , иначе - нет.
      if ((MaskEdit->Text != '0') &&
          (MaskEdit->Text.UpperCase() !=
           as_Overflow_Error_String.UpperCase()) &&
          (MaskEdit->Text.UpperCase() !=
           as_Maximum_Excess_Error_String.UpperCase()))
      {
        // Если первый символ строки вывода - не минус,
        // то минус записывается в начало строки.
        if (MaskEdit->Text[1] != '-')
          // Дополнение строки с начала на одним символом.
          MaskEdit->Text = (AnsiString) "-" + MaskEdit->Text;

        // Иначе минус удаляется, строка сдвигается влево,
        // все остальные её символы получают декременты индексов размещения.
        else
          // Усечение строки с начала на один символ.
          MaskEdit->Text =
            MaskEdit->Text.SubString(2, MaskEdit->Text.Length() - 1);
      } // if
    } // case 100
    break;
  } // switch (SpeedButton->Tag)

  // Если кнопка не означает операцию смены знака, ранее определённую,
  // то опрация вызывается через определённый только что символ клавиатуры.
  if (SpeedButton->Tag != 100)
    MaskEditKeyPress(Main_Form, ch_SpeedButton_Key);
} // TMain_Form :: SpeedButtonClick


//==============================================================================
// Ф у н к ц и и.
//------------------------------------------------------------------------------
// Названия:  ...SpeedButtonClick.
// Класс:     TMain_Form.
// Описание:  нажатие на кнопки,
//            вызов выполнения операции посредствам свойства Tag.
// Параметры:
//   Sender - текущая нажатая кнопка.
//------------------------------------------------------------------------------
// Равенство, обнуление, удаление последнего символа строки.
void __fastcall TMain_Form :: EQUALITY_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(EQUALITY_SpeedButton);  }

void __fastcall TMain_Form :: ZEROIZE_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(ZEROIZE_SpeedButton);  }

void __fastcall TMain_Form :: BACKSPACE_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(BACKSPACE_SpeedButton);  }

//------------------------------------------------------------------------------
// Смена знака, сложение, вычитание, умножение, деление.
void __fastcall TMain_Form :: Sign_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(Sign_SpeedButton);  }

void __fastcall TMain_Form :: ADDING_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(ADDING_SpeedButton);  }

void __fastcall TMain_Form :: SUBTRACTION_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(SUBTRACTION_SpeedButton);  }

void __fastcall TMain_Form :: MULTIPLYING_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(MULTIPLYING_SpeedButton);  }

void __fastcall TMain_Form :: DIVISION_SpeedButtonClick(TObject *Sender)
{  SpeedButtonClick(DIVISION_SpeedButton);  }

//------------------------------------------------------------------------------
// Цифры из алфавитов всех систем счисления.

void __fastcall TMain_Form :: SpeedButton0Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton0);  }

void __fastcall TMain_Form :: SpeedButton1Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton1);  }

void __fastcall TMain_Form :: SpeedButton2Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton2);  }

void __fastcall TMain_Form :: SpeedButton3Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton3);  }

void __fastcall TMain_Form :: SpeedButton4Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton4);  }

void __fastcall TMain_Form :: SpeedButton5Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton5);  }

void __fastcall TMain_Form :: SpeedButton6Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton6);  }

void __fastcall TMain_Form :: SpeedButton7Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton7);  }

void __fastcall TMain_Form :: SpeedButton8Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton8);  }

void __fastcall TMain_Form :: SpeedButton9Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton9);  }

void __fastcall TMain_Form :: SpeedButton10Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton10);  }

void __fastcall TMain_Form :: SpeedButton11Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton11);  }

void __fastcall TMain_Form :: SpeedButton12Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton12);  }

void __fastcall TMain_Form :: SpeedButton13Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton13);  }

void __fastcall TMain_Form :: SpeedButton14Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton14);  }

void __fastcall TMain_Form :: SpeedButton15Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton15);  }

void __fastcall TMain_Form :: SpeedButton16Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton16);  }

void __fastcall TMain_Form :: SpeedButton17Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton17);  }

void __fastcall TMain_Form :: SpeedButton18Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton18);  }

void __fastcall TMain_Form :: SpeedButton19Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton19);  }

void __fastcall TMain_Form :: SpeedButton20Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton20);  }

void __fastcall TMain_Form :: SpeedButton21Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton21);  }

void __fastcall TMain_Form :: SpeedButton22Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton22);  }

void __fastcall TMain_Form :: SpeedButton23Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton23);  }

void __fastcall TMain_Form :: SpeedButton24Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton24);  }

void __fastcall TMain_Form :: SpeedButton25Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton25);  }

void __fastcall TMain_Form :: SpeedButton26Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton26);  }

void __fastcall TMain_Form :: SpeedButton27Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton27);  }

void __fastcall TMain_Form :: SpeedButton28Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton28);  }

void __fastcall TMain_Form :: SpeedButton29Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton29);  }

void __fastcall TMain_Form :: SpeedButton30Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton30);  }

void __fastcall TMain_Form :: SpeedButton31Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton31);  }

void __fastcall TMain_Form :: SpeedButton32Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton32);  }

void __fastcall TMain_Form :: SpeedButton33Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton33);  }

void __fastcall TMain_Form :: SpeedButton34Click(TObject *Sender)
{  SpeedButtonClick(SpeedButton34);  }


//==============================================================================
// Ф у н к ц и и.
//------------------------------------------------------------------------------
// Названия:  About_SpeedButtonClick.
// Класс:     TMain_Form.
// Описание:  вызов окна информации о программе.
// Параметры:
//   Sender - текущая нажатая кнопка.
//------------------------------------------------------------------------------
void __fastcall TMain_Form::About_SpeedButtonClick(TObject *Sender)
{
  About_SpeedButton->Enabled = false;
  AboutBox->ShowModal();
} // TMain_Form::About_SpeedButtonClick


//==============================================================================
// Ф у н к ц и и.
//------------------------------------------------------------------------------
// Названия:  Help_SpeedButtonClick.
// Класс:     TMain_Form.
// Описание:  вызов окна справки.
// Параметры:
//   Sender - текущая нажатая кнопка.
//------------------------------------------------------------------------------
void __fastcall TMain_Form::Help_SpeedButtonClick(TObject *Sender)
{
  Application->HelpFile = "HELP_CALCULATOR.hlp";
  Application->HelpContext(1);
} // TMain_Form::Help_SpeedButtonClick

