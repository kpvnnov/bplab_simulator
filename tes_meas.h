//---------------------------------------------------------------------------
//$Id: tes_meas.h,v 1.2 2004-03-23 17:55:50 peter Exp $
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
        TSplitter *Splitter2;
        TSplitter *Splitter1;
        TPointSeries *Series4;
        TPointSeries *Series5;
        TPointSeries *Series7;
        TPointSeries *Series8;
        TChart *Chart1;
        void __fastcall FileListBox1Click(TObject *Sender);
        void __fastcall Chart1Zoom(TObject *Sender);
        void __fastcall Chart1Scroll(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
        void LoadFromFile(AnsiString );
        double signal_d[32767]; //сигнал
        s16 signal_thread[32767]; //сигнал с вычтенным тредом
        s16 diff[32768];   //разностный сигнал
        s16 diff2[32768];  //второй разностный сигнал
        long counter;
        void auto_shift();
        MAXIMUM maximum[3000];
        u16 number_maximum;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
