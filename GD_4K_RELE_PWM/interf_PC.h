//--------------------------------------- interf_PC.h ------------------------------------------------------

unsigned char test_1;
unsigned char test_2;
unsigned int ik,ccc;

void PC_indicator_state(void)
{
  unsigned int dopi_per;
  
  if(enable_out_pc_paket == 0)
  {
     //------------------------------------------------------------------------
     ERROR_kil = 0;
     ERROR_kil = ERROR_kil + ERROR_f1 + ERROR_f2 + ERROR_f3 + ERROR_f4 +
                             ERROR_f5 + ERROR_f6 + ERROR_f7 + ERROR_f8 +
                             ERROR_f_kz;
     ERROR_kil = ERROR_kil + ERROR_faza + ERROR_tax + ERROR_tt + ERROR_dd + ERROR_gkl + ERROR_term + ERROR_HD;
  
     array_test[0] = '{';
     array_test[1] = (char)(Delay_kl>>8);
     array_test[2] = (char)(Delay_kl&0x00FF);
     array_test[3] = high_level_index_Y;
     array_test[4] = high_level_index_I;
     array_test[5] = (char)(taxometer>>8);
     array_test[6] = (char)(taxometer&0x00FF);
     array_test[7] = (char)(temperature_Col>>8);
     array_test[8] = (char)(temperature_Col&0x00FF);
     array_test[9] = (char)(ADC_area_[ADC_MUX_pressure]>>8);            //датчик давления над 
     array_test[10] = (char)(ADC_area_[ADC_MUX_pressure]&0x00FF);       //датчик давления над  
     array_test[11] = (char)(ADC_area_[ADC_MUX_axeleratora]>>8);        //датчик педали    
     array_test[12] = (char)(ADC_area_[ADC_MUX_axeleratora]&0x00FF);    //датчик педали    
  
     array_test[13] = ERROR_kil;
     array_test[14] = ERROR_out_1;
     array_test[15] = ERROR_out_2;
     array_test[16] = ERROR_out_3;
     array_test[17] = ERROR_out_4;
     array_test[18] = ERROR_out_5;
     array_test[19] = ERROR_out_6;  
     array_test[20] = ERROR_out_7;
     array_test[21] = ERROR_out_8;
  
     array_test[22] = (char)(ADC_area_[ADC_MUX_temp_shem]>>8);          //датчик Т БУ  
     array_test[23] = (char)(ADC_area_[ADC_MUX_temp_shem]&0x00FF);      //датчик Т БУ  
     array_test[24] = (char)(ADC_area_[ADC_MUX_termopara]>>8);          //датчик Т выхлопа    
     array_test[25] = (char)(ADC_area_[ADC_MUX_termopara]&0x00FF);      //датчик Т выхлопа 

     array_test[26] = (char)(ADC_area_[ADC_MUX_akumulator]>>8);         //бортовое напряжение    
     array_test[27] = (char)(ADC_area_[ADC_MUX_akumulator]&0x00FF);     //бортовое напряжение 
     array_test[28] = (char)(ADC_area_[ADC_MUX_pressure_gaza]>>8);      //датчик давления над 
     array_test[29] = (char)(ADC_area_[ADC_MUX_pressure_gaza]&0x00FF);  //датчик давления над  
     
     array_test[30] = STOP_RUN_GD;//передаем состояние "вкл/выкл" ГД
     array_test[31] = 12;
     array_test[32] = term_switch;//передаем критическое состояние по температуре
     array_test[33] = 0;//ERROR_HD; //dob_paket_3;ADC_MUX_DC_HD_A
     dopi_per = Step_Motor_Position;
     dopi_per = dopi_per/4;
     dopi_per = dopi_per - Step_Motor_OffSet;
     array_test[34] = dopi_per; //dob_paket_4;
     array_test[35] = dopi_per_2; //dob_paket_5;
     array_test[36] = 0; //dob_paket_6;
     array_test[37] = 0; //dob_paket_7;
     array_test[38] = 0; //dob_paket_8;
     array_test[39] = 0; //dob_paket_9;
     
     //CRC_out
     array_test[40] = 0;
     for(ik=0;ik<40;ik++)
     {
         array_test[40] = array_test[40] ^ array_test[ik];
     }  
  
     //начало передачи данных
     enable_out_pc_paket = 1;
     addr_uart = 0;
     UDR0=array_test[addr_uart];
  }
}
//----------------------------------------------end-------------------------------------------------------------


