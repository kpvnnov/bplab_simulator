//---------------------------------------------------------------------------
//$Id: tes_meas.cpp,v 1.1 2004-03-22 20:21:46 peter Exp $
#include "..\msp\type_def.h"
#include "algoritm.h"

#include <iostream>
#include <fstream>


#include <vcl.h>
#pragma hdrstop

#include "tes_meas.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"



TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FileListBox1Click(TObject *Sender)
{
    LoadFromFile(FileListBox1->FileName);
}
//---------------------------------------------------------------------------

enum STATES{FIND_HEAD,READ_STRINGS};

void TForm1::LoadFromFile(AnsiString file_name)
{
  // create a read/write file-stream object on tiny char
  // and attach it to the file "filebuf.out"
  char n_f[256];
  char one_str[1024];
  double t;
  counter=0;
  s16 blackman_windows[20];
  STATES state=FIND_HEAD;
  strcpy(n_f,file_name.c_str());
  ifstream in(n_f,ios_base::in );
  // seek to the beginning of the file
  //in.seekg(0);
  Series1->Clear();
  Series2->Clear();
  Series3->Clear();
  while(!in.eof()){
   switch(state){
    case FIND_HEAD:
     in >> one_str;
     if (strstr(one_str,"WAVES"))
       state=READ_STRINGS;
     break;
    case READ_STRINGS:
     in >> t;
     signal[counter]=t;
     Series1->AddXY(counter++,t,"",clTeeColor);
     break;
     }
   }
   if (counter){
    for (int z=0;z<(counter-(24));z++){
     for (int w=0;w<24;w++)
      blackman_windows[w]=(s16)((signal[z+w]/320.0)*65536.0-32768);
     diff[z]=((double)black_men8_12(blackman_windows))*320.0/65536.0;
     Series2->AddXY(z,diff[z],"",clTeeColor);
     diff2[z]=((double)zykov_man_4_12_blackman(blackman_windows))*320.0/65536.0;
     Series3->AddXY(z,diff2[z],"",clTeeColor);
     }
    }
}


void __fastcall TForm1::Chart1Zoom(TObject *Sender)
{
auto_shift();

}
//---------------------------------------------------------------------------





void TForm1::auto_shift()
{
long left,right,bottom,up;
double middle;
double smeshenie;

  right=Chart1->BottomAxis->Maximum;
  left=Chart1->BottomAxis->Minimum;
  bottom=Chart1->LeftAxis->Minimum;
  up=Chart1->LeftAxis->Maximum;

  if ((right-left)<=0) return;

//  middle=right-left;

  //вычисляем среднее по экрану
  middle=0;
  for (int z=left;z<right;z++){
   middle=+signal[z];
   }
  middle/=(right-left);
  smeshenie=signal[left+(right-left)/2]-(bottom+(up-bottom)/2);
   for (int z=0;z<counter;z++){
    Series1->YValues->Value[z]=signal[z]-smeshenie;
    }



}
void __fastcall TForm1::Chart1Scroll(TObject *Sender)
{
auto_shift();        
}
//---------------------------------------------------------------------------

