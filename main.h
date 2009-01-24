//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TF : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer;
        TMainMenu *MainMenu;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N4;
        TStatusBar *SBar;
        TTimer *tmrInf;
        TRichEdit *Inf;
        TShape *Shape;
        TPanel *pAll;
        TPanel *pScr;
        TTimer *tmrSlide;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall N4Click(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall tmrInfTimer(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall ShapeMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall tmrSlideTimer(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall N8Click(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall N10Click(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        __fastcall TF(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TF *F;
//---------------------------------------------------------------------------
#endif
