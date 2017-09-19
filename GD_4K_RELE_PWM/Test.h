//--------------------------------- Test.h ---------------------------------


/*
void TEST_KIL_ZYB(void)
{
     switch(enable_pysk_ras)
     {  
         case(0):
         {
            //запускаем проверку по расчету зубьев
            //enable_pysk_ras = 1; 
         }
         break;
         
         case(1):
         {
         }
         break;
         
         case(2):
         {
         }
         break;

         case(3):
         {
            //enable_pysk_ras = 0;  
         }
         break;
         
         default:
         {
         }
         break;
     }
}
*/


void TEST_HD(void)
{
    unsigned int perem_test_hd;
    
    ERROR_HD = 0;
    perem_test_hd = ADC_area_[ADC_MUX_DC_HD_A]; 
    if(perem_test_hd < 70)
    {
       ERROR_HD = 1;
    }
    perem_test_hd = ADC_area_[ADC_MUX_DC_HD_B]; 
    if(perem_test_hd < 70)
    {
       ERROR_HD = 1;
    }
}  

void TEST_DD(void)
{
       ERROR_out_5 = 0x00; 
       ERROR_tt = 0; 
       if(test_treadle()==1)
       {
          ERROR_tt = 1;
          ERROR_out_5 = ERROR_out_5 + 0x30;
       }
       else if(test_treadle()==2)
       {
          ERROR_tt = 1;
          ERROR_out_5 = ERROR_out_5 + 0x40;
       }
       //проверка работы датчика давления
       ERROR_dd = 0;
       if(test_dat_dav()==1)
       {
          ERROR_dd = 1;
          ERROR_out_5 = ERROR_out_5 + 0x05;
       }
       else if(test_dat_dav()==2)
       {
          ERROR_dd = 1; 
          ERROR_out_5 = ERROR_out_5 + 0x07;
       }
       enable_test_system = 0;
}


void TEST_FORS_2(void)
{
//---------------------------------------------------------работа с 1 форсункой
if(STOP_RUN_GD == 0)
{  
   switch(enable_out_data)
   {
     case 0:
     {       
        if((Switch_Klapan_3_READ)!=0)
        {
            kil_f_1 = kil_f_1 + 1;
            if(kil_f_1 > 50)
            {   
               enab_for_1 = 0;
               ERROR_f1 = 0;
               ERROR_out_1 = 0xF0;
               enable_test_fors = 0;
            }
        } 
        else if((Switch_Klapan_3_READ)==0)
        {
            kil_f_2 = kil_f_2 + 1;
            if(kil_f_2 > 50)
            { 
               enab_for_1 = 0;            
               ERROR_f1 = 1;
               ERROR_out_1 = 0x03;
               enable_test_fors = 0;
            }   
        }
     }
     break;
//---------------------------------------------------------работа с 2 форсункой 
     case 1:
     {  
       if((Switch_Klapan_2_READ)!=0)
       {
          kil_f_1 = kil_f_1 + 1;
          if(kil_f_1 > 50)
          {
             enab_for_2 = 0;
             enable_test_fors = 0;
             ERROR_f2 = 0;
             ERROR_out_1 = 0x0F;
          } 
       } 
       else if((Switch_Klapan_2_READ)==0)
       {
          kil_f_2 = kil_f_2 + 1;
          if(kil_f_2 > 50)
          { 
             enab_for_2 = 0;   
             enable_test_fors = 0;
             ERROR_f2 = 1;
             ERROR_out_1 = 0x20;
          }   
       }
     }
     break;

//---------------------------------------------------------работа с 3 форсункой
     case 2:
     {  
       if((Switch_Klapan_4_READ)!=0)
       {
          kil_f_1 = kil_f_1 + 1;
          if(kil_f_1 > 50)
          {
             enab_for_3 = 0;
             ERROR_f3 = 0; 
             enable_test_fors = 0;
             ERROR_out_2 = ERROR_out_2 & 0xF0;
          } 
       } 
       else if((Switch_Klapan_4_READ)==0)
       {
          kil_f_2 = kil_f_2 + 1;
          if(kil_f_2 > 50)
          { 
             enab_for_3 = 0;            
             ERROR_f3 = 1;
             enable_test_fors = 0;
             ERROR_out_2 = ERROR_out_2 | 0x03;
          }   
       }
     }
     break;

//---------------------------------------------------------работа с 4 форсункой  
     case 3:
     {  
       if((Switch_Klapan_1_READ)!=0)
       {
          kil_f_1 = kil_f_1 + 1;
          if(kil_f_1 > 50)
          {
             enab_for_4 = 0;
             ERROR_f4 = 0; 
             ERROR_out_2 = ERROR_out_2 & 0x0F;
             enable_test_fors = 0;
          } 
       } 
       else if((Switch_Klapan_1_READ)==0)
       {
          kil_f_2 = kil_f_2 + 1;
          if(kil_f_2 > 50)
          { 
             enab_for_4 = 0;            
             ERROR_f4 = 1;
             ERROR_out_2 = ERROR_out_2 | 0x20;
             enable_test_fors = 0;
          }   
       }
   }
   break;
/*   
//---------------------------------------------------------работа с 5 форсункой
   case 4:
   {  
       if((Switch_Klapan_5_READ)!=0)
       {
          kil_f_1 = kil_f_1 + 1;
          if(kil_f_1 > 50)
          {
             enab_for_5 = 0;
             ERROR_f5 = 0; 
             enable_test_fors = 0;
             ERROR_out_3 = ERROR_out_3 & 0xF0;
          } 
       } 
       else if((Switch_Klapan_5_READ)==0)
       {
          kil_f_2 = kil_f_2 + 1;
          if(kil_f_2 > 50)
          { 
             enab_for_5 = 0;            
             ERROR_f5 = 1;
             enable_test_fors = 0;
             ERROR_out_3 = ERROR_out_3 | 0x03;
          }   
       }
     }
     break;

//---------------------------------------------------------работа с 6 форсункой  
     case 5:
     {  
       if((Switch_Klapan_6_READ)!=0)
       {
          kil_f_1 = kil_f_1 + 1;
          if(kil_f_1 > 50)
          {
             enab_for_6 = 0;
             ERROR_f6 = 0;
             ERROR_out_3 = ERROR_out_3 & 0xF0;
             enable_test_fors = 0;
          } 
       } 
       else if((Switch_Klapan_6_READ)==0)
       {
          kil_f_2 = kil_f_2 + 1;
          if(kil_f_2 > 50)
          { 
             enab_for_6 = 0;            
             ERROR_f6 = 1;
             ERROR_out_3 = ERROR_out_3 | 0x03;
             enable_test_fors = 0;
          }   
       }
   }
   break;
//---------------------------------------------------------работа с 7 форсункой
   case 6:
   {  
       if((Switch_Klapan_7_READ)!=0)
       {
          kil_f_1 = kil_f_1 + 1;
          if(kil_f_1 > 50)
          {
             enab_for_7 = 0;
             ERROR_f7 = 0; 
             enable_test_fors = 0;
             ERROR_out_4 = ERROR_out_4 & 0xF0;
          } 
       } 
       else if((Switch_Klapan_7_READ)==0)
       {
          kil_f_2 = kil_f_2 + 1;
          if(kil_f_2 > 50)
          { 
             enab_for_7 = 0;            
             ERROR_f7 = 1;
             enable_test_fors = 0;
             ERROR_out_4 = ERROR_out_4 | 0x03;
          }   
       }
     }
     break;

//---------------------------------------------------------работа с 8 форсункой  
     case 7:
     {  
       if((Switch_Klapan_8_READ)!=0)
       {
          kil_f_1 = kil_f_1 + 1;
          if(kil_f_1 > 50)
          {
             enab_for_8 = 0;
             ERROR_f8 = 0;
             ERROR_out_4 = ERROR_out_4 & 0xF0;
             enable_test_fors = 0;
          } 
       } 
       else if((Switch_Klapan_8_READ)==0)
       {
          kil_f_2 = kil_f_2 + 1;
          if(kil_f_2 > 50)
          { 
             enab_for_8 = 0;            
             ERROR_f8 = 1;
             ERROR_out_4 = ERROR_out_4 | 0x03;
             enable_test_fors = 0;
          }   
       }
   }
   break;
*/
   }
}
}


void Error_function_e(unsigned int Er_L)
{
  Flag_error_N=Er_L;
  __disable_interrupt();
  write_Card_2K_I2C(Flag_error_N_24LC16B, (char)(Flag_error_N>>8));
  write_Card_2K_I2C(Flag_error_N_24LC16B+1, (char)(Flag_error_N&0x00FF));
  __enable_interrupt();
  if(Er_L<27) Red_diod_ON;          // red diod
}


void Taxometer_test(void)
{
  unsigned char St=0;
  //Send_UART_char('e');
  Flag_State_Run_GD=0;
  Flag_quantization_step_PID=0;
  //Flag_taxometer=0;
  Delay_kl=0;
  Switch_Klapan_1_OFF;    //disable Kl_1
  Switch_Klapan_2_OFF;
  Switch_Klapan_3_OFF;
  Switch_Klapan_4_OFF;
  
  //---------------- test Faza --------------------------------
  Faza_motora=1;
  __disable_interrupt();
  miliSekundomer_ms=0;
  __enable_interrupt();
  do
  {
    if(Faza_motora==0) St=1;
    if(miliSekundomer_ms>30) St=2;
  }
  while(St==0);
  if(St==2)
  {
    Error_function_e(Error_D_Faza);
    Send_UART_char('e');
    Send_UART_char('F');
    NRZ_UART();
  }
  //-------------------- test maxovik -------------------------
  TCNT0=256-sw1_number_tooth;
  TCCR0B |=_CK_dev_TC0;
  TIMSK0 |=0x01;
  Faza_motora=0;
  St=0;
  __disable_interrupt();
  miliSekundomer_ms=0;
  __enable_interrupt();
  do
  {
    if(Faza_motora==3) St=1;
    if(miliSekundomer_ms>40) St=2;
  }
  while(St==0);
  if(St==2) 
  {
    Error_function_e(Error_D_Maxovik);
    Send_UART_char('e');
    Send_UART_char('M');
    NRZ_UART();
  }
}


unsigned char test_hdd(void)
{
  unsigned int A_L=0;
  
  A_L=ADC_area_[ADC_MUX_DC_HD_A];
  if(A_L<70)
  {
     return(1);
  }
  A_L=ADC_area_[ADC_MUX_DC_HD_B];
  if(A_L<70)
  {
     return(1);
  }
  return(0);
}


unsigned char test_treadle(void)
{
  unsigned int A_L=0;
  A_L=ADC_area_[ADC_MUX_axeleratora];
  if(A_L<5)
  {
     //Error_function_e(Error_D_Treadle);
     return(1);
  }
  if(A_L>910)
  {
     //Error_function_e(Error_D_Treadle);
     return(2);
  }
  return(0);
}


unsigned char test_dat_dav(void)
{
  unsigned int I_L=0;
  I_L=ADC_area_[ADC_MUX_pressure];
  if(I_L<5)
  {
    return(1);
  }
  if(I_L>910)
  {
    return(2);
  }
  return(0);
}


void Test_Switch(void)
{
  //if((Switch_Klapan_1_READ)==0) Error_function_e(Error_Switch_Klapan_1);
  //if((Switch_Klapan_2_READ)==0) Error_function_e(Error_Switch_Klapan_2);
  //if((Switch_Klapan_3_READ)==0) Error_function_e(Error_Switch_Klapan_3);
  //if((Switch_Klapan_4_READ)==0) Error_function_e(Error_Switch_Klapan_4);
  //if((Switch_Klapan_5_READ)==0) Error_function_e(Error_Switch_Klapan_5);
  //if((Switch_Klapan_6_READ)==0) Error_function_e(Error_Switch_Klapan_6);
  //if((Switch_Klapan_7_READ)==0) Error_function_e(Error_Switch_Klapan_7);
  //if((Switch_Klapan_8_READ)==0) Error_function_e(Error_Switch_Klapan_8);
  
  //if((Switch_RELE_READ)==0) Error_function_e(Error_Switch_RELE);
  //if((Switch_GAS_READ)==0) Error_function_e(Error_Switch_GAS);
  //if((Switch_MUZD_READ)==0) Error_function_e(Error_Switch_MUZD);
  //if((Switch_MUZD_V_READ)==0) Error_function_e(Error_Switch_MUZD_V); 
}


void test_system__GD(void)
{
  unsigned char Symbol_key=0;
  
  NRZ_UART();
  printf_const_UART(test_00);
  printf_const_UART(test_01);
  printf_const_UART(test_02);
  printf_const_UART(test_03);
  printf_const_UART(test_04);
  NRZ_UART();
  
  Test_Switch();
  
  Send_UART_char(':');
  do
  {
    UART_RX_int();
    if(Flag_State_Run_GD==1)
    {
      if(Flag_quantization_step_PID==1) PID_regulator();
      //if(Flag_PC==1) void;
    }
    if(Flag_taxometer==1) Taxometer_qvant();
    Condition();
    
    Symbol_key=Buffer_UART_RX[address_BUF_RX-1];
    if(Symbol_key=='r') Rele_on_off();
    if(Symbol_key=='g') GAS_on_off();
    if(Symbol_key=='m') MUZD_on_off();
    if(Symbol_key=='1') Kl_on_off();
    if(Symbol_key=='2') Kl_on_off();
    if(Symbol_key=='3') Kl_on_off();
    if(Symbol_key=='4') Kl_on_off();
    if(Symbol_key=='5') Kl_on_off();
    if(Symbol_key=='6') Kl_on_off();
    if(Symbol_key=='7') Kl_on_off();
    if(Symbol_key=='8') Kl_on_off();
    if(Symbol_key=='t') VAR_test_ind(taxometer);
    if(Symbol_key=='a') akselerometr_test_ind();
    if(Symbol_key=='A') ADC_test_ind();
    if(Symbol_key=='C') VAR_test_ind(temperature_Col);
    if(Symbol_key=='R') VAR_test_ind(temperature_Reduktor);
    if(Flag_test_local==1)
    {
      Buffer_UART_RX[address_BUF_RX-1]=0;
      Send_UART_char(':');
      Flag_test_local=0;
    }
  }
  while(Symbol_key!='Q');
}


void Rele_on_off(void)
{
  NRZ_UART();
  //if((Switch_RELE_READ)!=0)
  if(Flag_en_dis_switch==0)
  {
    //Switch_RELE_ON;  // YA1
    printf_const_UART(test_on);
    Flag_en_dis_switch=1;
  }
  else
  {
    //Switch_RELE_OFF;  // YA1
    printf_const_UART(test_off);
    Flag_en_dis_switch=0;
  }
  //Symbol_key=0;
  Flag_test_local=1;
}

void GAS_on_off(void)
{
  NRZ_UART();
  //if((Switch_GAS_READ)!=0)
  if(Flag_en_dis_switch==0)
  {
    Switch_GAS_ON;  // YA3
    printf_const_UART(test_on);
    Flag_en_dis_switch=1;
  }
  else
  {
    Switch_GAS_OFF;  // YA3
    printf_const_UART(test_off);
    Flag_en_dis_switch=0;
  }
  //Symbol_key=0;
  Flag_test_local=1;
}

void Kl_on_off(void)
{
  unsigned char number_klapan;
  NRZ_UART();
  number_klapan=Buffer_UART_RX[address_BUF_RX-1];
  //if((Switch_Klapan_1_READ)!=0)
  if(Flag_en_dis_switch==0)
  {
     switch(number_klapan)
     {
          case '1':
            Switch_Klapan_1_ON;   //enable Kl_1
            break;
          case '2':
            Switch_Klapan_2_ON;   //enable Kl_2
            break;
          case '3':
            Switch_Klapan_3_ON;   //enable Kl_3
            break;
          case '4':
            Switch_Klapan_4_ON;   //enable Kl_4
            break;
       }
       printf_const_UART(test_on);
       Flag_en_dis_switch=1;
  }
  else
  {
       switch(number_klapan)
       {
          case '1':
            Switch_Klapan_1_OFF;   //enable Kl_1
            break;
          case '2':
            Switch_Klapan_2_OFF;   //enable Kl_2
            break;
          case '3':
            Switch_Klapan_3_OFF;   //enable Kl_3
            break;
          case '4':
            Switch_Klapan_4_OFF;   //enable Kl_4
            break;
       }
       printf_const_UART(test_off);
       Flag_en_dis_switch=0;
  }
  //Symbol_key=0;
  Flag_test_local=1;
}


void VAR_test_ind(signed int var_indik)
{
  //NRZ_UART();
  Send_UART_char('=');
  Printf_Variable_UART(var_indik);
  NRZ_UART();
  //Symbol_key=0;
  Flag_test_local=1;
}

void akselerometr_test_ind(void)
{
  unsigned char i_L=0;
  unsigned int Acselerometr_ADC;
  Acselerometr_ADC=ADC_area_[ADC_MUX_axeleratora];
  if(Axelerometr_tax[0][0]>Acselerometr_ADC)
  {
    taxometer_predetermined=idling_motor_dizel;
  }
  else
  {
    while(Axelerometr_tax[++i_L][0]<Acselerometr_ADC);
    if(i_L==8) i_L=7;
    taxometer_predetermined=(Axelerometr_tax[i_L][2]/10)*((Acselerometr_ADC*10)/Axelerometr_tax[i_L][3])+Axelerometr_tax[i_L][4]-offset_motor_tax; //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
  }
  
  if(taxometer_predetermined > max_turns_motora_dizel) taxometer_predetermined=max_turns_motora_dizel;  
  if(taxometer_predetermined < idling_motor_dizel) taxometer_predetermined=idling_motor_dizel;  
  
  Send_UART_char('=');
  Printf_Variable_UART(taxometer_predetermined);
  NRZ_UART();
  //Symbol_key=0;
  Flag_test_local=1;
}

void ADC_test_ind(void)
{
  unsigned char i;
  i=0;
  Send_UART_char(';');
  for(i=0; i<8; i++)
  {
    Printf_Variable_UART(i);
    Send_UART_char('=');
    Printf_Variable_UART(ADC_area_[i]);
    Send_UART_char(',');
  }
  NRZ_UART();
  //Symbol_key=0;
  Flag_test_local=1;
}

void Axelerometr_calibr(void)
{
  unsigned char i=0;
  unsigned char Sumbol=0;
  
  Send_UART_char(':');
  do
    {
      if(Flag_taxometer==1) Taxometer_qvant();
      
      switch(Buffer_UART_RX[address_BUF_RX-1])
      {
        case '0':
          i=0;
          __disable_interrupt();
          Axelerometr_tax[0][0] = ADC_area_[ADC_MUX_axeleratora];   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B          
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+0)*2, (char)(Axelerometr_tax[0][0]>>8));
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+0)*2+1, (char)(Axelerometr_tax[0][0]&0x00FF));
          Axelerometr_tax[0][1] = taxometer;   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+1)*2, (char)(Axelerometr_tax[0][1]>>8));
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+1)*2+1, (char)(Axelerometr_tax[0][1]&0x00FF));
          __enable_interrupt();
          NRZ_UART();
          Send_UART_char('a');
          Printf_Variable_UART(Axelerometr_tax[0][0]);
          Send_UART_char(' ');
          Send_UART_char('t');
          Printf_Variable_UART(Axelerometr_tax[0][1]);
          Send_UART_char(' ');
          NRZ_UART();
          Buffer_UART_RX[address_BUF_RX-1]=0;
          Send_UART_char(':');
          break;
        case '1':
          i=1;
          Sumbol=1;
          break;
        case '2':
          i=2;
          Sumbol=1;
          break;
        case '3':
          i=3;
          Sumbol=1;
          break;
        case '4':
          i=4;
          Sumbol=1;
          break;
        case '5':
          i=5;
          Sumbol=1;
          break;
        case '6':
          i=6;
          Sumbol=1;
          break;
        case '7':
          i=7;
          Sumbol=1;
          break;
        case '8':
          i=8;
          __disable_interrupt();
          Axelerometr_tax[8][0] = 1025;   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
          //*(var_s_int+Axelerometr_tax_eeprom+i*5+0)=Axelerometr_tax[8][0];
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+0)*2, (char)(Axelerometr_tax[8][0]>>8));
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+0)*2+1, (char)(Axelerometr_tax[8][0]&0x00FF));
          Axelerometr_tax[8][1] = taxometer;   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
          //*(var_s_int+Axelerometr_tax_eeprom+i*5+1)=Axelerometr_tax[8][1];
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+1)*2, (char)(Axelerometr_tax[8][1]>>8));
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+1)*2+1, (char)(Axelerometr_tax[8][1]&0x00FF));
          __enable_interrupt();
          i=0;
          while(Axelerometr_tax[++i][0]<ADC_area_[ADC_MUX_axeleratora]);
          if(i==8) i=7;
          taxometer_predetermined=(Axelerometr_tax[i][2]/10)*((ADC_area_[ADC_MUX_axeleratora]*10)/Axelerometr_tax[i][3])+Axelerometr_tax[i][4]; //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
          NRZ_UART();
          Send_UART_char('a');
          Printf_Variable_UART(ADC_area_[ADC_MUX_axeleratora]);
          Send_UART_char(' ');
          Send_UART_char('t');
          Printf_Variable_UART(Axelerometr_tax[8][1]);
          Send_UART_char(' ');
          NRZ_UART();
          Send_UART_char('p');
          Printf_Variable_UART(taxometer_predetermined);
          Send_UART_char(' ');
          NRZ_UART();
          Buffer_UART_RX[address_BUF_RX-1]=0;
          Send_UART_char(':');
          i=8;
          break;
      }
      if(Sumbol==1)
      {
        __disable_interrupt();
        Axelerometr_tax[i][0] = ADC_area_[ADC_MUX_axeleratora];   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
        //*(var_s_int+Axelerometr_tax_eeprom+i*5+0)=Axelerometr_tax[i][0];
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+0)*2, (char)(Axelerometr_tax[i][0]>>8));
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+0)*2+1, (char)(Axelerometr_tax[i][0]&0x00FF));
        Axelerometr_tax[i][1] = taxometer;   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
        //*(var_s_int+Axelerometr_tax_eeprom+i*5+1)=Axelerometr_tax[i][1];
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+1)*2, (char)(Axelerometr_tax[i][1]>>8));
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+1)*2+1, (char)(Axelerometr_tax[i][1]&0x00FF));
        Axelerometr_tax[i][2] = Axelerometr_tax[i][1]-Axelerometr_tax[i-1][1];   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
        //*(var_s_int+Axelerometr_tax_eeprom+i*5+2)=Axelerometr_tax[i][2];
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+2)*2, (char)(Axelerometr_tax[i][2]>>8));
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+2)*2+1, (char)(Axelerometr_tax[i][2]&0x00FF));
        Axelerometr_tax[i][3] = Axelerometr_tax[i][0]-Axelerometr_tax[i-1][0];   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
        //*(var_s_int+Axelerometr_tax_eeprom+i*5+3)=Axelerometr_tax[i][3];
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+3)*2, (char)(Axelerometr_tax[i][3]>>8));
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+3)*2+1, (char)(Axelerometr_tax[i][3]&0x00FF));
        Axelerometr_tax[i][4] = Axelerometr_tax[i][1]-(Axelerometr_tax[i][2]/10)*((Axelerometr_tax[i][0]*10)/Axelerometr_tax[i][3]);   //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
        //*(var_s_int+Axelerometr_tax_eeprom+i*5+4)=Axelerometr_tax[i][4];
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+4)*2, (char)(Axelerometr_tax[i][4]>>8));
        write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+4)*2+1, (char)(Axelerometr_tax[i][4]&0x00FF));
        __enable_interrupt();
        NRZ_UART();
        Send_UART_char('a');
        Printf_Variable_UART(Axelerometr_tax[i][0]);
        Send_UART_char(' ');
        Send_UART_char('t');
        Printf_Variable_UART(Axelerometr_tax[i][1]);
        Send_UART_char(' ');
        Send_UART_char('1');
        Printf_Variable_UART(Axelerometr_tax[i][2]);
        Send_UART_char(' ');
        Send_UART_char('2');
        Printf_Variable_UART(Axelerometr_tax[i][3]);
        Send_UART_char(' ');
        Send_UART_char('B');
        Printf_Variable_UART(Axelerometr_tax[i][4]);
        Send_UART_char(' ');
        NRZ_UART();
        Buffer_UART_RX[address_BUF_RX-1]=0;
        Send_UART_char(':');
        Sumbol=0;
      }
      UART_RX_int();
    }
    while(Buffer_UART_RX[address_BUF_RX-1]!='q');
}

void pressure_calibration(void)
{
  ADC_offset_min = ADC_area_[ADC_MUX_pressure];
    Send_UART_char('m');
    Send_UART_char('i');
    Send_UART_char('n');
    Send_UART_char('=');
    Printf_Variable_UART((unsigned int)ADC_offset_min);
    NRZ_UART();
    do
    {
     UART_RX_int();
     ADC_offset_max = ADC_area_[ADC_MUX_pressure];
    }
    while (Buffer_UART_RX[address_BUF_RX-1]!='c');
    Send_UART_char('m');
    Send_UART_char('a');
    Send_UART_char('x');
    Send_UART_char('=');
    Printf_Variable_UART((unsigned int)ADC_offset_max);
    NRZ_UART();
    Turbo_Koeff=(ADC_offset_max-ADC_offset_min)/5;
    Turbo_offset=ADC_offset_min;
    __disable_interrupt();
    //*(var_s_int+Turbo_Koeff_eeprom) = Turbo_Koeff;
    write_Card_2K_I2C(Turbo_Koeff_24LC16B, (char)(Turbo_Koeff>>8));
    write_Card_2K_I2C(Turbo_Koeff_24LC16B+1, (char)(Turbo_Koeff&0x00FF));
    //*(var_s_int+Turbo_offset_eeprom) = Turbo_offset;
    write_Card_2K_I2C(Turbo_offset_24LC16B, (char)(Turbo_offset>>8));
    write_Card_2K_I2C(Turbo_offset_24LC16B+1, (char)(Turbo_offset&0x00FF));
    __enable_interrupt();
    Send_UART_char('T');
    Send_UART_char('k');
    Send_UART_char('=');
    Printf_Variable_UART(Turbo_Koeff);
}


void Mahovik_Calibration(void)
{
  /*unsigned char F_0=0;
  unsigned char F_1;
  unsigned char T_0=0;
  unsigned char T_1;
  unsigned char B_f=0;*/
  //unsigned char B_t=0;
  unsigned char Count_t=0;
  
  Faza_motora=1;
  sw1_number_tooth=255;
  while(Faza_motora!=0) __no_operation();
  Faza_motora=1;
  while(Faza_motora!=0) Count_t=TCNT0-1;
  sw1_number_tooth=55;
  
  /*F_1=Faza_Motora_READ;
  do
  {
    F_0=F_1;
    F_1=Faza_Motora_READ;
    if((F_0!=0)&&(F_1==0)) B_f=1;
  }
  while(B_f==0);
  
  F_0=F_1;
  F_1=Faza_Motora_READ;
  T_1=Tooth_Motora_READ;
  do
  {
    F_0=F_1;
    F_1=Faza_Motora_READ;
    if((F_0!=0)&&(F_1==0)) B_f=1;
    T_0=T_1;
    T_1=Tooth_Motora_READ;
    if((T_0!=0)&&(T_1==0)) Count_t++;
  }
  while(B_f==0);*/
  
  Kol_zubov_kolenvala=Count_t;
  __disable_interrupt();
    write_Card_2K_I2C(Kol_zubov_kolenvala_24LC16B, Kol_zubov_kolenvala);
  __enable_interrupt();
  printf_const_UART(Start_hello_15);
  Printf_Variable_UART(Kol_zubov_kolenvala);
  NRZ_UART();
}

void Test_MUZD_ON(void)
{
  unsigned char Status_w=0;
  
  //Switch_RELE_ON;
  I01_stepM_OFF;
  I11_stepM_OFF;
  I02_stepM_OFF;
  I12_stepM_OFF;
  miliSekundomer_ms=0;
  while(miliSekundomer_ms<30) __no_operation();
  Send_UART_char('|');
  while(Step_Motor_Future!=Step_Motor_Position) __no_operation();
  Switch_GAS_OFF;
  //Switch_MUZD_V_ON;      //vtyagivanie glushilki
  //miliSekundomer_ms=0;
  //while(miliSekundomer_ms<30) __no_operation();
  //Switch_MUZD_V_OFF;     //vtyagivanie glushilki
  //Switch_MUZD_ON;
  miliSekundomer_ms=0;
  Status_w=0;
  do
  {
    if((Koncevik_MUZD_READ)==0) Status_w=1;
    if(miliSekundomer_ms>=100) Status_w=2;
    //------------------
  }
  while(Status_w==0);
  Send_UART_char('|');
  if(Status_w==2)
  {
    Test_MUZD_OFF();
    Error_function_e(Error_D_Konc_MUZD);
  }
  else Send_UART_char('S');
}

void Test_MUZD_OFF(void)
{
  Step_Motor_Future=0;
  Switch_GAS_OFF;   // YA3   gas
  //Switch_MUZD_OFF;  // YA2   muzd
  I01_stepM_ON;
  I11_stepM_ON;
  I02_stepM_ON;
  I12_stepM_ON;
  /*Switch_MUZD_V_ON;     //vtyagivanie glushilki
  miliSekundomer_ms=0;
  while(miliSekundomer_ms<30) __no_operation();
  Switch_MUZD_V_OFF;     //vtyagivanie glushilki*/
  //Switch_RELE_OFF;  // YA1   rele
  Send_UART_char('X');
}

//--------------------------------- end Test.h -----------------------------

