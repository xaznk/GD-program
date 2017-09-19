//---------------------------------------------------------------- UART.h -----------------------------------------------------------------------------------
#define Speed_UART  3    //25 скорость 250000 кбит/сек
//#define Speed_UART  103    //скорость 9600 бит/сек

__near unsigned char address_BUF_RX=0;
__near unsigned char Buffer_UART_RX[100];//64
__near unsigned char Buffer_String_v[18];//8



#pragma vector=USART0_TX_vect
__interrupt void USART0_TX_interrupt(void)
{

switch(enable_out_pc_paket)
{
  case(1):
  {
     addr_uart = addr_uart + 1;
     if(addr_uart != 41)
     {
        UDR0=array_test[addr_uart];
     }
     else if(addr_uart == 41)
     {
        enable_out_pc_paket = 2;
        addr_uart = 0;
        UCSR0B |= 0x10;
        Flag_UART_TXD_empty=0;
     }
  }
  break;
  default: 
  {
     UART_FO_address++;
     if(UART_FO_address==UART_FI_address)
     {
        //UCSR0B &= ~0x08;        // TxD disable
        UCSR0B |= 0x10;           // RxD enable
        RS485_Transmit_OFF;       // DE
        Flag_UART_TXD_empty=0;
     }
     else
     {
        UDR0=UART_buffer_FIFO[UART_FO_address];
     }
  }
  break;
}
}
  
  

void Init_UART(void)
{
  //__disable_interrupt();
  address_BUF_RX=0;
  Flag_UART_TXD_empty=0;
  UART_FI_address=0;
  UART_FO_address=0;
  
  UDR0=0x00;
  //UCSRB |=0x18;  //  RX En TX En
  UCSR0B |= 0x08;   // TxD enable
  UCSR0B |= 0x10;  //  RX En
  UCSR0B |= 0x40;  //  interrupt TXCIE
  //UBRRH=0x00;
  UBRR0L=Speed_UART;
  //UCSR0B &= ~0x08;  // TxD disable
  RS485_Transmit_OFF;   // DE
  //__enable_interrupt();
}


void UART_RX_int(void)
{
   register unsigned char Uart_char;
   //UCSR0B |=0x10;
   if((UCSR0A&0x80)==0x80)
   {
      //__disable_interrupt();
      Uart_char=UDR0; 
      
      //анализ прихода конца пакета
      if(Uart_char==0x0D)
      {
         Buffer_UART_RX[address_BUF_RX]='\0';
         address_BUF_RX=0;
         Flag_Command=1;//флаг конца пакета
         Uart_char = 0;
      }
      else
      {
         Buffer_UART_RX[address_BUF_RX]=Uart_char;
         address_BUF_RX++;
         if(address_BUF_RX==100) address_BUF_RX=0;
      }
      //__enable_interrupt();
   }
}


void Send_UART_char(register unsigned char char_UTx)
{  
  register unsigned char Loc_adr=0;
  
  if(Flag_UART_TXD_empty==0)
  {
    RS485_Transmit_ON;        // DE
    //UCSR0B &=~0x10;         // RxD disable
    UCSR0B |= 0x08;           // TxD enable
    UART_buffer_FIFO[UART_FI_address]=char_UTx;
    UDR0=char_UTx;
    UART_FI_address++;
    Flag_UART_TXD_empty=1;
  }
  else
  {
    Loc_adr=UART_FI_address+1;
    while(UART_FO_address==Loc_adr) __no_operation();
    UART_buffer_FIFO[UART_FI_address]=char_UTx;
    UART_FI_address++;
  }
}


signed int Sscanf_variable(unsigned char __near *array_char_var)
{
  unsigned int Loc_var_sscanf=0;
  signed char znak=1;
  if(*array_char_var == '-')
  {
    znak=-1;
    *(array_char_var++);
  }
  while(*array_char_var!='\0')
  {      
      Loc_var_sscanf=Loc_var_sscanf*10+((*(array_char_var++))&0x0F); 
  }
  return Loc_var_sscanf*znak;
} 


signed int Sf_variable(unsigned char __near *array_char_var)
{
  unsigned int Loc_var_sscanf=0;
  while(*array_char_var!='P')
  {      
      Loc_var_sscanf=Loc_var_sscanf*10+((*(array_char_var++))&0x0F);
      next_p = next_p + 1;
  }
  return Loc_var_sscanf;
} 


void Printf_Variable_UART(int var)
{
    unsigned char i=0;
    if(var<0)
    {
      Send_UART_char('-');
      var=var*(-1);
    }
    Sprintf_main(&Buffer_String_v[0],(unsigned int)var);
    
    if(Buffer_String_v[i]=='\0') Send_UART_char('0');
    while (Buffer_String_v[i]!='\0')
    {
       Send_UART_char(Buffer_String_v[i]);
       i++;
    }
}
 

void Sprintf_main(unsigned char __near *Arr_ch, int var_m)
{
    register unsigned int ost_var,i=10000;
    unsigned char ch_var, kl_c=0;
    ost_var=var_m;
    do
    {
      ch_var=(unsigned char)(ost_var/i);
      ost_var=(unsigned int)(ost_var%i);
      if(ch_var!=0) kl_c=1;
      if(kl_c==1) *(Arr_ch++)=48+(unsigned char)(ch_var);
      i=(unsigned int)(i/10); 
    }
    while(i!=0);
    *Arr_ch='\0';
}


void printf_const_UART(unsigned char const __flash *Array_const_char)
{
     unsigned char Local_3;
     Local_3=__load_program_memory(Array_const_char);
     while (Local_3!='\0')
     {
            Send_UART_char(Local_3);
            Local_3=__load_program_memory(++Array_const_char);
     }
}


void NRZ_UART(void)
{
  printf_const_UART(NRZ_00);
}


void Ok_UART(void)
{
  printf_const_UART(Ok_00);
}

//-------------------------end
