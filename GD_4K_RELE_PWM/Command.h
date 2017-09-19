//----------------------------------Command.h--------------------------------------
unsigned char data_test;
unsigned int t;
unsigned char crc_data;
unsigned char proverka_crc_ok;
unsigned char loc_x=0;


//---------------------------------------------------------------------------------
//ПОДПРОГРАММА ПРОВЕРКИ ПРИНЯТЫХ ДАННЫХ
//---------------------------------------------------------------------------------
void Analiz_Command(void)
{
  unsigned int Number_COM;

  NRZ_UART();
  Number_COM = Search_Find_Command(command_00);
  
      switch(Number_COM)
      {
          case 1:
            test();
          break;
      
          case 2:
            reset();
          break;
      
          case 3:
            ver();
          break;
      
          case 4:
            run();
          break;
      
          case 6:
            var();     
          break;
      
          case 7:
            read(); 
          break;
          
          case 8:
            tab(); 
          break;
          
          case 9:
            rxd();  
          break;  
          
          case 10:
            tbk();  
          break;  
          
          default:
            Error_message(1);
     }
          Flag_Command=0;
          Send_UART_char('#');
}


unsigned char Search_Find_Command(unsigned char const __flash *Array_const_char)
{
  unsigned char Char_Find,number_com;
  unsigned char i, flag_equ;
    
  do
  {
    Char_Find=__load_program_memory(Array_const_char++);
    
    if(Char_Find==' ')
    {
      i=0;
      flag_equ=0;
      do
      {
        Char_Find=__load_program_memory(Array_const_char);
        if(Buffer_UART_RX[i++]!=__load_program_memory(Array_const_char++)) flag_equ=1;
      }
      while((Char_Find!='\0')&&(flag_equ!=1));
      
      if(Char_Find=='\0')
      {
        if(flag_equ==0)
        {
          number_com=(__load_program_memory(Array_const_char+1)&0x0F)*10;
          number_com=number_com + __load_program_memory(Array_const_char+2)&0x0F;
          return(number_com);
        }
    
        if(Buffer_UART_RX[i-1]==' ')
        {
          number_com=(__load_program_memory(Array_const_char+1)&0x0F)*10;
          number_com=number_com + __load_program_memory(Array_const_char+2)&0x0F;
          return(number_com);
        }
    
      }
    }
  }
  while(Char_Find!='\n');
  return 0;
}


void Error_message(unsigned char Number_error)
{ 
  switch(Number_error)
  {
    case 0:
      printf_const_UART(error_00);
      break;
      
    case 1:
      printf_const_UART(error_01);
      break;
             
    default:
      printf_const_UART(error_00);
      //_NOP();
  }
}




void rxd(void)
{  
   unsigned int vremen_rxd;
   
   //==========================================================================================
   if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='0'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Serial_number == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 1;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача серийного номера Serial_number
          number_paket_tx_now = 0;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='1'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Step_Motor_Koeff == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 2;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Step_Motor_Koeff
          number_paket_tx_now = 1;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='2'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Kp_Gain_2 == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 3;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Kp_Gain_2
          number_paket_tx_now = 2;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='3'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Kp_Gain_PID_t_1 == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 4;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Kp_Gain_PID_t_1
          number_paket_tx_now = 3;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='4'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Kp_Gain_PID_t_2 == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 5;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Kp_Gain_PID_t_2
          number_paket_tx_now = 4;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='c'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(temperature_predetermined == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 6;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача temperature_predetermined
          number_paket_tx_now = 5;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='l'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(D_min == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 7;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача D_min
          number_paket_tx_now = 6;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='h'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(D_max == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 8;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача D_max
          number_paket_tx_now = 7;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='I')&&(Buffer_UART_RX[5]=='d'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(idling_motor_dizel == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 9;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача idling_motor_dizel
          number_paket_tx_now = 8;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='M')&&(Buffer_UART_RX[5]=='o'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Step_Motor_OffSet == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 10;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Step_Motor_OffSet
          number_paket_tx_now = 9;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='o'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Turbo_offset == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 11;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Turbo_offset
          number_paket_tx_now = 10;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='k'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Turbo_Koeff == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 12;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Turbo_Koeff
          number_paket_tx_now = 11;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='m'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(offset_motor_tax == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 13;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача offset_motor_tax
          number_paket_tx_now = 12;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='M')&&(Buffer_UART_RX[5]=='t'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if(Kol_zubov_kolenvala == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 14;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Kol_zubov_kolenvala
          number_paket_tx_now = 13;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='P')&&(Buffer_UART_RX[5]=='l'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if((High_Level_PID/div_milisek_switch) == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 15;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Kol_zubov_kolenvala
          number_paket_tx_now = 14;
          init_PRINTF_var();
       }  
   }
   //==========================================================================================
   if((Buffer_UART_RX[4]=='P')&&(Buffer_UART_RX[5]=='i'))
   {
       vremen_rxd=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
       if((Low_Level_Idling/div_milisek_switch) == vremen_rxd)
       {
          //разрешить новую передачу данных
          number_paket_tx_now = 16;
          init_PRINTF_var();
       }
       else
       {
          //повтор - передача Kol_zubov_kolenvala
          number_paket_tx_now = 15;
          init_PRINTF_var();
       }  
   }
}


void reset(void)
{
  __watchdog_reset();
}


//подпрограмма для считывания первичных данных
void read(void)
{
   int i,y; 
   number_paket_tx_now = 0;
   
   for(i=0;i<6;i++)
   {
        for(y=0;y<16;y++)
        {
            array_high_level_PID[i][y] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y);
            array_high_level_PID[i][y] = array_high_level_PID[i][y]*div_milisek_switch;
        }
   }
   
   init_PRINTF_var();
   //Flag_Command=0;
   //Send_UART_char('$');
}



void test(void)
{
  if(Buffer_UART_RX[5]=='a')
  {
    Axelerometr_calibr();
    NRZ_UART();
    Ok_UART();
  }
  
  if(Buffer_UART_RX[5]=='p')
  {
    pressure_calibration();
    NRZ_UART();
    Ok_UART();
  }
 
  if(Buffer_UART_RX[5]=='t')
  {
    Mahovik_Calibration();
    NRZ_UART();
    Ok_UART();
  }
  
  if((Buffer_UART_RX[5]=='d')&&(Buffer_UART_RX[6]=='r'))
  {
    Test_MUZD_ON();
    NRZ_UART();
    Ok_UART();
  }
  if((Buffer_UART_RX[5]=='d')&&(Buffer_UART_RX[6]=='q'))
  {
    Test_MUZD_OFF();
    NRZ_UART();
    Ok_UART();
  }
}



void ver(void)
{
   printf_const_UART(ver_00);
}


void tbk (void)
{
  unsigned char i,y;
  unsigned char num_element = 0;
  unsigned char error_paket = 0;
  unsigned int mass_paket;
  
  next_p = 0;
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][1]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 16;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 17;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][2]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 17;     
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 18;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][3]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 18;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 19;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][4]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 19;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 20;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][5]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 20;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 21;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][6]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 21;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 22;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][7]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 22;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 23;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][8]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 23;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 24;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][9]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 24;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 25;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][10]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 25;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 26;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][11]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 26;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 27;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][12]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 27;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 28;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][13]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 28;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 29;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][14]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 29;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 30;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='A')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[0][15]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 30;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 31;    
             init_PRINTF_var();
         }
  }

  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][1]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 31;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 32;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][2]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 32;     
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 33;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][3]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 33;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 34;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][4]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 34;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 35;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][5]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 35;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 36;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][6]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 36;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 37;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][7]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 37;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 38;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][8]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 38;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 39;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][9]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 39;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 40;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][10]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 40;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 41;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][11]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 41;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 42;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][12]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 42;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 43;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][13]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 43;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 44;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][14]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 44;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 45;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='B')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[1][15]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 45;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 46;    
             init_PRINTF_var();
         }
  }

  
  
  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][1]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 46;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 47;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][2]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 47;     
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 48;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][3]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 48;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 49;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][4]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 49;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 50;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][5]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 50;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 51;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][6]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 51;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 52;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][7]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 52;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 53;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][8]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 53;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 54;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][9]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 54;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 55;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][10]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 55;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 56;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][11]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 56;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 57;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][12]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 57;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 58;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][13]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 58;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 59;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][14]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 59;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 60;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='C')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[2][15]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 60;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 61;    
             init_PRINTF_var();
         }
  }

  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][1]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 61;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 62;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][2]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 62;     
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 63;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][3]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 63;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 64;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][4]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 64;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 65;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][5]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 65;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 66;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][6]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 66;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 67;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][7]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 67;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 68;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][8]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 68;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 69;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][9]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 69;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 70;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][10]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 70;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 71;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][11]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 71;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 72;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][12]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 72;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 73;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][13]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 73;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 74;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][14]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 74;   
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 75;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='D')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[3][15]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 75;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 76;    
             init_PRINTF_var();
         }
  }

  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][1]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 76;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 77;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][2]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 77;     
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 78;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][3]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 78;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 79;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][4]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 79;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 80;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][5]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 80;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 81;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][6]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 81;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 82;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][7]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 82;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 83;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][8]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 83;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 84;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][9]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 84;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 85;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][10]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 85;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 86;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][11]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 86;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 87;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][12]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 87;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 88;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][13]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 88;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 89;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][14]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 89;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 90;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='E')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[4][15]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 90;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 91;    
             init_PRINTF_var();
         }
  }

  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][1]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 91;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 92;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][2]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 92;     
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 93;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][3]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 93;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 94;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][4]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 94;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 95;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][5]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 95;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 96;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][6]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 96;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 97;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][7]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 97;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 98;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][8]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 98;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 99;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][9]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 99;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 100;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][10]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 100;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 101;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][11]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 101;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 102;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][12]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 102;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 103;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][13]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 103;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 104;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][14]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 104;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 105;    
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='F')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if((array_high_level_PID[5][15]) != (mass_paket*div_milisek_switch))
         {
             number_paket_tx_now = 105;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 106;    
             init_PRINTF_var();
         }
  }

  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][0] != mass_paket)
         {
             number_paket_tx_now = 106;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 107;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][1] != mass_paket)
         {
             number_paket_tx_now = 107;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 108;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][2] != mass_paket)
         {
             number_paket_tx_now = 108;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 109;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][3] != mass_paket)
         {
             number_paket_tx_now = 109;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 110;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][4] != mass_paket)
         {
             number_paket_tx_now = 110;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 111;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][5] != mass_paket)
         {
             number_paket_tx_now = 111;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 112;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][6] != mass_paket)
         {
             number_paket_tx_now = 112;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 113;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][7] != mass_paket)
         {
             number_paket_tx_now = 113;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 114;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][8] != mass_paket)
         {
             number_paket_tx_now = 114;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 115;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][9] != mass_paket)
         {
             number_paket_tx_now = 115;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 116;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][10] != mass_paket)
         {
             number_paket_tx_now = 116;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 117;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][11] != mass_paket)
         {
             number_paket_tx_now = 117;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 118;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][12] != mass_paket)
         {
             number_paket_tx_now = 118;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 119;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][13] != mass_paket)
         {
             number_paket_tx_now = 119;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 120;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='G')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[0][14] != mass_paket)
         {
             number_paket_tx_now = 120;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 121;   
             init_PRINTF_var();
         }
  }

  
  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][0] != mass_paket)
         {
             number_paket_tx_now = 121;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 122;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][1] != mass_paket)
         {
             number_paket_tx_now = 122;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 123;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][2] != mass_paket)
         {
             number_paket_tx_now = 123;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 124;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][3] != mass_paket)
         {
             number_paket_tx_now = 124;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 125;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][4] != mass_paket)
         {
             number_paket_tx_now = 125;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 126;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][5] != mass_paket)
         {
             number_paket_tx_now = 126;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 127;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][6] != mass_paket)
         {
             number_paket_tx_now = 127;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 128;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][7] != mass_paket)
         {
             number_paket_tx_now = 128;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 129;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][8] != mass_paket)
         {
             number_paket_tx_now = 129;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 130;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][9] != mass_paket)
         {
             number_paket_tx_now = 130;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 131;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][10] != mass_paket)
         {
             number_paket_tx_now = 131;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 132;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][11] != mass_paket)
         {
             number_paket_tx_now = 132;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 133;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][12] != mass_paket)
         {
             number_paket_tx_now = 133;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 134;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][13] != mass_paket)
         {
             number_paket_tx_now = 134;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 135;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='Z')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[1][14] != mass_paket)
         {
             number_paket_tx_now = 135;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 136;   
             init_PRINTF_var();
         }
  }

  
  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][0] != mass_paket)
         {
             number_paket_tx_now = 136;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 137;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][1] != mass_paket)
         {
             number_paket_tx_now = 137;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 138;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][2] != mass_paket)
         {
             number_paket_tx_now = 138;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 139;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][3] != mass_paket)
         {
             number_paket_tx_now = 139;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 140;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][4] != mass_paket)
         {
             number_paket_tx_now = 140;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 141;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][5] != mass_paket)
         {
             number_paket_tx_now = 141;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 142;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][6] != mass_paket)
         {
             number_paket_tx_now = 142;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 143;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][7] != mass_paket)
         {
             number_paket_tx_now = 143;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 144;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][8] != mass_paket)
         {
             number_paket_tx_now = 144;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 145;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][9] != mass_paket)
         {
             number_paket_tx_now = 145;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 146;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][10] != mass_paket)
         {
             number_paket_tx_now = 146;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 147;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][11] != mass_paket)
         {
             number_paket_tx_now = 147;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 148;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][12] != mass_paket)
         {
             number_paket_tx_now = 148;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 149;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][13] != mass_paket)
         {
             number_paket_tx_now = 149;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 150;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='X')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[2][14] != mass_paket)
         {
             number_paket_tx_now = 150;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 151;   
             init_PRINTF_var();
         }
  }

  
  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][0] != mass_paket)
         {
             number_paket_tx_now = 151;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 152;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][1] != mass_paket)
         {
             number_paket_tx_now = 152;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 153;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][2] != mass_paket)
         {
             number_paket_tx_now = 153;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 154;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][3] != mass_paket)
         {
             number_paket_tx_now = 154;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 155;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][4] != mass_paket)
         {
             number_paket_tx_now = 155;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 156;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][5] != mass_paket)
         {
             number_paket_tx_now = 156;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 157;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][6] != mass_paket)
         {
             number_paket_tx_now = 157;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 158;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][7] != mass_paket)
         {
             number_paket_tx_now = 158;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 159;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][8] != mass_paket)
         {
             number_paket_tx_now = 159;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 160;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][9] != mass_paket)
         {
             number_paket_tx_now = 160;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 161;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][10] != mass_paket)
         {
             number_paket_tx_now = 161;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 162;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][11] != mass_paket)
         {
             number_paket_tx_now = 162;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 163;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][12] != mass_paket)
         {
             number_paket_tx_now = 163;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 164;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][13] != mass_paket)
         {
             number_paket_tx_now = 164;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 165;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='V')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[3][14] != mass_paket)
         {
             number_paket_tx_now = 165;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 166;   
             init_PRINTF_var();
         }
  }

  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][0] != mass_paket)
         {
             number_paket_tx_now = 166;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 167;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][1] != mass_paket)
         {
             number_paket_tx_now = 167;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 168;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][2] != mass_paket)
         {
             number_paket_tx_now = 168;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 169;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][3] != mass_paket)
         {
             number_paket_tx_now = 169;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 170;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][4] != mass_paket)
         {
             number_paket_tx_now = 170;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 171;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][5] != mass_paket)
         {
             number_paket_tx_now = 171;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 172;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][6] != mass_paket)
         {
             number_paket_tx_now = 172;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 173;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][7] != mass_paket)
         {
             number_paket_tx_now = 173;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 174;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][8] != mass_paket)
         {
             number_paket_tx_now = 174;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 175;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][9] != mass_paket)
         {
             number_paket_tx_now = 175;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 176;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][10] != mass_paket)
         {
             number_paket_tx_now = 176;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 177;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][11] != mass_paket)
         {
             number_paket_tx_now = 177;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 178;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][12] != mass_paket)
         {
             number_paket_tx_now = 178;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 179;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][13] != mass_paket)
         {
             number_paket_tx_now = 179;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 180;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='N')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[4][14] != mass_paket)
         {
             number_paket_tx_now = 180;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 181;   
             init_PRINTF_var();
         }
  }

  
  
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][0] != mass_paket)
         {
             number_paket_tx_now = 181;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 182;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][1] != mass_paket)
         {
             number_paket_tx_now = 182;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 183;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][2] != mass_paket)
         {
             number_paket_tx_now = 183;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 184;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][3] != mass_paket)
         {
             number_paket_tx_now = 184;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 185;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][4] != mass_paket)
         {
             number_paket_tx_now = 185;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 186;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][5] != mass_paket)
         {
             number_paket_tx_now = 186;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 187;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][6] != mass_paket)
         {
             number_paket_tx_now = 187;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 188;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][7] != mass_paket)
         {
             number_paket_tx_now = 188;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 189;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][8] != mass_paket)
         {
             number_paket_tx_now = 189;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 190;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][9] != mass_paket)
         {
             number_paket_tx_now = 190;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 191;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][10] != mass_paket)
         {
             number_paket_tx_now = 191;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 192;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][11] != mass_paket)
         {
             number_paket_tx_now = 192;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 193;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][12] != mass_paket)
         {
             number_paket_tx_now = 193;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 194;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][13] != mass_paket)
         {
             number_paket_tx_now = 194;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 195;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='M')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(faza_array_tooth[5][14] != mass_paket)
         {
             number_paket_tx_now = 195;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 196;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[0] != mass_paket)
         {
             number_paket_tx_now = 196;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 197;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[1] != mass_paket)
         {
             number_paket_tx_now = 197;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 198;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[2] != mass_paket)
         {
             number_paket_tx_now = 198;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 199;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[3] != mass_paket)
         {
             number_paket_tx_now = 199;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 200;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[4] != mass_paket)
         {
             number_paket_tx_now = 200;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 201;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[5] != mass_paket)
         {
             number_paket_tx_now = 201;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 202;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[6] != mass_paket)
         {
             number_paket_tx_now = 202;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 203;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[7] != mass_paket)
         {
             number_paket_tx_now = 203;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 204;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[8] != mass_paket)
         {
             number_paket_tx_now = 204;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 205;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[9] != mass_paket)
         {
             number_paket_tx_now = 205;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 206;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[10] != mass_paket)
         {
             number_paket_tx_now = 206;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 207;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[11] != mass_paket)
         {
             number_paket_tx_now = 207;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 208;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[12] != mass_paket)
         {
             number_paket_tx_now = 208;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 209;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[13] != mass_paket)
         {
             number_paket_tx_now = 209;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 210;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[14] != mass_paket)
         {
             number_paket_tx_now = 210;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 211;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='L')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Step_motor_array_cicle[15] != mass_paket)
         {
             number_paket_tx_now = 211;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 212;   
             init_PRINTF_var();
         }
  }
  
  
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[0][0] != mass_paket)
         {
             number_paket_tx_now = 212;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 213;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[1][0] != mass_paket)
         {
             number_paket_tx_now = 213;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 214;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[2][0] != mass_paket)
         {
             number_paket_tx_now = 214;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 215;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[3][0] != mass_paket)
         {
             number_paket_tx_now = 215;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 216;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[4][0] != mass_paket)
         {
             number_paket_tx_now = 216;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 217;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[5][0] != mass_paket)
         {
             number_paket_tx_now = 217;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 218;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='7'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[6][0] != mass_paket)
         {
             number_paket_tx_now = 218;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 219;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='8'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[7][0] != mass_paket)
         {
             number_paket_tx_now = 219;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 220;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='0')&&(Buffer_UART_RX[7]=='9'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[0][1] != mass_paket)
         {
             number_paket_tx_now = 220;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 221;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='0'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[1][1] != mass_paket)
         {
             number_paket_tx_now = 221;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 222;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[2][1] != mass_paket)
         {
             number_paket_tx_now = 222;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 223;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[3][1] != mass_paket)
         {
             number_paket_tx_now = 223;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 224;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[4][1] != mass_paket)
         {
             number_paket_tx_now = 224;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 225;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[5][1] != mass_paket)
         {
             number_paket_tx_now = 225;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 226;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[6][1] != mass_paket)
         {
             number_paket_tx_now = 226;    
             init_PRINTF_var();
         }
         else
         {
             number_paket_tx_now = 227;   
             init_PRINTF_var();
         }
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='K')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='6'))
  {
         //---------------------------------------------------------------------перезапись пакета     
         mass_paket=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
         //---------------------------------------------------------------------проверка пакета
         if(Axelerometr_tax[7][1] != mass_paket)
         {
             number_paket_tx_now = 227;    
             init_PRINTF_var();
         }
         else
         {
             //number_paket_tx_now = 228;   
             //init_PRINTF_var();
         }
  }
}






//----------------------------------------------------------------
//ЗАПИСЬ ТАБЛИЦ В ПАМЯТЬ
//----------------------------------------------------------------
void tab(void)
{
  unsigned char i,y;
  unsigned char num_element = 0;
     
 
  //==========================================================================================
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='1'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         //--------------------------------------------------------------------------------------
         for(y=1;y<16;y++)
         {
             i = 0;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{array_high_level_PID[i][y]=DATA_1;};break;
                 case(2):{array_high_level_PID[i][y]=DATA_2;};break;
                 case(3):{array_high_level_PID[i][y]=DATA_3;};break;
                 case(4):{array_high_level_PID[i][y]=DATA_4;};break;
                 case(5):{array_high_level_PID[i][y]=DATA_5;};break;
                 case(6):{array_high_level_PID[i][y]=DATA_6;};break;
                 case(7):{array_high_level_PID[i][y]=DATA_7;};break;
                 case(8):{array_high_level_PID[i][y]=DATA_8;};break;
                 case(9):{array_high_level_PID[i][y]=DATA_9;};break;
                 case(10):{array_high_level_PID[i][y]=DATA_10;};break;
                 case(11):{array_high_level_PID[i][y]=DATA_11;};break;
                 case(12):{array_high_level_PID[i][y]=DATA_12;};break;
                 case(13):{array_high_level_PID[i][y]=DATA_13;};break;
                 case(14):{array_high_level_PID[i][y]=DATA_14;};break;
                 case(15):{array_high_level_PID[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, (char)array_high_level_PID[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         //--------------------------------------------------------------------------------------
         
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_11);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_11_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='2'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         //--------------------------------------------------------------------------------------
         for(y=1;y<16;y++)
         {
             i = 1;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{array_high_level_PID[i][y]=DATA_1;};break;
                 case(2):{array_high_level_PID[i][y]=DATA_2;};break;
                 case(3):{array_high_level_PID[i][y]=DATA_3;};break;
                 case(4):{array_high_level_PID[i][y]=DATA_4;};break;
                 case(5):{array_high_level_PID[i][y]=DATA_5;};break;
                 case(6):{array_high_level_PID[i][y]=DATA_6;};break;
                 case(7):{array_high_level_PID[i][y]=DATA_7;};break;
                 case(8):{array_high_level_PID[i][y]=DATA_8;};break;
                 case(9):{array_high_level_PID[i][y]=DATA_9;};break;
                 case(10):{array_high_level_PID[i][y]=DATA_10;};break;
                 case(11):{array_high_level_PID[i][y]=DATA_11;};break;
                 case(12):{array_high_level_PID[i][y]=DATA_12;};break;
                 case(13):{array_high_level_PID[i][y]=DATA_13;};break;
                 case(14):{array_high_level_PID[i][y]=DATA_14;};break;
                 case(15):{array_high_level_PID[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, (char)array_high_level_PID[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         //--------------------------------------------------------------------------------------
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_12);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_12_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='3'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         //--------------------------------------------------------------------------------------
         for(y=1;y<16;y++)
         {
             i = 2;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{array_high_level_PID[i][y]=DATA_1;};break;
                 case(2):{array_high_level_PID[i][y]=DATA_2;};break;
                 case(3):{array_high_level_PID[i][y]=DATA_3;};break;
                 case(4):{array_high_level_PID[i][y]=DATA_4;};break;
                 case(5):{array_high_level_PID[i][y]=DATA_5;};break;
                 case(6):{array_high_level_PID[i][y]=DATA_6;};break;
                 case(7):{array_high_level_PID[i][y]=DATA_7;};break;
                 case(8):{array_high_level_PID[i][y]=DATA_8;};break;
                 case(9):{array_high_level_PID[i][y]=DATA_9;};break;
                 case(10):{array_high_level_PID[i][y]=DATA_10;};break;
                 case(11):{array_high_level_PID[i][y]=DATA_11;};break;
                 case(12):{array_high_level_PID[i][y]=DATA_12;};break;
                 case(13):{array_high_level_PID[i][y]=DATA_13;};break;
                 case(14):{array_high_level_PID[i][y]=DATA_14;};break;
                 case(15):{array_high_level_PID[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, (char)array_high_level_PID[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         //--------------------------------------------------------------------------------------
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_13);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_13_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='4'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         //--------------------------------------------------------------------------------------
         for(y=1;y<16;y++)
         {
             i = 3;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{array_high_level_PID[i][y]=DATA_1;};break;
                 case(2):{array_high_level_PID[i][y]=DATA_2;};break;
                 case(3):{array_high_level_PID[i][y]=DATA_3;};break;
                 case(4):{array_high_level_PID[i][y]=DATA_4;};break;
                 case(5):{array_high_level_PID[i][y]=DATA_5;};break;
                 case(6):{array_high_level_PID[i][y]=DATA_6;};break;
                 case(7):{array_high_level_PID[i][y]=DATA_7;};break;
                 case(8):{array_high_level_PID[i][y]=DATA_8;};break;
                 case(9):{array_high_level_PID[i][y]=DATA_9;};break;
                 case(10):{array_high_level_PID[i][y]=DATA_10;};break;
                 case(11):{array_high_level_PID[i][y]=DATA_11;};break;
                 case(12):{array_high_level_PID[i][y]=DATA_12;};break;
                 case(13):{array_high_level_PID[i][y]=DATA_13;};break;
                 case(14):{array_high_level_PID[i][y]=DATA_14;};break;
                 case(15):{array_high_level_PID[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, (char)array_high_level_PID[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         //--------------------------------------------------------------------------------------
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_14);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_14_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='5'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         //--------------------------------------------------------------------------------------
         for(y=1;y<16;y++)
         {
             i = 4;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{array_high_level_PID[i][y]=DATA_1;};break;
                 case(2):{array_high_level_PID[i][y]=DATA_2;};break;
                 case(3):{array_high_level_PID[i][y]=DATA_3;};break;
                 case(4):{array_high_level_PID[i][y]=DATA_4;};break;
                 case(5):{array_high_level_PID[i][y]=DATA_5;};break;
                 case(6):{array_high_level_PID[i][y]=DATA_6;};break;
                 case(7):{array_high_level_PID[i][y]=DATA_7;};break;
                 case(8):{array_high_level_PID[i][y]=DATA_8;};break;
                 case(9):{array_high_level_PID[i][y]=DATA_9;};break;
                 case(10):{array_high_level_PID[i][y]=DATA_10;};break;
                 case(11):{array_high_level_PID[i][y]=DATA_11;};break;
                 case(12):{array_high_level_PID[i][y]=DATA_12;};break;
                 case(13):{array_high_level_PID[i][y]=DATA_13;};break;
                 case(14):{array_high_level_PID[i][y]=DATA_14;};break;
                 case(15):{array_high_level_PID[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, (char)array_high_level_PID[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         //--------------------------------------------------------------------------------------
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_15);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_15_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='1')&&(Buffer_UART_RX[7]=='6'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         //--------------------------------------------------------------------------------------
         for(y=1;y<16;y++)
         {
             i = 5;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{array_high_level_PID[i][y]=DATA_1;};break;
                 case(2):{array_high_level_PID[i][y]=DATA_2;};break;
                 case(3):{array_high_level_PID[i][y]=DATA_3;};break;
                 case(4):{array_high_level_PID[i][y]=DATA_4;};break;
                 case(5):{array_high_level_PID[i][y]=DATA_5;};break;
                 case(6):{array_high_level_PID[i][y]=DATA_6;};break;
                 case(7):{array_high_level_PID[i][y]=DATA_7;};break;
                 case(8):{array_high_level_PID[i][y]=DATA_8;};break;
                 case(9):{array_high_level_PID[i][y]=DATA_9;};break;
                 case(10):{array_high_level_PID[i][y]=DATA_10;};break;
                 case(11):{array_high_level_PID[i][y]=DATA_11;};break;
                 case(12):{array_high_level_PID[i][y]=DATA_12;};break;
                 case(13):{array_high_level_PID[i][y]=DATA_13;};break;
                 case(14):{array_high_level_PID[i][y]=DATA_14;};break;
                 case(15):{array_high_level_PID[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, (char)array_high_level_PID[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         //--------------------------------------------------------------------------------------
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_16);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_16_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='1'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         //--------------------------------------------------------------------------------------
         for(y=0;y<15;y++)
         {
             i = 0;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
              __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_21);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_21_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='2'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 1;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_22);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_22_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='3'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 2;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_23);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_23_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='4'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 3;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_24);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_24_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='5'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 4;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_25);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_25_END);
  }
  
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='6'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 5;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_26);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_26_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='7'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 6;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_27);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_27_END);
  }
  
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='8'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 7;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_28);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_28_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='2')&&(Buffer_UART_RX[7]=='9'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 8;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_29);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_29_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='3')&&(Buffer_UART_RX[7]=='0'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 9;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_30);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_30_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='3')&&(Buffer_UART_RX[7]=='1'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 10;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_31);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_31_END);
  }
  
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='3')&&(Buffer_UART_RX[7]=='2'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 11;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_32);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_32_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='3')&&(Buffer_UART_RX[7]=='3'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         for(y=0;y<15;y++)
         {
             i = 12;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_33);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_33_END);
  }
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='3')&&(Buffer_UART_RX[7]=='4'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         num_element = 0;  
         for(y=0;y<15;y++)
         {
             i = 13;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_34);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_34_END);
  }
  
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='3')&&(Buffer_UART_RX[7]=='5'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);

         num_element = 0;  
         for(y=0;y<15;y++)
         {
             i = 14;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{faza_array_tooth[i][y]=DATA_1;};break;
                 case(2):{faza_array_tooth[i][y]=DATA_2;};break;
                 case(3):{faza_array_tooth[i][y]=DATA_3;};break;
                 case(4):{faza_array_tooth[i][y]=DATA_4;};break;
                 case(5):{faza_array_tooth[i][y]=DATA_5;};break;
                 case(6):{faza_array_tooth[i][y]=DATA_6;};break;
                 case(7):{faza_array_tooth[i][y]=DATA_7;};break;
                 case(8):{faza_array_tooth[i][y]=DATA_8;};break;
                 case(9):{faza_array_tooth[i][y]=DATA_9;};break;
                 case(10):{faza_array_tooth[i][y]=DATA_10;};break;
                 case(11):{faza_array_tooth[i][y]=DATA_11;};break;
                 case(12):{faza_array_tooth[i][y]=DATA_12;};break;
                 case(13):{faza_array_tooth[i][y]=DATA_13;};break;
                 case(14):{faza_array_tooth[i][y]=DATA_14;};break;
                 case(15):{faza_array_tooth[i][y]=DATA_15;};break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_35);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_35_END);  
  }
  
  
  
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='T')&&(Buffer_UART_RX[6]=='4')&&(Buffer_UART_RX[7]=='1'))
  {
         DATA_1 = (unsigned char)Sf_variable(&Buffer_UART_RX[8+next_p]);
         DATA_2 = (unsigned char)Sf_variable(&Buffer_UART_RX[9+next_p]);
         DATA_3 = (unsigned char)Sf_variable(&Buffer_UART_RX[10+next_p]);
         DATA_4 = (unsigned char)Sf_variable(&Buffer_UART_RX[11+next_p]);
         DATA_5 = (unsigned char)Sf_variable(&Buffer_UART_RX[12+next_p]);
         DATA_6 = (unsigned char)Sf_variable(&Buffer_UART_RX[13+next_p]);
         DATA_7 = (unsigned char)Sf_variable(&Buffer_UART_RX[14+next_p]);
         DATA_8 = (unsigned char)Sf_variable(&Buffer_UART_RX[15+next_p]);
         DATA_9 = (unsigned char)Sf_variable(&Buffer_UART_RX[16+next_p]);
         DATA_10 = (unsigned char)Sf_variable(&Buffer_UART_RX[17+next_p]);
         DATA_11 = (unsigned char)Sf_variable(&Buffer_UART_RX[18+next_p]);
         DATA_12 = (unsigned char)Sf_variable(&Buffer_UART_RX[19+next_p]);
         DATA_13 = (unsigned char)Sf_variable(&Buffer_UART_RX[20+next_p]);
         DATA_14 = (unsigned char)Sf_variable(&Buffer_UART_RX[21+next_p]);
         DATA_15 = (unsigned char)Sf_variable(&Buffer_UART_RX[22+next_p]);
         DATA_16 = (unsigned char)Sf_variable(&Buffer_UART_RX[23+next_p]);
         
         num_element = 0;
         for(i=0;i<16;i++)
         {
             y = 0;
             num_element = num_element + 1;
             switch(num_element)
             {
                 case(1):{Step_motor_array_cicle[i]=DATA_1;};break;
                 case(2):{Step_motor_array_cicle[i]=DATA_2;};break;
                 case(3):{Step_motor_array_cicle[i]=DATA_3;};break;
                 case(4):{Step_motor_array_cicle[i]=DATA_4;};break;
                 case(5):{Step_motor_array_cicle[i]=DATA_5;};break;
                 case(6):{Step_motor_array_cicle[i]=DATA_6;};break;
                 case(7):{Step_motor_array_cicle[i]=DATA_7;};break;
                 case(8):{Step_motor_array_cicle[i]=DATA_8;};break;
                 case(9):{Step_motor_array_cicle[i]=DATA_9;};break;
                 case(10):{Step_motor_array_cicle[i]=DATA_10;};break;
                 case(11):{Step_motor_array_cicle[i]=DATA_11;};break;
                 case(12):{Step_motor_array_cicle[i]=DATA_12;};break;
                 case(13):{Step_motor_array_cicle[i]=DATA_13;};break;
                 case(14):{Step_motor_array_cicle[i]=DATA_14;};break;
                 case(15):{Step_motor_array_cicle[i]=DATA_15;};break;
                 case(16):{Step_motor_array_cicle[i]=DATA_16;};break;
             default:break;
             }
             __disable_interrupt();
             write_Card_2K_I2C(Step_motor_array_cicle_24LC16B+i, Step_motor_array_cicle[i]);
             __enable_interrupt();
         }
         num_element = 0;
         loc_x=1;
         Ok_UART();
         //разрешить передачу данных - ответ
         next_p = 0;
         printf_const_UART(DT_41);
         Printf_Variable_UART(DATA_1);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_2);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_3);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_4);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_5);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_6);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_7);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_8);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_9);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_10);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_11);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_12);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_13);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_14);
         Send_UART_char('.');
         Printf_Variable_UART(DATA_15);
         Send_UART_char('.');
         printf_const_UART(DT_41_END);
  }
}




//----------------------------------------------------------------
//ЗАПИСЬ ДАННЫХ В ПАМЯТЬ
//----------------------------------------------------------------
void var(void)
{
  unsigned char i,y;
  
  //==========================================================================================
  if((Buffer_UART_RX[4]=='E')&&(Buffer_UART_RX[5]=='r'))
  {
    Flag_error_N=(int)Sscanf_variable(&Buffer_UART_RX[7]);
    __disable_interrupt();
    write_Card_2K_I2C(Flag_error_N_24LC16B, (char)(Flag_error_N>>8));
    write_Card_2K_I2C(Flag_error_N_24LC16B+1, (char)(Flag_error_N&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='0'))
  {
    Serial_number=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    write_Card_2K_I2C(Serial_number_24LC16B, (char)(Serial_number>>8));
    write_Card_2K_I2C(Serial_number_24LC16B+1, (char)(Serial_number&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_1);
    Printf_Variable_UART(Serial_number);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='1'))
  {
    Step_Motor_Koeff=(int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_s_int+Kp_Gain_1_eeprom) = Kp_Gain_1;
    write_Card_2K_I2C(Step_Motor_Koeff_24LC16B, (char)(Step_Motor_Koeff>>8));
    write_Card_2K_I2C(Step_Motor_Koeff_24LC16B+1, (char)(Step_Motor_Koeff&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_2);
    Printf_Variable_UART(Step_Motor_Koeff);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='2'))
  {
    Kp_Gain_2=(int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_s_int+Kp_Gain_2_eeprom) = Kp_Gain_2;
    write_Card_2K_I2C(Kp_Gain_2_24LC16B, (char)(Kp_Gain_2>>8));
    write_Card_2K_I2C(Kp_Gain_2_24LC16B+1, (char)(Kp_Gain_2&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_3);
    Printf_Variable_UART(Kp_Gain_2);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='3'))
  {
    Kp_Gain_PID_t_1=(int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_s_int+Kp_Gain_2_eeprom) = Kp_Gain_2;
    write_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B, (char)(Kp_Gain_PID_t_1>>8));
    write_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B+1, (char)(Kp_Gain_PID_t_1&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_4);
    Printf_Variable_UART(Kp_Gain_PID_t_1);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='4'))
  {
    Kp_Gain_PID_t_2=(int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_s_int+Kp_Gain_2_eeprom) = Kp_Gain_2;
    write_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B, (char)(Kp_Gain_PID_t_2>>8));
    write_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B+1, (char)(Kp_Gain_PID_t_2&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_5);
    Printf_Variable_UART(Kp_Gain_PID_t_2);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='I')&&(Buffer_UART_RX[5]=='d'))
  {
    idling_motor_dizel=(unsigned int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_uns_int+idling_motor_dizel_eeprom) = idling_motor_dizel;
    write_Card_2K_I2C(idling_motor_dizel_24LC16B, (char)(idling_motor_dizel>>8));
    write_Card_2K_I2C(idling_motor_dizel_24LC16B+1, (char)(idling_motor_dizel&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_8);
    Printf_Variable_UART(idling_motor_dizel);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='m'))
  {
    offset_motor_tax=(signed int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_s_int+offset_motor_tax_eeprom) = offset_motor_tax;
    write_Card_2K_I2C(offset_motor_tax_24LC16B, (char)(offset_motor_tax>>8));
    write_Card_2K_I2C(offset_motor_tax_24LC16B+1, (char)(offset_motor_tax&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_12);
    Printf_Variable_UART(offset_motor_tax);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='k'))
  {
    Turbo_Koeff=Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_s_int+Turbo_Koeff_eeprom) = Turbo_Koeff;
    write_Card_2K_I2C(Turbo_Koeff_24LC16B, (char)(Turbo_Koeff>>8));
    write_Card_2K_I2C(Turbo_Koeff_24LC16B+1, (char)(Turbo_Koeff&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_11);
    Printf_Variable_UART(Turbo_Koeff);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='o'))
  {
    Turbo_offset=Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_s_int+Turbo_offset_eeprom) = Turbo_offset;
    write_Card_2K_I2C(Turbo_offset_24LC16B, (char)(Turbo_offset>>8));
    write_Card_2K_I2C(Turbo_offset_24LC16B+1, (char)(Turbo_offset&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_10);
    Printf_Variable_UART(Turbo_offset);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='T')&&(Buffer_UART_RX[5]=='c'))
  {
    temperature_predetermined=(int)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    write_Card_2K_I2C(temperature_pred_24LC16B, (char)(temperature_predetermined>>8));
    write_Card_2K_I2C(temperature_pred_24LC16B+1, (char)(temperature_predetermined&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_6);
    Printf_Variable_UART(temperature_predetermined);
    Send_UART_char(' ');
  }
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='l'))
  {
    D_min=(int)Sscanf_variable(&Buffer_UART_RX[8]);
    D_min_max = D_max;
    D_min_max<<=8;
    D_min_max = D_min_max&0xFF00;
    D_min_max = D_min_max+D_min;
    __disable_interrupt();
    write_Card_2K_I2C(D_min_max_24LC16B, (char)(D_min_max>>8));
    write_Card_2K_I2C(D_min_max_24LC16B+1, (char)(D_min_max&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_7l);
    Printf_Variable_UART(D_min);
    Send_UART_char(' ');
  }
  if((Buffer_UART_RX[4]=='D')&&(Buffer_UART_RX[5]=='h'))
  {
    D_max=(int)Sscanf_variable(&Buffer_UART_RX[8]);
    D_min_max = D_max;
    D_min_max<<=8;
    D_min_max = D_min_max&0xFF00;
    D_min_max = D_min_max+D_min;
    __disable_interrupt();
    write_Card_2K_I2C(D_min_max_24LC16B, (char)(D_min_max>>8));
    write_Card_2K_I2C(D_min_max_24LC16B+1, (char)(D_min_max&0x00FF));
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_7h);
    Printf_Variable_UART(D_max);
    Send_UART_char(' ');
  }
  if((Buffer_UART_RX[4]=='M')&&(Buffer_UART_RX[5]=='p'))
  {
    Step_Motor_Position=(unsigned int)Sscanf_variable(&Buffer_UART_RX[7]);
    loc_x=1;
    Ok_UART();
  }
  if((Buffer_UART_RX[4]=='M')&&(Buffer_UART_RX[5]=='f'))
  {
    Step_Motor_Future=(unsigned int)Sscanf_variable(&Buffer_UART_RX[7]);
    Step_Motor_Future = Step_Motor_Future*Step_Motor_Koeff;
    loc_x=1;
    Ok_UART();
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='M')&&(Buffer_UART_RX[5]=='o'))
  {
    Step_Motor_OffSet=(unsigned char)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    write_Card_2K_I2C(Step_Motor_OffSet_24LC16B, Step_Motor_OffSet);
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_9);
    Printf_Variable_UART(Step_Motor_OffSet);
    Send_UART_char(' ');
  }
  //==========================================================================================
  if((Buffer_UART_RX[4]=='M')&&(Buffer_UART_RX[5]=='t'))
  {
    Kol_zubov_kolenvala=(unsigned char)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    write_Card_2K_I2C(Kol_zubov_kolenvala_24LC16B, Kol_zubov_kolenvala);
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
    //разрешить передачу данных - ответ
    printf_const_UART(OTV_13);
    Printf_Variable_UART(Kol_zubov_kolenvala);
    Send_UART_char(' ');
  }
  if((Buffer_UART_RX[4]=='F')&&(Buffer_UART_RX[5]=='d'))
  {
    Flag_Duo_Mono=(unsigned char)Sscanf_variable(&Buffer_UART_RX[7]);
    __disable_interrupt();
    //*(var_uns_char+Flag_Duo_Mono_eeprom)=Flag_Duo_Mono;
    write_Card_2K_I2C(Flag_Duo_Mono_24LC16B, Flag_Duo_Mono);
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
  }
  if((Buffer_UART_RX[4]=='F')&&(Buffer_UART_RX[5]=='p'))
  {
    Flag_PID_PI=(unsigned char)Sscanf_variable(&Buffer_UART_RX[7]);
    loc_x=1;
    Ok_UART();
  }
  if((Buffer_UART_RX[4]=='F')&&(Buffer_UART_RX[5]=='i'))
  {
    Flag_PC_interf=(unsigned char)Sscanf_variable(&Buffer_UART_RX[7]);
    loc_x=1;
    Ok_UART();
  }
  if((Buffer_UART_RX[4]=='P')&&(Buffer_UART_RX[5]=='h'))
  {
    High_Level_PID=(unsigned char)Sscanf_variable(&Buffer_UART_RX[7]);
    __disable_interrupt();
    //*(var_uns_char+High_Level_PID_eeprom)=High_Level_PID;
    write_Card_2K_I2C(High_Level_PID_24LC16B, (char)High_Level_PID);
    High_Level_PID=High_Level_PID*div_milisek_switch;
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
  }
  if((Buffer_UART_RX[4]=='P')&&(Buffer_UART_RX[5]=='l'))
  {
    Low_Level_PID=(unsigned char)Sscanf_variable(&Buffer_UART_RX[7]);
    __disable_interrupt();
    //*(var_uns_char+Low_Level_PID_eeprom)=Low_Level_PID;
    write_Card_2K_I2C(Low_Level_PID_24LC16B, (char)Low_Level_PID);
    Low_Level_PID=Low_Level_PID*div_milisek_switch;
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
  }
  if((Buffer_UART_RX[4]=='P')&&(Buffer_UART_RX[5]=='i'))
  {
    Low_Level_Idling=(unsigned char)Sscanf_variable(&Buffer_UART_RX[8]);
    __disable_interrupt();
    //*(var_uns_char+Low_Level_Idling_eeprom)=(unsigned char)Low_Level_Idling;
    write_Card_2K_I2C(Low_Level_Idling_24LC16B, (char)Low_Level_Idling);
    Low_Level_Idling=Low_Level_Idling*div_milisek_switch;
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
  }
  if(Buffer_UART_RX[4]=='A')
  {
    i=(Buffer_UART_RX[5]&0x0F)*10+(Buffer_UART_RX[6]&0x0F);
    y=(Buffer_UART_RX[7]&0x0F)*10+(Buffer_UART_RX[8]&0x0F);

    faza_array_tooth[i][y]=(unsigned char)Sscanf_variable(&Buffer_UART_RX[10]);
    __disable_interrupt();
    //*(var_uns_char+faza_array_tooth_eeprom+i) = faza_array_tooth[i];
    write_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y, faza_array_tooth[i][y]);
    __enable_interrupt();
    loc_x=1;
    Ok_UART();
  }
  if(Buffer_UART_RX[4]=='S')
  {
     i=(Buffer_UART_RX[5]&0x0F)*10+(Buffer_UART_RX[6]&0x0F);
     Step_motor_array_cicle[i]=(unsigned char)Sscanf_variable(&Buffer_UART_RX[8]);
     __disable_interrupt();
     //*(var_uns_char+faza_array_tooth_eeprom+i) = faza_array_tooth[i];
     write_Card_2K_I2C(Step_motor_array_cicle_24LC16B+i, Step_motor_array_cicle[i]);
     __enable_interrupt();
     loc_x=1;
     Ok_UART();
  }
  if(Buffer_UART_RX[4]=='H')
  {
     i=(Buffer_UART_RX[5]&0x0F);
     y=(Buffer_UART_RX[6]&0x0F)*10+(Buffer_UART_RX[7]&0x0F);
     array_high_level_PID[i][y]=(unsigned char)Sscanf_variable(&Buffer_UART_RX[9]);
     __disable_interrupt();
     write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, array_high_level_PID[i][y]);
     __enable_interrupt();
     loc_x=1;
     Ok_UART();
     //if(y == 3)
     //{
     //   Bazer_ON;
     //}
     //else
     //{
     //   Bazer_OFF;
     //}  
  }
  if((Buffer_UART_RX[4]=='K')&&(Buffer_UART_RX[5]=='z'))
  {
     enable_pysk_ras = 1;
     loc_x=1;
     Ok_UART();
  }
  //если команда не пришла - ошибка
  if(loc_x==0) Error_message(1);
}


//------------------------------------------------------------------------------
//"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"-"RUN"
//------------------------------------------------------------------------------
void run(void)
{
  register unsigned char loc_error=0;
  
  if(Buffer_UART_RX[4]=='q')
  {
     
     loc_error=1;
     Ok_UART();
     if(Flag_State_Run_GD==0)
     {  
        //ответный сигнал на STOP - GD
        printf_const_UART(OTV_STOP_GD);
        Send_UART_char(' ');
        Flag_GD_Button=1;
        comand_run_gd = 1;
     }
  }
  
  if(Buffer_UART_RX[4]=='r')
  {
     loc_error=1;
     Ok_UART();
     if(Flag_State_Run_GD==1)
     {  
        //ответный сигнал на START - GD
        printf_const_UART(OTV_RUN_GD);
        Send_UART_char(' ');
        Flag_GD_Button=1;
        comand_run_gd = 1;
     }
     /*
     if(Flag_State_Run_GD==0)
     {
     if((ON_OFF_Car_READ)!=0)
     {
     if(taxometer>idling_motor_dizel-200)
     {
        if(test_treadle()==0)
        {
           //if(temperature_Reduktor>temperature_predetermined_Reduktor)
           //{
                Flag_State_Run_GD=1;
                //if(test_dat_dav()==0)
                //{ 
                     Run_GD();
                //off_sys = 0;
                //enable_off_sys = 0;
                //}
              Flag_GD_Button=0;
           //}else Error_function_e(Error_t_Reduktor);
           printf_const_UART(OK_RUN_GD);
           Send_UART_char(' ');
        }
        else
        {  
            printf_const_UART(ERROR_GD);
            Send_UART_char(' ');
        }
     }
     else
     {  
        printf_const_UART(ERROR_GD);
        Send_UART_char(' ');
     }
     }
     else
     {
        printf_const_UART(ERROR_GD);
        Send_UART_char(' ');
     }
     }
     else
     {
        printf_const_UART(ERROR_GD);
        Send_UART_char(' '); 
     } 
     */
  }
  /*
  if(Buffer_UART_RX[4]=='t')
  {
     //Sekundomer_s=0;
     Flag_State_Run_GD=0;
     test_system__GD();
     loc_error=1;
     Ok_UART();
  }
  if((Buffer_UART_RX[4]=='e')&&(Buffer_UART_RX[5]=='w'))
  {
     write_eeprom_24LC16B();
     loc_error=1;
     Ok_UART();
  }
  if((Buffer_UART_RX[4]=='e')&&(Buffer_UART_RX[5]=='r'))
  {
     read_eeprom_24LC16B();
     loc_error=1;
     Ok_UART();
  }
  */
  if(loc_error==0) Error_message(1);
}



//---------------------------------------------------------------------------------
//ПОДПРОГРАММА РАСЧЕТА КОНТРОЛЬНОЙ СУММЫ
//---------------------------------------------------------------------------------
unsigned char CRC_PROV(unsigned char wert)
{
  unsigned char tty;
  unsigned char data_ttt;
  unsigned char crc_kontr;
  
  
  crc_kontr = 0;  
  for(tty=0;tty<wert;tty++)
  {
      data_ttt = Buffer_UART_RX[tty];
      crc_kontr = crc_kontr^data_ttt;
  }
  if(crc_kontr == 0)
  {
     //ошибки нет - можно анализировать данные 
     return(1);
  }
  return(0);
}

