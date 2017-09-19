
//3-4-2-1

#include <stdio.h>
//#include <iom640.h>
#include <iom2560.h>
#include <ina90.h>
#include <math.h>
//--------------------------
#include <List_Command.h>
#include <Declar.h>
#include <model_var.h>
#include <UART.h>
#include <timer.h>
#include <Kernel.h>
#include <Command.h>
#include <ADC.h>
#include <interr_Ex.h>
#include <GD.h>
#include <Test.h>
#include <RW_EEPROM.h>
#include <interf_PC.h>
#include <Step_Motor.h>
//#include <iccext.h>

//--------------------------------- main ---------------------------------

void main(void)
{ 
 //----- 24LC16B RESET ----------
 Reset_Card_I2C();
 //write_test_data();

 //настройки для АЦП
 //PORTF = 0x00;
 DDRF = 0x00;
 //PORTF = 0x00;
 
 //-----------------
 Switch_Klapan_1_OUT;
 Switch_Klapan_2_OUT;
 Switch_Klapan_3_OUT;
 Switch_Klapan_4_OUT;
 //-----------------
 Switch_Klapan_1_OFF;
 Switch_Klapan_2_OFF;
 Switch_Klapan_3_OFF;
 Switch_Klapan_4_OFF;
 //----------------
 Switch_Klapan_1_IN;
 Switch_Klapan_2_IN;
 Switch_Klapan_3_IN;
 Switch_Klapan_4_IN;

 //------------
 //DDRA |= 0x0F;      //disable switch
 //Switch_RELE_OUT;
 Switch_GAS_OUT;
 Switch_MUZD_OUT;
 Switch_MUZD_V_OUT;
 ///PORTA &= ~0x0F;
 //Switch_RELE_OFF;
 Switch_GAS_OFF;
 Switch_MUZD_OFF;
 Switch_MUZD_V_OFF;
 //DDRA &= ~0xF0;
 //Switch_RELE_IN;
 Switch_GAS_IN;
 Switch_MUZD_IN;
 Switch_MUZD_V_IN;

 
 Button_GD_IN;
 Yellow_diod_OUT;
 Red_diod_OUT;
 Bazer_OUT;
 Yellow_diod_OFF;
 Red_diod_OFF;
 on_fors_8 = 0; 
 Bazer_ON;
 
 //--------------------
 DDRD &= ~0x80;     // Sensor maxovika
 DDRD &= ~0x01;     // Sensor Holla
 PORTD |= 0x01;
 Koncevik_MUZD_IN;  // konc MYZD
 ON_OFF_Car_IN;     // ON OFF switch Car

 
 
 // -------------- EEPROM ---------------------------------------------
 //init_eeprom_var();
 init_24LC16B_var();
 //------------- end EEPROM -------------------------------------------
 
 
 PORTK = 0x00;
 DDRK = 0xFF;//0x00;
 PORTK = 0x00;//0xFF;
 
 Init_UART();
 Init_ADC_Free();
 init_timer1();
 //init_timer0_2();
 init_External_interrupt();
 init_External_PCINT();
 init_timer3();
 //init_timer4();
 
 //отключение PWM
 TCNT5=0;
 TIMSK5=0;
 TCCR5B=0;
 
 Prot_F1_OUT;
 Prot_F2_OUT;
 Prot_F3_OUT;
 Prot_F4_OUT;
 
 Prot_F1_OFF;
 Prot_F2_OFF;
 Prot_F3_OFF;
 Prot_F4_OFF;
     
 __enable_interrupt();
 
 //init_PRINTF_var();
 
 //DDRJ |= 0x3F;      //step motor
 //коэф. для шаговика....
 Step_Motor_Koeff = 4;
 enable_out_pc_paket = 2;
 speed_SM = 64190;
 Step_Motor_init();
 
 I01_stepM_OFF;
 I11_stepM_ON;//OFF;
 I02_stepM_OFF;
 I12_stepM_ON;//OFF;
 
 //Flag_PC_interf = 1;
 
 Bazer_OFF;
 STOP_RUN_GD = 0;
 
 
 
 Run_Kernel();

}