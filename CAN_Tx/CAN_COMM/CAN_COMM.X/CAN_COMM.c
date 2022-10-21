/*
 * File:   CAN_COMM.c
 * Author: an69572
 *
 * Created on October 11, 2022, 5:23 PM
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
#define LED_ON           1//mm
#define LED_OFF          0//mm
#define _XTAL_FREQ 20000000
#define BAUD 250000
#include <xc.h>

void main(void) 
{
    //SYS_INIT
    
    
    //CAN_INIT
    
     TRISB2=0;
     TRISB3=1;
//            
     //SET MODE
    
          CANCON=0X80; //CONFIGURATION MODE  
           //BRGCON1: BAUD RATE CONTROL REGISTER 1
                BRGCON1=0XC1;
                BRGCON2=0XAE;
                BRGCON3=0X45;
//          //CAN MODULE I/O CONTROL REGISTER
                CIOCON=0X00;
          CANCON=0X08;//NORMAL MODE FOR TRANSMISSION...
          
                  
  
         while(1)
         {        
     //MASK AND FILTER
          
                  
       //TRANSMISSION DATA WRITE
       //SET MESSAGE IDS:
          unsigned char ID=0X7F;
          unsigned char DL=((ID<<5) & 0xFF);
          unsigned char HL=((ID>>3) & 0xFF);
          
        //TRANSMISSION IDENTIFIOER BUFFERS...
         TXB0SIDH=HL;
         TXB0SIDL=DL;
         
         //DLC REGISTERS
       
         TXB0DLC=0X01;//1byte DLC.
       
         TXB0D0=0x01;
           TXB0D1=0x00;
             TXB0D2=0x00;
               TXB0D3=0x00; 
               TXB0D4=0x00;
                 TXB0D5=0x00; 
                 TXB0D6=0x00;
                   TXB0D7=0x00;
                 
         
         TXB0CON=0X08;//
        
          CANCON=0X08;
          __delay_ms(500);
         }
    return;
}
