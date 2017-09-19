//----------------------------------------- GD.h --------------------------------------------------------------
//#define   d0_koef_PID   2.45
//#define   d1_koef_PID   -3.5
//#define   d2_koef_PID   1.25

//#define   d0_koef_PI    1.2
//#define   d1_koef_PI    
//#define   d2_koef_PI    0

//__near unsigned int taxometer_test;
__near float R_int;
void PID_regulator(void)
{
  //unsigned char i_L=0, y_L=0, s_L=0;
  unsigned char i_L=0, y_L=0;
  unsigned int Acselerometr_ADC;
  unsigned int DOP_DELAY;
  
  float K_prop;
  float K_int;
  float K_dif;
  float R_prop;
  float R_dif;
  
  Turbo_Koeff  = 78;
  Turbo_offset = 365; 
  
  /*tx_deter =(tx_deter + (taxometer_K * ADC_read(7) + taxometer_B))/2;  // + working sensor
  taxometer_predetermined = tx_deter + idling_motor_dizel;*/
  
  //òåêóùåå çíà÷åíèå òàõîìåòðà
  y_L=taxometer/200;
  if(y_L<(min_turns_motora_dizel/200)) y_L=min_turns_motora_dizel/200;
  if(y_L>15) y_L=15;
  
  
  //s_L=(taxometer+vector_taxo*())/200;
  Step_Motor_Koeff = 4;
  Step_Motor_Future = (Step_Motor_OffSet + Step_motor_array_cicle[y_L])*Step_Motor_Koeff;// Step motor
  
  //òåêóùåå çíà÷åíèå äàâëåíèÿ 
  if(ADC_area_[ADC_MUX_pressure] < Turbo_offset) i_L=0;
  else i_L=(unsigned char)((ADC_area_[ADC_MUX_pressure]-Turbo_offset)/Turbo_Koeff);
  if(i_L>6) i_L=6;//äî çíà÷åíèÿ 1.2 - ìàêñèìóì
  
  //ïåðåìåííûå ìàðêåðà â Delphi
  high_level_index_I=i_L;
  high_level_index_Y=y_L;
  
  //ìàêñèìàëüíîå çíà÷åíèå ãàçà
  High_Level_PID_tax = array_high_level_PID[i_L][y_L];  
  //êîððåêöèÿ óãëà âïðûñêà
  sw1_number_tooth = faza_array_tooth[i_L][y_L-1];  
  
  i_L=0;
  //çíà÷åíèå ñ äàò÷èêà ïåäàëè
  Acselerometr_ADC=ADC_area_[ADC_MUX_axeleratora];
  if(Axelerometr_tax[0][0]>Acselerometr_ADC)
  {
     taxometer_predetermined=idling_motor_dizel;
     //Kp_Gain_CH=Kp_Gain_0;
     /*if(200>fabs(taxometer-taxometer_predetermined)) Triger_Idling_K0++;
     else Triger_Idling_K0=0;
     Kp_Gain_CH=Kp_Gain_0;
     if(Triger_Idling_K0>80) Kp_Gain_CH=Kp_Gain_0;*/
     //High_Level_PID=High_Level_PID*2;     // x*2 idling mono
     //Flag_DM=0;
  }
  else
  {
    while(Axelerometr_tax[++i_L][0]<Acselerometr_ADC);
    if(i_L==8) i_L=7;
    taxometer_predetermined=(Axelerometr_tax[i_L][2]/10)*((Acselerometr_ADC*10)/Axelerometr_tax[i_L][3])+Axelerometr_tax[i_L][4]; //  0 - ADC, 1 - Tax, 2 - K1, 3 - K2, 4 - B
    if(Axelerometr_tax[i_L][1]<taxometer_predetermined) taxometer_predetermined=Axelerometr_tax[i_L][1];
    taxometer_predetermined=taxometer_predetermined-offset_motor_tax;//
    //Kp_Gain_CH=Kp_Gain_1;
    //Flag_DM=Flag_Duo_Mono;
  }
  if(taxometer_predetermined > max_turns_motora_dizel) taxometer_predetermined=max_turns_motora_dizel;  
  if(taxometer_predetermined < idling_motor_dizel) taxometer_predetermined=idling_motor_dizel;  
  
  float alfa=0.25;
  taxo_filt=taxo_filt+alfa*(taxometer-taxo_filt);
  taxometer_delta[2]=taxometer_delta[1];
  taxometer_delta[1]=taxometer_delta[0];
  taxometer_delta[0]=taxometer_predetermined-taxo_filt;
      
    //Rezult_PID=Rezult_PID - ((49*taxometer_delta[0])/20-(7*taxometer_delta[1])/2+(5*taxometer_delta[2])/4)/Kp_Gain_2;     //PID -----
    //Rezult_PID=Rezult_PID - ((49*taxometer_delta[0])/20-(7*taxometer_delta[1])/2+(5*taxometer_delta[2])/4)/8;           //PID -----
    //else Rezult_PID=Rezult_PID -((6*taxometer_delta[0])/5-taxometer_delta[1])/Kp_Gain_2;     //PI  -----
    /*if(Flag_PID_PI==0)
    {
      if(taxometer_predetermined<idling_motor_dizel+150) Rezult_PID=Rezult_PID -((6*taxometer_delta[0])/5-taxometer_delta[1])/Kp_Gain_2;     //PI  -----
      else
      {
        if(taxometer>max_turns_motora_dizel-100) Rezult_PID=Rezult_PID -((6*taxometer_delta[0])/5-taxometer_delta[1])/Kp_Gain_2;     //PI  -----
        else Rezult_PID= tx_deter/(2000/High_Level_PID);     //P  -----
      }
    }*/
    
  //Rezult_PID=Rezult_PID - ((6*taxometer_delta[0])/5-taxometer_delta[1])/Kp_Gain_2;     //PI  -----
  
  K_prop = 0.5;     // coef. of prop
  K_int = 0.001;	// coef. of integ
  K_dif = 0.0;	    // coef. of diff
  R_prop = K_prop * taxometer_delta[0];
  R_int = R_int + K_int * taxometer_delta[0];
  R_dif = K_dif * (taxometer_delta[1]-taxometer_delta[0]);
  Rezult_PID = (R_prop + R_int + R_dif);
  
  /*if(Flag_PID_PI==0) Rezult_PID=Rezult_PID - (Kp_Gain_CH*((6*taxometer_delta[0])/5-taxometer_delta[1]))/Kp_Gain_2;     //PI  -----
  else Rezult_PID=Rezult_PID - (Kp_Gain_CH*((49*taxometer_delta[0])/20-(7*taxometer_delta[1])/2+(5*taxometer_delta[2])/4))/Kp_Gain_2;     //PID -----*/
    
    /*if(Flag_PID_PI==1) Rezult_PID=Rezult_PID -((6*taxometer_delta[0])/5-taxometer_delta[1])/Kp_Gain_2;     //PI  -----
    if(Flag_PID_PI==2) Rezult_PID=Rezult_PID -((6*taxometer_delta[0])/5-taxometer_delta[1])/Kp_Gain_2;     //PI  -----
    if(Flag_PID_PI==3) Rezult_PID=Rezult_PID - ((49*taxometer_delta[0])/20-(7*taxometer_delta[1])/2+(5*taxometer_delta[2])/4)/Kp_Gain_2;     //PID -----*/
  
  //------------------------------------------------------------------------------------------------------
  if(taxometer_predetermined<idling_motor_dizel+50)//idling_motor_dizel - îáîðîòû ÕÕ
  {
    if(taxometer<idling_motor_dizel+350) 
    {
      Q_PID_count++;
      if(Q_PID_count<Q_PID_const)
      {
         if(Rezult_PID<Low_Level_Idling) Rezult_PID=Low_Level_Idling;//Low_Level_Idling - âïðûñê ãàçà íà ÕÕ
      }
    }
  }
  else Q_PID_count=0;
  //------------------------------------------------------------------------------------------------------
  
  //---------------- PID temperature collectors
  //if(Flag_PID_t_collectora==1) PID_regulator_temperature();
  //---------------- PID temperature collectors
  
  if(Rezult_PID>High_Level_PID_tax) Rezult_PID=High_Level_PID_tax;
  //if(Rezult_PID>Rezult_PID_temperature) Rezult_PID=Rezult_PID_temperature;
  if(Rezult_PID<Low_Level_PID) Rezult_PID=0;//Low_Level_PID;
  Delay_kl=(unsigned char)Rezult_PID; 
  //if(Flag_PC_interf==1) PC_indicator_state();
  
  
  //------------------------------------------------------------------------------------------------------
  //ïîäïðîãðàììà "ÐÅÀÊÖÈß ÍÀ ÒÅÌÏÅÐÀÒÓÐÓ" 
  //------------------------------------------------------------------------------------------------------
  switch(term_switch)
  {
      case(0):
      { 
         temperature_ADC = ADC_area_[ADC_MUX_termopara];
         temperature_ADC_B = ADC_area_[ADC_MUX_temp_shem];
         temperature_ADC_SUMM = temperature_ADC - temperature_ADC_B; 
         
         temperature_ADC = ADC_area_[ADC_MUX_termopara];
         temperature_ADC = temperature_ADC*100;
         temperature_ADC = temperature_ADC/122;
         
         temperature_ADC_B = ADC_area_[ADC_MUX_temp_shem];
         temperature_ADC_B = temperature_ADC_B*100;
         temperature_ADC_B = temperature_ADC_B/307;
         temperature_ADC_B = temperature_ADC_B - 55;
         
         temperature_ADC_SUMM = temperature_ADC - temperature_ADC_B; 
         temperature_ADC_SUMM = temperature_ADC_SUMM + 45;
         if(temperature_ADC_SUMM > temperature_predetermined)
         {
            term_switch = 1;
         }
      }
      break;
      case(1):
      {
         // - 20%
         DOP_DELAY = Delay_kl;
         DOP_DELAY = DOP_DELAY*100;
         DOP_DELAY = DOP_DELAY/500;
         Delay_kl = Delay_kl-DOP_DELAY;
         
         temperature_ADC = ADC_area_[ADC_MUX_termopara];
         temperature_ADC = temperature_ADC*100;
         temperature_ADC = temperature_ADC/122;
         
         temperature_ADC_B = ADC_area_[ADC_MUX_temp_shem];
         temperature_ADC_B = temperature_ADC_B*100;
         temperature_ADC_B = temperature_ADC_B/307;
         temperature_ADC_B = temperature_ADC_B - 55;
         
         temperature_ADC_SUMM = temperature_ADC - temperature_ADC_B; 
         temperature_ADC_SUMM = temperature_ADC_SUMM + 45;
         if(temperature_ADC_SUMM < (temperature_predetermined-10))
         {
            term_switch = 0;
         }
      }
      break; 
  }

      Flag_quantization_step_PID=0;
}




/*
void PID_regulator_temperature(void)
{
  //unsigned char i_L=0, y_L=0;
  //unsigned int temperature_ADC;
  
  temperature_delta[2]=temperature_delta[1];
  temperature_delta[1]=temperature_delta[0];
  temperature_delta[0]=temperature_Col-temperature_predetermined;
    
  Rezult_PID_temperature=Rezult_PID_temperature - (Kp_Gain_PID_t_1*((6*temperature_delta[0])/5-temperature_delta[1]))/Kp_Gain_PID_t_2;     //PI  -----
  
  if(Rezult_PID_temperature>High_Level_PID) Rezult_PID_temperature=High_Level_PID;
  if(Rezult_PID_temperature<0) Rezult_PID_temperature=0;
  
  Flag_PID_t_collectora=0;
}
*/




/*
void temperature_collector_reduktor(void)
{
  unsigned int temperature_ADC;
  temperature_ADC=ADC_area_[ADC_MUX_termopara];
  temperature_Col=(10*(temperature_ADC*5)+62)/39;  // temperature out collectora
  
  temperature_ADC=ADC_area_[ADC_MUX_temp_D];
  temperature_Reduktor=120-(8*temperature_ADC)/56;  // temperature reduktora gas
  //temperature_Reduktor=temperature_ADC;
  
  Flag_PID_t_collectora=1;
  Flag_temperature=0;
}
*/



void Taxometer_qvant(void)
{
  /*Tax_arrea[9]=Tax_arrea[8];
  Tax_arrea[8]=Tax_arrea[7];
  Tax_arrea[7]=Tax_arrea[6];
  Tax_arrea[6]=Tax_arrea[5];
  Tax_arrea[5]=Tax_arrea[4];
  Tax_arrea[4]=Tax_arrea[3];
  Tax_arrea[3]=Tax_arrea[2];
  Tax_arrea[2]=Tax_arrea[1];
  Tax_arrea[1]=Tax_arrea[0];
  Tax_arrea[0]=(i_maxovik_timer/(taxometer_count/10))*6;   // taxometer=(57600/(taxo_count/10))*6;
  taxometer=(Tax_arrea[0]+Tax_arrea[1]+Tax_arrea[2]+Tax_arrea[3]+Tax_arrea[4]+Tax_arrea[5]+Tax_arrea[6]+Tax_arrea[7]+Tax_arrea[8]+Tax_arrea[9])/10;*/
  //taxometer_delta[0]=taxometer-taxometer_predetermined;
  
  /*if(Faza_motora==1)
  {
     taxometer=(i_maxovik_timer/((taxometer_count*(motor_cylinders/2))/10))*6;   // taxometer=(57600/(taxo_count/10))*6;
   
     Flag_taxometer=0;
     Flag_quantization_step_PID=1;
     //if(Flag_PC_interf==1) PC_indicator_state(); 
  }*/
  
  if(Faza_motora==2)
  {
     taxometer=(i_maxovik_timer/((taxometer_count*(motor_cylinders/2))/10))*6;   // taxometer=(57600/(taxo_count/10))*6;
   
     Flag_taxometer=0;
     Flag_quantization_step_PID=1;
     //if(Flag_PC_interf==1) PC_indicator_state(); 
  }
  
  /*if(Faza_motora==3)
  {
     taxometer=(i_maxovik_timer/((taxometer_count*(motor_cylinders/2))/10))*6;   // taxometer=(57600/(taxo_count/10))*6;
   
     Flag_taxometer=0;
     Flag_quantization_step_PID=1;
     //if(Flag_PC_interf==1) PC_indicator_state(); 
  }*/
  
  if(Faza_motora==4)
  {
    taxometer=(i_maxovik_timer/((taxometer_count*(motor_cylinders/2))/10))*6;   // taxometer=(57600/(taxo_count/10))*6;
    
    Flag_taxometer=0;
    Flag_quantization_step_PID=1;
    //if(Flag_PC_interf==1) PC_indicator_state();
  }
  /*
  if(Faza_motora==6)
  {
    taxometer=(i_maxovik_timer/((taxometer_count*(motor_cylinders/2))/10))*6;   // taxometer=(57600/(taxo_count/10))*6;
  
    Flag_taxometer=0;
    Flag_quantization_step_PID=1;
    //if(Flag_PC_interf==1) PC_indicator_state();
  }
  if(Faza_motora==8)
  {
    taxometer=(i_maxovik_timer/((taxometer_count*(motor_cylinders/2))/10))*6;   // taxometer=(57600/(taxo_count/10))*6;
  
    Flag_taxometer=0;
    Flag_quantization_step_PID=1;
    //if(Flag_PC_interf==1) PC_indicator_state();
  }
  */
}



void Condition(void)
{
  if(miliSekundomer_ms>20)
  {
    if((Button_GD_READ)==0)
    {
      //Flag_GD_Button=(~Flag_GD_Button)&0x01;   // Button on/off
      Triger_Button++;
      if(Triger_Button==300)
      {
         if((ON_OFF_Car_READ)!=0)
         {
             Flag_GD_Button=1;
         }  
         Triger_Button=0;
      }
       //miliSekundomer_ms=0;
    }
    else Triger_Button=0;
  }
  
  if(Flag_State_Run_GD==0)
  {
    if((ON_OFF_Car_READ)!=0)
    {
      if(Flag_GD_Button==1)
      {
        if(taxometer>idling_motor_dizel-200)
        {
          //if(test_hdd()==0)
          //{
          if(test_treadle()==0)
          {
            //if(temperature_Reduktor>temperature_predetermined_Reduktor)
            //{
              Flag_State_Run_GD=1;
              if(test_dat_dav()==0)
              { 
                 STOP_RUN_GD = 2;     
                 Run_GD();
                 //off_sys = 0;
                 //enable_off_sys = 0;
                  if(comand_run_gd == 1)
                  {
                    if(Flag_PC_interf == 0)
                    {
                        //ïåðåäà÷à îòâåòíîãî ñèãíàëà
                        printf_const_UART(OK_RUN_GD);
                        Send_UART_char(' ');
                     }
                  }
              }
              Flag_GD_Button=0;
            //}else Error_function_e(Error_t_Reduktor);
          //}
          }
        }
        else Taxometer_test();
        Flag_GD_Button=0;
      } //else Error_function_e(Error_OnOff_Button);
    } //else Error_function_e(Error_ON_OFF_Car);
  }
  else if(Flag_State_Run_GD==1)
  {
    if((ON_OFF_Car_READ)==0)
    {
      Triger_ON_OFF++;
      if(Triger_ON_OFF==0xFE)
      {
         STOP_RUN_GD = 2;
         Stop_GD();
         Triger_ON_OFF=0;
      }
    }
    if(Flag_GD_Button==1)
    {
       //Flag_State_Run_GD=0;
       STOP_RUN_GD = 2;
       Stop_GD();
       if(comand_run_gd == 1)
       {
          if(Flag_PC_interf == 0)
          {
             //ïåðåäà÷à îòâåòíîãî ñèãíàëà
             printf_const_UART(OTV_STOP_GD);
             Send_UART_char(' ');
          }
       }
       Flag_GD_Button=0;
       miliSekundomer_ms=0;
    }
    /*if(temperature_Reduktor<temperature_predetermined_Reduktor-10)
    {
      Stop_GD();
    }*/
  
    if((TIFR1&0x01)==0x01)   // maxovik stop
    {
        TIFR1 |= 0x01;
        Stop_GD();
    }
    if(taxometer<300)
    {
        Stop_GD();
    }
        
    /*
    if((Koncevik_MUZD_READ)!=0)
    {
        Triger_Koncevik++;
        if(Triger_Koncevik==2600)
        {
           Stop_GD();
           Triger_Koncevik=0;
        }
    }
    */
    //else 
    Triger_Koncevik=0;
  }
}

//----------------------------------------- end GD.h ---------------------------------------------------------
