//---------------------------------------------------------------------------
//$Id: tes_meas.cpp,v 1.2 2004-03-23 17:55:50 peter Exp $


// сдвиг фазы фильтров
#define SHIFT_DIFF      (6+4)
#define SHIFT_DIFF2     (8)





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

s16 signal[32767]; //сигнал


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
  u16 interval_analisys;
  s16 blackman_windows[200];
  u16 pos_diff_2[3];
  char temp[128];
  number_maximum=0;
  STATES state=FIND_HEAD;
  strcpy(n_f,file_name.c_str());
  ifstream in(n_f,ios_base::in );
  // seek to the beginning of the file
  //in.seekg(0);
  Series1->Clear();
  Series2->Clear();
  Series3->Clear();
  Series4->Clear();
  Series5->Clear();
  //Series6->Clear();
  Series7->Clear();
  Series8->Clear();
  while(!in.eof()){
   switch(state){
    case FIND_HEAD:
     in >> one_str;
     if (strstr(one_str,"WAVES"))
       state=READ_STRINGS;
     break;
    case READ_STRINGS:
     in >> t;
     signal_d[counter]=t;
     signal[counter]=s16((((double)t)/320.0)*65536.0-32768);
     Series1->AddXY(counter++,t,"",clTeeColor);
     break;
     }
   }

   if (counter){
    for (int z=0;z<(counter-(24));z++){
     diff[z]=black_men8_12(&signal[z]);
     Series2->AddXY(z+SHIFT_DIFF,((double)diff[z])*320.0/65536.0,"",clTeeColor);

     diff2[z]=zykov_man_4_12_blackman(&signal[z]);
     Series3->AddXY(z+SHIFT_DIFF2,((double)diff2[z])*320.0/65536.0,"",clTeeColor);
     }
    // поиск максимумов по первой производной diff
    interval_analisys=24;
    for (int z=0;z<(counter-interval_analisys);z++){
     if (find_max(&diff[z], interval_analisys)==(interval_analisys/2)){
      Series4->AddXY(z+SHIFT_DIFF+(interval_analisys/2),((double)diff[z+(interval_analisys/2)])*320.0/65536.0,"",clTeeColor);
      }
     }
    // поиск максимумов по второй производной diff2
    interval_analisys=24;
    for (int z=0;z<(counter-interval_analisys);z++){
     if (find_max(&diff2[z], interval_analisys)==(interval_analisys/2)){
      Series5->AddXY(z+SHIFT_DIFF2+(interval_analisys/2),((double)diff2[z+(interval_analisys/2)])*320.0/65536.0,"",clTeeColor);
      maximum[number_maximum].point_max_diff2=z+SHIFT_DIFF2+(interval_analisys/2);
      maximum[number_maximum].pulse_begin=signal[maximum[number_maximum].point_max_diff2];
      maximum[number_maximum].amplitude_diff2=diff2[z+(interval_analisys/2)];
      maximum[number_maximum].amplitude_diff2_ok=0;
      maximum[number_maximum].amplitude[0]=0;
      maximum[number_maximum].amplitude[1]=0;
      maximum[number_maximum].amplitude[2]=0;
      //Series7->AddXY(maximum[number_maximum].point_max,((double)signal[maximum[number_maximum].point_max])*320.0/65536.0,"",clTeeColor);
      number_maximum++;

      }
     }

    //if (number_maximum>10) number_maximum=10;
    for (int z=0;z<(number_maximum-1);z++){
     pos_diff_2[0]=z;
     pos_diff_2[1]=z+1;
     sprintf(temp,"%2.3lf ",((double)compute_amplitude(maximum,pos_diff_2))*320.0/65536.0);
     Series8->AddXY(maximum[z].point_max_diff2,((double)signal[maximum[z].point_max_diff2])*320.0/65536.0,temp,clTeeColor);
     }
    //добавляем "последний максимум
    //Series8->AddXY(maximum[number_maximum-1].point_max_diff2,((double)signal[maximum[number_maximum-1].point_max_diff2])*320.0/65536.0,"0",clTeeColor);

    auto_shift();
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
int z,y;
  right=Chart1->BottomAxis->Maximum;
  left=Chart1->BottomAxis->Minimum;
  bottom=Chart1->LeftAxis->Minimum;
  up=Chart1->LeftAxis->Maximum;

  if ((right-left)<=0) return;

//  middle=right-left;

  //вычисляем среднее по экрану
  middle=0;
  for (int z=left;z<right;z++){
   middle=+signal_d[z];
   }
  middle/=(right-left);
  smeshenie=signal_d[left+(right-left)/2]-(bottom+(up-bottom)/2);
   for (z=0;z<counter;z++){
    Series1->YValues->Value[z]=signal_d[z]-smeshenie;
    }
   z=0; //продяковый номер в массиве максимумов
   y=0; // порядковый номер реальных максимумов
//   while(z<number_maximum){
   while(z< Series8->Count()){
    //Series7->YValues->Value[z]=signal_d[maximum[z].point_max]-smeshenie;
    Series8->XValues->Value[y]=maximum[z].point_max_diff2;
    Series8->YValues->Value[y]=signal_d[maximum[z].point_max_diff2]-smeshenie;
    z++;
    y++;
    }

}
void __fastcall TForm1::Chart1Scroll(TObject *Sender)
{
auto_shift();        
}
//---------------------------------------------------------------------------

