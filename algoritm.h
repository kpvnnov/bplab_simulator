//$Id: algoritm.h,v 1.4 2004-03-24 17:33:42 peter Exp $



struct MAXIMUM {
     u16 point_max_diff2;       //����� ��������� �� diff2
     s16 pulse_begin;           //��������� ������ ���������
     s16 amplitude[3];          //��������� ����������� �� ����� �� ��������� �����
     s16 amplitude_diff2;       //��������� ��������� diff2
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
        ALL_OK,         //��� ������� ���������
        AMP_BAD_LEFT_LOW,   //��������� ������ �� ������ � "������" ��������
        AMP_BAD_LEFT_HIGH,   //��������� ������ �� ������ � "������" ��������
        AMP_BAD_RIGHT_LOW,  //��������� ������� �� ������ � "������" ��������
        AMP_BAD_RIGHT_HIGH,  //��������� ������� �� ������ � "������" ��������
        TIME_LOW,       //����� �� ������ � �������� "������"
        TIME_HIGH,      //����� �� ������ � �������� "������"
        AMP_LEFT_LOW,   //��������� ������ �������� "�������" ������ (����� �� ������)
        AMP_RIGHT_LOW}; //��������� ������� �������� "�������" ������ (����� �� ������)


#define TIME_MAX        300     // 20 ������ � ������ - 3 ������� �� ���� => 300 ��������
#define TIME_MIN        30      // 200 ������ � ������ - 0.3 ������� �� ���� => 30 ��������
#define PRESS_MIN       20      // 65536 - 320 ��.��.��. => 0.1 ��.��.��. = 20.48
#define PRESS_MAX       2048    // 65536 - 320 ��.��.��. => 10 ��.��.��. = 2048 


#define ZYKOV_MAN8_12_WINDOWS   20
#define ZYKOV_MAN4_12_WINDOWS   24
#define FOR_SIGNAL_SIZE         1500
#define FOR_DIFF_SIZE           1500
#define FOR_DIFF2_SIZE          20
#define NUM_MAXIMUMS            1000    //���������� ����������

enum INTERNAL_ERROR{
        BAD_INDEX_SIGNAL_1=1,
        BAD_INDEX_DIFF_1=2,
        BAD_INDEX_DIFF2_1=3,
        BAD_MIN_CASE_1=4,
        BAD_INDEX_MAX_1=5};


enum STATE{
 INITIALIZATION,
 SYNCHRONIZATION_INIT,
 SYNCHRONIZATION};       //������������� � �������



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



