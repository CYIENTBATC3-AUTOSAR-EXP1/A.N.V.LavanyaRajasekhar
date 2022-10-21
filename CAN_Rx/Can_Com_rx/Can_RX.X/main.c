/*
 * File:   main.c
 * Author: an69572
 *
 * Created on October 18, 2022, 3:09 PM
 */

// PIC18F458 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 25        // Brown-out Reset Voltage bits (VBOR set to 2.5V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)

// CONFIG4L
#pragma config STVR = OFF       // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will not cause Reset)
#pragma config LVP = OFF        // Low-Voltage ICSP Enable bit (Low-Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 20000000

void sys_init();
void can_init();
void can_config();
void read_can();
void tx_data();

unsigned char CAN_READ_MESSAGE[8];
int flag=0;
void __interrupt() ISR1()
{
//flag=1;
        if(PIR3bits.RXB0IF==1) /*this check data check in rx buffer*/
        {
         PIR3bits.RXB0IF=0;
         flag = 1;
         
        }
        
}
void main(void)
{ 
    sys_init();
    can_init();
    can_config();
    
//    tx_data();
    while(1)
    {
        tx_data();
        if(flag)
        {
            read_can();
            flag=0;          
            __delay_ms(500);
            PORTBbits.RB6 = ~(PORTBbits.RB6); 
        }         
    }
    
}

void sys_init()
{
/*ALL INTERRUPTS INITIALIZED HERE & SYSTEM RELATED INITIALISATIONS DONE HERE
 */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}

void can_init()
{
    TRISBbits.RB2=0;//tx pins by defalut to pic controller
    TRISBbits.RB3=1;//rx pins by defalut to pic controller
    TRISBbits.RB7= 0;  /* LED IS CONNECTING AT PORTA BIT 7 O/P for checking interrupt*/
    TRISBbits.RB6= 0;
}
void can_config()
{
    /*CONFIGURATION MODE BOTHE TX BUFFER 0 AND RX BUFFER 0..*/
    CANCON= 0x80;
    /*baud rate*/
    BRGCON1=0XC1;
    BRGCON2=0XAE;
    BRGCON3=0XA5;
    /*message id loading in to rx buffers*/
    unsigned char IDL;
    unsigned char IDH;
    IDH=RXB0SIDH;//TXBOSIDH=RXBOSIDH
    IDL=RXB0SIDL;//TXBOSIDL=RXBOSIDL
    /*can control register*/
    CIOCON=0x20;
    /*MADE NORMAL MODE AFTER CONFIGURATION*/  
    CANCON=0X0E;
    PIE3bits.RXB0IE=1;
    IPR3bits.RXB0IP =1;
   /*Filter registers*/
    RXF0SIDH=0x00;
    RXF0SIDL=0x00;
    /*MASK Registers*/
    RXM0SIDH=0x00;
    RXM0SIDL=0x00; 
}
void read_can()
{
    CANCON = 0X0E;//normal mode for receive buffer 0
    CAN_READ_MESSAGE[0]= RXB0D0;
    CAN_READ_MESSAGE[1]= RXB0D1;
    CAN_READ_MESSAGE[2]= RXB0D2;
    CAN_READ_MESSAGE[3]= RXB0D3;
    CAN_READ_MESSAGE[4]= RXB0D4;
    CAN_READ_MESSAGE[5]= RXB0D5;
    CAN_READ_MESSAGE[6]= RXB0D6;
    CAN_READ_MESSAGE[7]= RXB0D7; 
    RXB0CONbits.RXB0FUL = 0; //clearing buffer to accept another message 
}
void tx_data()
{
    unsigned char ID=0X7F;
    unsigned char DL=((ID<<5) & 0xFF);
    unsigned char HL=((ID>>3) & 0xFF);
    TXB0SIDH=HL;
    TXB0SIDL=DL;
    TXB0DLC=0X01;
    TXB0D0=0x01 ;
    TXB0D1=0x02;
    TXB0D2=0x03;
    TXB0D3=0x04; 
    TXB0D4=0x05;
    TXB0D5=0x06; 
    TXB0D6=0x07;
    TXB0D7=0x08;  
    TXB0CON=0X08;
    CANCON=0X08;/*normal mode for transmission buffer 0 register */
    __delay_ms(1000);
  
}

