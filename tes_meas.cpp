//---------------------------------------------------------------------------
//$Id: tes_meas.cpp,v 1.3 2004-03-24 17:33:42 peter Exp $


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
extern u16     counter_of_samples;


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
  //переменные симулятора алгоритма

  STATE state_mode;
  u16 signal_index;
  u16 interval_analisys;
  u16 diff_index;
  u16 diff2_index;
  s16 for_signal[FOR_SIGNAL_SIZE];         //массив для хранения поступающего сигнала
  s16 for_diff[FOR_DIFF_SIZE];             //массив для хранения разностного сигнала
  s16 for_diff2[FOR_DIFF_SIZE];            //массив для хранения второго разностного сигнала
  MAXIMUM maximum[NUM_MAXIMUMS];                //массив максимумов
  u16 number_maximum;                   //количество найденных максимумов

  // конец переменных симулятора алгоритма





  char n_f[256];
  char one_str[1024];
  double t;
  counter=0;
  u16 interval_analisys_win;
  s16 blackman_windows[200];
  u16 pos_diff_2[3];
  char temp[128];
  number_maximum_win=0;
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
  Series6->Clear();
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
     Series1->AddXY(counter,t,"",clTeeColor);
     Series6->AddXY(counter++,t,"",clTeeColor);
     break;
     }
   }

   if (counter){
    for (int z=0;z<(counter-(24));z++){
     diff_win[z]=black_men8_12(&signal[z]);
     Series2->AddXY(z+SHIFT_DIFF,((double)diff_win[z])*320.0/65536.0,"",clTeeColor);

     diff2_win[z]=zykov_man_4_12_blackman(&signal[z]);
     Series3->AddXY(z+SHIFT_DIFF2,((double)diff2_win[z])*320.0/65536.0,"",clTeeColor);
     }
    // поиск максимумов по первой производной diff
    interval_analisys_win=24;
    for (int z=0;z<(counter-interval_analisys_win);z++){
     if (find_max_win(&diff_win[z], interval_analisys_win)==(interval_analisys_win/2)){
      Series4->AddXY(z+SHIFT_DIFF+(interval_analisys_win/2),((double)diff_win[z+(interval_analisys_win/2)])*320.0/65536.0,"",clTeeColor);
      }
     }
    // поиск максимумов по второй производной diff2
    interval_analisys_win=24;
    for (int z=0;z<(counter-interval_analisys_win);z++){
     if (find_max_win(&diff2_win[z], interval_analisys_win)==(interval_analisys_win/2)){
      Series5->AddXY(z+SHIFT_DIFF2+(interval_analisys_win/2),((double)diff2_win[z+(interval_analisys_win/2)])*320.0/65536.0,"",clTeeColor);
      maximum_win[number_maximum_win].point_max_diff2=z+SHIFT_DIFF2+(interval_analisys_win/2);
      maximum_win[number_maximum_win].pulse_begin=signal[maximum_win[number_maximum_win].point_max_diff2];
      maximum_win[number_maximum_win].amplitude_diff2=diff2_win[z+(interval_analisys_win/2)];
      maximum_win[number_maximum_win].amplitude_diff2_ok=0;
      maximum_win[number_maximum_win].amplitude[0]=0;
      maximum_win[number_maximum_win].amplitude[1]=0;
      maximum_win[number_maximum_win].amplitude[2]=0;
      //Series7->AddXY(maximum[number_maximum_win].point_max,((double)signal[maximum[number_maximum_win].point_max])*320.0/65536.0,"",clTeeColor);
      number_maximum_win++;

      }
     }

    //if (number_maximum_win>10) number_maximum_win=10;
    for (int z=0;z<(number_maximum_win-1);z++){
     pos_diff_2[0]=z;
     pos_diff_2[1]=z+1;
     sprintf(temp,"%2.3lf ",((double)compute_amplitude_win(maximum_win,pos_diff_2))*320.0/65536.0);
     Series8->AddXY(maximum_win[z].point_max_diff2,((double)signal[maximum_win[z].point_max_diff2])*320.0/65536.0,temp,clTeeColor);
     }
    //добавляем "последний максимум
    //Series8->AddXY(maximum[number_maximum_win-1].point_max_diff2,((double)signal[maximum[number_maximum_win-1].point_max_diff2])*320.0/65536.0,"0",clTeeColor);

    state_mode=INITIALIZATION;


    counter_of_samples=0;
    do {
     switch(state_mode){
      case INITIALIZATION:
       state_mode=SYNCHRONIZATION_INIT;
       number_maximum=0;
       break;
      case SYNCHRONIZATION_INIT:
       diff_index=0;
       signal_index=0;
       interval_analisys=40;  // 32*1.25 минимальный AnalysisInterval;
       state_mode=SYNCHRONIZATION;
       break;
      case SYNCHRONIZATION:

                //берем один отсчет
       if (signal_index<FOR_SIGNAL_SIZE){
                get_signal(&for_signal[signal_index]);
                 //увеличиваем указатель на массив хранения сигнала
                signal_index++;
        }        
       else {
                internal_error(BAD_INDEX_SIGNAL_1);
                return;
       }
                //если достаточно данных, то вычисляем diff
       if (++diff_index>=ZYKOV_MAN8_12_WINDOWS){


                if ((diff_index-ZYKOV_MAN8_12_WINDOWS)<FOR_DIFF_SIZE){
                        for_diff[diff_index-ZYKOV_MAN8_12_WINDOWS]=zykov_man8_12(&for_signal[signal_index-1]);
                }
                else{
                       internal_error(BAD_INDEX_DIFF_1);
                        return;
                }

        }

                //если достаточно данных для поиска максимума на интервале interval_analisys

        if (interval_analisys>(diff_index-ZYKOV_MAN8_12_WINDOWS)){
                        //максимум попадает в середину интервала анализа
                if (find_max(&for_diff[diff_index-ZYKOV_MAN8_12_WINDOWS], interval_analisys)==(interval_analisys/2)){
                        //максимум на diff нашли, теперь слева от этой точки
                        // необходимо найти максимум на diff2
                         //если достаточно данных, то вычисляем diff2
                        diff2_index=0;
                        if (diff_index>=(ZYKOV_MAN4_12_WINDOWS+FOR_DIFF2_SIZE)){
                                // считаем diff2
                                while(diff2_index<FOR_DIFF2_SIZE)
                                        for_diff2[diff2_index++]=zykov_man4_12(&for_signal[signal_index-1-diff2_index]);
                                //ищем максимум на интервале diff2
                                if (number_maximum<NUM_MAXIMUMS){
                                        maximum[number_maximum].point_max_diff2=find_max(for_diff2, FOR_DIFF2_SIZE);
                                }
                                else{
                                       internal_error(BAD_INDEX_MAX_1);
                                        return;         
                                }
                        }
                }
        }


       break;
      default:
        internal_error(BAD_MIN_CASE_1);
        return;
      }
     }while (counter_of_samples<counter);

    auto_shift();
    auto_shift1();
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
//   while(z<number_maximum_win){
   while(z< Series8->Count()){
    //Series7->YValues->Value[z]=signal_d[maximum[z].point_max]-smeshenie;
    Series8->XValues->Value[y]=maximum_win[z].point_max_diff2;
    Series8->YValues->Value[y]=signal_d[maximum_win[z].point_max_diff2]-smeshenie;
    z++;
    y++;
    }

}
void TForm1::auto_shift1()
{
long left,right,bottom,up;
double middle;
double smeshenie;
int z,y;
  right=Chart2->BottomAxis->Maximum;
  left=Chart2->BottomAxis->Minimum;
  bottom=Chart2->LeftAxis->Minimum;
  up=Chart2->LeftAxis->Maximum;

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
    Series6->YValues->Value[z]=signal_d[z]-smeshenie;
    }
   z=0; //продяковый номер в массиве максимумов
   y=0; // порядковый номер реальных максимумов
//   while(z<number_maximum_win){

//   while(z< Series8->Count()){
    //Series7->YValues->Value[z]=signal_d[maximum[z].point_max]-smeshenie;
//    Series8->XValues->Value[y]=maximum_win[z].point_max_diff2;
//    Series8->YValues->Value[y]=signal_d[maximum_win[z].point_max_diff2]-smeshenie;
//    z++;
//    y++;
//    }

}


void __fastcall TForm1::Chart1Scroll(TObject *Sender)
{
auto_shift();        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Chart2Zoom(TObject *Sender)
{
  auto_shift1();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Chart2Scroll(TObject *Sender)
{
  auto_shift1();
}
//---------------------------------------------------------------------------


TForm1::internal_error(INTERNAL_ERROR)
{
MessageBox(0,"This should be on top.", "Look", MB_OK);
}
