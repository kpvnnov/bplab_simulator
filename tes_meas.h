//---------------------------------------------------------------------------
//$Id: tes_meas.h,v 1.3 2004-03-24 17:33:42 peter Exp $
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
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:    // IDE-managed Components
        TPanel *Panel2;
        TFilterComboBox *FilterComboBox1;
        TEdit *Edit1;
        TFileListBox *FileListBox1;
        TPanel *Panel3;
        TDriveComboBox *DriveComboBox1;
        TDirectoryListBox *DirectoryListBox1;
        TSplitter *Splitter2;
        TSplitter *Splitter1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TPanel *Panel1;
        TChart *Chart1;
        TLineSeries *Series1;
        TLineSeries *Series2;
        TLineSeries *Series3;
        TPointSeries *Series4;
        TPointSeries *Series5;
        TPointSeries *Series7;
        TPointSeries *Series8;
        TTabSheet *TabSheet2;
        TPanel *Panel4;
        TChart *Chart2;
        TLineSeries *Series6;
        void __fastcall FileListBox1Click(TObject *Sender);
        void __fastcall Chart1Zoom(TObject *Sender);
        void __fastcall Chart1Scroll(TObject *Sender);
        void __fastcall Chart2Zoom(TObject *Sender);
        void __fastcall Chart2Scroll(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
        void LoadFromFile(AnsiString );
        double signal_d[32767]; //сигнал
        s16 signal_thread_win[32767]; //сигнал с вычтенным тредом
        s16 diff_win[32768];   //разностный сигнал
        s16 diff2_win[32768];  //второй разностный сигнал
        long counter;
        void auto_shift();
        void auto_shift1();
        MAXIMUM maximum_win[3000];

        u16 number_maximum_win;
        internal_error(INTERNAL_ERROR);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
