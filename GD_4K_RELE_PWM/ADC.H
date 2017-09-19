//--------------------------------ADC.h------------------------------------------
__near unsigned char ADC_MUX=0;



#pragma vector=ADC_vect
__interrupt void ADC_interrupt(void)
{
  //__disable_interrupt();
  ADC_area_[ADC_MUX]=ADC;
  ADC_MUX++;
  if(ADC_MUX==8) ADC_MUX=0;
  ADMUX &= ~0x0F;
  ADMUX |= ADC_MUX; 
  //__enable_interrupt();
}

void Init_ADC_Free(void)
{
  //__disable_interrupt();
  ADMUX |= 0x40;
  ADCSRA = 0xBF;
  ADCSRA |= 0x40;
  __enable_interrupt();
}

void Stop_ADC(void)
{
  ADCSRA = 0x00;
}

/*unsigned int ADC_read(unsigned char adc_mux)
{
  register int convert;
  //unsigned char reg_loc;
  //Init_ADC_singl();
  
  ADMUX |= 0x40;
  ADMUX &= ~0x0F;
  ADMUX |= adc_mux;
  ADCSRA = 0x87;          //dev/128
  ADCSRA &= ~0x40;
  ADCSRA |= 0x40;
  while((ADCSRA&0x10)!=0x10) __no_operation();
  convert=ADC;
  ADCSRA |= 0x10;
  
  //Stop_ADC();
  return(convert);
}*/
