//$Id: algoritm.cpp,v 1.4 2004-03-24 17:33:42 peter Exp $

#include "..\msp\type_def.h"
#include "algoritm.h"
// Коэфициенты ОКОН

extern  s16 signal[32767]; //сигнал
u16     counter_of_samples;


const s16 WIN_BL[]={417, 4233, 16655, 30465, 30465, 16655, 4233, 417};
const s16 WIN_BL_MINUS[]={-417,-4233,-16655,-30465,-30465,-16655,-4233,-417};
const s16 WIN_BL_075[]={ 313, 3175, 12491, 22849, 22849, 12491, 3175, 313};
const s16 WIN_BL_025[]={ 104, 1058,  4164,  7616,  7616,  4164, 1058, 104};

//требуемая ширина для обсчета 20 отсчетов

s16 black_men8_12(s16* inp){
 long t=0;

 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL_MINUS[x];
  }
 inp+=4;
 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL[x];
  }
 return t/32768;
}
//требуемая ширина для обсчета 20 отсчетов
// подсчет производится в "обратную" сторону
s16 zykov_man8_12(s16* inp){
 long t=0;
 u8 x;

 x=7;
 do{
  t+=((long)(*inp--))*WIN_BL[x];
  } while(x--!=0);
 inp-=4;
 x=7;
 do{
  t+=((long)(*inp--))*WIN_BL_MINUS[x];
  } while(x--!=0);
 return t/32768;
}


//требуемая ширина для обсчета 24 отсчета
s16 zykov_man_4_12_blackman(s16* inp){
 double long t=0;
 s16* inp1=inp;
 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL_075[x];
  }

 inp=inp1+4;
 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL_MINUS[x];
  }

 inp=inp1+16;
 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL_025[x];
  }

 return t/32768;
}
//требуемая ширина для обсчета 24 отсчета
// подсчет производится в "обратную" сторону
s16 zykov_man4_12(s16* inp){
 double long t=0;
 s16* inp1=inp;
 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL_075[x];
  }

 inp=inp1+4;
 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL_MINUS[x];
  }

 inp=inp1+16;
 for (int x=0;x<8;x++){
  t+=((long)(*inp++))*WIN_BL_025[x];
  }

 return t/32768;
}

u16 find_max_win(s16* inp, u16 interval){
 int x;
 s16 max=*inp++;
 u16 pos_max=0;
 for (x=1;x<interval;x++){
  if (*inp>max){
   pos_max=x;
   max=*inp;}
  inp++;
  }
return pos_max;
}

// поиск максимума влево
u16 find_max(s16* inp, u16 interval){
 int x;
 s16 max=*inp--;
 u16 pos_max=0;
 for (x=1;x<interval;x++){
  if (*inp>max){
   pos_max=x;
   max=*inp;}
  inp--;
  }
return pos_max;
}

u16 find_min(s16* inp, u16 interval){
 int x;
 s16 max=*inp++;
 u16 pos_min=0;
 for (x=1;x<interval;x++){
  if (*inp<max){
   pos_min=x;
   max=*inp;}
  inp++;
  }
return pos_min;
}


//вычисление амплитуды с учетом тренда
s16 compute_amplitude_win(MAXIMUM* m,u16* pos){
s16 temp_m[200];

double a0=(double)m[pos[0]].pulse_begin;
double a1=(double)m[pos[1]].pulse_begin;
u16 pos0=m[pos[0]].point_max_diff2;
u16 pos1=m[pos[1]].point_max_diff2;
if (pos1==pos0) return 32767;
if ((pos1-pos0)>=200) return 29000;
double delta=(double(a1-a0))/(pos1-pos0);
 for (int x=0;x<(pos1-pos0);x++){
  temp_m[x]=((double)signal[pos0+x])-delta*(double)x;
  }
 return temp_m[find_max_win(temp_m,pos1-pos0)]-temp_m[0];
}


RES_TWO_PULSES compute_pulses(MAXIMUM* m,u16* pos){
u16 time_0_1;
s16 amp_diff2_0,amp_diff2_1;
float diff_amp;

 amp_diff2_0=m[pos[0]].amplitude_diff2;
 if (amp_diff2_0<PRESS_MIN)     return AMP_BAD_LEFT_LOW; //амплитуда левого не попала в "грубый" диапазон
 if (amp_diff2_0>PRESS_MAX)     return AMP_BAD_LEFT_HIGH; //амплитуда левого не попала в "грубый" диапазон

 amp_diff2_1=m[pos[1]].amplitude_diff2;
 if (amp_diff2_1<PRESS_MIN)     return AMP_BAD_RIGHT_LOW; //амплитуда правого не попала в "грубый" диапазон
 if (amp_diff2_1>PRESS_MAX)     return AMP_BAD_RIGHT_HIGH; //амплитуда правого не попала в "грубый" диапазон

 time_0_1=m[pos[1]].point_max_diff2-m[pos[0]].point_max_diff2;
 if (time_0_1<TIME_MIN) return TIME_LOW; //не попал в грубые ворота по времени
 if (time_0_1>TIME_MAX) return TIME_HIGH; //не попал в грубые ворота по времени

 diff_amp=((float)amp_diff2_0)/((float)amp_diff2_1);
 if (diff_amp<0.75)     return AMP_LEFT_LOW;    //левый импульс намного меньше
 if (diff_amp>1.15)     return AMP_RIGHT_LOW;   //правый импульс намного меньше
 return ALL_OK;
}

u16 get_signal(s16* sample){
 *sample=signal[counter_of_samples++];
 return 1;
}


/*

// поиск максимумов по следующим признакам
//    ALL_GOOD,
//    FIRST_GOOD,
//    FIRST_SECOND_GOOD,
//    SECOND_THIRD_GOOD,
//    FIRST_THIRD_GOOD,
//    ALL_BAD

RES_MAX find_pulses(MAXIMUM* m,u16* pos){
u16 time_0_1;   //интервал между максимумом 0 и 1
u16 time_1_2;   //интервал между максимумом 1 и 2
u16 time_0_2;   //интервал между максимумом 0 и 2
s16 amp_diff2_0;        //амплитуда максимума diff2 точки 0
s16 amp_diff2_1;        //амплитуда максимума diff2 точки 1
s16 amp_diff2_2;        //амплитуда максимума diff2 точки 2

u16 i_p1=0,i_p2=0,i_p3=0;
u16 i_t1=0,i_t2=0,i_t3=0,i_t4=0;
u16 i_a1=0,i_a2=0,i_a3=0;

 time_0_1=m[pos[1]].point_min-m[pos[0]].point_min;
 time_1_2=m[pos[2]].point_min-m[pos[1]].point_min;
 time_0_2=m[pos[2]].point_min-m[pos[0]].point_min;

 amp_diff2_0=m[pos[0]].amplitude_diff2;
 amp_diff2_1=m[pos[1]].amplitude_diff2;
 amp_diff2_2=m[pos[2]].amplitude_diff2;

 if ((amp_diff2_0>=PRESS_MIN) && (amp_diff2_0<=PRESS_MAX)) i_p1=1; //первый импульс по амплитуде OK?
 if ((amp_diff2_1>=PRESS_MIN) && (amp_diff2_1<=PRESS_MAX)) i_p2=1; //первый импульс по амплитуде OK?
 if ((amp_diff2_2>=PRESS_MIN) && (amp_diff2_2<=PRESS_MAX)) i_p3=1; //второй импульс по амплитуде OK?
 m[pos[0]].amplitude_diff2_ok=i_p1;
 m[pos[1]].amplitude_diff2_ok=i_p2;
 m[pos[2]].amplitude_diff2_ok=i_p3;

 if ( (time_0_1>=TIME_MIN) && (time_0_1<=TIME_MAX) ) i_t1=1; //время 0-1 норма
 if ( (time_1_2>=TIME_MIN) && (time_1_2<=TIME_MAX) ) i_t2=1; //время 1-2 норма
 if ( (time_0_2>=TIME_MIN) && (time_0_2<=TIME_MAX) ) i_t3=1; //время 0-2 норма
 else if ( (time_0_2>=TIME_MIN) && (time_0_2<=(TIME_MAX*2) ) i_t4=1; //время 0-2 возможно двойное

 if (compare_amplitude(amp_diff2_0,amp_diff2_1)) i_a1=1; //соотношение амплитуд 0 и 1 нормальное
 if (compare_amplitude(amp_diff2_1,amp_diff2_2)) i_a2=1; //соотношение амплитуд 1 и 2 нормальное
 if (compare_amplitude(amp_diff2_0,amp_diff2_2)) i_a3=1; //соотношение амплитуд 0 и 2 нормальное




}





 if (i_p1){ //по первому импульсу

        if (i_p2){ //по второму импульсу

                if (i_a1){ //соотношение амплитуд 0 и 1 нормальное

                        if (i_p3){ //по третьему импульсу

                                if (i_a2) {//соотношение амплитуд 1 и 2 нормальное

                                        if (i_t1){ //проверяем временные интервалы 0-1 (грубо)

                                                if (i_t2){ //проверяем временные интервалы 1-2 (грубо)

                                                        if (compare_time(time_0_1,time_1_2)){ //во временные ворота попали
                                                                return ALL_GOOD;
                                                        }
                                                        else{ //во временные ворота не попали
                                                                return ALL_BAD;
                                                        }
                                                }
                                                else{ //временной интервал 1-2 не верен (грубо)
                                                        return FIRST_SECOND_GOOD; //преполагаем что 0-1 хорошие
                                                }
                                        }
                                        else{ //временной интервал 0-1 не верен (грубо)
                                                if (i_t2){ //проверяем временные интервалы 1-2
                                                        return SECOND_THIRD_GOOD; //преполагаем что 1-2 хорошие
                                                }
                                                else{ //по времени не прошли (грубо)
                                                        return ALL_BAD;
                                                }
                                        }
                                }
                                else{ //соотношение амплитуд 1 и 2 плохое
                                        if (i_t1){ //проверяем временные интервалы 0-1 (грубо)
                                                return FIRST_SECOND_GOOD;
                                        }
                                        else
                                                return ALL_BAD;
                                }
                        else{ //третий импульс в анализе не учавствует
                                if (i_a2) {//соотношение амплитуд 1 и 2 нормальное
                                        if (i_t1){ //проверяем временные интервалы 0-1 (грубо)
                                                return FIRST_SECOND_GOOD;       //преполагаем что 0-1 хорошие
                                        }
                                        else //временные интервалы 0-1 (грубо) не прошли
                                                return ALL_BAD;
                                }
                                else
                                        return ALL_BAD;
                        }
                }
                else{ ////соотношение амплитуд 0 и 1 плохое
                        if (i_a3) //соотношение амплитуд 0 и 1 нормальное
                }
        else { //второй импульс плохой
        }
 }
 else{ //первый импульс плохой
 }

*/