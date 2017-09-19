//--------------------------------------- Kernel.h -------------------------------------------------------

/*unsigned char Flag_Command=0;
unsigned char Flag_paketa=0;
unsigned char Flag_Run=0;*/
int i,it;

unsigned char LED_ON_OFF;


void Run_Kernel(void)
{
  Flag_Command=0;
  //Send_UART_char('#');
  
  do
  {
    /* 
    Switch_Klapan_3_ON;//fors_1 -> ON
     for(i=0;i<10;i++)
     {
        Delay_S(10000);
     }
     
     
     for(it=0;it<1000;it++)
     {
     Switch_Klapan_3_ON;//fors_1 -> ON
     for(i=0;i<10;i++)
     {
         Delay_S(100);
     }
     Switch_Klapan_3_OFF;//fors_1 -> OFF
     for(i=0;i<10;i++)
     {
        Delay_S(100);
     }
     }
     
     
     for(it=0;it<1000;it++)
     {
     for(i=0;i<10;i++)
     {
         Delay_S(100);
     }
     Switch_Klapan_3_OFF;//fors_1 -> OFF
     for(i=0;i<10;i++)
     {
        Delay_S(100);
     }
     }
    */
     
     

    if(Flag_State_Run_GD==1)
    {
      if(Flag_quantization_step_PID==1) PID_regulator();
      //if(Flag_PC==1) void;
    }
    if(Flag_taxometer==1) 
    {
       Taxometer_qvant();
    }
    //if(Flag_temperature==1) temperature_collector_reduktor();
    //---if(taxometer>idling_motor_dizel-200) Flag_on_off_motor=1; else Flag_on_off_motor=0;
    if(taxometer>300) Flag_on_off_motor=1; else Flag_on_off_motor=0;
    if(Flag_Command==1) Analiz_Command();//пришел сигнал конца пакета - переход к анализу пакетов данных "COMMAND"
    //
    Condition();
    //"UART" - прием данных.... 
    UART_RX_int();
    

    //-----------------------------------------------------------------------------
    //проверка форсунок во время работы
    //-----------------------------------------------------------------------------
    switch(proverka_fors)
    {
       case(0):
       {
       }
       break;
       case(1):
       {
           //---------------------------------------------------------------------форсунка 1
           if(step_opros_fors_1 > 30)
           {
              step_opros_fors_1 = 0;
              ERROR_f1 = 0; 
              ERROR_out_1 = ERROR_out_1 & 0xF0; 
              proverka_fors = 0;
           }
           else if(step_opros_fors_1 < 30)
           {
              step_opros_fors_1 = 0;
              ERROR_f1 = 1;
              ERROR_out_1 = ERROR_out_1 | 0x03; 
              proverka_fors = 0;
           }
       }
       break;
       
       case(2):
       {
           //-------------------------------------------------------------------форсунка 2
           if(step_opros_fors_2 > 30)
           {
              step_opros_fors_2 = 0;
              ERROR_f2 = 0;
              ERROR_out_1 = ERROR_out_1 & 0x0F; 
              proverka_fors = 0;
           }
           else if(step_opros_fors_2 < 30)
           {
              step_opros_fors_2 = 0;
              ERROR_f2 = 1;
              ERROR_out_1 = ERROR_out_1 | 0x20;
              proverka_fors = 0;
           }  
       }
       break;
       
       case(3):
       {
           //-------------------------------------------------------------------форсунка 3 +  
           if(step_opros_fors_3 > 30)
           {
              step_opros_fors_3 = 0;
              ERROR_f3 = 0;
              ERROR_out_2 = ERROR_out_2 & 0xF0;
              proverka_fors = 0;
           }
           else if(step_opros_fors_3 < 30)
           {
              step_opros_fors_3 = 0;
              ERROR_f3 = 1;
              ERROR_out_2 = ERROR_out_2 | 0x03;
              proverka_fors = 0;
           }  
       }
       break;
       
       case(4):
       {  
           //-------------------------------------------------------------------форсунка 4 
           if(step_opros_fors_4 > 30)
           {
              step_opros_fors_4 = 0;
              ERROR_f4 = 0;
              ERROR_out_2 = ERROR_out_2 & 0x0F;
              proverka_fors = 0;
           }
           else if(step_opros_fors_4 < 30)
           {
              step_opros_fors_4 = 0;
              ERROR_f4 = 1;
              ERROR_out_2 = ERROR_out_2 | 0x20;
              proverka_fors = 0;
           }
       }
       break;
       
       default:
       {
       }
       break;
}

//--------------------------------------------------------------------------проверка системы
if(enable_test_system == 1)
{ 
       //проверка работы датчика педали
       TEST_DD();
       //проверка ШД на обрыв
       //TEST_HD();
       //проверка работы датчика фазы
       clear_error_faza = clear_error_faza + 1;
       clear_error_tax = clear_error_tax + 1;
       if(clear_error_faza > 3)
       {
          ERROR_out_6 = ERROR_out_6 | 0x07;
          ERROR_faza = 1;
          clear_error_faza = 0;
       }
       if(clear_error_tax > 3)
       {
          ERROR_out_6 = ERROR_out_6 | 0x50;
          ERROR_tax = 1;
          clear_error_tax = 0;
       }
    }
    ERROR_out_8 = 0xff;
    //------------------------------------------------------------------------------------------------------------проверка системы
    //------------------------------------------------------------------------------------------------------------проверка системы
    if((ON_OFF_Car_READ)!=0)
    {
       ALL_KIL_ERROR_SYS = 0;
       ALL_KIL_ERROR_SYS = ALL_KIL_ERROR_SYS + ERROR_f1 + ERROR_f2 + ERROR_f3 + ERROR_f4;
       ALL_KIL_ERROR_SYS = ALL_KIL_ERROR_SYS + ERROR_faza + ERROR_tax + ERROR_tt + ERROR_dd + ERROR_gkl + ERROR_term + ERROR_HD;
       if(ALL_KIL_ERROR_SYS == 0)
       {
          if(term_switch == 0)
          {
             Red_diod_OFF;
          }
       }
       else
       {
          if(term_switch == 0)
          {
             Red_diod_ON;
          }
       }
    }
    else
    {
       if(term_switch == 0)
       {
          Red_diod_OFF;
       }
    }  
    //------------------------------------------------------------------------------------------------------------проверка системы
    //------------------------------------------------------------------------------------------------------------проверка системы
    //конец расчета импульсов
    if(enable_pysk_ras == 3)
    {     
       //отправляем сообщение 
       Send_UART_char('&');
       Send_UART_char((char)(data_TCNT0_now));
       enable_pysk_ras = 0;     
       data_TCNT0_now = 0;
    } 
    //------------------------------------------------------------------------------------------------------------сигнал по температуре
    //------------------------------------------------------------------------------------------------------------сигнал по температуре
    //проверяем данные по температуре
    switch(term_switch)
    {
      case(0):
      { 
         Red_diod_OFF;
         //Bazer_OFF;
         ERROR_term = 0;
         enable_signal = 0;
      }
      break;
      case(1):
      {
         //Red_diod_ON;
         ERROR_term = 1;
         enable_signal = 1;
      }
      break;
    }
    //------------------------------------------------------------------------------------------------------------звуковой сигнал 
    //------------------------------------------------------------------------------------------------------------звуковой сигнал
    if(enable_signal == 1)
    {
       switch(signal_number)
       {
           case 0:
           {
               if(signal_timer_ms > 10)
               {
                  signal_timer_ms = 0;
                  enable_signal = 0;
                  signal_number = 1;
                  Bazer_ON;
                  Red_diod_ON;
               }
           }
           break;
           case 1:
           {
               if(signal_timer_ms > 10)
               {
                  signal_timer_ms = 0;
                  enable_signal = 0;
                  signal_number = 2;
                  //Bazer_OFF;
                  Red_diod_OFF;
               }
           }
           break;
           case 2:
           {
               if(signal_timer_ms > 10)
               {
                  signal_timer_ms = 0;
                  enable_signal = 0;
                  signal_number = 3;
                  Bazer_ON;
                  Red_diod_ON;
               }
           }
           break;
           case 3:
           {
               if(signal_timer_ms > 10)
               {
                  signal_timer_ms = 0;
                  enable_signal = 0;
                  signal_number = 4;
                  //Bazer_OFF;
                  Red_diod_OFF;
               }
           }
           break;
           case 4:
           {  
               if(signal_timer_ms > 30)
               {
                  signal_timer_ms = 0;
                  enable_signal = 0;
                  signal_number = 0;
                  //Bazer_OFF;
                  Red_diod_OFF;
               }
           }
           break;
       }
    }
    __enable_interrupt();
    //------------------------------------------------------------------------------------------------------------звуковой сигнал 
    //------------------------------------------------------------------------------------------------------------звуковой сигнал
    
  }
  while(1==1);
}

/*
    switch(nn_m)
    {
       case(1):{Bazer_OFF;nn_m = 0;};break;
       case(0):{Bazer_ON;nn_m = 1;};break;
    }
*/
