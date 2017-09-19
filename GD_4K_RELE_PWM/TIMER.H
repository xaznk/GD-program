//-------------------------------- timer.h --------------------------------------
// 16 000 000 MHz
// interrupt timer/counter0  overflow error

//#define _offset_TC0     219   //zub //1ms  //183
#define _CK_dev_TC0     7     // external //4   dev / 256

#define _offset_TC1     0
#define _CK_dev_TC1     4       // dev/256  62500
//#define _offset_TC2     100       //125   231
//#define _CK_dev_TC2     7           // dev/128
#define _offset_TC3     64911       // 625 0   --- 64911
#define _CK_dev_TC3     4           // dev/256 
#define _CK_dev_TC4     2           // dev/8
#define _offset_TC4     65136       // 400 ---- 0,2 ms
//#define _CK_dev_TC5     2           // dev/8 

/*#define sw1_number_tooth  256-10
#define sw2_number_tooth  256-100
#define sw3_number_tooth  256-100
#define sw4_number_tooth  256-100*/



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                        ОБРАБОТКА ПРЕРЫВАНИЯ "ТАЙМЕРА 0"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma vector=TIMER0_OVF_vect
__interrupt void TIMER0_OVF_interrupt(void)
{    
if(enable_pysk_ras == 0)
{     
         Faza_motora = Faza_motora + 1;
         TCNT0=256-swN_number_tooth;
      
         //сбросили счетчик ошибки тах
         clear_error_tax = 0;
         ERROR_tax = 0;
         ERROR_out_6 = ERROR_out_6 & 0x0F;
 
         if(Delay_kl>Low_Level_PID)
         {      
            switch(Faza_motora)
            {
               case 1:
               {                 
                  if(disable_pwm_f1 == 0)
                  {
                     //проверка первой форсунки
                     if((Switch_Klapan_4_READ)!=0)
                     {
                         enab_for_3 = 2; 
                     }
                     //открываем форсунку 3
                     Switch_Klapan_4_ON;//fors_3 -> ON
                     Prot_F3_ON;   
                     //начало опроса форсунки 3 на КЗ
                     number_fors_kz = 3;
                     //PCMSK2 = 0x80; 
                     //PORTK|=0x80;
                     //PORTK&=~0x40;

                     //включаем PWM
                     fors_pwm = 2;
                     kil_thit = 0;
                     kil_open_fors = 0;
                     on_off_fors_pwm = 2;
                     TCNT5=0xfd0e;
                     TCCR5B=0x01;
                     TIMSK5|=0x01;
                     //запрещаем вход 
                     disable_pwm_f1 = 1;
                  }
               }
               break;
               
               case 2:
               {                   
                  if(disable_pwm_f2 == 0)
                  {
                     if((Switch_Klapan_1_READ)!=0)
                     {
                         enab_for_4 = 2;    //enable Kl_3   
                     }
                
                     Switch_Klapan_1_ON;//fors_4 -> ON
                     Prot_F4_ON;
                     //начало опроса форсунки 4
                     number_fors_kz = 4;
                     //PCMSK2 = 0x40;
                     //PORTK|=0x40;
                     //PORTK&=~0x80;
                    
                     //включаем PWM
                     fors_pwm = 3;
                     kil_open_fors = 0;
                     on_off_fors_pwm = 2;
                     TCNT5=0xfd0e;
                     TCCR5B=0x01;
                     TIMSK5|=0x01;
                     
                     disable_pwm_f2 = 1;
                  }
               }
               break;
          
               case 3:
               {
                  if(disable_pwm_f3 == 0)
                  {
                     if((Switch_Klapan_2_READ)!=0)
                     {
                         enab_for_2 = 2;    
                     }
                     Switch_Klapan_2_ON;//fors_2 -> ON
                     Prot_F2_ON;
                     //начало опроса форсунки 2
                     number_fors_kz = 2;
                     //PCMSK2 = 0x20;
                    
                     //включаем PWM
                     fors_pwm = 1;
                     kil_open_fors = 0;
                     on_off_fors_pwm = 2;
                     TCNT5=0xfd0e;
                     TCCR5B=0x01;
                     TIMSK5 |= 0x01;
                    
                     disable_pwm_f3 = 1;
                  }
               }
               break;
               
               case 4:
               {  
                  if(disable_pwm_f4 == 0)
                  {
                     if((Switch_Klapan_3_READ)!=0)
                     {
                         enab_for_1 = 2;    
                     }
                    
                     //Switch_Klapan_1_ON;
                     Switch_Klapan_3_ON;//fors_1 -> ON  
                     Prot_F1_ON;
                     //начало опроса форсунки 1
                     number_fors_kz = 1;
                     PCMSK2 = 0x10;//01;
                    
                     //включаем PWM
                     fors_pwm = 0;
                     kil_open_fors = 0;
                     on_off_fors_pwm = 2;
                     TCNT5=0xfd0e;
                     TCCR5B=0x01;
                     TIMSK5 |= 0x01;
                     
                     disable_pwm_f4 = 1;
                  }
               }
               break;
               default:break;
           }
           Klapana_area[Faza_motora-1]=Delay_kl;
        }
        taxometer_count=TCNT1;        // 1 oborota motora    
        if((TIFR1&0x01)==0x01)
        {
           taxometer_count=i_maxovik_timer;
           TIFR1 |= 0x01;
        }
        TCNT1=0;
        TCCR1B=_CK_dev_TC1;  // dev /256
        Flag_taxometer=1;      
}
else if(enable_pysk_ras == 2)
{
     tim_io = 1;
}
      //__enable_interrupt();      
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                        ОБРАБОТКА ПРЕРЫВАНИЯ ТАЙМЕРА 3
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma vector=TIMER3_OVF_vect
__interrupt void TIMER3_OVF_interrupt(void)
{
  TCNT3=speed_SM;//_offset_TC3;
  miliSekundomer_ms++;//10ms
  signal_timer_ms++;//10ms
  migi_migi++;
  
  //----------------------------------------------------------------------------
  //запуск RUN_GD   
  //----------------------------------------------------------------------------
  if(enable_mig_green == 1)
  {
     switch(migi_migi)
     {
         case(12):{Yellow_diod_OFF;};break;
         case(24):{Yellow_diod_ON;};break;
         case(36):{Yellow_diod_OFF;};break;
         case(48):{Yellow_diod_ON;migi_migi = 0;};break;
         default:{};break;
     }      
  }
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
    
  //--------------
  Test_PC_count++;
  if(Test_PC_count==10)
  {
     //сделать проверку
     enable_test_system = 1;
  }
  //разрешить передачу
  if(Test_PC_count==12)
  {
     Test_PC_count=0;
     if(enable_out_pc_paket == 2)
     {
         if(Flag_PC_interf==1) 
         {
            enable_out_pc_paket = 0; 
            PC_indicator_state();
         }
     }
    //--- narabotka
    Test_Narabotka_count++;
    if(Test_Narabotka_count==120)
    {
       if(Flag_State_Run_GD==1) Narabotka_GAS_count++;
       if(Flag_on_off_motor==1) Narabotka_count++;
       Test_Narabotka_count=0;
    }
    //----
    //if((Test_Narabotka_count&0x01)==0) Flag_temperature=1;
    //----
  }
  //---------------
  if(Step_Motor_Position!=Step_Motor_Future)
  {
     switch(NAP_MUZD)
     {
        case(0):
        {
           if(Step_Motor_Position<Step_Motor_Future)
           {
              Faza_Step_Motor++;
              if(Faza_Step_Motor==5) Faza_Step_Motor=1;
              Step_Motor_Position++;
              speed_SM = 64911;//64800;//64500;//65536
           }
           else
           {
              Faza_Step_Motor--;
              if(Faza_Step_Motor==0) Faza_Step_Motor=4;
              Step_Motor_Position--;
              speed_SM = 64911;//65100;//64911;//64900;//65000;//65536
           }
        }
        break;
        default:
        {
           if(Step_Motor_Position<Step_Motor_Future)
           {
              Faza_Step_Motor--;
              if(Faza_Step_Motor==0) Faza_Step_Motor=4;
              Step_Motor_Position++;
              speed_SM = 64911;//64800;//64500;//65536
           }
           else
           {
              Faza_Step_Motor++;
              if(Faza_Step_Motor==5) Faza_Step_Motor=1;
              Step_Motor_Position--;
              speed_SM = 64911;//65100;//64911;//64900;//65000;//65536
           }
        }
        break;
     }
     switch(Faza_Step_Motor)
     {
         case 1:
             PHASE1_stepM_ON;
             PHASE2_stepM_ON;
         break;
         case 2:
             PHASE1_stepM_OFF;
             PHASE2_stepM_ON;
         break; 
         case 3:
             PHASE1_stepM_OFF;
             PHASE2_stepM_OFF;
         break;
         case 4:
             PHASE1_stepM_ON;
             PHASE2_stepM_OFF;
         break;
      }
      //Count_Step_Motor--;
   }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                        ОБРАБОТКА ПРЕРЫВАНИЯ ТАЙМЕРА 4
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma vector=TIMER4_OVF_vect
__interrupt void TIMER4_OVF_interrupt(void)
{
  TCNT4=_offset_TC4;
  //microSecundomer++;
  
  //----------------------------------------------------------------------------1
  if(Klapana_area[0]!=0) 
  {
     Klapana_area[0]--;
  }
  else
  {   
     //отключение PWM
     if(disable_pwm_f1 == 1)
     {
        TCNT5=0;
        TIMSK5=0;
        TCCR5B=0;
        disable_pwm_f1 = 0;
     } 
     
     //Switch_Klapan_6_OFF; 
     Switch_Klapan_4_OFF;//fors_3 -> OFF
     Prot_F3_OFF;
     PORTK&=~0x80;
  }
  //----------------------------------------------------------------------------2
  if(Klapana_area[1]!=0) 
  {
     Klapana_area[1]--; 
  }
  else
  {    
     //отключение PWM
     if(disable_pwm_f2 == 1)
     {
        TCNT5=0;
        TIMSK5=0;
        TCCR5B=0;
        disable_pwm_f2 = 0;
     } 
     
     //Switch_Klapan_3_OFF;
     Switch_Klapan_1_OFF;//fors_4 -> OFF
     Prot_F4_OFF;
     PORTK&=~0x40;
  }
  //----------------------------------------------------------------------------3
  if(Klapana_area[2]!=0) 
  {
      Klapana_area[2]--;
  }
  else
  {
      //отключение PWM
      if(disable_pwm_f3 == 1)
      {
         TCNT5=0;
         TIMSK5=0;
         TCCR5B=0;
         disable_pwm_f3 = 0;
      } 
      
      //Switch_Klapan_4_OFF;
      Switch_Klapan_2_OFF;//fors_2 -> OFF
      Prot_F2_OFF;
  }
  //----------------------------------------------------------------------------4
  if(Klapana_area[3]!=0) 
  {   
     Klapana_area[3]--; 
  }
  else 
  {  
     //отключение PWM
     if(disable_pwm_f4 == 1)
     {
        TCNT5=0;
        TIMSK5=0;
        TCCR5B=0;
        disable_pwm_f4 = 0;
     } 
     //Switch_Klapan_1_OFF;
     Switch_Klapan_3_OFF;//fors_1 -> OFF
     Prot_F1_OFF;
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++PWM-----
//                        ОБРАБОТКА ПРЕРЫВАНИЯ ТАЙМЕРА 5
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++PWM-----
#pragma vector=TIMER5_OVF_vect
__interrupt void TIMER5_OVF_interrupt(void)
{
  TCNT5=0xfd0e;
  
  switch(fors_pwm)
  {
      //PWM для форсунки номер 1
      case(0):
      {
          switch(on_off_fors_pwm)
          {
              case(0):
              {
                  Switch_Klapan_3_OFF;
                  on_off_fors_pwm = 1;
              }
              break;
              case(1):
              {
                  Switch_Klapan_3_ON;
                  on_off_fors_pwm = 0;
              }
              break;
              case(2):
              {
                  if(enab_for_1 == 2)
                  {
                     if((Switch_Klapan_3_READ)==0)
                     {
                         step_opros_fors_1 = step_opros_fors_1 + 1;
                     }
                  } 
                  
                  kil_open_fors = kil_open_fors + 1;
                  if(kil_open_fors == 70)
                  {
                     kil_open_fors = 0;
                     on_off_fors_pwm = 0;
                     enab_for_1 = 0;
                     proverka_fors = 1;
                  }
              }
              break;
          }
      }
      break;
      //PWM для форсунки номер 2
      case(1):
      {
          switch(on_off_fors_pwm)
          {
              case(0):
              {
                  Switch_Klapan_2_OFF;
                  on_off_fors_pwm = 1;
              }
              break;
              case(1):
              {
                  Switch_Klapan_2_ON;
                  on_off_fors_pwm = 0;
              }
              break;
              case(2):
              {
                  if(enab_for_2 == 2)
                  {
                     if((Switch_Klapan_2_READ)==0)
                     {
                         step_opros_fors_2 = step_opros_fors_2 + 1;
                     }
                  } 
                
                  kil_open_fors = kil_open_fors + 1;
                  if(kil_open_fors == 70)
                  {
                     kil_open_fors = 0;
                     on_off_fors_pwm = 0;
                     enab_for_2 = 0;
                     proverka_fors = 2;
                  }
              }
              break;
          }
      }
      break;
      //PWM для форсунки номер 3
      case(2):
      {
          switch(on_off_fors_pwm)
          {
              case(0):
              {
                  Switch_Klapan_4_OFF;
                  on_off_fors_pwm = 1;
              }
              break;
              case(1):
              {
                  Switch_Klapan_4_ON;
                  on_off_fors_pwm = 0;
              }
              break;
              case(2):
              {
                  if(enab_for_3 == 2)
                  {
                      if((Switch_Klapan_4_READ)==0)
                      {
                          step_opros_fors_3 = step_opros_fors_3 + 1;
                      }
                  } 
                
                  kil_open_fors = kil_open_fors + 1;
                  if(kil_open_fors == 70)
                  {
                      kil_open_fors = 0;
                      on_off_fors_pwm = 0;
                      enab_for_3 = 0;
                      proverka_fors = 3;
                  }
              }
              break;
          }
      }
      break;
      //PWM для форсунки номер 4
      case(3):
      {
          switch(on_off_fors_pwm)
          {
              case(0):
              {
                  Switch_Klapan_1_OFF;
                  on_off_fors_pwm = 1;
              }
              break;
              case(1):
              {
                  Switch_Klapan_1_ON;
                  on_off_fors_pwm = 0;
              }
              break;
              case(2):
              {
                  if(enab_for_4 == 2)
                  {
                     if((Switch_Klapan_1_READ)==0)
                     {
                         step_opros_fors_4 = step_opros_fors_4 + 1;
                     }
                  }
                
                  kil_open_fors = kil_open_fors + 1;
                  if(kil_open_fors == 70)
                  {
                     kil_open_fors = 0;
                     on_off_fors_pwm = 0;
                     enab_for_4 = 0;
                     proverka_fors = 4;
                  }
              }
              break;
          }
      }
      break;
  } 
}  


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            ИНИЦИАЛИЗАЦИЯ ТАЙМЕРА 0
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_timer0_2(void)
{
  //__disable_interrupt();
  //TCNT0=_offset_TC0;
  TCCR0B |=_CK_dev_TC0;
  TIMSK0 |=0x01;
  //__enable_interrupt();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            ИНИЦИАЛИЗАЦИЯ ТАЙМЕРА 1
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_timer1(void)
{
  //__disable_interrupt();
  TCNT1=0;
  //TIMSK |= 0x04;
  TCCR1B=_CK_dev_TC1;
  //__enable_interrupt();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            ИНИЦИАЛИЗАЦИЯ ТАЙМЕРА 3
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_timer3(void)
{
  //__disable_interrupt();
  TCNT3=_offset_TC3;
  TIMSK3 |= 0x01;
  TCCR3B=_CK_dev_TC3;
  //__enable_interrupt();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            ИНИЦИАЛИЗАЦИЯ ТАЙМЕРА 4
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_timer4(void)
{
  //__disable_interrupt();
  TCNT4=_offset_TC4;
  TIMSK4 |= 0x01;
  TCCR4B=_CK_dev_TC4;
  //__enable_interrupt();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                            ИНИЦИАЛИЗАЦИЯ ТАЙМЕРА 5
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void init_timer5(void)
{
  //__disable_interrupt();
  TCNT5=0x00;
  TIMSK5 |= 0x01;
  TCCR5B=0x01;
  //__enable_interrupt();
}

void stop_timer4(void)
{
  __disable_interrupt();
  TIMSK4 &= ~0x01;
  TCCR4B=0x00;
  __enable_interrupt();
}

void Delay_S(unsigned int Delay_long)
{
  register unsigned int counter=0;
  while(counter != Delay_long) counter++;
}

//--------------------------------- end
