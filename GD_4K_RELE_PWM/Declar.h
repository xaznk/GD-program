//-------------------------------- Declar.h ----------------------------------
#define     i_maxovik_timer           62500
#define     div_milisek_switch        5      // 2000
//#define     Kol_zubov_kolenvala       125

//------------
#define     Error_D_Faza              10
#define     Error_D_Maxovik           12
#define     Error_D_Konc_MUZD         13
#define     Error_D_Treadle           14
#define     Error_Switch_Klapan_1     15
#define     Error_Switch_Klapan_2     16
#define     Error_Switch_Klapan_3     17
#define     Error_Switch_Klapan_4     18
#define     Error_Switch_Klapan_5     19
#define     Error_Switch_Klapan_6     20
#define     Error_Switch_Klapan_7     21
#define     Error_Switch_Klapan_8     22
#define     Error_Switch_RELE         23
#define     Error_Switch_GAS          24
#define     Error_Switch_MUZD         25
#define     Error_Switch_MUZD_V       26

#define     Error_ON_OFF_Car          27
#define     Error_OnOff_Button        28
#define     Error_t_Reduktor          29
//------------
 
#define     Yellow_diod_OUT       DDRH|=0x01
#define     Yellow_diod_ON        PORTH|=0x01
#define     Yellow_diod_OFF       PORTH&=~0x01
#define     Red_diod_OUT          DDRH|=0x02
#define     Red_diod_ON           PORTH|=0x02
#define     Red_diod_OFF          PORTH&=~0x02
#define     Bazer_OUT             DDRH|=0x04
#define     Bazer_ON              PORTH|=0x04
#define     Bazer_OFF             PORTH&=~0x04
#define     PHASE1_stepM_OUT      DDRJ|=0x20
#define     PHASE1_stepM_ON       PORTJ|=0x20
#define     PHASE1_stepM_OFF      PORTJ&=~0x20
#define     I01_stepM_OUT         DDRJ|=0x08
#define     I01_stepM_ON          PORTJ|=0x08
#define     I01_stepM_OFF         PORTJ&=~0x08
#define     I11_stepM_OUT         DDRJ|=0x10
#define     I11_stepM_ON          PORTJ|=0x10
#define     I11_stepM_OFF         PORTJ&=~0x10
#define     PHASE2_stepM_OUT      DDRJ|=0x04
#define     PHASE2_stepM_ON       PORTJ|=0x04
#define     PHASE2_stepM_OFF      PORTJ&=~0x04

#define     I02_stepM_OUT         DDRJ|=0x01
#define     I02_stepM_ON          PORTJ|=0x01
#define     I02_stepM_OFF         PORTJ&=~0x01
#define     I12_stepM_OUT         DDRJ|=0x02
#define     I12_stepM_ON          PORTJ|=0x02
#define     I12_stepM_OFF         PORTJ&=~0x02

#define     RS485_Transmit_OUT    DDRB|=0x01
#define     RS485_Transmit_ON     PORTB|=0x01
#define     RS485_Transmit_OFF    PORTB&=~0x01
#define     ADC_MUX_akumulator        1  //áîðòîâîå íàïðÿæåíèå   ADC0 - ïî ñõåìå 
#define     ADC_MUX_axeleratora       2  //äàò÷èê ïåäàëè         ADC1 - ïî ñõåìå
#define     ADC_MUX_pressure_gaza     3  //äàò÷èê äàâëåíèÿ ãàçà  ADC3 - ïî ñõåìå 
#define     ADC_MUX_pressure          4  //äàò÷èê äàâëåíèÿ íàä   ADC3 - ïî ñõåìå
#define     ADC_MUX_termopara         5  //äàò÷èê Ò âûõëîïà      ADC4 - ïî ñõåìå
#define     ADC_MUX_temp_shem         6  //äàò÷èê Ò ÁÓ           ADC5 - ïî ñõåìå
#define     ADC_MUX_DC_HD_A           7  //äàò÷èê òîêà ØÄ - À    ADC6 - ïî ñõåìå //ADC_MUX_temp_D
#define     ADC_MUX_DC_HD_B           0  //äàò÷èê òîêà ØÄ - B    ADC7 - ïî ñõåìå //ADC_MUX_stM_sens1
#define     Faza_Motora_READ      PIND&0x01
#define     Tooth_Motora_READ     PIND&0x80

//------------------------- EEPROM ------------------------------
#define   offset_int_eeprom             0
#define   offset_char_eeprom            40
//int
//#define   Kp_Gain_0_eeprom                offset_int_eeprom+0
//#define   Kp_Gain_1_eeprom                offset_int_eeprom+1
//#define   Kp_Gain_2_eeprom                offset_int_eeprom+2
#define   idling_motor_dizel_eeprom         offset_int_eeprom+3
#define   Turbo_Koeff_eeprom                offset_int_eeprom+4
#define   Turbo_offset_eeprom               offset_int_eeprom+5
#define   offset_motor_tax_eeprom           offset_int_eeprom+6
#define   Serial_number_eeprom              offset_int_eeprom+7
#define   Step_Motor_Koeff_eeprom           offset_int_eeprom+8
#define   Kp_Gain_2_eeprom                  offset_int_eeprom+9
#define   Kp_Gain_PID_t_1_eeprom            offset_int_eeprom+10
#define   Kp_Gain_PID_t_2_eeprom            offset_int_eeprom+11
#define   temperature_pred_eeprom           offset_int_eeprom+12
#define   D_min_max_eeprom                  offset_int_eeprom+13

//char
#define   sw1_number_tooth_eeprom           offset_char_eeprom+0
#define   High_Level_PID_eeprom             offset_char_eeprom+1
#define   Low_Level_PID_eeprom              offset_char_eeprom+2
#define   Flag_Duo_Mono_eeprom              offset_char_eeprom+3
#define   Low_Level_Idling_eeprom           offset_char_eeprom+4
#define   Step_Motor_OffSet_eeprom          offset_char_eeprom+5
#define   Kol_zubov_kolenvala_eeprom        offset_char_eeprom+6
//array char
#define   faza_array_tooth_eeprom           offset_char_eeprom+10
#define   array_high_level_PID_eeprom       offset_char_eeprom+286//+28
#define   Step_motor_array_cicle_eeprom     offset_char_eeprom+384//126
//array int
#define   Axelerometr_tax_eeprom            offset_char_eeprom+446//188

//---------------------- 24LC16B -------------------------------

#define   idling_motor_dizel_24LC16B          4
#define   Turbo_Koeff_24LC16B                 6
#define   Turbo_offset_24LC16B                8
#define   offset_motor_tax_24LC16B            10
#define   Serial_number_24LC16B               12
#define   Step_Motor_Koeff_24LC16B            14
#define   Kp_Gain_2_24LC16B                   16
#define   Flag_error_N_24LC16B                18
#define   Kp_Gain_PID_t_1_24LC16B             20
#define   Kp_Gain_PID_t_2_24LC16B             22
#define   temperature_pred_24LC16B            24
#define   D_min_max_24LC16B                   26
//char
#define   sw1_number_tooth_24LC16B         30
#define   High_Level_PID_24LC16B           31
#define   Low_Level_PID_24LC16B            32
#define   Flag_Duo_Mono_24LC16B            33
#define   Low_Level_Idling_24LC16B         34
#define   Step_Motor_OffSet_24LC16B        35
#define   Kol_zubov_kolenvala_24LC16B      36
//array char
#define   faza_array_tooth_24LC16B         40
#define   array_high_level_PID_24LC16B     298//58
#define   Step_motor_array_cicle_24LC16B   396//156
//array int
#define   Axelerometr_tax_24LC16B          458//218

//íàïðàâëåíèå ÌÓÇÄ
#define   NAP_MUZD   1 //0
//ïèñê RUN_GD
#define   PISK_RUN_GD   120
//#define   PISK_STOP_GD   120


//-------------------------- end EEPROM -------------------------

__near unsigned char __eeprom *var_uns_char;
__near signed int __eeprom *var_s_int;
__near unsigned int __eeprom *var_uns_int; 

/*unsigned char __eeprom *sw1_number_tooth_eeprom;
unsigned char __eeprom *sw2_number_tooth_eeprom;
unsigned char __eeprom *sw3_number_tooth_eeprom;
unsigned char __eeprom *sw4_number_tooth_eeprom;*/


__near  unsigned char next_p;

__near  unsigned int Serial_number=0;

unsigned char DATA_1;
unsigned char DATA_2;
unsigned char DATA_3;
unsigned char DATA_4;
unsigned char DATA_5;
unsigned char DATA_6;
unsigned char DATA_7;
unsigned char DATA_8;
unsigned char DATA_9;
unsigned char DATA_10;
unsigned char DATA_11;
unsigned char DATA_12;
unsigned char DATA_13;
unsigned char DATA_14;
unsigned char DATA_15;
unsigned char DATA_16;

__near unsigned char Flag_Command=0;    // Kernel.h
__near unsigned char Flag_State_Run_GD=0;
//__near unsigned char Flag_taxometer=0;
unsigned char Flag_taxometer=0;
__near unsigned char Flag_GD_Button=0;
__near unsigned char Flag_Duo_Mono;
//__near unsigned char Flag_Idling=0;
__near unsigned char Flag_quantization_step_PID=0;
__near unsigned char Flag_PID_PI=0;
__near unsigned int Flag_error_N;
__near unsigned char Flag_UART_TXD_empty=0;
__near unsigned char Flag_PC_interf=0;
__near unsigned char Flag_en_dis_switch=0;
__near unsigned char Flag_on_off_motor=0;
__near unsigned char Flag_temperature=0;
__near unsigned char Flag_PID_t_collectora=0;
__near unsigned char Flag_test_local=0;
//unsigned char Zub_Counter=0;
//unsigned char Flag_zuba=0;
__near unsigned char Faza_motora=0;
__near unsigned char Kol_zubov_kolenvala=145;
//unsigned int timer_ms=0;  // Sekundomer timer.h 10ms
//unsigned int frequency_qvant=100;    //  *1 ms
//unsigned char mikroSekundomer_mk=0;         // *0.2 ms

__near unsigned int miliSekundomer_ms=0;            // 10 ms
//unsigned char microSecundomer=0;

unsigned char Klapana_area[8]={0,0,0,0,0,0,0,0};
__near unsigned int Delay_kl=0;

__near unsigned char faza_array_tooth[16][16];//faza_array_tooth[16];
__near unsigned char Step_motor_array_cicle[16];
__near unsigned char array_high_level_PID[6][16];

__near unsigned char sw1_number_tooth=10;//55;
__near unsigned char swN_number_tooth=73;

__near unsigned int Tax_arrea[10];
__near unsigned int idling_motor_dizel;
__near signed int taxometer=60;
__near unsigned int taxometer_count=i_maxovik_timer;
__near signed long taxometer_delta[3]={0,0,0};
__near signed int taxometer_predetermined;
__near signed int offset_motor_tax;
__near unsigned int ADC_offset_min;
__near unsigned int ADC_offset_max;
__near signed int Axelerometr_tax[9][5];       //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
//__near signed int taxometer_K;  // -+1, -+2, -+3, -+4
//__near signed int taxometer_B;
__near signed int tx_deter;
__near unsigned char Error_number_device=0;     // 4,

__near signed int Kp_Gain_2;
//__near signed int Kp_Gain_1;
//__near signed int Kp_Gain_0;
//__near signed int Kp_Gain_CH;
__near float Rezult_PID=0;
__near unsigned char high_level_index_I=0;
__near unsigned char high_level_index_Y=0;
__near unsigned int High_Level_PID;
__near unsigned int High_Level_PID_tax;
__near unsigned int Low_Level_PID;
__near unsigned int Low_Level_Idling;

//------------- PID temperature
__near signed long Rezult_PID_temperature=0;
__near signed long temperature_delta[3]={0,0,0};
__near signed int temperature_predetermined=600;              // in FLASH
__near signed int temperature_Col=0;
__near signed int temperature_Reduktor=0;
__near signed int D_min_max=0 ;                               // in FLASH
__near signed int Kp_Gain_PID_t_2;                            // in FLASH
__near signed int Kp_Gain_PID_t_1;                            // in FLASH
//------------- PID temperature

__near signed int Turbo_Koeff;
__near signed int Turbo_offset;
__near unsigned int Triger_Koncevik=0;
__near unsigned int Triger_Button=0;
__near unsigned char Triger_ON_OFF=0;

__near unsigned int Q_PID_count=0;
__near unsigned int Q_PID_const=60;

__near unsigned char Step_Motor_OffSet;
__near unsigned int Step_Motor_Position=0;
__near unsigned int Step_Motor_Future=0;
__near unsigned int Step_Motor_Koeff;
//__near unsigned char Count_Step_Motor=0;
//__near unsigned char Flag_SM_polarity=0;
__near unsigned char Faza_Step_Motor=1;
//__near unsigned int Triger_Idling_K0=0;

__near unsigned char Test_PC_count=0;
__near unsigned char Test_Narabotka_count=0;
__near unsigned int Narabotka_GAS_count=0;
__near unsigned int Narabotka_count=0;

//ïåðåìåííàÿ îòîáðàæàþùàÿ êîë. äàííûõ â ïàêåòå
//UART
unsigned int speed_SM;
unsigned char UART_FI_address=0;
unsigned char UART_FO_address=0;
__near unsigned char UART_buffer_FIFO[256]; 

//ïåðåìåííûå äëÿ ðàñ÷åòà êîëè÷åñòâà çóáüåâ
unsigned char enable_pysk_ras = 0;
unsigned int data_TCNT0_now = 0;
unsigned char tim_io;
unsigned int timer_cou_int;
unsigned char CRC_out = 0;
unsigned char ERROR_out_1 = 0;
unsigned char ERROR_out_2 = 0;
unsigned char ERROR_out_3 = 0;
unsigned char ERROR_out_4 = 0;
unsigned char ERROR_out_5 = 0;
unsigned char ERROR_out_6 = 0;
unsigned char ERROR_out_7 = 0;
unsigned char ERROR_out_8 = 0;
unsigned char ERROR_kil = 0;
unsigned char ERROR_term = 0;
unsigned char ERROR_HD = 0;
//----------------------------------------
unsigned char enab_for_1 = 0;
unsigned char enab_for_2 = 0;
unsigned char enab_for_3 = 0;
unsigned char enab_for_4 = 0;
unsigned char enab_for_5 = 0;
unsigned char enab_for_6 = 0;
unsigned char enab_for_7 = 0;
unsigned char enab_for_8 = 0;
unsigned char error_kl_1;
unsigned char kil_f_1 = 0;
unsigned char kil_f_2 = 0;
unsigned char array_test[42];
unsigned char enable_test_system = 0;
unsigned char clear_error_faza = 0;
unsigned char clear_error_tax = 0;
unsigned char ERROR_faza = 0;
unsigned char ERROR_tax  = 0;

unsigned char ERROR_f1   = 0;
unsigned char ERROR_f2   = 0;
unsigned char ERROR_f3   = 0;
unsigned char ERROR_f4   = 0;
unsigned char ERROR_f5   = 0;
unsigned char ERROR_f6   = 0;
unsigned char ERROR_f7   = 0;
unsigned char ERROR_f8   = 0;
unsigned char ERROR_f_kz = 0;

unsigned char ERROR_tt = 0;
unsigned char ERROR_dd = 0;
unsigned char ERROR_gkl = 0;

unsigned char er_1_test = 0;
unsigned char er_2_test = 0;
unsigned char er_3_test = 0;
unsigned char er_4_test = 0;

unsigned char enable_out_data = 0;
unsigned char enable_test_fors = 0;

unsigned char STOP_RUN_GD = 0;
unsigned char ALL_KIL_ERROR_SYS = 0;
unsigned char nn_m;

unsigned char enable_signal = 0;
unsigned char signal_number = 0;
unsigned char signal_timer_ms = 0;
unsigned char on_fors_8 = 0;
unsigned char number_ost_8 = 0; 

unsigned char enable_out_pc_paket = 0;
unsigned char addr_uart = 0;

unsigned char off_sys = 0;
unsigned char enable_off_sys = 0;
unsigned char enable_mig_green = 0;
unsigned int step_opros_fors_1 = 0;
unsigned int step_opros_fors_2 = 0;
unsigned int step_opros_fors_3 = 0;
unsigned int step_opros_fors_4 = 0;
unsigned int step_opros_fors_5 = 0;
unsigned int step_opros_fors_6 = 0;
unsigned int step_opros_fors_7 = 0;
unsigned int step_opros_fors_8 = 0;
unsigned int kil_thit = 0;
unsigned char Enable_tx_data = 0;
unsigned char interf_pc_open = 0;
unsigned char number_fors_kz = 0;


//äîïîëíèòåëüíûå ïåðåìåííûå äëÿ îòâåòíîãî ïàêåòà
unsigned char dob_paket_0 = 0;
unsigned char dob_paket_1 = 0;
unsigned char dob_paket_2 = 0;
unsigned char dob_paket_3 = 0;
unsigned char dob_paket_4 = 0;
unsigned char dob_paket_5 = 0;
unsigned char dob_paket_6 = 0;
unsigned char dob_paket_7 = 0;
unsigned char dob_paket_8 = 0;
unsigned char dob_paket_9 = 0;


unsigned char data_out_tx = 0;
unsigned int D_min = 0;
unsigned int D_max = 0;
unsigned char status_GD = 0;
unsigned char comand_run_gd = 0;
unsigned char number_paket_tx_now = 0;
unsigned char term_switch = 0;
unsigned int temperature_ADC = 0;
unsigned int temperature_ADC_SUMM = 0;
unsigned int temperature_ADC_B = 0; 


unsigned char on_off_fors_1_real = 0;
unsigned char migi_migi = 0;
unsigned char prov_perne = 0;


//ïåðåìåííûå äëÿ ðàáîòû â ðåæèìå äîáàâëåíèÿ PWM
unsigned char fors_pwm;
unsigned char on_off_fors_pwm;
unsigned char disable_pwm_f1 = 0;
unsigned char disable_pwm_f2 = 0;
unsigned char disable_pwm_f3 = 0;
unsigned char disable_pwm_f4 = 0;
unsigned char kil_open_fors = 0;
unsigned char proverka_fors = 20;


//ïåðåìåííàÿ äëÿ ðàáîòû ñ îòîáðàæåíèåì ðàáîòû ÄÔ
unsigned char dopi_per_2;
unsigned char kil_zyb_df;


//--------------------------- UART
void Init_UART(void);
void UART_RX_int(void);
void Send_UART_char(register unsigned char char_UTx);
signed int Sscanf_variable(unsigned char __near *array_char_var);
signed int Sf_variable(unsigned char __near *array_char_var);
void Printf_Variable_UART(int var);
void Sprintf_main(unsigned char __near *Arr_ch, int var_m);
void printf_const_UART(unsigned char const __flash *Array_const_char);
void NRZ_UART(void);
void Ok_UART(void);
//--------------------------- end UART
//--------------------------- timer
void init_timer0_2(void);
void init_timer1(void);
//void init_timer2(void);
void init_timer3(void);
void init_timer4(void);
void init_timer5(void);
void stop_timer0(void);
void stop_timer1(void);
void stop_timer2(void);
void stop_timer4(void);
void Delay_S(unsigned int Delay_long);
//void delay(unsigned int delay_us);
//--------------------------------- end timer
//--------------------------------- Kernel
void Run_Kernel(void);
//--------------------------------- end Kernel
//--------------------------------- Command
void Analiz_Command(void);
unsigned char Search_Find_Command(unsigned char const __flash *Array_const_char);
void Error_message(unsigned char Number_error);
unsigned char CRC_PROV(unsigned char wert);

//------------------------------------------------------------------------------
void reset(void);
void test(void);
void ver(void);
void var(void);
void run(void);
void read(void);
void tab(void);
void rxd(void);
void tbk(void);

//--------------------------------- end Command
//----------------------------------ADC
__near unsigned int ADC_area_[8];

void Init_ADC_Free(void);
void Stop_ADC(void);
//unsigned int ADC_read(unsigned char adc_mux);
//----------------------------------end ADC

//---------------------------------- interr_Ex.h
void init_External_interrupt(void);
void init_External_PCINT(void);
void stop_External_interrupt(void);
//---------------------------------- end interr_Ex.h

//---------------------------------- GD.h
void PID_regulator(void);
void PID_regulator_temperature(void);
void Taxometer_qvant(void);
void temperature_collector_reduktor(void);
void Run_GD(void);
void Stop_GD(void);
void Condition(void);
//---------------------------------- end GD.h

//--------------------------------- Test.h ---------------------------------
void test_system__GD(void);
void Rele_on_off(void);
void GAS_on_off(void);
void MUZD_on_off(void);
void Kl_on_off(void);

void VAR_test_ind(signed int var_indik);
void akselerometr_test_ind(void);
void ADC_test_ind(void);
void Taxometer_test(void);
void Axelerometr_calibr(void);
void pressure_calibration(void);
void Mahovik_Calibration(void);
void Error_function_e(unsigned int Er_L);
unsigned char test_hdd(void);
unsigned char test_treadle(void);
unsigned char test_dat_dav(void);
void Test_Switch(void);
void Test_MUZD_ON(void);
void Test_MUZD_OFF(void);

void TEST_FORS_2(void);
void TEST_HD(void);
void TEST_DD(void);
void TEST_KIL_ZYB(void);
//--------------------------------- end Test.h -----------------------------

// -------------------------------- RW_EEPROM.h ----------------------------
void send_byte_Card_I2C(unsigned char byte_l);
char Get_byte_Card_I2C(void);
void S_P_Card_I2C(unsigned char flag_l);
void Reset_Card_I2C(void);
unsigned char ACK_Card_I2C(void);
void write_Card_2K_I2C(int addrres, char byte_i2c);
char Read_Card_2K_I2C(int addrres);
void init_PRINTF_var(void);
//void init_eeprom_var(void);
void write_eeprom_24LC16B(void);
void read_eeprom_24LC16B(void);
void init_24LC16B_var(void);
//ïðîãðàììà äëÿ çàïèñè íà÷àëüíûõ ïàðàìåòðîâ ðàáîòû
void write_test_data(void);
// -------------------------------- end RW_EEPROM.h ------------------------

// -------------------------------- interf_PC.h ----------------------------
void PC_indicator_state(void);
// -------------------------------- end interf_PC.h ------------------------

//--------------------------------- Step_Motor.h ---------------------------
void Step_Motor_init(void);
//--------------------------------- end Step_Motor.h -----------------------

float taxo_filt=0; //ôèëüòð òàõîìåòðà 1-ãî ïîðÿäêà

