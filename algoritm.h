//$Id: algoritm.h,v 1.3 2004-03-23 17:55:50 peter Exp $



struct MAXIMUM {
     u16 point_max_diff2;       //точка максимума по diff2
     s16 pulse_begin;           //амплитуда начала пульсации
     s16 amplitude[3];          //амплитуда выстроенная по треду до следующих точек
     s16 amplitude_diff2;       //амплитуда максимума diff2
     u16 amplitude_diff2_ok:1;
 };


enum RES_MAX {
    ALL_GOOD,
    FIRST_GOOD,
    FIRST_SECOND_GOOD,
    SECOND_THIRD_GOOD,
    FIRST_THIRD_GOOD,
    ALL_BAD
};
s16 black_men8_12(s16* inp);
s16 zykov_man_4_12_blackman(s16* inp);
u16 find_max(s16* inp, u16 interval);
u16 find_min(s16* inp, u16 interval);
s16 compute_amplitude(MAXIMUM* m,u16* pos);
