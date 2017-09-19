// -------------------------------- RW_EEPROM.h -----------------------------------------
// SCL - PC7
// SDA - PB4

#define   EE24LC16B_WP_OUT      DDRG|=0x04
#define   EE24LC16B_WP_ON       PORTG|=0x04
#define   EE24LC16B_WP_OFF      PORTG&=~0x04
#define   EE24LC16B_SCL_OUT     DDRG|=0x01
#define   EE24LC16B_SCL_ON      PORTG|=0x01
#define   EE24LC16B_SCL_OFF     PORTG&=~0x01
#define   EE24LC16B_SDA_IN      DDRG&=~0x02
#define   EE24LC16B_SDA_OUT     DDRG|=0x02
#define   EE24LC16B_SDA_READ    PING&0x02
#define   EE24LC16B_SDA_ON      PORTG|=0x02
#define   EE24LC16B_SDA_OFF     PORTG&=~0x02

#define   EE24LC16B_delay_reset     16000
#define   EE24LC16B_delay_SP        200
#define   EE24LC16B_delay_clock     400

/*#define SCL 0x80
#define SDA 0x10*/

//#define delay_start_stop 100
//#define delay_clock 200 


void send_byte_Card_I2C(unsigned char byte_l)
{
   unsigned char local_count;
   EE24LC16B_SDA_OUT;
   for(local_count=0; local_count<=7; local_count++)
   {
       if(((byte_l>>7-local_count)&0x01)==0) EE24LC16B_SDA_OFF;
       else EE24LC16B_SDA_ON;
       Delay_S(EE24LC16B_delay_clock);
       EE24LC16B_SCL_ON;
       Delay_S(EE24LC16B_delay_clock);
       EE24LC16B_SCL_OFF;
   }
}


char Get_byte_Card_I2C(void)
{
  unsigned char local_count;
  unsigned char Local_b=0;
  EE24LC16B_SDA_IN;
  for(local_count=0; local_count<=7; local_count++)
  {
      Delay_S(EE24LC16B_delay_clock);
      EE24LC16B_SCL_ON;
      Delay_S(EE24LC16B_delay_clock);
      if((EE24LC16B_SDA_READ)==0) Local_b=(Local_b<<1)&0xFE;
      else Local_b=(Local_b<<1)|0x01;
      EE24LC16B_SCL_OFF;
  }
  EE24LC16B_SDA_OUT;
  return(Local_b);
}


void S_P_Card_I2C(unsigned char flag_l)
{
  EE24LC16B_SDA_OUT;
  if(flag_l==1)
  {
     EE24LC16B_SDA_ON;
     Delay_S(EE24LC16B_delay_clock);
     EE24LC16B_SCL_ON;
     Delay_S(EE24LC16B_delay_SP);
     EE24LC16B_SDA_OFF;
     Delay_S(EE24LC16B_delay_SP);
     EE24LC16B_SCL_OFF;
  }
  else
  {
     EE24LC16B_SCL_OFF;
     EE24LC16B_SDA_OFF;
     Delay_S(EE24LC16B_delay_clock);
     EE24LC16B_SCL_ON;
     Delay_S(EE24LC16B_delay_SP);
     EE24LC16B_SDA_ON;
     Delay_S(EE24LC16B_delay_SP);
  }
}

//-----------------------------------------------------------
//НАЧАЛЬНЫЕ УСТАНОВКИ ДЛЯ РАБОТЫ С ВНЕШНЕЙ ПАМЯТЬЮ
//-----------------------------------------------------------
void Reset_Card_I2C(void)
{
  EE24LC16B_WP_OUT;
  //EE24LC16B_WP_OFF;
  EE24LC16B_WP_ON;
  EE24LC16B_SCL_OUT;
  EE24LC16B_SDA_OUT;
  EE24LC16B_SDA_ON;
  EE24LC16B_SCL_ON;
  //Delay_S(EE24LC16B_delay_reset);
}

unsigned char ACK_Card_I2C(void)
{
  unsigned char ack_b;
  EE24LC16B_SDA_IN;
  //EE24LC16B_SDA_ON;
  EE24LC16B_SCL_OFF;
  Delay_S(EE24LC16B_delay_clock);
  EE24LC16B_SCL_ON;
  Delay_S(EE24LC16B_delay_clock);
  if((EE24LC16B_SDA_READ)==0) ack_b=0; 
  else ack_b=1;
  EE24LC16B_SCL_OFF;
  EE24LC16B_SDA_OUT;
  return(ack_b);
}


void write_Card_2K_I2C(int addrres, char byte_i2c)
{  
  unsigned char local_control_b;
  unsigned char local_ad_b;
  unsigned int local_ad_2b;
  unsigned char *local_loop;
  
  EE24LC16B_WP_OFF;
  Delay_S(EE24LC16B_delay_clock);
  
  local_ad_2b=addrres;
  local_loop=(unsigned char *)&local_ad_2b;
  local_control_b=(0xA0|(*(local_loop+1)<<1))&(~0x01);
  local_ad_b = *local_loop;
  
  goto SWL0; 
SWL1: S_P_Card_I2C(0);
SWL0: S_P_Card_I2C(1);
  send_byte_Card_I2C(local_control_b);
  
  if(ACK_Card_I2C()!=0) goto SWL1;
  send_byte_Card_I2C(local_ad_b);
  if(ACK_Card_I2C()!=0) goto SWL1;
  //ACK_Card_I2C();
  send_byte_Card_I2C(byte_i2c);
  if(ACK_Card_I2C()!=0) goto SWL1;
  //ACK_Card_I2C();
  S_P_Card_I2C(0);
  
  /*Delay_S(EE24LC16B_delay_clock);
  S_P_Card_I2C(1);
  send_byte_Card_I2C(local_control_b);
  ACK_Card_I2C();
  send_byte_Card_I2C(local_ad_b);
  ACK_Card_I2C();
  send_byte_Card_I2C(byte_i2c);
  ACK_Card_I2C();
  S_P_Card_I2C(0);*/
  
  Delay_S(EE24LC16B_delay_reset);
  
  //if(byte_i2c!=Read_Card_2K_I2C(local_ad_2b)) goto SWL0;
  
  Delay_S(EE24LC16B_delay_clock);
  EE24LC16B_WP_ON;
}


char Read_Card_2K_I2C(int addrres)
{
  unsigned char local_control_b;
  unsigned char local_ad_b;
  unsigned int local_ad_2b;
  unsigned char *local_loop;
  unsigned char l_byte_ret;
  
  local_ad_2b=addrres;
  local_loop=(unsigned char *)&local_ad_2b;
  local_control_b=(0xA0|(*(local_loop+1)<<1))&(~0x01);
  local_ad_b = *local_loop;
  
  goto SRL0;
SRL2: S_P_Card_I2C(0);
SRL0: S_P_Card_I2C(1);
  send_byte_Card_I2C(local_control_b);
  if(ACK_Card_I2C()!=0) goto SRL2;
  //ACK_Card_I2C();
  send_byte_Card_I2C(local_ad_b);
  if(ACK_Card_I2C()!=0) goto SRL2;
  //ACK_Card_I2C();
  
  S_P_Card_I2C(1);
  send_byte_Card_I2C(local_control_b|0x01);
  if(ACK_Card_I2C()!=0) goto SRL2;
  //ACK_Card_I2C();
  l_byte_ret = Get_byte_Card_I2C();
  ACK_Card_I2C();
  S_P_Card_I2C(0);
  return(l_byte_ret);
}
//------------------------------------- programm load------------------------


void init_24LC16B_var(void)
{
  unsigned char i,y;
  //unsigned char *l_vchar;
  __disable_interrupt();
  Serial_number = Read_Card_2K_I2C(Serial_number_24LC16B);
  Serial_number = (Serial_number<<8)|(Read_Card_2K_I2C(Serial_number_24LC16B+1));
  Step_Motor_Koeff = Read_Card_2K_I2C(Step_Motor_Koeff_24LC16B);
  Step_Motor_Koeff = (Step_Motor_Koeff<<8)|(Read_Card_2K_I2C(Step_Motor_Koeff_24LC16B+1));
  Kp_Gain_2 = Read_Card_2K_I2C(Kp_Gain_2_24LC16B);
  Kp_Gain_2 = (Kp_Gain_2<<8)|(Read_Card_2K_I2C(Kp_Gain_2_24LC16B+1));
  idling_motor_dizel = Read_Card_2K_I2C(idling_motor_dizel_24LC16B);
  idling_motor_dizel = (idling_motor_dizel<<8)|(Read_Card_2K_I2C(idling_motor_dizel_24LC16B+1));
  Turbo_Koeff = Read_Card_2K_I2C(Turbo_Koeff_24LC16B);
  Turbo_Koeff = (Turbo_Koeff<<8)|(Read_Card_2K_I2C(Turbo_Koeff_24LC16B+1));
  Turbo_offset = Read_Card_2K_I2C(Turbo_offset_24LC16B);
  Turbo_offset = (Turbo_offset<<8)|(Read_Card_2K_I2C(Turbo_offset_24LC16B+1));
  offset_motor_tax = Read_Card_2K_I2C(offset_motor_tax_24LC16B);
  offset_motor_tax = (offset_motor_tax<<8)|(Read_Card_2K_I2C(offset_motor_tax_24LC16B+1));
  
  High_Level_PID = Read_Card_2K_I2C(High_Level_PID_24LC16B);
  High_Level_PID=High_Level_PID*div_milisek_switch;
  Rezult_PID_temperature=High_Level_PID;
  Low_Level_PID = Read_Card_2K_I2C(Low_Level_PID_24LC16B);
  Low_Level_PID=Low_Level_PID*div_milisek_switch;
  Step_Motor_OffSet = Read_Card_2K_I2C(Step_Motor_OffSet_24LC16B);
  Kol_zubov_kolenvala = Read_Card_2K_I2C(Kol_zubov_kolenvala_24LC16B);
  swN_number_tooth=Kol_zubov_kolenvala/(motor_cylinders/2);
  /*
  for(i=0;i<16;i++)
  {
    faza_array_tooth[i] = Read_Card_2K_I2C(faza_array_tooth_24LC16B+i);
  }
  */
  for(i=0;i<16;i++)
  {
     for(y=0;y<16;y++)
     {
         faza_array_tooth[i][y] = Read_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y);
     }
  }
  sw1_number_tooth = faza_array_tooth[0][(min_turns_motora_dizel/200)];
  //начальное кол.зубьев для минимальной скорости 800(min_turns_motora_dizel)
  //--------------------------------------------------------------------------------
  if(sw1_number_tooth == 0)
  {
     sw1_number_tooth = 10;
  } 
  //--------------------------------------------------------------------------------

  for(i=0;i<16;i++)
  {
    Step_motor_array_cicle[i] = Read_Card_2K_I2C(Step_motor_array_cicle_24LC16B+i);
  }
  for(i=0;i<9;i++)
  {
        for(y=0;y<5;y++)
        {
          Axelerometr_tax[i][y] = Read_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+y)*2);
          Axelerometr_tax[i][y] = (Axelerometr_tax[i][y]<<8)|(Read_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+y)*2+1));
        }
  }
  for(i=0;i<6;i++)
  {
        for(y=0;y<16;y++)
        {
          array_high_level_PID[i][y] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y);
          array_high_level_PID[i][y] = array_high_level_PID[i][y]*div_milisek_switch;
        }
  }
  Low_Level_Idling = Read_Card_2K_I2C(Low_Level_Idling_24LC16B);
  Low_Level_Idling=Low_Level_Idling*div_milisek_switch;
  Flag_error_N = Read_Card_2K_I2C(Flag_error_N_24LC16B);
  Flag_error_N = (Flag_error_N<<8)|(Read_Card_2K_I2C(Flag_error_N_24LC16B+1));
  
  Kp_Gain_PID_t_1 = Read_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B);
  Kp_Gain_PID_t_1 = (Kp_Gain_PID_t_1<<8)|(Read_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B+1));
  Kp_Gain_PID_t_2 = Read_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B);
  Kp_Gain_PID_t_2 = (Kp_Gain_PID_t_2<<8)|(Read_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B+1));
  temperature_predetermined = Read_Card_2K_I2C(temperature_pred_24LC16B);
  temperature_predetermined = (temperature_predetermined<<8)|(Read_Card_2K_I2C(temperature_pred_24LC16B+1));
  D_min_max = Read_Card_2K_I2C(D_min_max_24LC16B);
  D_min_max = (D_min_max<<8)|(Read_Card_2K_I2C(D_min_max_24LC16B+1));
  
  D_min = D_min_max;
  D_min = D_min&0x00FF;
  D_min_max>>=8;
  D_min_max = D_min_max&0x00FF;
  D_max = D_min_max;
  D_max = D_max&0x00FF;
  __enable_interrupt();
}



void write_eeprom_24LC16B(void)
{
  unsigned char i,y;
  //unsigned char *l_vchar;
  __disable_interrupt();
  Serial_number = *(var_s_int+Serial_number_eeprom);
  write_Card_2K_I2C(Serial_number_24LC16B, (char)(Serial_number>>8));
  write_Card_2K_I2C(Serial_number_24LC16B+1, (char)(Serial_number&0x00FF));
  Step_Motor_Koeff = *(var_s_int+Step_Motor_Koeff_eeprom);
  write_Card_2K_I2C(Step_Motor_Koeff_24LC16B, (char)(Step_Motor_Koeff>>8));
  write_Card_2K_I2C(Step_Motor_Koeff_24LC16B+1, (char)(Step_Motor_Koeff&0x00FF));
  Kp_Gain_2 = *(var_s_int+Kp_Gain_2_eeprom);
  write_Card_2K_I2C(Kp_Gain_2_24LC16B, (char)(Kp_Gain_2>>8));
  write_Card_2K_I2C(Kp_Gain_2_24LC16B+1, (char)(Kp_Gain_2&0x00FF));
  idling_motor_dizel = *(var_uns_int+idling_motor_dizel_eeprom);
  write_Card_2K_I2C(idling_motor_dizel_24LC16B, (char)(idling_motor_dizel>>8));
  write_Card_2K_I2C(idling_motor_dizel_24LC16B+1, (char)(idling_motor_dizel&0x00FF));
  High_Level_PID = *(var_uns_char+High_Level_PID_eeprom);
  write_Card_2K_I2C(High_Level_PID_24LC16B, (char)High_Level_PID);
  High_Level_PID=High_Level_PID*div_milisek_switch;
  Low_Level_PID = *(var_uns_char+Low_Level_PID_eeprom);
  write_Card_2K_I2C(Low_Level_PID_24LC16B, (char)Low_Level_PID);
  Low_Level_PID=Low_Level_PID*div_milisek_switch;
  Step_Motor_OffSet = *(var_uns_char+Step_Motor_OffSet_eeprom);
  write_Card_2K_I2C(Step_Motor_OffSet_24LC16B, (char)Step_Motor_OffSet);
  Kol_zubov_kolenvala = *(var_uns_char+Kol_zubov_kolenvala_eeprom);
  write_Card_2K_I2C(Kol_zubov_kolenvala_24LC16B, (char)Kol_zubov_kolenvala);
  
  //запись в память таблицы "КОРРЕКЦИЯ УГЛА ВПРЫСКА" [16][16]
  for(i=0;i<16;i++)
  {
      for(y=0;y<16;y++)
      {
         faza_array_tooth[i][y]= *(var_uns_char + faza_array_tooth_eeprom + i*16+y);
         write_Card_2K_I2C(faza_array_tooth_24LC16B + i*16+y, faza_array_tooth[i][y]);
      }
  }
  
  for(i=0;i<16;i++)
  {
      Step_motor_array_cicle[i]= *(var_uns_char+Step_motor_array_cicle_eeprom+i);
      write_Card_2K_I2C(Step_motor_array_cicle_24LC16B+i, Step_motor_array_cicle[i]);
  }
  
  //Flag_Duo_Mono = *(var_uns_char+Flag_Duo_Mono_eeprom);
  Turbo_Koeff = *(var_s_int+Turbo_Koeff_eeprom);
  write_Card_2K_I2C(Turbo_Koeff_24LC16B, (char)(Turbo_Koeff>>8));
  write_Card_2K_I2C(Turbo_Koeff_24LC16B+1, (char)(Turbo_Koeff&0x00FF));
  Turbo_offset = *(var_s_int+Turbo_offset_eeprom);
  write_Card_2K_I2C(Turbo_offset_24LC16B, (char)(Turbo_offset>>8));
  write_Card_2K_I2C(Turbo_offset_24LC16B+1, (char)(Turbo_offset&0x00FF));
  offset_motor_tax = *(var_s_int+offset_motor_tax_eeprom);
  write_Card_2K_I2C(offset_motor_tax_24LC16B, (char)(offset_motor_tax>>8));
  write_Card_2K_I2C(offset_motor_tax_24LC16B+1, (char)(offset_motor_tax&0x00FF));
  for(i=0;i<9;i++)
  {
        for(y=0;y<5;y++)
        {
          Axelerometr_tax[i][y]=*(var_s_int+Axelerometr_tax_eeprom+i*5+y);
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+y)*2, (char)(Axelerometr_tax[i][y]>>8));
          write_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+y)*2+1, (char)(Axelerometr_tax[i][y]&0x00FF));
        }
  }
  for(i=0;i<6;i++)
  {
        for(y=0;y<16;y++)
        {
          array_high_level_PID[i][y]= *(var_uns_char+array_high_level_PID_eeprom+i*16+y);
          write_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y, (char)array_high_level_PID[i][y]);
          array_high_level_PID[i][y]=array_high_level_PID[i][y]*div_milisek_switch;
        }
  }
  Low_Level_Idling = *(var_uns_char+Low_Level_Idling_eeprom);
  write_Card_2K_I2C(Low_Level_Idling_24LC16B, (char)Low_Level_Idling);
  Low_Level_Idling=Low_Level_Idling*div_milisek_switch;
  
  Kp_Gain_PID_t_1 = *(var_s_int+Kp_Gain_PID_t_1_eeprom);
  write_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B, (char)(Kp_Gain_PID_t_1>>8));
  write_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B+1, (char)(Kp_Gain_PID_t_1&0x00FF));
  Kp_Gain_PID_t_2 = *(var_s_int+Kp_Gain_PID_t_2_eeprom);
  write_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B, (char)(Kp_Gain_PID_t_2>>8));
  write_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B+1, (char)(Kp_Gain_PID_t_2&0x00FF));
  temperature_predetermined = *(var_s_int+temperature_pred_eeprom);
  write_Card_2K_I2C(temperature_pred_24LC16B, (char)(temperature_predetermined>>8));
  write_Card_2K_I2C(temperature_pred_24LC16B+1, (char)(temperature_predetermined&0x00FF));  
  
  D_min_max = D_max;
  D_min_max<<=8;
  D_min_max = D_min_max&0xFF00;
  D_min_max = D_min_max + D_min;
  
  D_min_max = *(var_s_int+D_min_max_eeprom);
  write_Card_2K_I2C(D_min_max_24LC16B, (char)(D_min_max>>8));
  write_Card_2K_I2C(D_min_max_24LC16B+1, (char)(D_min_max&0x00FF));
  __enable_interrupt();
}



void read_eeprom_24LC16B(void)
{
  unsigned char i,y;
  //unsigned char *l_vchar;
  __disable_interrupt();
  Serial_number = Read_Card_2K_I2C(Serial_number_24LC16B);
  Serial_number = (Serial_number<<8)|(Read_Card_2K_I2C(Serial_number_24LC16B+1));
  *(var_s_int+Serial_number_eeprom)=Serial_number;
  Step_Motor_Koeff = Read_Card_2K_I2C(Step_Motor_Koeff_24LC16B);
  Step_Motor_Koeff = (Step_Motor_Koeff<<8)|(Read_Card_2K_I2C(Step_Motor_Koeff_24LC16B+1));
  *(var_s_int+Step_Motor_Koeff_eeprom)=Step_Motor_Koeff;
  Kp_Gain_2 = Read_Card_2K_I2C(Kp_Gain_2_24LC16B);
  Kp_Gain_2 = (Kp_Gain_2<<8)|(Read_Card_2K_I2C(Kp_Gain_2_24LC16B+1));
  *(var_s_int+Kp_Gain_2_eeprom)=Kp_Gain_2;
  idling_motor_dizel = Read_Card_2K_I2C(idling_motor_dizel_24LC16B);
  idling_motor_dizel = (idling_motor_dizel<<8)|(Read_Card_2K_I2C(idling_motor_dizel_24LC16B+1));
  *(var_uns_int+idling_motor_dizel_eeprom)=idling_motor_dizel;
  Turbo_Koeff = Read_Card_2K_I2C(Turbo_Koeff_24LC16B);
  Turbo_Koeff = (Turbo_Koeff<<8)|(Read_Card_2K_I2C(Turbo_Koeff_24LC16B+1));
  *(var_s_int+Turbo_Koeff_eeprom)=Turbo_Koeff;
  Turbo_offset = Read_Card_2K_I2C(Turbo_offset_24LC16B);
  Turbo_offset = (Turbo_offset<<8)|(Read_Card_2K_I2C(Turbo_offset_24LC16B+1));
  *(var_s_int+Turbo_offset_eeprom)=Turbo_offset;
  offset_motor_tax = Read_Card_2K_I2C(offset_motor_tax_24LC16B);
  offset_motor_tax = (offset_motor_tax<<8)|(Read_Card_2K_I2C(offset_motor_tax_24LC16B+1));
  *(var_s_int+offset_motor_tax_eeprom)=offset_motor_tax;
  
  High_Level_PID = Read_Card_2K_I2C(High_Level_PID_24LC16B);
  *(var_uns_char+High_Level_PID_eeprom)=High_Level_PID;
  High_Level_PID=High_Level_PID*div_milisek_switch;
  Low_Level_PID = Read_Card_2K_I2C(Low_Level_PID_24LC16B);
  *(var_uns_char+Low_Level_PID_eeprom)=Low_Level_PID;
  Low_Level_PID=Low_Level_PID*div_milisek_switch;
  Step_Motor_OffSet = Read_Card_2K_I2C(Step_Motor_OffSet_24LC16B);
  *(var_uns_char+Step_Motor_OffSet_eeprom)=Step_Motor_OffSet;
  Kol_zubov_kolenvala = Read_Card_2K_I2C(Kol_zubov_kolenvala_24LC16B);
  *(var_uns_char+Kol_zubov_kolenvala_eeprom)=Kol_zubov_kolenvala;
  
  //чтение с памяти таблицы "КОРРЕКЦИЯ УГЛА ВПРЫСКА" [16][16]
  for(i=0;i<16;i++)
  {
      for(y=0;y<16;y++)
      {
          faza_array_tooth[i][y] = Read_Card_2K_I2C(faza_array_tooth_24LC16B+i*16+y);
          *(var_uns_char+faza_array_tooth_eeprom+i*16+y)=faza_array_tooth[i][y];
      }
  }
  
  for(i=0;i<16;i++)
  {
    Step_motor_array_cicle[i] = Read_Card_2K_I2C(Step_motor_array_cicle_24LC16B+i);
    *(var_uns_char+Step_motor_array_cicle_eeprom+i)=Step_motor_array_cicle[i];
  }
  for(i=0;i<9;i++)
  {
        for(y=0;y<5;y++)
        {
          Axelerometr_tax[i][y] = Read_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+y)*2);
          Axelerometr_tax[i][y] = (Axelerometr_tax[i][y]<<8)|(Read_Card_2K_I2C(Axelerometr_tax_24LC16B+(i*5+y)*2+1));
          *(var_s_int+Axelerometr_tax_eeprom+i*5+y)=Axelerometr_tax[i][y];
        }
  }
  for(i=0;i<6;i++)
  {
        for(y=0;y<16;y++)
        {
          array_high_level_PID[i][y] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y);
          *(var_uns_char+array_high_level_PID_eeprom+i*16+y)=array_high_level_PID[i][y];
          array_high_level_PID[i][y]=array_high_level_PID[i][y]*div_milisek_switch;
        }
    }
  Low_Level_Idling = Read_Card_2K_I2C(Low_Level_Idling_24LC16B);
  *(var_uns_char+Low_Level_Idling_eeprom)=Low_Level_Idling;
  Low_Level_Idling=Low_Level_Idling*div_milisek_switch;
  
  Kp_Gain_PID_t_1 = Read_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B);
  Kp_Gain_PID_t_1 = (Kp_Gain_PID_t_1<<8)|(Read_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B+1));
  *(var_s_int+Kp_Gain_PID_t_1_eeprom)=Kp_Gain_PID_t_1;
  Kp_Gain_PID_t_2 = Read_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B);
  Kp_Gain_PID_t_2 = (Kp_Gain_PID_t_2<<8)|(Read_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B+1));
  *(var_s_int+Kp_Gain_PID_t_2_eeprom)=Kp_Gain_PID_t_2;
  temperature_predetermined = Read_Card_2K_I2C(temperature_pred_24LC16B);
  temperature_predetermined = (temperature_predetermined<<8)|(Read_Card_2K_I2C(temperature_pred_24LC16B+1));
  *(var_s_int+temperature_pred_eeprom)=temperature_predetermined;
  D_min_max = Read_Card_2K_I2C(D_min_max_24LC16B);
  D_min_max = (D_min_max<<8)|(Read_Card_2K_I2C(D_min_max_24LC16B+1));
  *(var_s_int+D_min_max_eeprom)=D_min_max;
  
  D_min = D_min_max;
  D_min = D_min&0x00FF;
  D_min_max>>=8;
  D_min_max = D_min_max&0x00FF;
  D_max = D_min_max;
  D_max = D_max&0x00FF;
  __enable_interrupt();
}



void write_test_data()
{
    __disable_interrupt();
    Serial_number=4864;
    write_Card_2K_I2C(Serial_number_24LC16B, (char)(Serial_number>>8));
    write_Card_2K_I2C(Serial_number_24LC16B+1, (char)(Serial_number&0x00FF));    
    ////////////////////
    Step_Motor_Koeff=4;
    write_Card_2K_I2C(Step_Motor_Koeff_24LC16B, (char)(Step_Motor_Koeff>>8));
    write_Card_2K_I2C(Step_Motor_Koeff_24LC16B+1, (char)(Step_Motor_Koeff&0x00FF));
    ////////////////////
    Kp_Gain_2=12;
    write_Card_2K_I2C(Kp_Gain_2_24LC16B, (char)(Kp_Gain_2>>8));
    write_Card_2K_I2C(Kp_Gain_2_24LC16B+1, (char)(Kp_Gain_2&0x00FF));
    ////////////////////
    Kp_Gain_PID_t_1=1;
    write_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B, (char)(Kp_Gain_PID_t_1>>8));
    write_Card_2K_I2C(Kp_Gain_PID_t_1_24LC16B+1, (char)(Kp_Gain_PID_t_1&0x00FF));
    ////////////////////
    Kp_Gain_PID_t_2=64;
    write_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B, (char)(Kp_Gain_PID_t_2>>8));
    write_Card_2K_I2C(Kp_Gain_PID_t_2_24LC16B+1, (char)(Kp_Gain_PID_t_2&0x00FF));
    ////////////////////
    idling_motor_dizel=670;
    write_Card_2K_I2C(idling_motor_dizel_24LC16B, (char)(idling_motor_dizel>>8));
    write_Card_2K_I2C(idling_motor_dizel_24LC16B+1, (char)(idling_motor_dizel&0x00FF));
    ///////////////////
    Step_Motor_OffSet=64;
    write_Card_2K_I2C(Step_Motor_OffSet_24LC16B, Step_Motor_OffSet);
    ///////////////////
    Low_Level_PID = 0;
    write_Card_2K_I2C(Low_Level_PID_24LC16B, (char)Low_Level_PID);
    Low_Level_Idling = 0;
    write_Card_2K_I2C(Low_Level_Idling_24LC16B, (char)Low_Level_Idling);
    ///////////////////
    Turbo_Koeff=72;
    write_Card_2K_I2C(Turbo_Koeff_24LC16B, (char)(Turbo_Koeff>>8));
    write_Card_2K_I2C(Turbo_Koeff_24LC16B+1, (char)(Turbo_Koeff&0x00FF));

    Turbo_offset=360;
    write_Card_2K_I2C(Turbo_offset_24LC16B, (char)(Turbo_offset>>8));
    write_Card_2K_I2C(Turbo_offset_24LC16B+1, (char)(Turbo_offset&0x00FF));
    //////////////////
    offset_motor_tax = 64;
    write_Card_2K_I2C(offset_motor_tax_24LC16B, (char)(offset_motor_tax>>8));
    write_Card_2K_I2C(offset_motor_tax_24LC16B+1, (char)(offset_motor_tax&0x00FF));
    /////////////////
    High_Level_PID = 24;
    write_Card_2K_I2C(High_Level_PID_24LC16B, (char)High_Level_PID);
    /////////////////
    temperature_predetermined=700;
    write_Card_2K_I2C(temperature_pred_24LC16B, (char)(temperature_predetermined>>8));
    write_Card_2K_I2C(temperature_pred_24LC16B+1, (char)(temperature_predetermined&0x00FF));
    
    D_min_max=0;
    D_min = 6;
    D_max = 25;
    D_min_max = D_max;
    D_min_max<<=8;
    D_min_max = D_min_max&0xFF00;
    D_min_max = D_min_max + D_min;
    
    write_Card_2K_I2C(D_min_max_24LC16B, (char)(D_min_max>>8));
    write_Card_2K_I2C(D_min_max_24LC16B+1, (char)(D_min_max&0x00FF));
}



void init_PRINTF_var(void)
{
     unsigned char i,y;
     
     
     switch(number_paket_tx_now)
     {
         case(0):
         {
             //передача серийного номера Serial_number
             printf_const_UART(OTV_1);//var K0
             Printf_Variable_UART(Serial_number);
             Send_UART_char(' ');
         }
         break;
         case(1):
         {
             //передача коэффициента Step_Motor_Koeff
             printf_const_UART(OTV_2);//var K1
             Printf_Variable_UART(Step_Motor_Koeff);
             Send_UART_char(' ');
         }
         break;
         case(2):
         {
             //передача коэффициента Kp_Gain_2
             printf_const_UART(OTV_3);//var K2
             Printf_Variable_UART(Kp_Gain_2);
             Send_UART_char(' ');
         }
         break;
         case(3):
         {
             //передача коэффициента Kp_Gain_PID_t_1
             printf_const_UART(OTV_4);//var K3
             Printf_Variable_UART(Kp_Gain_PID_t_1);
             Send_UART_char(' ');//передача пробела 
         }
         break;
         case(4):
         {
             //передача коэффициента Kp_Gain_PID_t_2
             printf_const_UART(OTV_5);//var K4
             Printf_Variable_UART(Kp_Gain_PID_t_2);
             Send_UART_char(' ');//передача пробела 
         }
         break;
         case(5):
         {
             //передача коэффициента temperature_predetermined
             printf_const_UART(OTV_6);//var Tc
             Printf_Variable_UART(temperature_predetermined);
             Send_UART_char(' ');
         }
         break;
         case(6):
         {
             //передача Dmin
             printf_const_UART(OTV_7l);
             Printf_Variable_UART(D_min);//var Dl
             Send_UART_char(' ');
         }
         break;
         case(7):
         {
            //передача Dmax
            printf_const_UART(OTV_7h);
            Printf_Variable_UART(D_max);//var Dh
            Send_UART_char(' ');
         }
         break;
         case(8):
         {
            //передача коэффициента idling_motor_dizel
            printf_const_UART(OTV_8);
            Printf_Variable_UART(idling_motor_dizel);//var Id
            Send_UART_char(' ');
         }
         break;
         case(9):
         {
            //передача коэффициента Step_Motor_OffSet
            printf_const_UART(OTV_9);
            Printf_Variable_UART(Step_Motor_OffSet);//var Mo
            Send_UART_char(' ');
         }
         break;
         case(10):
         {
            //передача коэффициента Turbo_offset
            printf_const_UART(OTV_10);
            Printf_Variable_UART(Turbo_offset);//var To
            Send_UART_char(' ');
         }
         break;         
         case(11):
         {
            //передача коэффициента Turbo_Koeff 
            printf_const_UART(OTV_11);
            Printf_Variable_UART(Turbo_Koeff);//var Tk
            Send_UART_char(' ');
         }
         break;        
         case(12):
         {
            //передача коэффициента offset_motor_tax  
            printf_const_UART(OTV_12);
            Printf_Variable_UART(offset_motor_tax);//var Tm
            Send_UART_char(' ');
         }
         break;        
         case(13):
         {
            //передача коэффициента Kol_zubov_kolenvala  
            printf_const_UART(OTV_13);
            Printf_Variable_UART(Kol_zubov_kolenvala);//var Mt
            Send_UART_char(' ');
         }
         break;
         case(14):
         {
            //передача коэффициента High_Level_PID  
            printf_const_UART(OTV_14);
            Printf_Variable_UART((High_Level_PID/div_milisek_switch));//var Pl
            Send_UART_char(' ');
         }
         break;
         case(15):
         {
            //передача коэффициента Low_Level_Idling  
            printf_const_UART(OTV_15);
            Printf_Variable_UART((Low_Level_Idling/div_milisek_switch));//var Pi
            Send_UART_char(' ');
         }
         break;
         case(16):
         {
            //передача
            printf_const_UART(tb1_01);
            Printf_Variable_UART((array_high_level_PID[0][1]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(17):
         {
            //передача  
            printf_const_UART(tb1_02);
            Printf_Variable_UART((array_high_level_PID[0][2]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(18):
         {
            //передача  
            printf_const_UART(tb1_03);
            Printf_Variable_UART((array_high_level_PID[0][3]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(19):
         {
            //передача  
            printf_const_UART(tb1_04);
            Printf_Variable_UART((array_high_level_PID[0][4]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(20):
         {
            //передача  
            printf_const_UART(tb1_05);
            Printf_Variable_UART((array_high_level_PID[0][5]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(21):
         {
            //передача  
            printf_const_UART(tb1_06);
            Printf_Variable_UART((array_high_level_PID[0][6]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(22):
         {
            //передача  
            printf_const_UART(tb1_07);
            Printf_Variable_UART((array_high_level_PID[0][7]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(23):
         {
            //передача  
            printf_const_UART(tb1_08);
            Printf_Variable_UART((array_high_level_PID[0][8]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(24):
         {
            //передача  
            printf_const_UART(tb1_09);
            Printf_Variable_UART((array_high_level_PID[0][9]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(25):
         {
            //передача  
            printf_const_UART(tb1_10);
            Printf_Variable_UART((array_high_level_PID[0][10]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(26):
         {
            //передача  
            printf_const_UART(tb1_11);
            Printf_Variable_UART((array_high_level_PID[0][11]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(27):
         {
            //передача  
            printf_const_UART(tb1_12);
            Printf_Variable_UART((array_high_level_PID[0][12]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(28):
         {
            //передача  
            printf_const_UART(tb1_13);
            Printf_Variable_UART((array_high_level_PID[0][13]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(29):
         {
            //передача  
            printf_const_UART(tb1_14);
            Printf_Variable_UART((array_high_level_PID[0][14]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(30):
         {
            //передача  
            printf_const_UART(tb1_15);
            Printf_Variable_UART((array_high_level_PID[0][15]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------2
         case(31):
         {
            //передача
            printf_const_UART(tb2_01);
            Printf_Variable_UART((array_high_level_PID[1][1]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(32):
         {
            //передача  
            printf_const_UART(tb2_02);
            Printf_Variable_UART((array_high_level_PID[1][2]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(33):
         {
            //передача  
            printf_const_UART(tb2_03);
            Printf_Variable_UART((array_high_level_PID[1][3]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(34):
         {
            //передача  
            printf_const_UART(tb2_04);
            Printf_Variable_UART((array_high_level_PID[1][4]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(35):
         {
            //передача  
            printf_const_UART(tb2_05);
            Printf_Variable_UART((array_high_level_PID[1][5]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(36):
         {
            //передача  
            printf_const_UART(tb2_06);
            Printf_Variable_UART((array_high_level_PID[1][6]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(37):
         {
            //передача  
            printf_const_UART(tb2_07);
            Printf_Variable_UART((array_high_level_PID[1][7]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(38):
         {
            //передача  
            printf_const_UART(tb2_08);
            Printf_Variable_UART((array_high_level_PID[1][8]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(39):
         {
            //передача  
            printf_const_UART(tb2_09);
            Printf_Variable_UART((array_high_level_PID[1][9]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(40):
         {
            //передача  
            printf_const_UART(tb2_10);
            Printf_Variable_UART((array_high_level_PID[1][10]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(41):
         {
            //передача  
            printf_const_UART(tb2_11);
            Printf_Variable_UART((array_high_level_PID[1][11]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(42):
         {
            //передача  
            printf_const_UART(tb2_12);
            Printf_Variable_UART((array_high_level_PID[1][12]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(43):
         {
            //передача  
            printf_const_UART(tb2_13);
            Printf_Variable_UART((array_high_level_PID[1][13]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(44):
         {
            //передача  
            printf_const_UART(tb2_14);
            Printf_Variable_UART((array_high_level_PID[1][14]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(45):
         {
            //передача  
            printf_const_UART(tb2_15);
            Printf_Variable_UART((array_high_level_PID[1][15]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------3
         case(46):
         {
            //передача
            printf_const_UART(tb3_01);
            Printf_Variable_UART((array_high_level_PID[2][1]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(47):
         {
            //передача  
            printf_const_UART(tb3_02);
            Printf_Variable_UART((array_high_level_PID[2][2]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(48):
         {
            //передача  
            printf_const_UART(tb3_03);
            Printf_Variable_UART((array_high_level_PID[2][3]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(49):
         {
            //передача  
            printf_const_UART(tb3_04);
            Printf_Variable_UART((array_high_level_PID[2][4]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(50):
         {
            //передача  
            printf_const_UART(tb3_05);
            Printf_Variable_UART((array_high_level_PID[2][5]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(51):
         {
            //передача  
            printf_const_UART(tb3_06);
            Printf_Variable_UART((array_high_level_PID[2][6]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(52):
         {
            //передача  
            printf_const_UART(tb3_07);
            Printf_Variable_UART((array_high_level_PID[2][7]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(53):
         {
            //передача  
            printf_const_UART(tb3_08);
            Printf_Variable_UART((array_high_level_PID[2][8]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(54):
         {
            //передача  
            printf_const_UART(tb3_09);
            Printf_Variable_UART((array_high_level_PID[2][9]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(55):
         {
            //передача  
            printf_const_UART(tb3_10);
            Printf_Variable_UART((array_high_level_PID[2][10]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(56):
         {
            //передача  
            printf_const_UART(tb3_11);
            Printf_Variable_UART((array_high_level_PID[2][11]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(57):
         {
            //передача  
            printf_const_UART(tb3_12);
            Printf_Variable_UART((array_high_level_PID[2][12]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(58):
         {
            //передача  
            printf_const_UART(tb3_13);
            Printf_Variable_UART((array_high_level_PID[2][13]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(59):
         {
            //передача  
            printf_const_UART(tb3_14);
            Printf_Variable_UART((array_high_level_PID[2][14]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(60):
         {
            //передача  
            printf_const_UART(tb3_15);
            Printf_Variable_UART((array_high_level_PID[2][15]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------4
         case(61):
         {
            //передача
            printf_const_UART(tb4_01);
            Printf_Variable_UART((array_high_level_PID[3][1]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(62):
         {
            //передача  
            printf_const_UART(tb4_02);
            Printf_Variable_UART((array_high_level_PID[3][2]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(63):
         {
            //передача  
            printf_const_UART(tb4_03);
            Printf_Variable_UART((array_high_level_PID[3][3]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(64):
         {
            //передача  
            printf_const_UART(tb4_04);
            Printf_Variable_UART((array_high_level_PID[3][4]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(65):
         {
            //передача  
            printf_const_UART(tb4_05);
            Printf_Variable_UART((array_high_level_PID[3][5]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(66):
         {
            //передача  
            printf_const_UART(tb4_06);
            Printf_Variable_UART((array_high_level_PID[3][6]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(67):
         {
            //передача  
            printf_const_UART(tb4_07);
            Printf_Variable_UART((array_high_level_PID[3][7]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(68):
         {
            //передача  
            printf_const_UART(tb4_08);
            Printf_Variable_UART((array_high_level_PID[3][8]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(69):
         {
            //передача  
            printf_const_UART(tb4_09);
            Printf_Variable_UART((array_high_level_PID[3][9]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(70):
         {
            //передача  
            printf_const_UART(tb4_10);
            Printf_Variable_UART((array_high_level_PID[3][10]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(71):
         {
            //передача  
            printf_const_UART(tb4_11);
            Printf_Variable_UART((array_high_level_PID[3][11]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(72):
         {
            //передача  
            printf_const_UART(tb4_12);
            Printf_Variable_UART((array_high_level_PID[3][12]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(73):
         {
            //передача  
            printf_const_UART(tb4_13);
            Printf_Variable_UART((array_high_level_PID[3][13]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(74):
         {
            //передача  
            printf_const_UART(tb4_14);
            Printf_Variable_UART((array_high_level_PID[3][14]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(75):
         {
            //передача  
            printf_const_UART(tb4_15);
            Printf_Variable_UART((array_high_level_PID[3][15]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------5
         case(76):
         {
            //передача
            printf_const_UART(tb5_01);
            Printf_Variable_UART((array_high_level_PID[4][1]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(77):
         {
            //передача  
            printf_const_UART(tb5_02);
            Printf_Variable_UART((array_high_level_PID[4][2]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(78):
         {
            //передача  
            printf_const_UART(tb5_03);
            Printf_Variable_UART((array_high_level_PID[4][3]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(79):
         {
            //передача  
            printf_const_UART(tb5_04);
            Printf_Variable_UART((array_high_level_PID[4][4]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(80):
         {
            //передача  
            printf_const_UART(tb5_05);
            Printf_Variable_UART((array_high_level_PID[4][5]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(81):
         {
            //передача  
            printf_const_UART(tb5_06);
            Printf_Variable_UART((array_high_level_PID[4][6]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(82):
         {
            //передача  
            printf_const_UART(tb5_07);
            Printf_Variable_UART((array_high_level_PID[4][7]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(83):
         {
            //передача  
            printf_const_UART(tb5_08);
            Printf_Variable_UART((array_high_level_PID[4][8]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(84):
         {
            //передача  
            printf_const_UART(tb5_09);
            Printf_Variable_UART((array_high_level_PID[4][9]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(85):
         {
            //передача  
            printf_const_UART(tb5_10);
            Printf_Variable_UART((array_high_level_PID[4][10]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(86):
         {
            //передача  
            printf_const_UART(tb5_11);
            Printf_Variable_UART((array_high_level_PID[4][11]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(87):
         {
            //передача  
            printf_const_UART(tb5_12);
            Printf_Variable_UART((array_high_level_PID[4][12]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(88):
         {
            //передача  
            printf_const_UART(tb5_13);
            Printf_Variable_UART((array_high_level_PID[4][13]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(89):
         {
            //передача  
            printf_const_UART(tb5_14);
            Printf_Variable_UART((array_high_level_PID[4][14]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(90):
         {
            //передача  
            printf_const_UART(tb5_15);
            Printf_Variable_UART((array_high_level_PID[4][15]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------6
         case(91):
         {
            //передача
            printf_const_UART(tb6_01);
            Printf_Variable_UART((array_high_level_PID[5][1]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(92):
         {
            //передача  
            printf_const_UART(tb6_02);
            Printf_Variable_UART((array_high_level_PID[5][2]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(93):
         {
            //передача  
            printf_const_UART(tb6_03);
            Printf_Variable_UART((array_high_level_PID[5][3]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(94):
         {
            //передача  
            printf_const_UART(tb6_04);
            Printf_Variable_UART((array_high_level_PID[5][4]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(95):
         {
            //передача  
            printf_const_UART(tb6_05);
            Printf_Variable_UART((array_high_level_PID[5][5]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(96):
         {
            //передача  
            printf_const_UART(tb6_06);
            Printf_Variable_UART((array_high_level_PID[5][6]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(97):
         {
            //передача  
            printf_const_UART(tb6_07);
            Printf_Variable_UART((array_high_level_PID[5][7]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(98):
         {
            //передача  
            printf_const_UART(tb6_08);
            Printf_Variable_UART((array_high_level_PID[5][8]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(99):
         {
            //передача  
            printf_const_UART(tb6_09);
            Printf_Variable_UART((array_high_level_PID[5][9]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(100):
         {
            //передача  
            printf_const_UART(tb6_10);
            Printf_Variable_UART((array_high_level_PID[5][10]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(101):
         {
            //передача  
            printf_const_UART(tb6_11);
            Printf_Variable_UART((array_high_level_PID[5][11]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(102):
         {
            //передача  
            printf_const_UART(tb6_12);
            Printf_Variable_UART((array_high_level_PID[5][12]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(103):
         {
            //передача  
            printf_const_UART(tb6_13);
            Printf_Variable_UART((array_high_level_PID[5][13]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(104):
         {
            //передача  
            printf_const_UART(tb6_14);
            Printf_Variable_UART((array_high_level_PID[5][14]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         case(105):
         {
            //передача  
            printf_const_UART(tb6_15);
            Printf_Variable_UART((array_high_level_PID[5][15]/div_milisek_switch));
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------7
         case(106):
         {
            //передача
            printf_const_UART(tb7_01);
            Printf_Variable_UART(faza_array_tooth[0][0]);
            Send_UART_char(' ');
         }
         break;
         case(107):
         {
            //передача  
            printf_const_UART(tb7_02);
            Printf_Variable_UART(faza_array_tooth[0][1]);
            Send_UART_char(' ');
         }
         break;
         case(108):
         {
            //передача  
            printf_const_UART(tb7_03);
            Printf_Variable_UART(faza_array_tooth[0][2]);
            Send_UART_char(' ');
         }
         break;
         case(109):
         {
            //передача  
            printf_const_UART(tb7_04);
            Printf_Variable_UART(faza_array_tooth[0][3]);
            Send_UART_char(' ');
         }
         break;
         case(110):
         {
            //передача  
            printf_const_UART(tb7_05);
            Printf_Variable_UART(faza_array_tooth[0][4]);
            Send_UART_char(' ');
         }
         break;
         case(111):
         {
            //передача  
            printf_const_UART(tb7_06);
            Printf_Variable_UART(faza_array_tooth[0][5]);
            Send_UART_char(' ');
         }
         break;
         case(112):
         {
            //передача  
            printf_const_UART(tb7_07);
            Printf_Variable_UART(faza_array_tooth[0][6]);
            Send_UART_char(' ');
         }
         break;
         case(113):
         {
            //передача  
            printf_const_UART(tb7_08);
            Printf_Variable_UART(faza_array_tooth[0][7]);
            Send_UART_char(' ');
         }
         break;
         case(114):
         {
            //передача  
            printf_const_UART(tb7_09);
            Printf_Variable_UART(faza_array_tooth[0][8]);
            Send_UART_char(' ');
         }
         break;
         case(115):
         {
            //передача  
            printf_const_UART(tb7_10);
            Printf_Variable_UART(faza_array_tooth[0][9]);
            Send_UART_char(' ');
         }
         break;
         case(116):
         {
            //передача  
            printf_const_UART(tb7_11);
            Printf_Variable_UART(faza_array_tooth[0][10]);
            Send_UART_char(' ');
         }
         break;
         case(117):
         {
            //передача  
            printf_const_UART(tb7_12);
            Printf_Variable_UART(faza_array_tooth[0][11]);
            Send_UART_char(' ');
         }
         break;
         case(118):
         {
            //передача  
            printf_const_UART(tb7_13);
            Printf_Variable_UART(faza_array_tooth[0][12]);
            Send_UART_char(' ');
         }
         break;
         case(119):
         {
            //передача  
            printf_const_UART(tb7_14);
            Printf_Variable_UART(faza_array_tooth[0][13]);
            Send_UART_char(' ');
         }
         break;
         case(120):
         {
            //передача  
            printf_const_UART(tb7_15);
            Printf_Variable_UART(faza_array_tooth[0][14]);
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------8
         case(121):
         {
            //передача
            printf_const_UART(tb8_01);
            Printf_Variable_UART(faza_array_tooth[1][0]);
            Send_UART_char(' ');
         }
         break;
         case(122):
         {
            //передача  
            printf_const_UART(tb8_02);
            Printf_Variable_UART(faza_array_tooth[1][1]);
            Send_UART_char(' ');
         }
         break;
         case(123):
         {
            //передача  
            printf_const_UART(tb8_03);
            Printf_Variable_UART(faza_array_tooth[1][2]);
            Send_UART_char(' ');
         }
         break;
         case(124):
         {
            //передача  
            printf_const_UART(tb8_04);
            Printf_Variable_UART(faza_array_tooth[1][3]);
            Send_UART_char(' ');
         }
         break;
         case(125):
         {
            //передача  
            printf_const_UART(tb8_05);
            Printf_Variable_UART(faza_array_tooth[1][4]);
            Send_UART_char(' ');
         }
         break;
         case(126):
         {
            //передача  
            printf_const_UART(tb8_06);
            Printf_Variable_UART(faza_array_tooth[1][5]);
            Send_UART_char(' ');
         }
         break;
         case(127):
         {
            //передача  
            printf_const_UART(tb8_07);
            Printf_Variable_UART(faza_array_tooth[1][6]);
            Send_UART_char(' ');
         }
         break;
         case(128):
         {
            //передача  
            printf_const_UART(tb8_08);
            Printf_Variable_UART(faza_array_tooth[1][7]);
            Send_UART_char(' ');
         }
         break;
         case(129):
         {
            //передача  
            printf_const_UART(tb8_09);
            Printf_Variable_UART(faza_array_tooth[1][8]);
            Send_UART_char(' ');
         }
         break;
         case(130):
         {
            //передача  
            printf_const_UART(tb8_10);
            Printf_Variable_UART(faza_array_tooth[1][9]);
            Send_UART_char(' ');
         }
         break;
         case(131):
         {
            //передача  
            printf_const_UART(tb8_11);
            Printf_Variable_UART(faza_array_tooth[1][10]);
            Send_UART_char(' ');
         }
         break;
         case(132):
         {
            //передача  
            printf_const_UART(tb8_12);
            Printf_Variable_UART(faza_array_tooth[1][11]);
            Send_UART_char(' ');
         }
         break;
         case(133):
         {
            //передача  
            printf_const_UART(tb8_13);
            Printf_Variable_UART(faza_array_tooth[1][12]);
            Send_UART_char(' ');
         }
         break;
         case(134):
         {
            //передача  
            printf_const_UART(tb8_14);
            Printf_Variable_UART(faza_array_tooth[1][13]);
            Send_UART_char(' ');
         }
         break;
         case(135):
         {
            //передача  
            printf_const_UART(tb8_15);
            Printf_Variable_UART(faza_array_tooth[1][14]);
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------9
         case(136):
         {
            //передача
            printf_const_UART(tb9_01);
            Printf_Variable_UART(faza_array_tooth[2][0]);
            Send_UART_char(' ');
         }
         break;
         case(137):
         {
            //передача  
            printf_const_UART(tb9_02);
            Printf_Variable_UART(faza_array_tooth[2][1]);
            Send_UART_char(' ');
         }
         break;
         case(138):
         {
            //передача  
            printf_const_UART(tb9_03);
            Printf_Variable_UART(faza_array_tooth[2][2]);
            Send_UART_char(' ');
         }
         break;
         case(139):
         {
            //передача  
            printf_const_UART(tb9_04);
            Printf_Variable_UART(faza_array_tooth[2][3]);
            Send_UART_char(' ');
         }
         break;
         case(140):
         {
            //передача  
            printf_const_UART(tb9_05);
            Printf_Variable_UART(faza_array_tooth[2][4]);
            Send_UART_char(' ');
         }
         break;
         case(141):
         {
            //передача  
            printf_const_UART(tb9_06);
            Printf_Variable_UART(faza_array_tooth[2][5]);
            Send_UART_char(' ');
         }
         break;
         case(142):
         {
            //передача  
            printf_const_UART(tb9_07);
            Printf_Variable_UART(faza_array_tooth[2][6]);
            Send_UART_char(' ');
         }
         break;
         case(143):
         {
            //передача  
            printf_const_UART(tb9_08);
            Printf_Variable_UART(faza_array_tooth[2][7]);
            Send_UART_char(' ');
         }
         break;
         case(144):
         {
            //передача  
            printf_const_UART(tb9_09);
            Printf_Variable_UART(faza_array_tooth[2][8]);
            Send_UART_char(' ');
         }
         break;
         case(145):
         {
            //передача  
            printf_const_UART(tb9_10);
            Printf_Variable_UART(faza_array_tooth[2][9]);
            Send_UART_char(' ');
         }
         break;
         case(146):
         {
            //передача  
            printf_const_UART(tb9_11);
            Printf_Variable_UART(faza_array_tooth[2][10]);
            Send_UART_char(' ');
         }
         break;
         case(147):
         {
            //передача  
            printf_const_UART(tb9_12);
            Printf_Variable_UART(faza_array_tooth[2][11]);
            Send_UART_char(' ');
         }
         break;
         case(148):
         {
            //передача  
            printf_const_UART(tb9_13);
            Printf_Variable_UART(faza_array_tooth[2][12]);
            Send_UART_char(' ');
         }
         break;
         case(149):
         {
            //передача  
            printf_const_UART(tb9_14);
            Printf_Variable_UART(faza_array_tooth[2][13]);
            Send_UART_char(' ');
         }
         break;
         case(150):
         {
            //передача  
            printf_const_UART(tb9_15);
            Printf_Variable_UART(faza_array_tooth[2][14]);
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------10
         case(151):
         {
            //передача
            printf_const_UART(tb10_01);
            Printf_Variable_UART(faza_array_tooth[3][0]);
            Send_UART_char(' ');
         }
         break;
         case(152):
         {
            //передача  
            printf_const_UART(tb10_02);
            Printf_Variable_UART(faza_array_tooth[3][1]);
            Send_UART_char(' ');
         }
         break;
         case(153):
         {
            //передача  
            printf_const_UART(tb10_03);
            Printf_Variable_UART(faza_array_tooth[3][2]);
            Send_UART_char(' ');
         }
         break;
         case(154):
         {
            //передача  
            printf_const_UART(tb10_04);
            Printf_Variable_UART(faza_array_tooth[3][3]);
            Send_UART_char(' ');
         }
         break;
         case(155):
         {
            //передача  
            printf_const_UART(tb10_05);
            Printf_Variable_UART(faza_array_tooth[3][4]);
            Send_UART_char(' ');
         }
         break;
         case(156):
         {
            //передача  
            printf_const_UART(tb10_06);
            Printf_Variable_UART(faza_array_tooth[3][5]);
            Send_UART_char(' ');
         }
         break;
         case(157):
         {
            //передача  
            printf_const_UART(tb10_07);
            Printf_Variable_UART(faza_array_tooth[3][6]);
            Send_UART_char(' ');
         }
         break;
         case(158):
         {
            //передача  
            printf_const_UART(tb10_08);
            Printf_Variable_UART(faza_array_tooth[3][7]);
            Send_UART_char(' ');
         }
         break;
         case(159):
         {
            //передача  
            printf_const_UART(tb10_09);
            Printf_Variable_UART(faza_array_tooth[3][8]);
            Send_UART_char(' ');
         }
         break;
         case(160):
         {
            //передача  
            printf_const_UART(tb10_10);
            Printf_Variable_UART(faza_array_tooth[3][9]);
            Send_UART_char(' ');
         }
         break;
         case(161):
         {
            //передача  
            printf_const_UART(tb10_11);
            Printf_Variable_UART(faza_array_tooth[3][10]);
            Send_UART_char(' ');
         }
         break;
         case(162):
         {
            //передача  
            printf_const_UART(tb10_12);
            Printf_Variable_UART(faza_array_tooth[3][11]);
            Send_UART_char(' ');
         }
         break;
         case(163):
         {
            //передача  
            printf_const_UART(tb10_13);
            Printf_Variable_UART(faza_array_tooth[3][12]);
            Send_UART_char(' ');
         }
         break;
         case(164):
         {
            //передача  
            printf_const_UART(tb10_14);
            Printf_Variable_UART(faza_array_tooth[3][13]);
            Send_UART_char(' ');
         }
         break;
         case(165):
         {
            //передача  
            printf_const_UART(tb10_15);
            Printf_Variable_UART(faza_array_tooth[3][14]);
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------10
         case(166):
         {
            //передача
            printf_const_UART(tb11_01);
            Printf_Variable_UART(faza_array_tooth[4][0]);
            Send_UART_char(' ');
         }
         break;
         case(167):
         {
            //передача  
            printf_const_UART(tb11_02);
            Printf_Variable_UART(faza_array_tooth[4][1]);
            Send_UART_char(' ');
         }
         break;
         case(168):
         {
            //передача  
            printf_const_UART(tb11_03);
            Printf_Variable_UART(faza_array_tooth[4][2]);
            Send_UART_char(' ');
         }
         break;
         case(169):
         {
            //передача  
            printf_const_UART(tb11_04);
            Printf_Variable_UART(faza_array_tooth[4][3]);
            Send_UART_char(' ');
         }
         break;
         case(170):
         {
            //передача  
            printf_const_UART(tb11_05);
            Printf_Variable_UART(faza_array_tooth[4][4]);
            Send_UART_char(' ');
         }
         break;
         case(171):
         {
            //передача  
            printf_const_UART(tb11_06);
            Printf_Variable_UART(faza_array_tooth[4][5]);
            Send_UART_char(' ');
         }
         break;
         case(172):
         {
            //передача  
            printf_const_UART(tb11_07);
            Printf_Variable_UART(faza_array_tooth[4][6]);
            Send_UART_char(' ');
         }
         break;
         case(173):
         {
            //передача  
            printf_const_UART(tb11_08);
            Printf_Variable_UART(faza_array_tooth[4][7]);
            Send_UART_char(' ');
         }
         break;
         case(174):
         {
            //передача  
            printf_const_UART(tb11_09);
            Printf_Variable_UART(faza_array_tooth[4][8]);
            Send_UART_char(' ');
         }
         break;
         case(175):
         {
            //передача  
            printf_const_UART(tb11_10);
            Printf_Variable_UART(faza_array_tooth[4][9]);
            Send_UART_char(' ');
         }
         break;
         case(176):
         {
            //передача  
            printf_const_UART(tb11_11);
            Printf_Variable_UART(faza_array_tooth[4][10]);
            Send_UART_char(' ');
         }
         break;
         case(177):
         {
            //передача  
            printf_const_UART(tb11_12);
            Printf_Variable_UART(faza_array_tooth[4][11]);
            Send_UART_char(' ');
         }
         break;
         case(178):
         {
            //передача  
            printf_const_UART(tb11_13);
            Printf_Variable_UART(faza_array_tooth[4][12]);
            Send_UART_char(' ');
         }
         break;
         case(179):
         {
            //передача  
            printf_const_UART(tb11_14);
            Printf_Variable_UART(faza_array_tooth[4][13]);
            Send_UART_char(' ');
         }
         break;
         case(180):
         {
            //передача  
            printf_const_UART(tb11_15);
            Printf_Variable_UART(faza_array_tooth[4][14]);
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------10
         case(181):
         {
            //передача
            printf_const_UART(tb12_01);
            Printf_Variable_UART(faza_array_tooth[5][0]);
            Send_UART_char(' ');
         }
         break;
         case(182):
         {
            //передача  
            printf_const_UART(tb12_02);
            Printf_Variable_UART(faza_array_tooth[5][1]);
            Send_UART_char(' ');
         }
         break;
         case(183):
         {
            //передача  
            printf_const_UART(tb12_03);
            Printf_Variable_UART(faza_array_tooth[5][2]);
            Send_UART_char(' ');
         }
         break;
         case(184):
         {
            //передача  
            printf_const_UART(tb12_04);
            Printf_Variable_UART(faza_array_tooth[5][3]);
            Send_UART_char(' ');
         }
         break;
         case(185):
         {
            //передача  
            printf_const_UART(tb12_05);
            Printf_Variable_UART(faza_array_tooth[5][4]);
            Send_UART_char(' ');
         }
         break;
         case(186):
         {
            //передача  
            printf_const_UART(tb12_06);
            Printf_Variable_UART(faza_array_tooth[5][5]);
            Send_UART_char(' ');
         }
         break;
         case(187):
         {
            //передача  
            printf_const_UART(tb12_07);
            Printf_Variable_UART(faza_array_tooth[5][6]);
            Send_UART_char(' ');
         }
         break;
         case(188):
         {
            //передача  
            printf_const_UART(tb12_08);
            Printf_Variable_UART(faza_array_tooth[5][7]);
            Send_UART_char(' ');
         }
         break;
         case(189):
         {
            //передача  
            printf_const_UART(tb12_09);
            Printf_Variable_UART(faza_array_tooth[5][8]);
            Send_UART_char(' ');
         }
         break;
         case(190):
         {
            //передача  
            printf_const_UART(tb12_10);
            Printf_Variable_UART(faza_array_tooth[5][9]);
            Send_UART_char(' ');
         }
         break;
         case(191):
         {
            //передача  
            printf_const_UART(tb12_11);
            Printf_Variable_UART(faza_array_tooth[5][10]);
            Send_UART_char(' ');
         }
         break;
         case(192):
         {
            //передача  
            printf_const_UART(tb12_12);
            Printf_Variable_UART(faza_array_tooth[5][11]);
            Send_UART_char(' ');
         }
         break;
         case(193):
         {
            //передача  
            printf_const_UART(tb12_13);
            Printf_Variable_UART(faza_array_tooth[5][12]);
            Send_UART_char(' ');
         }
         break;
         case(194):
         {
            //передача  
            printf_const_UART(tb12_14);
            Printf_Variable_UART(faza_array_tooth[5][13]);
            Send_UART_char(' ');
         }
         break;
         case(195):
         {
            //передача  
            printf_const_UART(tb12_15);
            Printf_Variable_UART(faza_array_tooth[5][14]);
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------11
         case(196):
         {
            //передача
            printf_const_UART(tb13_01);
            Printf_Variable_UART(Step_motor_array_cicle[0]);
            Send_UART_char(' ');
         }
         break;
         case(197):
         {
            //передача  
            printf_const_UART(tb13_02);
            Printf_Variable_UART(Step_motor_array_cicle[1]);
            Send_UART_char(' ');
         }
         break;
         case(198):
         {
            //передача  
            printf_const_UART(tb13_03);
            Printf_Variable_UART(Step_motor_array_cicle[2]);
            Send_UART_char(' ');
         }
         break;
         case(199):
         {
            //передача  
            printf_const_UART(tb13_04);
            Printf_Variable_UART(Step_motor_array_cicle[3]);
            Send_UART_char(' ');
         }
         break;
         case(200):
         {
            //передача  
            printf_const_UART(tb13_05);
            Printf_Variable_UART(Step_motor_array_cicle[4]);
            Send_UART_char(' ');
         }
         break;
         case(201):
         {
            //передача  
            printf_const_UART(tb13_06);
            Printf_Variable_UART(Step_motor_array_cicle[5]);
            Send_UART_char(' ');
         }
         break;
         case(202):
         {
            //передача  
            printf_const_UART(tb13_07);
            Printf_Variable_UART(Step_motor_array_cicle[6]);
            Send_UART_char(' ');
         }
         break;
         case(203):
         {
            //передача  
            printf_const_UART(tb13_08);
            Printf_Variable_UART(Step_motor_array_cicle[7]);
            Send_UART_char(' ');
         }
         break;
         case(204):
         {
            //передача  
            printf_const_UART(tb13_09);
            Printf_Variable_UART(Step_motor_array_cicle[8]);
            Send_UART_char(' ');
         }
         break;
         case(205):
         {
            //передача  
            printf_const_UART(tb13_10);
            Printf_Variable_UART(Step_motor_array_cicle[9]);
            Send_UART_char(' ');
         }
         break;
         case(206):
         {
            //передача  
            printf_const_UART(tb13_11);
            Printf_Variable_UART(Step_motor_array_cicle[10]);
            Send_UART_char(' ');
         }
         break;
         case(207):
         {
            //передача  
            printf_const_UART(tb13_12);
            Printf_Variable_UART(Step_motor_array_cicle[11]);
            Send_UART_char(' ');
         }
         break;
         case(208):
         {
            //передача  
            printf_const_UART(tb13_13);
            Printf_Variable_UART(Step_motor_array_cicle[12]);
            Send_UART_char(' ');
         }
         break;
         case(209):
         {
            //передача  
            printf_const_UART(tb13_14);
            Printf_Variable_UART(Step_motor_array_cicle[13]);
            Send_UART_char(' ');
         }
         break;
         case(210):
         {
            //передача  
            printf_const_UART(tb13_15);
            Printf_Variable_UART(Step_motor_array_cicle[14]);
            Send_UART_char(' ');
         }
         break;
         case(211):
         {
            //передача  
            printf_const_UART(tb13_16);
            Printf_Variable_UART(Step_motor_array_cicle[15]);
            Send_UART_char(' ');
         }
         break;
         //--------------------------------------------------------------------------------------------------12
         case(212):
         {
            //передача
            printf_const_UART(tb14_01);
            Printf_Variable_UART(Axelerometr_tax[0][0]);
            Send_UART_char(' ');
         }
         break;
         case(213):
         {
            //передача  
            printf_const_UART(tb14_02);
            Printf_Variable_UART(Axelerometr_tax[1][0]);
            Send_UART_char(' ');
         }
         break;
         case(214):
         {
            //передача  
            printf_const_UART(tb14_03);
            Printf_Variable_UART(Axelerometr_tax[2][0]);
            Send_UART_char(' ');
         }
         break;
         case(215):
         {
            //передача  
            printf_const_UART(tb14_04);
            Printf_Variable_UART(Axelerometr_tax[3][0]);
            Send_UART_char(' ');
         }
         break;
         case(216):
         {
            //передача  
            printf_const_UART(tb14_05);
            Printf_Variable_UART(Axelerometr_tax[4][0]);
            Send_UART_char(' ');
         }
         break;
         case(217):
         {
            //передача  
            printf_const_UART(tb14_06);
            Printf_Variable_UART(Axelerometr_tax[5][0]);
            Send_UART_char(' ');
         }
         break;
         case(218):
         {
            //передача  
            printf_const_UART(tb14_07);
            Printf_Variable_UART(Axelerometr_tax[6][0]);
            Send_UART_char(' ');
         }
         break;
         case(219):
         {
            //передача  
            printf_const_UART(tb14_08);
            Printf_Variable_UART(Axelerometr_tax[7][0]);
            Send_UART_char(' ');
         }
         break;
         case(220):
         {
            //передача  
            printf_const_UART(tb14_09);
            Printf_Variable_UART(Axelerometr_tax[0][1]);
            Send_UART_char(' ');
         }
         break;
         case(221):
         {
            //передача  
            printf_const_UART(tb14_10);
            Printf_Variable_UART(Axelerometr_tax[1][1]);
            Send_UART_char(' ');
         }
         break;
         case(222):
         {
            //передача  
            printf_const_UART(tb14_11);
            Printf_Variable_UART(Axelerometr_tax[2][1]);
            Send_UART_char(' ');
         }
         break;
         case(223):
         {
            //передача  
            printf_const_UART(tb14_12);
            Printf_Variable_UART(Axelerometr_tax[3][1]);
            Send_UART_char(' ');
         }
         break;
         case(224):
         {
            //передача  
            printf_const_UART(tb14_13);
            Printf_Variable_UART(Axelerometr_tax[4][1]);
            Send_UART_char(' ');
         }
         break;
         case(225):
         {
            //передача  
            printf_const_UART(tb14_14);
            Printf_Variable_UART(Axelerometr_tax[5][1]);
            Send_UART_char(' ');
         }
         break;
         case(226):
         {
            //передача  
            printf_const_UART(tb14_15);
            Printf_Variable_UART(Axelerometr_tax[6][1]);
            Send_UART_char(' ');
         }
         break;
         case(227):
         {
            //передача  
            printf_const_UART(tb14_16);
            Printf_Variable_UART(Axelerometr_tax[7][1]);
            Send_UART_char(' ');
         }
         break;
    } 
     
    
    /*
    //передача серийного номера Serial_number
    printf_const_UART(Start_hello_01);
    Printf_Variable_UART(Serial_number);
    Send_UART_char(' ');
    
    //передача коэффициента Step_Motor_Koeff
    printf_const_UART(Start_hello_02);
    Printf_Variable_UART(Step_Motor_Koeff);
    Send_UART_char(' ');
         
    //передача коэффициента Kp_Gain_2
    printf_const_UART(Start_hello_03);
    Printf_Variable_UART(Kp_Gain_2);
    NRZ_UART();  
    
    //передача коэффициента Kp_Gain_PID_t_1
    printf_const_UART(Start_hello_17);
    Printf_Variable_UART(Kp_Gain_PID_t_1);
    Send_UART_char(' ');//передача пробела 
     
    //передача коэффициента Kp_Gain_PID_t_2
    printf_const_UART(Start_hello_18);
    Printf_Variable_UART(Kp_Gain_PID_t_2);
    NRZ_UART();

    //передача коэффициента temperature_predetermined
    printf_const_UART(Start_hello_19);
    Printf_Variable_UART(temperature_predetermined);
    Send_UART_char(' ');
     
    //передача Dmin
    printf_const_UART(Start_hello_20);
    Printf_Variable_UART(D_min);//D_min_max
    NRZ_UART();
     
    //передача Dmax
    printf_const_UART(Start_hello_24);
    Printf_Variable_UART(D_max);//D_min_max
    NRZ_UART();
     
    //передача коэффициента idling_motor_dizel
    printf_const_UART(Start_hello_04);//idling motor
    Printf_Variable_UART(idling_motor_dizel);
    Send_UART_char(' ');
     
    //передача коэффициента Step_Motor_OffSet
    printf_const_UART(Start_hello_14);//Motor Step Offset
    Printf_Variable_UART(Step_Motor_OffSet);
    NRZ_UART();
     
     
         
    //--------------------------------------------------------------------------   
    printf_const_UART(Start_hello_07);
    NRZ_UART();
   
    for(i=0;i<16;i++)
    {
        for(y=0;y<16;y++)
        {
            Printf_Variable_UART(faza_array_tooth[i][y]);
            Send_UART_char('.');
        }
        NRZ_UART();
    }
    NRZ_UART();      
    
    //--------------------------------------------------------------------------
    printf_const_UART(Start_hello_13);
    for(i=0;i<16;i++)
    {
        Printf_Variable_UART(Step_motor_array_cicle[i]);
        Send_UART_char('.');
    }
    NRZ_UART();  
    
    //--------------------------------------------------------------------------    
    printf_const_UART(Start_hello_08);
    Printf_Variable_UART(Flag_Duo_Mono);
    NRZ_UART();
       
    printf_const_UART(Start_hello_23);
    NRZ_UART();
    //--------------------------------------------------------------------------
    for(i=0;i<9;i++)
    {
        for(y=0;y<5;y++)
        {
            Printf_Variable_UART(Axelerometr_tax[i][y]);
            Send_UART_char('.');
        }
        NRZ_UART();
    }
     
    //--------------------------------------------------------------------------
    printf_const_UART(Start_hello_09);
    Printf_Variable_UART(Turbo_offset);//Pressure offset
    Send_UART_char(' ');
     
    printf_const_UART(Start_hello_10);
    Printf_Variable_UART(Turbo_Koeff);//Pressure Koef
    NRZ_UART();
     
    printf_const_UART(Start_hello_11);
    Printf_Variable_UART(offset_motor_tax);//Zapazdivanie po oborotam
    Send_UART_char(' ');
     
    printf_const_UART(Start_hello_15);
    Printf_Variable_UART(Kol_zubov_kolenvala);//Mahovik tooth
    NRZ_UART();
     
     
      
    //--------------------------------------------------------------------------
    printf_const_UART(Start_hello_21);
    Printf_Variable_UART(High_Level_PID/div_milisek_switch);
    NRZ_UART();
    printf_const_UART(Start_hello_06);
    Printf_Variable_UART(Low_Level_PID/div_milisek_switch);
    Send_UART_char(' ');
    printf_const_UART(Start_hello_12);
    Printf_Variable_UART(Low_Level_Idling/div_milisek_switch);
    NRZ_UART();
    printf_const_UART(Start_hello_05);
    NRZ_UART();

    //--------------------------------------------------------------------------
    for(i=0;i<6;i++)
    {
        for(y=0;y<16;y++)
        {
          array_high_level_PID[i][y] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y);
          array_high_level_PID[i][y] = array_high_level_PID[i][y]*div_milisek_switch;
        }
    }
     
    for(i=0;i<6;i++)
    {
        for(y=0;y<16;y++)
        {
          Printf_Variable_UART(array_high_level_PID[i][y]/div_milisek_switch);
          Send_UART_char('.');
        }
        NRZ_UART();
    }
    printf_const_UART(Start_hello_16);
    Printf_Variable_UART(Flag_error_N);
    NRZ_UART();
    printf_const_UART(Start_hello_22);
    NRZ_UART();
    */
}

//------------------------------------ end -----------------------------------



/*
     switch(number_paket_tx_now)
     {
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(0):
         {
            array_test[0] = 1;//'R';
            array_test[1] = 2;//'X';
            array_test[2] = 3;//'0';
            array_test[3] = 4;//'1';
            
            array_test[4] = 12;//(char)(ADC_area_[Serial_number]>>8);    
            array_test[5] = 24;//(char)(ADC_area_[Serial_number]&0x00FF);
            
            array_test[6] = 35;//(char)(ADC_area_[Step_Motor_Koeff]>>8);    
            array_test[7] = 46;//(char)(ADC_area_[Step_Motor_Koeff]&0x00FF);
            
            array_test[8] = (char)(ADC_area_[Kp_Gain_2]>>8);    
            array_test[9] = (char)(ADC_area_[Kp_Gain_2]&0x00FF);
            
            array_test[10] = (char)(ADC_area_[Kp_Gain_PID_t_1]>>8);    
            array_test[11] = (char)(ADC_area_[Kp_Gain_PID_t_1]&0x00FF);
            
            array_test[12] = (char)(ADC_area_[Kp_Gain_PID_t_2]>>8);    
            array_test[13] = (char)(ADC_area_[Kp_Gain_PID_t_2]&0x00FF);
            
            array_test[14] = (char)(ADC_area_[temperature_predetermined]>>8);    
            array_test[15] = (char)(ADC_area_[temperature_predetermined]&0x00FF);
            
            array_test[16] = (char)(ADC_area_[D_min]>>8);    
            array_test[17] = (char)(ADC_area_[D_min]&0x00FF);
            
            array_test[18] = (char)(ADC_area_[D_max]>>8);    
            array_test[19] = (char)(ADC_area_[D_max]&0x00FF);
            
            array_test[20] = (char)(ADC_area_[idling_motor_dizel]>>8);    
            array_test[21] = (char)(ADC_area_[idling_motor_dizel]&0x00FF);
            
            array_test[22] = (char)(ADC_area_[Step_Motor_OffSet]>>8);    
            array_test[23] = (char)(ADC_area_[Step_Motor_OffSet]&0x00FF);
            
            for(i=0;i<16;i++)
            {
                array_test[i+24] = faza_array_tooth[i][0];   
            }
            
            //передаем первый байт  
            addr_uart = 0;
            enable_out_pc_paket = 1;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(1):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '2';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][1];   
            }
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][2];   
            }
            
            //передаем первый байт   
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(2):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '3';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][3];   
            }
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][4];   
            }
            
            //передаем первый байт   
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(3):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '4';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][5];   
            }
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][6];   
            }
            
            //передаем первый байт 
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(4):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '5';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][7];   
            }
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][8];   
            }
            
            //передаем первый байт    
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(5):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '6';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][9];   
            }
            for(i=0;i<16;i++)
            {
                array_test[i+20] = faza_array_tooth[i][10];   
            }
            
            //передаем первый байт   
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(6):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '7';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][11];   
            }
            for(i=0;i<16;i++)
            {
                array_test[i+20] = faza_array_tooth[i][12];   
            }
            
            //передаем первый байт   
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(7):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '8';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][13];   
            }
            for(i=0;i<16;i++)
            {
                array_test[i+20] = faza_array_tooth[i][14];   
            }
            
            //передаем первый байт  
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(8):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '0';
            array_test[3] = '9';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = faza_array_tooth[i][15];   
            }
            
            //передаем первый байт   
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(9):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '1';
            array_test[3] = '0';
            
            for(i=0;i<16;i++)
            {
                array_test[i+4] = Step_motor_array_cicle[i];   
            }
            
            array_test[20] = (char)(ADC_area_[Axelerometr_tax[0][0]]>>8);    
            array_test[21] = (char)(ADC_area_[Axelerometr_tax[0][0]]&0x00FF);
            
            array_test[22] = (char)(ADC_area_[Axelerometr_tax[1][0]]>>8);    
            array_test[23] = (char)(ADC_area_[Axelerometr_tax[1][0]]&0x00FF);
            
            array_test[24] = (char)(ADC_area_[Axelerometr_tax[2][0]]>>8);    
            array_test[25] = (char)(ADC_area_[Axelerometr_tax[2][0]]&0x00FF);
            
            array_test[26] = (char)(ADC_area_[Axelerometr_tax[3][0]]>>8);    
            array_test[27] = (char)(ADC_area_[Axelerometr_tax[3][0]]&0x00FF);
            
            array_test[28] = (char)(ADC_area_[Axelerometr_tax[4][0]]>>8);    
            array_test[29] = (char)(ADC_area_[Axelerometr_tax[4][0]]&0x00FF);
            
            array_test[30] = (char)(ADC_area_[Axelerometr_tax[5][0]]>>8);    
            array_test[31] = (char)(ADC_area_[Axelerometr_tax[5][0]]&0x00FF);
            
            array_test[32] = (char)(ADC_area_[Axelerometr_tax[6][0]]>>8);    
            array_test[33] = (char)(ADC_area_[Axelerometr_tax[6][0]]&0x00FF);
            
            array_test[34] = (char)(ADC_area_[Axelerometr_tax[7][0]]>>8);    
            array_test[35] = (char)(ADC_area_[Axelerometr_tax[7][0]]&0x00FF);
            
            array_test[36] = (char)(ADC_area_[Axelerometr_tax[8][0]]>>8);    
            array_test[37] = (char)(ADC_area_[Axelerometr_tax[8][0]]&0x00FF);
            
            //передаем первый байт    
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;

         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(10):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '1';
            array_test[3] = '1';
            
            array_test[20] = (char)(ADC_area_[Axelerometr_tax[0][1]]>>8);    
            array_test[21] = (char)(ADC_area_[Axelerometr_tax[0][1]]&0x00FF);
            
            array_test[22] = (char)(ADC_area_[Axelerometr_tax[1][1]]>>8);    
            array_test[23] = (char)(ADC_area_[Axelerometr_tax[1][1]]&0x00FF);
            
            array_test[24] = (char)(ADC_area_[Axelerometr_tax[2][1]]>>8);    
            array_test[25] = (char)(ADC_area_[Axelerometr_tax[2][1]]&0x00FF);
            
            array_test[26] = (char)(ADC_area_[Axelerometr_tax[3][1]]>>8);    
            array_test[27] = (char)(ADC_area_[Axelerometr_tax[3][1]]&0x00FF);
            
            array_test[28] = (char)(ADC_area_[Axelerometr_tax[4][1]]>>8);    
            array_test[29] = (char)(ADC_area_[Axelerometr_tax[4][1]]&0x00FF);
            
            array_test[30] = (char)(ADC_area_[Axelerometr_tax[5][1]]>>8);    
            array_test[31] = (char)(ADC_area_[Axelerometr_tax[5][1]]&0x00FF);
            
            array_test[32] = (char)(ADC_area_[Axelerometr_tax[6][1]]>>8);    
            array_test[33] = (char)(ADC_area_[Axelerometr_tax[6][1]]&0x00FF);
            
            array_test[34] = (char)(ADC_area_[Axelerometr_tax[7][1]]>>8);    
            array_test[35] = (char)(ADC_area_[Axelerometr_tax[7][1]]&0x00FF);
            
            array_test[36] = (char)(ADC_area_[Axelerometr_tax[8][1]]>>8);    
            array_test[37] = (char)(ADC_area_[Axelerometr_tax[8][1]]&0x00FF);
                        
            //передаем первый байт    
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;         
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(11):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '1';
            array_test[3] = '2';
            
            array_test[4] = (char)(Turbo_offset>>8);    
            array_test[5] = (char)(Turbo_offset&0x00FF);
            
            array_test[6] = (char)(Turbo_Koeff>>8);    
            array_test[7] = (char)(Turbo_Koeff&0x00FF);
            
            array_test[8] = (char)(offset_motor_tax>>8);    
            array_test[9] = (char)(offset_motor_tax&0x00FF);
            
            array_test[10] = Kol_zubov_kolenvala;
            
            array_test[11] = (char)((High_Level_PID/div_milisek_switch)>>8);    
            array_test[12] = (char)((High_Level_PID/div_milisek_switch)&0x00FF);
            
            array_test[13] = (char)((Low_Level_PID/div_milisek_switch)>>8);    
            array_test[14] = (char)((Low_Level_PID/div_milisek_switch)&0x00FF);
            
            array_test[15] = (char)((Low_Level_Idling/div_milisek_switch)>>8);    
            array_test[16] = (char)((Low_Level_Idling/div_milisek_switch)&0x00FF);
   
            
            //передаем первый байт 
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;

         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(12):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '1';
            array_test[3] = '3';
            
            i = 0;
            for(y=0;y<16;y++)
            {
                array_high_level_PID[i][y+4] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y+4);
                array_high_level_PID[i][y+4] = array_high_level_PID[i][y+4]*div_milisek_switch;
            }
            i = 1;
            for(y=0;y<16;y++)
            {
                array_high_level_PID[i][y+20] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y+20);
                array_high_level_PID[i][y+20] = array_high_level_PID[i][y+20]*div_milisek_switch;
            }
            
            //передаем первый байт  
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;       
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(13):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '1';
            array_test[3] = '4';
            
            i = 2;
            for(y=0;y<16;y++)
            {
                array_high_level_PID[i][y+4] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y+4);
                array_high_level_PID[i][y+4] = array_high_level_PID[i][y+4]*div_milisek_switch;
            }
            i = 3;
            for(y=0;y<16;y++)
            {
                array_high_level_PID[i][y+20] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y+20);
                array_high_level_PID[i][y+20] = array_high_level_PID[i][y+20]*div_milisek_switch;
            }
            
            //передаем первый байт   
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
         
         //--------------------------------------------------------------------------
         //--------------------------------------------------------------------------
         case(14):
         {
            array_test[0] = 'R';
            array_test[1] = 'X';
            array_test[2] = '1';
            array_test[3] = '5';
            
            i = 4;
            for(y=0;y<16;y++)
            {
                array_high_level_PID[i][y+4] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y+4);
                array_high_level_PID[i][y+4] = array_high_level_PID[i][y+4]*div_milisek_switch;
            }
            i = 5;
            for(y=0;y<16;y++)
            {
                array_high_level_PID[i][y+20] = Read_Card_2K_I2C(array_high_level_PID_24LC16B+i*16+y+20);
                array_high_level_PID[i][y+20] = array_high_level_PID[i][y+20]*div_milisek_switch;
            }
            
            //передаем первый байт 
            addr_uart = 0;
            UDR0=array_test[addr_uart];  
         }
         break;
    }   
    */     