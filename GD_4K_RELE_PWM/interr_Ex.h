//-------------------------------------- interr_Ex.h -----------------------------------


#pragma vector=PCINT2_vect
__interrupt void PCINT2_interrupt(void)
{
   PCIFR = 0x00; 
   
   //полное отключение всех форсунок - переход на ГД
   //Stop_GD();  
   //ERROR_f_kz = 1;
   /*
   switch(nn_m)
   {
       case(1):{Bazer_OFF;nn_m = 0;};break;
       case(0):{Bazer_ON;nn_m = 1;};break;
   }
   
   switch(number_fors_kz)
   {
      case(1):
      {
          Switch_Klapan_1_OFF;//fors_1 -> OFF
          //ERROR_out_1 = ERROR_out_1 | 0x08;
      }
      break;
      case(2):
      {
          Switch_Klapan_2_OFF;//fors_2 -> OFF
          //ERROR_out_1 = ERROR_out_1 | 0x80;
      }
      break;
      case(3):
      {
          Switch_Klapan_3_OFF;//fors_3 -> OFF
          //ERROR_out_2 = ERROR_out_2 | 0x08;
      }
      break;
      case(4):
      {
          Switch_Klapan_4_OFF;//fors_4 -> OFF
          //ERROR_out_2 = ERROR_out_2 | 0x80;
      }
      break;
      case(5):
      {
          Switch_Klapan_5_OFF;//fors_5 -> OFF
          //ERROR_out_3 = ERROR_out_3 | 0x08;
      }
      break;
      case(6):
      {
          Switch_Klapan_6_OFF;//fors_6 -> OFF
          //ERROR_out_3 = ERROR_out_3 | 0x80;
      }
      break;
      case(7):
      {
          Switch_Klapan_7_OFF;//fors_7 -> OFF
          //ERROR_out_4 = ERROR_out_4 | 0x08;
      }
      break;
      case(8):
      {
          Switch_Klapan_8_OFF;//fors_8 -> OFF
          //ERROR_out_4 = ERROR_out_4 | 0x80;
      }
      break;
   }  
   */
}  


#pragma vector=INT0_vect
__interrupt void INT0_interrupt(void)
{

  
/*  
 //индикация работы датчика фазы 
 if(dopi_per_2 == 1)
 {
    dopi_per_2 = 0;
    EICRA |= 0x03;                // rising edge(per)  [0V->5V]
    EIMSK |= 0x01;
 }
 else if(dopi_per_2 == 0)
 { 
    dopi_per_2 = 1;
    EICRA |= 0x02;              // falling edge(zad) [5V->0V]
    EIMSK |= 0x01;
 }
 */
 
 
 switch(enable_pysk_ras)
 {
       case(0):
       {
          //__disable_interrupt();
          TIMSK0 &= ~0x01;
          TCCR0B = 0x00;
          //
          //if(on_fors_8 == 0)
          //{
             Faza_motora=0;
             //
             clear_error_faza = 0;
             ERROR_faza = 0;
             ERROR_out_6 = ERROR_out_6 & 0xF0;
            
             TCNT0=256-sw1_number_tooth;
             
             enable_out_data = enable_out_data + 1;
             enable_test_fors = 1;
             kil_f_1 = 0;
             kil_f_2 = 0;
             if(enable_out_data == 4)
             {
                enable_out_data = 0;
             }
          //}
          /*
          else if(on_fors_8 == 1)
          {
             number_ost_8 = TCNT0;
             number_ost_8 = 256-number_ost_8;
             TCNT0=256-number_ost_8;
             on_fors_8 = 2;
             
             //
             clear_error_faza = 0;
             ERROR_faza = 0;
             ERROR_out_6 = ERROR_out_6 & 0xF0;
          } 
          */
          TCCR0B |=_CK_dev_TC0;
          TIMSK0 |=0x01;
          //__enable_interrupt();        
      }
      break;

      case(1):
      {
          TCNT0 = 0; 
          data_TCNT0_now = 0;
          enable_pysk_ras = 2;
          tim_io = 0;
      }
      break;
      
      case(2):
      {
          if(tim_io == 1)
          {
             data_TCNT0_now = TCNT0;
             timer_cou_int = 256;
             timer_cou_int = timer_cou_int + data_TCNT0_now;
             timer_cou_int = timer_cou_int/2;
             data_TCNT0_now = timer_cou_int;
          }
          else if(tim_io == 0)
          {
             timer_cou_int = 0;
             data_TCNT0_now = TCNT0; 
          }         
          enable_pysk_ras = 3;
      }
      break;
      default:
      {      
      }
      break;
   }
}


void init_External_interrupt(void)
{
   EICRA |= 0x03;                // rising edge(per)  [0V->5V]
   //EICRA |= 0x02;              // falling edge(zad) [5V->0V]
   EIMSK |= 0x01;
}


void stop_External_interrupt(void)
{
   EICRA &= ~0x03;
   EIMSK &= ~0x01;
}


void init_External_PCINT(void)
{
   PCICR = 0x04;  
   PCIFR = 0x00;
   PCMSK2 = 0x00;
}

//--------------------------------------- end interr_Ex.h ------------------------------
