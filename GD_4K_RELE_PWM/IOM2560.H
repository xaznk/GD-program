/****************************************************************************
 **             - io2560.h -
 **
 **     This file declares the internal register addresses for AT902560.
 **
 **     Used with iccAVR and aAVR.
 **
 **     Copyright IAR Systems 2004. All rights reserved.
 **
 **     File version: $Revision: 1.3 $
 **
 ***************************************************************************/

#include "iomacro.h"

#if TID_GUARD(5)
#error This file should only be compiled with iccavr or aavr whith processor option -v5
#endif /* TID_GUARD(5) */

/* Include the SFR part if this file has not been included before,
 * OR this file is included by the assembler (SFRs must be defined in
 * each assembler module). */
#if !defined(__IO2560_H) || defined(__IAR_SYSTEMS_ASM__)

#pragma language=extended

/*==========================*/
/* Predefined SFR Addresses */
/*==========================*/

/****************************************************************************
 * An example showing the SFR_B() macro call, 
 * the expanded result and usage of this result:
 *
 * SFR_B_R(0x1F,   AVR) Expands to:
 * __io union {
 *             unsigned char AVR;                 // The sfrb as 1 byte
 *             struct {                           // The sfrb as 8 bits
 *                     unsigned char AVR_Bit0:1,
 *                                   AVR_Bit1:1,
 *                                   AVR_Bit2:1,
 *                                   AVR_Bit3:1,
 *                                   AVR_Bit4:1,
 *                                   AVR_Bit5:1,
 *                                   AVR_Bit6:1,
 *                                   AVR_Bit7:1;
 *                    };
 *            } @ 0x1F;
 * Examples of how to use the expanded result:
 * AVR |= (1<<5);
 * or like this:
 * AVR_Bit5 = 1;
 *
 *
 *
 * An example showing the SFR_B_N() macro call, 
 * the expanded result and usage of this result:
 * SFR_B_N(0x25,  TCCR2, FOC2, WGM20, COM21, COM20, WGM21, CS22, CS21, CS20)
 *  Expands to:
 *  __io union { 
 *              unsigned char TCCR2; 
 *              struct { 
 *                      unsigned char TCCR2_Bit0:1, 
 *                                    TCCR2_Bit1:1, 
 *                                    TCCR2_Bit2:1, 
 *                                    TCCR2_Bit3:1, 
 *                                    TCCR2_Bit4:1, 
 *                                    TCCR2_Bit5:1, 
 *                                    TCCR2_Bit6:1, 
 *                                    TCCR2_Bit7:1; 
 *                     }; 
 *              struct { 
 *                      unsigned char TCCR2_CS20:1, 
 *                                    TCCR2_CS21:1, 
 *                                    TCCR2_CS22:1, 
 *                                    TCCR2_WGM21:1, 
 *                                    TCCR2_COM20:1, 
 *                                    TCCR2_COM21:1, 
 *                                    TCCR2_WGM20:1, 
 *                                    TCCR2_FOC2:1; 
 *                     }; 
 *             } @ 0x25;
 * Examples of how to use the expanded result:
 * TCCR2 |= (1<<5); 
 * or if ENABLE_BIT_DEFINITIONS is defined   
 * TCCR2 |= (1<<COM21);
 * or like this:
 * TCCR2_Bit5 = 1;
 * or like this:
 * TCCR2_COM21 = 1;
 ***************************************************************************/

SFR_B_EXT_IO_R(0x136, UDR3)
SFR_W_EXT_IO_R(0x134, UBRR3)
SFR_B_EXT_IO_N(0x132, UCSR3C, UMSEL31, UMSEL30, UPM31, UPM30, USBS3, UCSZ31, UCSZ30, UCPOL3)
SFR_B_EXT_IO_N(0x131, UCSR3B, RXCIE3, TXCIE3, UDRIE3, RXEN3, TXEN3, UCSZ32, RXB83, TXB83)
SFR_B_EXT_IO_N(0x130, UCSR3A, RXC3, TXC3, UDRE3, FE3, DOR3, PE3, U2X3, MPCM3)
SFR_W_EXT_IO_R(0x12C, OCR5C)
SFR_W_EXT_IO_R(0x12A, OCR5B)
SFR_W_EXT_IO_R(0x128, OCR5A)
SFR_W_EXT_IO_R(0x126, ICR5)
SFR_W_EXT_IO_R(0x124, TCNT5)
SFR_B_EXT_IO_N(0x122, TCCR5C, FOC5A, FOC5B, FOC5C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_EXT_IO_N(0x121, TCCR5B, ICNC5, ICES5, Dummy5, WGM53, WGM52, CS52, CS51, CS50)
SFR_B_EXT_IO_N(0x120, TCCR5A, COM5A1, COM5A0, COM5B1, COM5B0, COM5C1, COM5C0, WGM51, WGM50)
SFR_B_EXT_IO_N(0x10B, PORTL, PORTL7, PORTL6, PORTL5, PORTL4, PORTL3, PORTL2, PORTL1, PORTL0)
SFR_B_EXT_IO_N(0x10A, DDRL, DDL7, DDL6, DDL5, DDL4, DDL3, DDL2, DDL1, DDL0)
SFR_B_EXT_IO_N(0x109, PINL, PINL7, PINL6, PINL5, PINL4, PINL3, PINL2, PINL1, PINL0)
SFR_B_EXT_IO_N(0x108, PORTK, PORTK7, PORTK6, PORTK5, PORTK4, PORTK3, PORTK2, PORTK1, PORTK0)
SFR_B_EXT_IO_N(0x107, DDRK, DDK7, DDK6, DDK5, DDK4, DDK3, DDK2, DDK1, DDK0)
SFR_B_EXT_IO_N(0x106, PINK, PINK7, PINK6, PINK5, PINK4, PINK3, PINK2, PINK1, PINK0)
SFR_B_EXT_IO_N(0x105, PORTJ, PORTJ7, PORTJ6, PORTJ5, PORTJ4, PORTJ3, PORTJ2, PORTJ1, PORTJ0)
SFR_B_EXT_IO_N(0x104, DDRJ, DDJ7, DDJ6, DDJ5, DDJ4, DDJ3, DDJ2, DDJ1, DDJ0)
SFR_B_EXT_IO_N(0x103, PINJ, PINJ7, PINJ6, PINJ5, PINJ4, PINJ3, PINJ2, PINJ1, PINJ0)
SFR_B_EXT_IO_N(0x102, PORTH, PORTH7, PORTH6, PORTH5, PORTH4, PORTH3, PORTH2, PORTH1, PORTH0)
SFR_B_EXT_IO_N(0x101, DDRH, DDH7, DDH6, DDH5, DDH4, DDH3, DDH2, DDH1, DDH0)
SFR_B_EXT_IO_N(0x100, PINH, PINH7, PINH6, PINH5, PINH4, PINH3, PINH2, PINH1, PINH0)

SFR_B_R(0xD6, UDR2)
SFR_W_R(0xD4, UBRR2)
SFR_B_N(0xD2, UCSR2C, UMSEL21, UMSEL20, UPM21, UPM20, USBS2, UCSZ21, UCSZ20, UCPOL2)
SFR_B_N(0xD1, UCSR2B, RXCIE2, TXCIE2, UDRIE2, RXEN2, TXEN2, UCSZ22, RXB82, TXB82)
SFR_B_N(0xD0, UCSR2A, RXC2, TXC2, UDRE2, FE2, DOR2, PE2, U2X2, MPCM2)
SFR_B_R(0xCE, UDR1)
SFR_W_R(0xCC, UBRR1)
SFR_B_N(0xCA, UCSR1C, UMSEL11, UMSEL10, UPM11, UPM10, USBS1, UCSZ11, UCSZ10, UCPOL1)
SFR_B_N(0xC9, UCSR1B, RXCIE1, TXCIE1, UDRIE1, RXEN1, TXEN1, UCSZ12, RXB81, TXB81)
SFR_B_N(0xC8, UCSR1A, RXC1, TXC1, UDRE1, FE1, DOR1, PE1, U2X1, MPCM1)
SFR_B_R(0xC6, UDR0)
SFR_W_R(0xC4, UBRR0)
SFR_B_N(0xC2, UCSR0C, UMSEL01, UMSEL00, UPM01, UPM00, USBS0, UCSZ01, UCSZ00, UCPOL0)
SFR_B_N(0xC1, UCSR0B, RXCIE0, TXCIE0, UDRIE0, RXEN0, TXEN0, UCSZ02, RXB80, TXB80)
SFR_B_N(0xC0, UCSR0A, RXC0, TXC0, UDRE0, FE0, DOR0, PE0, U2X0, MPCM0)
SFR_B_N(0xBD, TWAMR, TWAM6, TWAM5, TWAM4, TWAM3, TWAM2, TWAM1, TWAM0, Dummy0)
SFR_B_N(0xBC, TWCR, TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN, Dummy1, TWIE)
SFR_B_R(0xBB, TWDR)
SFR_B_N(0xBA, TWAR, TWA6, TWA5, TWA4, TWA3, TWA2, TWA1, TWA0, TWGCE)
SFR_B_N(0xB9, TWSR, TWS7, TWS6, TWS5, TWS4, TWS3, Dummy2, TWPS1, TWPS0)
SFR_B_R(0xB8, TWBR)
SFR_B_N(0xB6, ASSR, Dummy7, EXCLK, AS2, TCN2UB, OCR2AUB, OCR2BUB, TCR2AUB, TCR2BUB)
SFR_B_R(0xB4, OCR2B)
SFR_B_R(0xB3, OCR2A)
SFR_B_R(0xB2, TCNT2)
SFR_B_N(0xB1, TCCR2B, FOC2A, FOC2B, Dummy5, Dummy4, WGM22, CS22, CS21, CS20)
SFR_B_N(0xB0, TCCR2A, COM2A1, COM2A0, COM2B1, COM2B0, Dummy3, Dummy2, WGM21, WGM20)
SFR_W_R(0xAC, OCR4C)
SFR_W_R(0xAA, OCR4B)
SFR_W_R(0xA8, OCR4A)
SFR_W_R(0xA6, ICR4)
SFR_W_R(0xA4, TCNT4)
SFR_B_N(0xA2, TCCR4C, FOC4A, FOC4B, FOC4C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0xA1, TCCR4B, ICNC4, ICES4, Dummy5, WGM43, WGM42, CS42, CS41, CS40)
SFR_B_N(0xA0, TCCR4A, COM4A1, COM4A0, COM4B1, COM4B0, COM4C1, COM4C0, WGM41, WGM40)
SFR_W_R(0x9C, OCR3C)
SFR_W_R(0x9A, OCR3B)
SFR_W_R(0x98, OCR3A)
SFR_W_R(0x96, ICR3)
SFR_W_R(0x94, TCNT3)
SFR_B_N(0x92, TCCR3C, FOC3A, FOC3B, FOC3C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x91, TCCR3B, ICNC3, ICES3, Dummy5, WGM33, WGM32, CS32, CS31, CS30)
SFR_B_N(0x90, TCCR3A, COM3A1, COM3A0, COM3B1, COM3B0, COM3C1, COM3C0, WGM31, WGM30)
SFR_W_R(0x8C, OCR1C)
SFR_W_R(0x8A, OCR1B)
SFR_W_R(0x88, OCR1A)
SFR_W_R(0x86, ICR1)
SFR_W_R(0x84, TCNT1)
SFR_B_N(0x82, TCCR1C, FOC1A, FOC1B, FOC1C, Dummy4, Dummy3, Dummy2, Dummy1, Dummy0)
SFR_B_N(0x81, TCCR1B, ICNC1, ICES1, Dummy5, WGM13, WGM12, CS12, CS11, CS10)
SFR_B_N(0x80, TCCR1A, COM1A1, COM1A0, COM1B1, COM1B0, COM1C1, COM1C0, WGM11, WGM10)
SFR_B_N(0x7F, DIDR1, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, AIN1D, AIN0D)
SFR_B_N(0x7E, DIDR0, ADC7D, ADC6D, ADC5D, ADC4D, ADC3D, ADC2D, ADC1D, ADC0D)
SFR_B_N(0x7D, DIDR2, ADC15D, ADC14D, ADC13D, ADC12D, ADC11D, ADC10D, ADC9D, ADC8D)
SFR_B_N(0x7C, ADMUX, REFS1, REFS0, ADLAR, MUX4, MUX3, MUX2, MUX1, MUX0)
SFR_B_N(0x7B, ADCSRB, Dummy7, ACME, Dummy5, Dummy4, MUX5, ADTS2, ADTS1, ADTS0)
SFR_B_N(0x7A, ADCSRA, ADEN, ADSC, ADATE, ADIF, ADIE, ADPS2, ADPS1, ADPS0)
SFR_W_R(0x78, ADC)
SFR_B_N(0x75, XMCRB, XMBK, Dummy6, Dummy5, Dummy4, Dummy3, XMM2, XMM1, XMM0)
SFR_B_N(0x74, XMCRA, SRE, SRL2, SRL1, SRL0, SRW11, SRW10, SRW01, SRW00)
SFR_B_N(0x73, TIMSK5, Dummy7, Dummy6, ICIE5, Dummy4, OCIE5C, OCIE5B, OCIE5A, TOIE5)
SFR_B_N(0x72, TIMSK4, Dummy7, Dummy6, ICIE4, Dummy4, OCIE4C, OCIE4B, OCIE4A, TOIE4)
SFR_B_N(0x71, TIMSK3, Dummy7, Dummy6, ICIE3, Dummy4, OCIE3C, OCIE3B, OCIE3A, TOIE3)
SFR_B_N(0x70, TIMSK2, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE2B, OCIE2A, TOIE2)
SFR_B_N(0x6F, TIMSK1, Dummy7, Dummy6, ICIE1, Dummy4, OCIE1C, OCIE1B, OCIE1A, TOIE1)
SFR_B_N(0x6E, TIMSK0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCIE0B, OCIE0A, TOIE0)
SFR_B_N(0x6D, PCMSK2, PCINT23, PCINT22, PCINT21, PCINT20, PCINT19, PCINT18, PCINT17, PCINT16)
SFR_B_N(0x6C, PCMSK1, PCINT15, PCINT14, PCINT13, PCINT12, PCINT11, PCINT10, PCINT9, PCINT8)
SFR_B_N(0x6B, PCMSK0, PCINT7, PCINT6, PCINT5, PCINT4, PCINT3, PCINT2, PCINT1, PCINT0)
SFR_B_N(0x6A, EICRB, ISC71, ISC70, ISC61, ISC60, ISC51, ISC50, ISC41, ISC40)
SFR_B_N(0x69, EICRA, ISC31, ISC30, ISC21, ISC20, ISC11, ISC10, ISC01, ISC00)
SFR_B_N(0x68, PCICR, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, PCIE2, PCIE1, PCIE0)
SFR_B_R(0x66, OSCCAL)
SFR_B_N(0x65, PRR1, Dummy7, Dummy6, PRTIM5, PRTIM4, PRTIM3, PRUSART3, PRUSART2, PRUSART1)
SFR_B_N(0x64, PRR0, PRTWI, PRTIM2, PRTIM0, Dummy4, PRTIM1, PRSPI, PRUSART0, PRADC)
SFR_B_N(0x61, CLKPR, CLKPCE, Dummy6, Dummy5, Dummy4, CLKPS3, CLKPS2, CLKPS1, CLKPS0)
SFR_B_N(0x60, WDTCSR, WDIF, WDIE, WDP3, WDCE, WDE, WDP2, WDP1, WDP0)

SFR_B_N(0x3F, SREG, I, T, H, S, V, N, Z, C)
SFR_W_N(0x3D, SP, SP15, SP14, SP13, SP12, SP11, SP10, SP9, SP8, SP7, SP6, SP5, SP4, SP3, SP2, SP1, SP0)
SFR_B_N(0x3C, EIND, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, EIND0)
SFR_B_N(0x3B, RAMPZ, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, RAMPZ1, RAMPZ0)
SFR_B_N(0x37, SPMCSR, SPMIE, RWWSB, SIGRD, RWWSRE, BLBSET, PGWRT, PGERS, SPMEN)
SFR_B_N(0x35, MCUCR, JTD, Dummy6, Dummy5, PUD, Dummy3, Dummy2, IVSEL, IVCE)
SFR_B_N(0x34, MCUSR, Dummy7, Dummy6, Dummy5, JTRF, WDRF, BORF, EXTRF, PORF)
SFR_B_N(0x33, SMCR, Dummy7, Dummy6, Dummy5, Dummy4, SM2, SM1, SM0, SE)
SFR_B2_N(0x31, OCDR, MONDR, OCDR7, OCDR6, OCDR5, OCDR4, OCDR3, OCDR2, OCDR1, OCDR0)
SFR_B_N(0x30, ACSR, ACD, ACBG, ACO, ACI, ACIE, ACIC, ACIS1, ACIS0)
SFR_B_R(0x2E, SPDR)
SFR_B_N(0x2D, SPSR, SPIF, WCOL, Dummy5, Dummy4, Dummy3, Dummy2, Dummy1, SPI2X)
SFR_B_N(0x2C, SPCR, SPIE, SPE, DORD, MSTR, CPOL, CPHA, SPR1, SPR0)
SFR_B_R(0x2B, GPIOR2)
SFR_B_R(0x2A, GPIOR1)
SFR_B_R(0x28, OCR0B)
SFR_B_R(0x27, OCR0A)
SFR_B_R(0x26, TCNT0)
SFR_B_N(0x25, TCCR0B, FOC0A, FOC0B, Dummy5, Dummy4, WGM02, CS02, CS01, CS00)
SFR_B_N(0x24, TCCR0A, COM0A1, COM0A0, COM0B1, COM0B0, Dummy3, Dummy2, WGM01, WGM00)
SFR_B_N(0x23, GTCCR, TSM, Dummy6, Dummy5, Dummy4, Dummy3, Dummy2, PSRASY, PSRSYNC)
SFR_W_R(0x21, EEAR)
SFR_B_R(0x20, EEDR)
SFR_B_N(0x1F, EECR, Dummy7, Dummy6, EEPM1, EEPM0, EERIE, EEMPE, EEPE, EERE)
SFR_B_R(0x1E, GPIOR0)
SFR_B_N(0x1D, EIMSK, INT7, INT6, INT5, INT4, INT3, INT2, INT1, INT0)
SFR_B_N(0x1C, EIFR, INTF7, INTF6, INTF5, INTF4, INTF3, INTF2, INTF1, INTF0)
SFR_B_N(0x1B, PCIFR, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, PCIF2, PCIF1, PCIF0)
SFR_B_N(0x1A, TIFR5, Dummy7, Dummy6, ICF5, Dummy4, OCF5C, OCF5B, OCF5A, TOV5)
SFR_B_N(0x19, TIFR4, Dummy7, Dummy6, ICF4, Dummy4, OCF4C, OCF4B, OCF4A, TOV4)
SFR_B_N(0x18, TIFR3, Dummy7, Dummy6, ICF3, Dummy4, OCF3C, OCF3B, OCF3A, TOV3)
SFR_B_N(0x17, TIFR2, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF2B, OCF2A, TOV2)
SFR_B_N(0x16, TIFR1, Dummy7, Dummy6, ICF1, Dummy4, OCF1C, OCF1B, OCF1A, TOV1)
SFR_B_N(0x15, TIFR0, Dummy7, Dummy6, Dummy5, Dummy4, Dummy3, OCF0B, OCF0A, TOV0)
SFR_B_N(0x14, PORTG, Dummy7, Dummy6, PORTG5, PORTG4, PORTG3, PORTG2, PORTG1, PORTG0)
SFR_B_N(0x13, DDRG, Dummy7, Dummy6, DDG5, DDG4, DDG3, DDG2, DDG1, DDG0)
SFR_B_N(0x12, PING, Dummy7, Dummy6, PING5, PING4, PING3, PING2, PING1, PING0)
SFR_B_N(0x11, PORTF, PORTF7, PORTF6, PORTF5, PORTF4, PORTF3, PORTF2, PORTF1, PORTF0)
SFR_B_N(0x10, DDRF, DDF7, DDF6, DDF5, DDF4, DDF3, DDF2, DDF1, DDF0)
SFR_B_N(0x0F, PINF, PINF7, PINF6, PINF5, PINF4, PINF3, PINF2, PINF1, PINF0)
SFR_B_N(0x0E, PORTE, PORTE7, PORTE6, PORTE5, PORTE4, PORTE3, PORTE2, PORTE1, PORTE0)
SFR_B_N(0x0D, DDRE, DDE7, DDE6, DDE5, DDE4, DDE3, DDE2, DDE1, DDE0)
SFR_B_N(0x0C, PINE, PINE7, PINE6, PINE5, PINE4, PINE3, PINE2, PINE1, PINE0)
SFR_B_N(0x0B, PORTD, PORTD7, PORTD6, PORTD5, PORTD4, PORTD3, PORTD2, PORTD1, PORTD0)
SFR_B_N(0x0A, DDRD, DDD7, DDD6, DDD5, DDD4, DDD3, DDD2, DDD1, DDD0)
SFR_B_N(0x09, PIND, PIND7, PIND6, PIND5, PIND4, PIND3, PIND2, PIND1, PIND0)
SFR_B_N(0x08, PORTC, PORTC7, PORTC6, PORTC5, PORTC4, PORTC3, PORTC2, PORTC1, PORTC0)
SFR_B_N(0x07, DDRC, DDC7, DDC6, DDC5, DDC4, DDC3, DDC2, DDC1, DDC0)
SFR_B_N(0x06, PINC, PINC7, PINC6, PINC5, PINC4, PINC3, PINC2, PINC1, PINC0)
SFR_B_N(0x05, PORTB, PORTB7, PORTB6, PORTB5, PORTB4, PORTB3, PORTB2, PORTB1, PORTB0)
SFR_B_N(0x04, DDRB, DDB7, DDB6, DDB5, DDB4, DDB3, DDB2, DDB1, DDB0)
SFR_B_N(0x03, PINB, PINB7, PINB6, PINB5, PINB4, PINB3, PINB2, PINB1, PINB0)
SFR_B_N(0x02, PORTA, PORTA7, PORTA6, PORTA5, PORTA4, PORTA3, PORTA2, PORTA1, PORTA0)
SFR_B_N(0x01, DDRA, DDA7, DDA6, DDA5, DDA4, DDA3, DDA2, DDA1, DDA0)
SFR_B_N(0x00, PINA, PINA7, PINA6, PINA5, PINA4, PINA3, PINA2, PINA1, PINA0)

#ifndef __IO2560_H
#define __IO2560_H


/* SFRs are local in assembler modules (so this file may need to be */
/* included in more than one module in the same source file), */
/* but #defines must only be made once per source file. */

/*==============================*/
/* Interrupt Vector Definitions */
/*==============================*/

/* NB! vectors are specified as byte addresses */

#define    RESET_vect          (0x00) /* External Pin, Power-on Reset, Brown-out Reset,
                                        Watchdog Reset, and JTAG AVR Reset */
#define    INT0_vect           (0x04) /* External Interrupt Request 0 */
#define    INT1_vect           (0x08) /* External Interrupt Request 1 */
#define    INT2_vect           (0x0C) /* External Interrupt Request 2 */
#define    INT3_vect           (0x10) /* External Interrupt Request 3 */
#define    INT4_vect           (0x14) /* External Interrupt Request 4 */
#define    INT5_vect           (0x18) /* External Interrupt Request 5 */
#define    INT6_vect           (0x1C) /* External Interrupt Request 6 */
#define    INT7_vect           (0x20) /* External Interrupt Request 7 */
#define    PCINT0_vect         (0x24) /* Pin Change Interrupt Request 0 */
#define    PCINT1_vect         (0x28) /* Pin Change Interrupt Request 1 */
#define    PCINT2_vect         (0x2C) /* Pin Change Interrupt Request 2 */
#define    WDT_vect            (0x30) /* Watchdog Time-out Interrupt */
#define    TIMER2_COMPA_vect   (0x34) /* Timer/Counter2 Compare Match A */
#define    TIMER2_COMPB_vect   (0x38) /* Timer/Counter2 Compare Match B */
#define    TIMER2_OVF_vect     (0x3C) /* Timer/Counter2 Overflow */
#define    TIMER1_CAPT_vect    (0x40) /* Timer/Counter1 Capture Event */
#define    TIMER1_COMPA_vect   (0x44) /* Timer/Counter1 Compare Match A */
#define    TIMER1_COMPB_vect   (0x48) /* Timer/Counter1 Compare Match B */
#define    TIMER1_COMPC_vect   (0x4C) /* Timer/Counter1 Compare Match C */
#define    TIMER1_OVF_vect     (0x50) /* Timer/Counter1 Overflow */
#define    TIMER0_COMPA_vect   (0x54) /* Timer/Counter0 Compare Match A */
#define    TIMER0_COMPB_vect   (0x58) /* Timer/Counter0 Compare match B */
#define    TIMER0_OVF_vect     (0x5C) /* Timer/Counter0 Overflow */
#define    SPI_STC_vect        (0x60) /* SPI Serial Transfer Complete */
#define    USART0_RX_vect      (0x64) /* USART0 Rx Complete */
#define    USART0_UDRE_vect    (0x68) /* USART0 Data Register Empty */
#define    USART0_TX_vect      (0x6C) /* USART0 Tx Complete */
#define    ANALOG_COMP_vect    (0x70) /* Analog Comparator */
#define    ADC_vect            (0x74) /* ADC Conversion Complete */
#define    EE_READY_vect       (0x78) /* EEPROM Ready */
#define    TIMER3_CAPT_vect    (0x7C) /* Timer/Counter3 Capture Event */
#define    TIMER3_COMPA_vect   (0x80) /* Timer/Counter3 Compare Match A */
#define    TIMER3_COMPB_vect   (0x84) /* Timer/Counter3 Compare Match B */
#define    TIMER3_COMPC_vect   (0x88) /* Timer/Counter3 Compare Match C */
#define    TIMER3_OVF_vect     (0x8C) /* Timer/Counter3 Overflow */
#define    USART1_RX_vect      (0x90) /* USART1 Rx Complete */
#define    USART1_UDRE_vect    (0x94) /* USART1 Data Register Empty */
#define    USART1_TX_vect      (0x98) /* USART1 Tx Complete */
#define    TWI_vect            (0x9C) /* 2-wire Serial Interface */
#define    SPM_READY_vect      (0xA0) /* Store Program Memory Ready */
#define    TIMER4_CAPT_vect    (0xA4) /* Timer/Counter4 Capture Event */
#define    TIMER4_COMPA_vect   (0xA8) /* Timer/Counter4 Compare Match A */
#define    TIMER4_COMPB_vect   (0xAC) /* Timer/Counter4 Compare Match B */
#define    TIMER4_COMPC_vect   (0xB0) /* Timer/Counter4 Compare Match C */
#define    TIMER4_OVF_vect     (0xB4) /* Timer/Counter4 Overflow */
#define    TIMER5_CAPT_vect    (0xB8) /* Timer/Counter5 Capture Event */
#define    TIMER5_COMPA_vect   (0xBC) /* Timer/Counter5 Compare Match A */
#define    TIMER5_COMPB_vect   (0xC0) /* Timer/Counter5 Compare Match B */
#define    TIMER5_COMPC_vect   (0xC4) /* Timer/Counter5 Compare Match C */
#define    TIMER5_OVF_vect     (0xC8) /* Timer/Counter5 Overflow */
#define    USART2_RX_vect      (0xCC) /* USART2 Rx Complete */
#define    USART2_UDRE_vect    (0xD0) /* USART2 Data Register Empty */
#define    USART2_TX_vect      (0xD4) /* USART2 Tx Complete */
#define    USART3_RX_vect      (0xD8) /* USART3 Rx Complete */
#define    USART3_UDRE_vect    (0xDC) /* USART3 Data Register Empty */
#define    USART3_TX_vect      (0xE0) /* USART3 Tx Complete */

#ifdef __IAR_SYSTEMS_ASM__   
#ifndef ENABLE_BIT_DEFINITIONS
#define  ENABLE_BIT_DEFINITIONS
#endif /* ENABLE_BIT_DEFINITIONS */
#endif /* __IAR_SYSTEMS_ASM__ */

#ifdef ENABLE_BIT_DEFINITIONS


/* Bit definitions for use with the IAR Assembler   
   The Register Bit names are represented by their bit number (0-7).
*/


  /* UCSR3C */
#define UMSEL31 7
#define UMSEL30 6
#define UPM31 5
#define UPM30 4
#define USBS3 3
#define UCSZ31 2
#define UCSZ30 1
#define UCPOL3 0

  /* UCSR3B */
#define RXCIE3 7
#define TXCIE3 6
#define UDRIE3 5
#define RXEN3 4
#define TXEN3 3
#define UCSZ32 2
#define RXB83 1
#define TXB83 0

  /* UCSR3A */
#define RXC3 7
#define TXC3 6
#define UDRE3 5
#define FE3 4
#define DOR3 3
#define PE3 2
#define U2X3 1
#define MPCM3 0

  /* TCCR5C */
#define FOC5A 7
#define FOC5B 6
#define FOC5C 5

  /* TCCR5B */
#define ICNC5 7
#define ICES5 6
#define WGM53 4
#define WGM52 3
#define CS52 2
#define CS51 1
#define CS50 0

  /* TCCR5A */
#define COM5A1 7
#define COM5A0 6
#define COM5B1 5
#define COM5B0 4
#define COM5C1 3
#define COM5C0 2
#define WGM51 1
#define WGM50 0

  /* PORTL */
#define PORTL7 7
#define PORTL6 6
#define PORTL5 5
#define PORTL4 4
#define PORTL3 3
#define PORTL2 2
#define PORTL1 1
#define PORTL0 0

  /* PL */
#define PL7 7
#define PL6 6
#define PL5 5
#define PL4 4
#define PL3 3
#define PL2 2
#define PL1 1
#define PL0 0

  /* DDRL */
#define DDL7 7
#define DDL6 6
#define DDL5 5
#define DDL4 4
#define DDL3 3
#define DDL2 2
#define DDL1 1
#define DDL0 0

  /* PINL */
#define PINL7 7
#define PINL6 6
#define PINL5 5
#define PINL4 4
#define PINL3 3
#define PINL2 2
#define PINL1 1
#define PINL0 0

  /* PORTK */
#define PORTK7 7
#define PORTK6 6
#define PORTK5 5
#define PORTK4 4
#define PORTK3 3
#define PORTK2 2
#define PORTK1 1
#define PORTK0 0

  /* PK */
#define PK7 7
#define PK6 6
#define PK5 5
#define PK4 4
#define PK3 3
#define PK2 2
#define PK1 1
#define PK0 0

  /* DDRK */
#define DDK7 7
#define DDK6 6
#define DDK5 5
#define DDK4 4
#define DDK3 3
#define DDK2 2
#define DDK1 1
#define DDK0 0

  /* PINK */
#define PINK7 7
#define PINK6 6
#define PINK5 5
#define PINK4 4
#define PINK3 3
#define PINK2 2
#define PINK1 1
#define PINK0 0

  /* PORTJ */
#define PORTJ7 7
#define PORTJ6 6
#define PORTJ5 5
#define PORTJ4 4
#define PORTJ3 3
#define PORTJ2 2
#define PORTJ1 1
#define PORTJ0 0

  /* PJ */
#define PJ7 7
#define PJ6 6
#define PJ5 5
#define PJ4 4
#define PJ3 3
#define PJ2 2
#define PJ1 1
#define PJ0 0

  /* DDRJ */
#define DDJ7 7
#define DDJ6 6
#define DDJ5 5
#define DDJ4 4
#define DDJ3 3
#define DDJ2 2
#define DDJ1 1
#define DDJ0 0

  /* PINJ */
#define PINJ7 7
#define PINJ6 6
#define PINJ5 5
#define PINJ4 4
#define PINJ3 3
#define PINJ2 2
#define PINJ1 1
#define PINJ0 0

  /* PORTH */
#define PORTH7 7
#define PORTH6 6
#define PORTH5 5
#define PORTH4 4
#define PORTH3 3
#define PORTH2 2
#define PORTH1 1
#define PORTH0 0

  /* PH */
#define PH7 7
#define PH6 6
#define PH5 5
#define PH4 4
#define PH3 3
#define PH2 2
#define PH1 1
#define PH0 0

  /* DDRH */
#define DDH7 7
#define DDH6 6
#define DDH5 5
#define DDH4 4
#define DDH3 3
#define DDH2 2
#define DDH1 1
#define DDH0 0

  /* PINH */
#define PINH7 7
#define PINH6 6
#define PINH5 5
#define PINH4 4
#define PINH3 3
#define PINH2 2
#define PINH1 1
#define PINH0 0

  /* UCSR2C */
#define UMSEL21 7
#define UMSEL20 6
#define UPM21 5
#define UPM20 4
#define USBS2 3
#define UCSZ21 2
#define UCSZ20 1
#define UCPOL2 0

  /* UCSR2B */
#define RXCIE2 7
#define TXCIE2 6
#define UDRIE2 5
#define RXEN2 4
#define TXEN2 3
#define UCSZ22 2
#define RXB82 1
#define TXB82 0

  /* UCSR2A */
#define RXC2 7
#define TXC2 6
#define UDRE2 5
#define FE2 4
#define DOR2 3
#define PE2 2
#define U2X2 1
#define MPCM2 0

  /* UCSR1C */
#define UMSEL11 7
#define UMSEL10 6
#define UPM11 5
#define UPM10 4
#define USBS1 3
#define UCSZ11 2
#define UCSZ10 1
#define UCPOL1 0

  /* UCSR1B */
#define RXCIE1 7
#define TXCIE1 6
#define UDRIE1 5
#define RXEN1 4
#define TXEN1 3
#define UCSZ12 2
#define RXB81 1
#define TXB81 0

  /* UCSR1A */
#define RXC1 7
#define TXC1 6
#define UDRE1 5
#define FE1 4
#define DOR1 3
#define PE1 2
#define U2X1 1
#define MPCM1 0

  /* UCSR0C */
#define UMSEL01 7
#define UMSEL00 6
#define UPM01 5
#define UPM00 4
#define USBS0 3
#define UCSZ01 2
#define UCSZ00 1
#define UCPOL0 0

  /* UCSR0B */
#define RXCIE0 7
#define TXCIE0 6
#define UDRIE0 5
#define RXEN0 4
#define TXEN0 3
#define UCSZ02 2
#define RXB80 1
#define TXB80 0

  /* UCSR0A */
#define RXC0 7
#define TXC0 6
#define UDRE0 5
#define FE0 4
#define DOR0 3
#define PE0 2
#define U2X0 1
#define MPCM0 0

  /* TWAMR */
#define TWAM6 7
#define TWAM5 6
#define TWAM4 5
#define TWAM3 4
#define TWAM2 3
#define TWAM1 2
#define TWAM0 1

  /* TWCR */
#define TWINT 7
#define TWEA 6
#define TWSTA 5
#define TWSTO 4
#define TWWC 3
#define TWEN 2
#define TWIE 0

  /* TWAR */
#define TWA6 7
#define TWA5 6
#define TWA4 5
#define TWA3 4
#define TWA2 3
#define TWA1 2
#define TWA0 1
#define TWGCE 0

  /* TWSR */
#define TWS7 7
#define TWS6 6
#define TWS5 5
#define TWS4 4
#define TWS3 3
#define TWPS1 1
#define TWPS0 0

  /* ASSR */
#define EXCLK 6
#define AS2 5
#define TCN2UB 4
#define OCR2AUB 3
#define OCR2BUB 2
#define TCR2AUB 1
#define TCR2BUB 0

  /* TCCR2B */
#define FOC2A 7
#define FOC2B 6
#define WGM22 3
#define CS22 2
#define CS21 1
#define CS20 0

  /* TCCR2A */
#define COM2A1 7
#define COM2A0 6
#define COM2B1 5
#define COM2B0 4
#define WGM21 1
#define WGM20 0

  /* TCCR4C */
#define FOC4A 7
#define FOC4B 6
#define FOC4C 5

  /* TCCR4B */
#define ICNC4 7
#define ICES4 6
#define WGM43 4
#define WGM42 3
#define CS42 2
#define CS41 1
#define CS40 0

  /* TCCR4A */
#define COM4A1 7
#define COM4A0 6
#define COM4B1 5
#define COM4B0 4
#define COM4C1 3
#define COM4C0 2
#define WGM41 1
#define WGM40 0

  /* TCCR3C */
#define FOC3A 7
#define FOC3B 6
#define FOC3C 5

  /* TCCR3B */
#define ICNC3 7
#define ICES3 6
#define WGM33 4
#define WGM32 3
#define CS32 2
#define CS31 1
#define CS30 0

  /* TCCR3A */
#define COM3A1 7
#define COM3A0 6
#define COM3B1 5
#define COM3B0 4
#define COM3C1 3
#define COM3C0 2
#define WGM31 1
#define WGM30 0

  /* TCCR1C */
#define FOC1A 7
#define FOC1B 6
#define FOC1C 5

  /* TCCR1B */
#define ICNC1 7
#define ICES1 6
#define WGM13 4
#define WGM12 3
#define CS12 2
#define CS11 1
#define CS10 0

  /* TCCR1A */
#define COM1A1 7
#define COM1A0 6
#define COM1B1 5
#define COM1B0 4
#define COM1C1 3
#define COM1C0 2
#define WGM11 1
#define WGM10 0

  /* DIDR1 */
#define AIN1D 1
#define AIN0D 0

  /* DIDR0 */
#define ADC7D 7
#define ADC6D 6
#define ADC5D 5
#define ADC4D 4
#define ADC3D 3
#define ADC2D 2
#define ADC1D 1
#define ADC0D 0

  /* DIDR2 */
#define ADC15D 7
#define ADC14D 6
#define ADC13D 5
#define ADC12D 4
#define ADC11D 3
#define ADC10D 2
#define ADC9D 1
#define ADC8D 0

  /* ADMUX */
#define REFS1 7
#define REFS0 6
#define ADLAR 5
#define MUX4 4
#define MUX3 3
#define MUX2 2
#define MUX1 1
#define MUX0 0

  /* ADCSRB */
#define ACME 6
#define MUX5 3
#define ADTS2 2
#define ADTS1 1
#define ADTS0 0

  /* ADCSRA */
#define ADEN 7
#define ADSC 6
#define ADATE 5
#define ADIF 4
#define ADIE 3
#define ADPS2 2
#define ADPS1 1
#define ADPS0 0

  /* XMCRB */
#define XMBK 7
#define XMM2 2
#define XMM1 1
#define XMM0 0

  /* XMCRA */
#define SRE 7
#define SRL2 6
#define SRL1 5
#define SRL0 4
#define SRW11 3
#define SRW10 2
#define SRW01 1
#define SRW00 0

  /* TIMSK5 */
#define ICIE5 5
#define OCIE5C 3
#define OCIE5B 2
#define OCIE5A 1
#define TOIE5 0

  /* TIMSK4 */
#define ICIE4 5
#define OCIE4C 3
#define OCIE4B 2
#define OCIE4A 1
#define TOIE4 0

  /* TIMSK3 */
#define ICIE3 5
#define OCIE3C 3
#define OCIE3B 2
#define OCIE3A 1
#define TOIE3 0

  /* TIMSK2 */
#define OCIE2B 2
#define OCIE2A 1
#define TOIE2 0

  /* TIMSK1 */
#define ICIE1 5
#define OCIE1C 3
#define OCIE1B 2
#define OCIE1A 1
#define TOIE1 0

  /* TIMSK0 */
#define OCIE0B 2
#define OCIE0A 1
#define TOIE0 0

  /* PCMSK2 */
#define PCINT23 7
#define PCINT22 6
#define PCINT21 5
#define PCINT20 4
#define PCINT19 3
#define PCINT18 2
#define PCINT17 1
#define PCINT16 0

  /* PCMSK1 */
#define PCINT15 7
#define PCINT14 6
#define PCINT13 5
#define PCINT12 4
#define PCINT11 3
#define PCINT10 2
#define PCINT9 1
#define PCINT8 0

  /* PCMSK0 */
#define PCINT7 7
#define PCINT6 6
#define PCINT5 5
#define PCINT4 4
#define PCINT3 3
#define PCINT2 2
#define PCINT1 1
#define PCINT0 0

  /* EICRB */
#define ISC71 7
#define ISC70 6
#define ISC61 5
#define ISC60 4
#define ISC51 3
#define ISC50 2
#define ISC41 1
#define ISC40 0

  /* EICRA */
#define ISC31 7
#define ISC30 6
#define ISC21 5
#define ISC20 4
#define ISC11 3
#define ISC10 2
#define ISC01 1
#define ISC00 0

  /* PCICR */
#define PCIE2 2
#define PCIE1 1
#define PCIE0 0

  /* PRR1 */
#define PRTIM5 5
#define PRTIM4 4
#define PRTIM3 3
#define PRUSART3 2
#define PRUSART2 1
#define PRUSART1 0

  /* PRR0 */
#define PRTWI 7
#define PRTIM2 6
#define PRTIM0 5
#define PRTIM1 3
#define PRSPI 2
#define PRUSART0 1
#define PRADC 0

  /* CLKPR */
#define CLKPCE 7
#define CLKPS3 3
#define CLKPS2 2
#define CLKPS1 1
#define CLKPS0 0

  /* WDTCSR */
#define WDIF 7
#define WDIE 6
#define WDP3 5
#define WDCE 4
#define WDE 3
#define WDP2 2
#define WDP1 1
#define WDP0 0

  /* SPH */
#define SP15 7
#define SP14 6
#define SP13 5
#define SP12 4
#define SP11 3
#define SP10 2
#define SP9 1
#define SP8 0

  /* SPL */
#define SP7 7
#define SP6 6
#define SP5 5
#define SP4 4
#define SP3 3
#define SP2 2
#define SP1 1
#define SP0 0

  /* EIND */
#define EIND0 0

  /* RAMPZ */
#define RAMPZ1 1
#define RAMPZ0 0

  /* SPMCSR */
#define SPMIE 7
#define RWWSB 6
#define SIGRD 5
#define RWWSRE 4
#define BLBSET 3
#define PGWRT 2
#define PGERS 1
#define SPMEN 0

  /* MCUCR */
#define JTD 7
#define PUD 4
#define IVSEL 1
#define IVCE 0

  /* MCUSR */
#define JTRF 4
#define WDRF 3
#define BORF 2
#define EXTRF 1
#define PORF 0

  /* SMCR */
#define SM2 3
#define SM1 2
#define SM0 1
#define SE 0

  /* OCDRM/ONDR */
#define OCDR7 7
#define OCDR6 6
#define OCDR5 5
#define OCDR4 4
#define OCDR3 3
#define OCDR2 2
#define OCDR1 1
#define OCDR0 0

  /* ACSR */
#define ACD 7
#define ACBG 6
#define ACO 5
#define ACI 4
#define ACIE 3
#define ACIC 2
#define ACIS1 1
#define ACIS0 0

  /* SPSR */
#define SPIF 7
#define WCOL 6
#define SPI2X 0

  /* SPCR */
#define SPIE 7
#define SPE 6
#define DORD 5
#define MSTR 4
#define CPOL 3
#define CPHA 2
#define SPR1 1
#define SPR0 0

  /* TCCR0B */
#define FOC0A 7
#define FOC0B 6
#define WGM02 3
#define CS02 2
#define CS01 1
#define CS00 0

  /* TCCR0A */
#define COM0A1 7
#define COM0A0 6
#define COM0B1 5
#define COM0B0 4
#define WGM01 1
#define WGM00 0

  /* GTCCR */
#define TSM 7
#define PSRASY 1
#define PSRSYNC 0

  /* EECR */
#define EEPM1 5
#define EEPM0 4
#define EERIE 3
#define EEMPE 2
#define EEPE 1
#define EERE 0

  /* EIMSK */
#define INT7 7
#define INT6 6
#define INT5 5
#define INT4 4
#define INT3 3
#define INT2 2
#define INT1 1
#define INT0 0

  /* EIFR */
#define INTF7 7
#define INTF6 6
#define INTF5 5
#define INTF4 4
#define INTF3 3
#define INTF2 2
#define INTF1 1
#define INTF0 0

  /* PCIFR */
#define PCIF2 2
#define PCIF1 1
#define PCIF0 0

  /* TIFR5 */
#define ICF5 5
#define OCF5C 3
#define OCF5B 2
#define OCF5A 1
#define TOV5 0

  /* TIFR4 */
#define ICF4 5
#define OCF4C 3
#define OCF4B 2
#define OCF4A 1
#define TOV4 0

  /* TIFR3 */
#define ICF3 5
#define OCF3C 3
#define OCF3B 2
#define OCF3A 1
#define TOV3 0

  /* TIFR2 */
#define OCF2B 2
#define OCF2A 1
#define TOV2 0

  /* TIFR1 */
#define ICF1 5
#define OCF1C 3
#define OCF1B 2
#define OCF1A 1
#define TOV1 0

  /* TIFR0 */
#define OCF0B 2
#define OCF0A 1
#define TOV0 0

  /* PORTG */
#define PORTG5 5
#define PORTG4 4
#define PORTG3 3
#define PORTG2 2
#define PORTG1 1
#define PORTG0 0

  /* PG */
#define PG5 5
#define PG4 4
#define PG3 3
#define PG2 2
#define PG1 1
#define PG0 0

  /* DDRG */
#define DDG5 5
#define DDG4 4
#define DDG3 3
#define DDG2 2
#define DDG1 1
#define DDG0 0

  /* PING */
#define PING5 5
#define PING4 4
#define PING3 3
#define PING2 2
#define PING1 1
#define PING0 0

  /* PORTF */
#define PORTF7 7
#define PORTF6 6
#define PORTF5 5
#define PORTF4 4
#define PORTF3 3
#define PORTF2 2
#define PORTF1 1
#define PORTF0 0

  /* PF */
#define PF7 7
#define PF6 6
#define PF5 5
#define PF4 4
#define PF3 3
#define PF2 2
#define PF1 1
#define PF0 0

  /* DDRF */
#define DDF7 7
#define DDF6 6
#define DDF5 5
#define DDF4 4
#define DDF3 3
#define DDF2 2
#define DDF1 1
#define DDF0 0

  /* PINF */
#define PINF7 7
#define PINF6 6
#define PINF5 5
#define PINF4 4
#define PINF3 3
#define PINF2 2
#define PINF1 1
#define PINF0 0

  /* PORTE */
#define PORTE7 7
#define PORTE6 6
#define PORTE5 5
#define PORTE4 4
#define PORTE3 3
#define PORTE2 2
#define PORTE1 1
#define PORTE0 0

  /* PE */
/*
#define PE7 7
#define PE6 6
#define PE5 5
#define PE4 4
#define PE3 3
#define PE2 2
#define PE1 1
#define PE0 0
*/
  /* DDRE */
#define DDE7 7
#define DDE6 6
#define DDE5 5
#define DDE4 4
#define DDE3 3
#define DDE2 2
#define DDE1 1
#define DDE0 0

  /* PINE */
#define PINE7 7
#define PINE6 6
#define PINE5 5
#define PINE4 4
#define PINE3 3
#define PINE2 2
#define PINE1 1
#define PINE0 0

  /* PORTD */
#define PORTD7 7
#define PORTD6 6
#define PORTD5 5
#define PORTD4 4
#define PORTD3 3
#define PORTD2 2
#define PORTD1 1
#define PORTD0 0

  /* PD */
#define PD7 7
#define PD6 6
#define PD5 5
#define PD4 4
#define PD3 3
#define PD2 2
#define PD1 1
#define PD0 0

  /* DDRD */
#define DDD7 7
#define DDD6 6
#define DDD5 5
#define DDD4 4
#define DDD3 3
#define DDD2 2
#define DDD1 1
#define DDD0 0

  /* PIND */
#define PIND7 7
#define PIND6 6
#define PIND5 5
#define PIND4 4
#define PIND3 3
#define PIND2 2
#define PIND1 1
#define PIND0 0

  /* PORTC */
#define PORTC7 7
#define PORTC6 6
#define PORTC5 5
#define PORTC4 4
#define PORTC3 3
#define PORTC2 2
#define PORTC1 1
#define PORTC0 0

  /* PC */
#define PC7 7
#define PC6 6
#define PC5 5
#define PC4 4
#define PC3 3
#define PC2 2
#define PC1 1
#define PC0 0

  /* DDRC */
#define DDC7 7
#define DDC6 6
#define DDC5 5
#define DDC4 4
#define DDC3 3
#define DDC2 2
#define DDC1 1
#define DDC0 0

  /* PINC */
#define PINC7 7
#define PINC6 6
#define PINC5 5
#define PINC4 4
#define PINC3 3
#define PINC2 2
#define PINC1 1
#define PINC0 0

  /* PORTB */
#define PORTB7 7
#define PORTB6 6
#define PORTB5 5
#define PORTB4 4
#define PORTB3 3
#define PORTB2 2
#define PORTB1 1
#define PORTB0 0

  /* PB */
#define PB7 7
#define PB6 6
#define PB5 5
#define PB4 4
#define PB3 3
#define PB2 2
#define PB1 1
#define PB0 0

  /* DDRB */
#define DDB7 7
#define DDB6 6
#define DDB5 5
#define DDB4 4
#define DDB3 3
#define DDB2 2
#define DDB1 1
#define DDB0 0

  /* PINB */
#define PINB7 7
#define PINB6 6
#define PINB5 5
#define PINB4 4
#define PINB3 3
#define PINB2 2
#define PINB1 1
#define PINB0 0

  /* PORTA */
#define PORTA7 7
#define PORTA6 6
#define PORTA5 5
#define PORTA4 4
#define PORTA3 3
#define PORTA2 2
#define PORTA1 1
#define PORTA0 0

  /* PA */
#define PA7 7
#define PA6 6
#define PA5 5
#define PA4 4
#define PA3 3
#define PA2 2
#define PA1 1
#define PA0 0

  /* DDRA */
#define DDA7 7
#define DDA6 6
#define DDA5 5
#define DDA4 4
#define DDA3 3
#define DDA2 2
#define DDA1 1
#define DDA0 0

  /* PINA */
#define PINA7 7
#define PINA6 6
#define PINA5 5
#define PINA4 4
#define PINA3 3
#define PINA2 2
#define PINA1 1
#define PINA0 0



/* Pointer definition */
#define    XL     r26
#define    XH     r27
#define    YL     r28
#define    YH     r29
#define    ZL     r30
#define    ZH     r31

/* Contants */
#define    RAMEND   0x10FF    /*Last On-Chip SRAM location*/
#define    XRAMEND  0xFFFF
#define    E2END    0x0FFF
#define    FLASHEND 0x1FFFF

#endif /* ENABLE_BIT_DEFINITIONS */ 
#endif /* __IO2560_H (define part) */
#endif /* __IO2560_H (SFR part) */
