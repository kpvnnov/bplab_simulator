//$Id: algoritm.cpp,v 1.4 2004-03-24 17:33:42 peter Exp $

#include "..\msp\type_def.h"
#include "algoritm.h"
// ����������� ����

extern  s16 signal[32767]; //������
u16     counter_of_samples;


const s16 WIN_BL[]={417, 4233, 16655, 30465, 30465, 16655, 4233, 417};
const s16 WIN_BL_MINUS[]={-417,-4233,-16655,-30465,-30465,-16655,-4233,-417};
const s16 WIN_BL_075[]={ 313, 3175, 12491, 22849, 22849, 12491, 3175, 313};
const s16 WIN_BL_025[]={ 104, 1058,  4164,  7616,  7616,  4164, 1058, 104};

//��������� ������ ��� ������� 20 ��������

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
//��������� ������ ��� ������� 20 ��������
// ������� ������������ � "��������" �������
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


//��������� ������ ��� ������� 24 �������
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
//��������� ������ ��� ������� 24 �������
// ������� ������������ � "��������" �������
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

// ����� ��������� �����
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


//���������� ��������� � ������ ������
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
 if (amp_diff2_0<PRESS_MIN)     return AMP_BAD_LEFT_LOW; //��������� ������ �� ������ � "������" ��������
 if (amp_diff2_0>PRESS_MAX)     return AMP_BAD_LEFT_HIGH; //��������� ������ �� ������ � "������" ��������

 amp_diff2_1=m[pos[1]].amplitude_diff2;
 if (amp_diff2_1<PRESS_MIN)     return AMP_BAD_RIGHT_LOW; //��������� ������� �� ������ � "������" ��������
 if (amp_diff2_1>PRESS_MAX)     return AMP_BAD_RIGHT_HIGH; //��������� ������� �� ������ � "������" ��������

 time_0_1=m[pos[1]].point_max_diff2-m[pos[0]].point_max_diff2;
 if (time_0_1<TIME_MIN) return TIME_LOW; //�� ����� � ������ ������ �� �������
 if (time_0_1>TIME_MAX) return TIME_HIGH; //�� ����� � ������ ������ �� �������

 diff_amp=((float)amp_diff2_0)/((float)amp_diff2_1);
 if (diff_amp<0.75)     return AMP_LEFT_LOW;    //����� ������� ������� ������
 if (diff_amp>1.15)     return AMP_RIGHT_LOW;   //������ ������� ������� ������
 return ALL_OK;
}

u16 get_signal(s16* sample){
 *sample=signal[counter_of_samples++];
 return 1;
}


/*

// ����� ���������� �� ��������� ���������
//    ALL_GOOD,
//    FIRST_GOOD,
//    FIRST_SECOND_GOOD,
//    SECOND_THIRD_GOOD,
//    FIRST_THIRD_GOOD,
//    ALL_BAD

RES_MAX find_pulses(MAXIMUM* m,u16* pos){
u16 time_0_1;   //�������� ����� ���������� 0 � 1
u16 time_1_2;   //�������� ����� ���������� 1 � 2
u16 time_0_2;   //�������� ����� ���������� 0 � 2
s16 amp_diff2_0;        //��������� ��������� diff2 ����� 0
s16 amp_diff2_1;        //��������� ��������� diff2 ����� 1
s16 amp_diff2_2;        //��������� ��������� diff2 ����� 2

u16 i_p1=0,i_p2=0,i_p3=0;
u16 i_t1=0,i_t2=0,i_t3=0,i_t4=0;
u16 i_a1=0,i_a2=0,i_a3=0;

 time_0_1=m[pos[1]].point_min-m[pos[0]].point_min;
 time_1_2=m[pos[2]].point_min-m[pos[1]].point_min;
 time_0_2=m[pos[2]].point_min-m[pos[0]].point_min;

 amp_diff2_0=m[pos[0]].amplitude_diff2;
 amp_diff2_1=m[pos[1]].amplitude_diff2;
 amp_diff2_2=m[pos[2]].amplitude_diff2;

 if ((amp_diff2_0>=PRESS_MIN) && (amp_diff2_0<=PRESS_MAX)) i_p1=1; //������ ������� �� ��������� OK?
 if ((amp_diff2_1>=PRESS_MIN) && (amp_diff2_1<=PRESS_MAX)) i_p2=1; //������ ������� �� ��������� OK?
 if ((amp_diff2_2>=PRESS_MIN) && (amp_diff2_2<=PRESS_MAX)) i_p3=1; //������ ������� �� ��������� OK?
 m[pos[0]].amplitude_diff2_ok=i_p1;
 m[pos[1]].amplitude_diff2_ok=i_p2;
 m[pos[2]].amplitude_diff2_ok=i_p3;

 if ( (time_0_1>=TIME_MIN) && (time_0_1<=TIME_MAX) ) i_t1=1; //����� 0-1 �����
 if ( (time_1_2>=TIME_MIN) && (time_1_2<=TIME_MAX) ) i_t2=1; //����� 1-2 �����
 if ( (time_0_2>=TIME_MIN) && (time_0_2<=TIME_MAX) ) i_t3=1; //����� 0-2 �����
 else if ( (time_0_2>=TIME_MIN) && (time_0_2<=(TIME_MAX*2) ) i_t4=1; //����� 0-2 �������� �������

 if (compare_amplitude(amp_diff2_0,amp_diff2_1)) i_a1=1; //����������� �������� 0 � 1 ����������
 if (compare_amplitude(amp_diff2_1,amp_diff2_2)) i_a2=1; //����������� �������� 1 � 2 ����������
 if (compare_amplitude(amp_diff2_0,amp_diff2_2)) i_a3=1; //����������� �������� 0 � 2 ����������




}





 if (i_p1){ //�� ������� ��������

        if (i_p2){ //�� ������� ��������

                if (i_a1){ //����������� �������� 0 � 1 ����������

                        if (i_p3){ //�� �������� ��������

                                if (i_a2) {//����������� �������� 1 � 2 ����������

                                        if (i_t1){ //��������� ��������� ��������� 0-1 (�����)

                                                if (i_t2){ //��������� ��������� ��������� 1-2 (�����)

                                                        if (compare_time(time_0_1,time_1_2)){ //�� ��������� ������ ������
                                                                return ALL_GOOD;
                                                        }
                                                        else{ //�� ��������� ������ �� ������
                                                                return ALL_BAD;
                                                        }
                                                }
                                                else{ //��������� �������� 1-2 �� ����� (�����)
                                                        return FIRST_SECOND_GOOD; //����������� ��� 0-1 �������
                                                }
                                        }
                                        else{ //��������� �������� 0-1 �� ����� (�����)
                                                if (i_t2){ //��������� ��������� ��������� 1-2
                                                        return SECOND_THIRD_GOOD; //����������� ��� 1-2 �������
                                                }
                                                else{ //�� ������� �� ������ (�����)
                                                        return ALL_BAD;
                                                }
                                        }
                                }
                                else{ //����������� �������� 1 � 2 ������
                                        if (i_t1){ //��������� ��������� ��������� 0-1 (�����)
                                                return FIRST_SECOND_GOOD;
                                        }
                                        else
                                                return ALL_BAD;
                                }
                        else{ //������ ������� � ������� �� ����������
                                if (i_a2) {//����������� �������� 1 � 2 ����������
                                        if (i_t1){ //��������� ��������� ��������� 0-1 (�����)
                                                return FIRST_SECOND_GOOD;       //����������� ��� 0-1 �������
                                        }
                                        else //��������� ��������� 0-1 (�����) �� ������
                                                return ALL_BAD;
                                }
                                else
                                        return ALL_BAD;
                        }
                }
                else{ ////����������� �������� 0 � 1 ������
                        if (i_a3) //����������� �������� 0 � 1 ����������
                }
        else { //������ ������� ������
        }
 }
 else{ //������ ������� ������
 }

*/