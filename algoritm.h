//$Id: algoritm.h,v 1.4 2004-03-24 17:33:42 peter Exp $



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

enum RES_TWO_PULSES{
        ALL_OK,         //все условия соблюдены
        AMP_BAD_LEFT_LOW,   //амплитуда левого не попала в "грубый" диапазон
        AMP_BAD_LEFT_HIGH,   //амплитуда левого не попала в "грубый" диапазон
        AMP_BAD_RIGHT_LOW,  //амплитуда правого не попала в "грубый" диапазон
        AMP_BAD_RIGHT_HIGH,  //амплитуда правого не попала в "грубый" диапазон
        TIME_LOW,       //время не попало в диапазон "грубый"
        TIME_HIGH,      //время не попало в диапазон "грубый"
        AMP_LEFT_LOW,   //амплитуда левого импульса "намного" меньше (вышла за ворота)
        AMP_RIGHT_LOW}; //амплитуда правого импульса "намного" меньше (вышла за ворота)


#define TIME_MAX        300     // 20 ударов в минуту - 3 секунды на удар => 300 отсчетов
#define TIME_MIN        30      // 200 ударов в минуту - 0.3 секунды на удар => 30 отсчетов
#define PRESS_MIN       20      // 65536 - 320 мм.рт.ст. => 0.1 мм.рт.ст. = 20.48
#define PRESS_MAX       2048    // 65536 - 320 мм.рт.ст. => 10 мм.рт.ст. = 2048 


#define ZYKOV_MAN8_12_WINDOWS   20
#define ZYKOV_MAN4_12_WINDOWS   24
#define FOR_SIGNAL_SIZE         1500
#define FOR_DIFF_SIZE           1500
#define FOR_DIFF2_SIZE          20
#define NUM_MAXIMUMS            1000    //количество максимумов

enum INTERNAL_ERROR{
        BAD_INDEX_SIGNAL_1=1,
        BAD_INDEX_DIFF_1=2,
        BAD_INDEX_DIFF2_1=3,
        BAD_MIN_CASE_1=4,
        BAD_INDEX_MAX_1=5};


enum STATE{
 INITIALIZATION,
 SYNCHRONIZATION_INIT,
 SYNCHRONIZATION};       //синхронизация с пульсом



s16 black_men8_12(s16* inp);
s16 zykov_man_4_12_blackman(s16* inp);
u16 find_max_win(s16* inp, u16 interval);
u16 find_max(s16* inp, u16 interval);
u16 find_min(s16* inp, u16 interval);
s16 compute_amplitude_win(MAXIMUM* m,u16* pos);
RES_TWO_PULSES compute_pulses(MAXIMUM* m,u16* pos);
u16 get_signal(s16* sample);
s16 zykov_man8_12(s16* inp);
s16 zykov_man4_12(s16* inp);



