//$Id: algoritm.cpp,v 1.2 2004-03-22 20:21:46 peter Exp $

#include "..\msp\type_def.h"
#include "algoritm.h"
// Коэфициенты ОКОН

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
