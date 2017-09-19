//-------------------------- model_var.h -----------------------------------------
#define     max_turns_motora_dizel    3000
#define     min_turns_motora_dizel    600//800
#define     motor_cylinders           4


//------------------------------------------------------------------------------
#define     Switch_Klapan_3_OUT   DDRC|=0x01     // 1 fors
#define     Switch_Klapan_3_OFF   PORTC&=~0x01
#define     Switch_Klapan_3_ON    PORTC|=0x01
#define     Switch_Klapan_3_IN    DDRC&=~0x10
#define     Switch_Klapan_3_READ  PINC&0x10
#define     Switch_Klapan_3_READ_on  PORTC|=0x10

#define     Prot_F1_OUT   DDRB|=0x80    
#define     Prot_F1_OFF   PORTB&=~0x80
#define     Prot_F1_ON    PORTB|=0x80

#define     Switch_Klapan_2_OUT   DDRC|=0x02     // 2 fors
#define     Switch_Klapan_2_OFF   PORTC&=~0x02
#define     Switch_Klapan_2_ON    PORTC|=0x02
#define     Switch_Klapan_2_IN    DDRC&=~0x20
#define     Switch_Klapan_2_READ  PINC&0x20
#define     Switch_Klapan_2_READ_on  PORTC|=0x20

#define     Prot_F2_OUT   DDRB|=0x02    
#define     Prot_F2_OFF   PORTB&=~0x02
#define     Prot_F2_ON    PORTB|=0x02

#define     Switch_Klapan_4_OUT   DDRC|=0x04     // 3 fors
#define     Switch_Klapan_4_OFF   PORTC&=~0x04
#define     Switch_Klapan_4_ON    PORTC|=0x04
#define     Switch_Klapan_4_IN    DDRC&=~0x40
#define     Switch_Klapan_4_READ  PINC&0x40
#define     Switch_Klapan_4_READ_on  PORTC|=0x40

#define     Prot_F3_OUT   DDRB|=0x08    
#define     Prot_F3_OFF   PORTB&=~0x08
#define     Prot_F3_ON    PORTB|=0x08

#define     Switch_Klapan_1_OUT   DDRC|=0x08     // 4 fors
#define     Switch_Klapan_1_OFF   PORTC&=~0x08
#define     Switch_Klapan_1_ON    PORTC|=0x08
#define     Switch_Klapan_1_IN    DDRC&=~0x80
#define     Switch_Klapan_1_READ  PINC&0x80
#define     Switch_Klapan_1_READ_on  PORTC|=0x80

#define     Prot_F4_OUT   DDRB|=0x04    
#define     Prot_F4_OFF   PORTB&=~0x04
#define     Prot_F4_ON    PORTB|=0x04

#define     Switch_Klapan_1_PCI   DDRK&=~0x01
#define     Switch_Klapan_2_PCI   DDRK&=~0x02
#define     Switch_Klapan_3_PCI   DDRK&=~0x04
#define     Switch_Klapan_4_PCI   DDRK&=~0x08
#define     Switch_Klapan_5_PCI   DDRK&=~0x10
#define     Switch_Klapan_6_PCI   DDRK&=~0x20
#define     Switch_Klapan_7_PCI   DDRK|=0x40//DDRK&=~0x40
#define     Switch_Klapan_8_PCI   DDRK|=0x80//&=~0x80
//------------------------------------------------------------------------------

//#define     Switch_RELE_OUT       DDRA|=0x01
//#define     Switch_RELE_ON        PORTA|=0x01
//#define     Switch_RELE_OFF       PORTA&=~0x01
//#define     Switch_RELE_IN        DDRA&=~0x10
//#define     Switch_RELE_READ      PINA&0x10

#define     Switch_GAS_OUT        DDRL|=0x10
#define     Switch_GAS_ON         PORTL|=0x10
#define     Switch_GAS_OFF        PORTL&=~0x10

#define     Switch_GAS_IN         DDRD&=~0x08
#define     Switch_GAS_READ       PIND&0x08
/*
#define     Switch_RELE_OUT       __no_operation()
#define     Switch_RELE_ON        __no_operation()
#define     Switch_RELE_OFF       __no_operation()
#define     Switch_RELE_IN        __no_operation()
#define     Switch_RELE_READ      0x01&0x01

#define     Switch_GAS_OUT        __no_operation()
#define     Switch_GAS_ON         __no_operation()
#define     Switch_GAS_OFF        __no_operation()
#define     Switch_GAS_IN         __no_operation()
#define     Switch_GAS_READ       0x01&0x01
*/

#define     Switch_MUZD_OUT     DDRA|=0x08     // 5 fors
#define     Switch_MUZD_OFF      PORTA&=~0x08
#define     Switch_MUZD_ON     PORTA|=0x08
#define     Switch_MUZD_IN      DDRD&=~0x20
#define     Switch_MUZD_READ    PIND&0x20

#define     Switch_MUZD_V_OUT   DDRA|=0x04     // 6 fors 
#define     Switch_MUZD_V_OFF    PORTA&=~0x04
#define     Switch_MUZD_V_ON   PORTA|=0x04
#define     Switch_MUZD_V_IN    DDRD&=~0x10
#define     Switch_MUZD_V_READ  PIND&0x10


#define     Koncevik_MUZD_IN      DDRB&=~0x10
#define     Koncevik_MUZD_READ    PINB&0x10

#define     Button_GD_IN          DDRB&=~0x40
#define     Button_GD_READ        PINB&0x40

#define     ON_OFF_Car_IN         DDRJ&=~0x40
#define     ON_OFF_Car_READ       PINJ&0x40
/*#define     ON_OFF_Car_IN         DDRF&=~0x04
#define     ON_OFF_Car_READ       PINF&0x04*/

#define     Faza_Motora_READ      PIND&0x01
#define     Tooth_Motora_READ     PIND&0x80



void Run_GD(void)
{
  unsigned char Status_w=0;
  unsigned char y_L=0;
  
  enable_mig_green = 1;
  ERROR_f_kz = 0;
  ERROR_out_1 = 0;
  ERROR_out_2 = 0;
  ERROR_out_3 = 0;
  ERROR_out_4 = 0;
  
  //miliSekundomer_ms=0;
  //init_timer0_2();
  
  //Triger_Idling_K0=0;
  ////////////////////////////////////////////Bazer_ON;
  //enable_signal = 1;
  signal_number = 0;
  signal_timer_ms = 0;
  Bazer_ON;
  ////////////////////////////////////////////Bazer_ON;
  
  I01_stepM_OFF;
  I11_stepM_OFF;
  I02_stepM_OFF;
  I12_stepM_OFF;
  Send_UART_char('|');
  
  while(signal_timer_ms<PISK_RUN_GD) __no_operation();
  Bazer_OFF;
  
  //Step_Motor_Future=Step_Motor_OffSet*Step_Motor_Koeff;
  //
  y_L=taxometer/200;
  if(y_L<(min_turns_motora_dizel/200)) y_L=min_turns_motora_dizel/200;
  if(y_L>15) y_L=15;
  Step_Motor_Koeff = 4;
  Step_Motor_Future = (Step_Motor_OffSet + Step_motor_array_cicle[y_L])*Step_Motor_Koeff;// Step motor  
   
  while(Step_Motor_Future!=Step_Motor_Position) __no_operation();
  //Switch_RELE_ON;
  miliSekundomer_ms=0;
  while(miliSekundomer_ms<30) __no_operation();
  //if(Status_w==1) Send_UART_char('T');
  //////////////////////////////////////////////////////while(Step_Motor_Future!=Step_Motor_Position) __no_operation();
  Send_UART_char('|');
  Switch_GAS_ON;
  Switch_MUZD_V_ON;     //vtyagivanie glushilki
  miliSekundomer_ms=0;
  while(miliSekundomer_ms<30) __no_operation();
  Switch_MUZD_V_OFF;     //vtyagivanie glushilki
  Switch_MUZD_ON;
  miliSekundomer_ms=0;
  Status_w=0;
  do
  {
    if((Koncevik_MUZD_READ)==0) Status_w=1;
    __no_operation();
    if(miliSekundomer_ms>100) Status_w=2;
    //------------------
  }
  while(Status_w==0);
  
  Send_UART_char('|');
  //if(Status_w==2)
  //{
  //  Stop_GD();
  //  Error_function_e(Error_D_Konc_MUZD);
  //}
  //else
  //{
    Send_UART_char('|');
    Yellow_diod_ON;         // yellow diod
    Send_UART_char('S');
    init_timer4();
    Flag_State_Run_GD=1;
  //}
  STOP_RUN_GD = 1;
  enable_mig_green = 0;
}



void Stop_GD(void)
{
  /////////////////////////////////////////////Bazer_ON;
  //enable_signal = 1;
  signal_number = 1;
  signal_timer_ms = 0;
  Bazer_ON;
  ////////////////////////////////////////////Bazer_ON;
  
  stop_timer4();
  Flag_State_Run_GD=0;
  Flag_quantization_step_PID=0;
  Flag_taxometer=0;
  Delay_kl=0;
  Switch_Klapan_1_OFF;    //disable Kl_1
  Switch_Klapan_2_OFF;
  Switch_Klapan_3_OFF;
  Switch_Klapan_4_OFF;
  Switch_GAS_OFF;  // YA3   gas
  Switch_MUZD_OFF;  // YA2   muzd
  Switch_MUZD_V_ON;     //vtyagivanie glushilki
  miliSekundomer_ms=0;
  while(miliSekundomer_ms<30) __no_operation();
  Switch_MUZD_V_OFF;     //vtyagivanie glushilki
  Yellow_diod_OFF;       // yellow diod
  //Switch_RELE_OFF;       // YA1   rele
  
  //Step_Motor_Future = 0;
  //miliSekundomer_ms=0;
  //while(miliSekundomer_ms<30) __no_operation();
  //while(Step_Motor_Future!=Step_Motor_Position) __no_operation();
  //while(miliSekundomer_ms<30) __no_operation();
  
  while(signal_timer_ms<40) __no_operation();
  Bazer_OFF;
  Step_Motor_init();
  
  I01_stepM_ON;
  I11_stepM_ON;
  I02_stepM_ON;
  I12_stepM_ON;
  Send_UART_char('X');
  
  Bazer_OFF;
  STOP_RUN_GD = 0;
}



void MUZD_on_off(void)
{
  NRZ_UART();
  //if((Switch_MUZD_READ)!=0)
  if(Flag_en_dis_switch==0)
  {
    //Switch_MUZD_V_ON;     //vtyagivanie glushilki
    //__disable_interrupt();
    //miliSekundomer_ms=0;
    //__enable_interrupt();
    //while(miliSekundomer_ms<30) __no_operation();
    //Switch_MUZD_V_OFF;     //vtyagivanie glushilki
    //Switch_MUZD_ON;  // YA2
    printf_const_UART(test_on);
    while((Koncevik_MUZD_READ)!=0) __no_operation();
    Send_UART_char('k');
    Flag_en_dis_switch=1;
  }
  else
  {
    //Switch_MUZD_OFF;  // YA2
    /*Switch_MUZD_V_ON;     //vtyagivanie glushilki
    __disable_interrupt();
    miliSekundomer_ms=0;
    __enable_interrupt();
    while(miliSekundomer_ms<30) __no_operation();
    Switch_MUZD_V_OFF;     //vtyagivanie glushilki*/
    printf_const_UART(test_off);
    Flag_en_dis_switch=0;
  }
  //Symbol_key=0;
  Flag_test_local=1;
}
//--------------------------end model_var.h --------------------------------------


