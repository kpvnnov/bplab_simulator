//---------------------------------------------------------------------------
//$Id: tes_meas.h,v 1.1 2004-03-22 20:21:46 peter Exp $
#ifndef tes_measH
#define tes_measH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:    // IDE-managed Components
        TPanel *Panel1;
        TChart *Chart1;
        TLineSeries *Series1;
        TPanel *Panel2;
        TFilterComboBox *FilterComboBox1;
        TEdit *Edit1;
        TFileListBox *FileListBox1;
        TPanel *Panel3;
        TDriveComboBox *DriveComboBox1;
        TDirectoryListBox *DirectoryListBox1;
        TLineSeries *Series2;
        TLineSeries *Series3;
        void __fastcall FileListBox1Click(TObject *Sender);
        void __fastcall Chart1Zoom(TObject *Sender);
        void __fastcall Chart1Scroll(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
        void LoadFromFile(AnsiString );
        double signal[32767]; //сигнал
        double diff[32768];   //разностный сигнал
        double diff2[32768];  //второй разностный сигнал
        long counter;
        void auto_shift();

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
