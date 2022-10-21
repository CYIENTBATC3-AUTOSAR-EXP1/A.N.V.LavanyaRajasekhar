/*
 * File:   MCAL.c
 * Author: an69572
 *
 * Created on October 20, 2022, 11:53 AM
 */

/* MCAL LAYER */
#include <xc.h>
#define _XTAL_FREQ 20000000
#include "CAN_DRIVER.h"
#include "CAN_DRIVER_CONFIG.h"
#include "CAN_IF.h"

void CAN_DRIVER(char Frame_type,int ID,char DLC,char* CAN_SEND_MESSAGE)
{
    sys_init();
    can_init();
    can_config();
    
    if(Frame_type)    /* Standard Mode */
    { 
    TXB0DLC=0X01;
    TXB0D0=CAN_SEND_MESSAGE[0] ;
    TXB0D1=CAN_SEND_MESSAGE[1];
    TXB0D2=CAN_SEND_MESSAGE[2];
    TXB0D3=CAN_SEND_MESSAGE[3]; 
    TXB0D4=CAN_READ_MESSAGE[4];
    TXB0D5=CAN_SEND_MESSAGE[5]; 
    TXB0D6=CAN_SEND_MESSAGE[6];
    TXB0D7=CAN_SEND_MESSAGE[7];  
    TXB0CON=0X08;
    CANCON=0X08;/*normal mode for transmission buffer 0 register */
    __delay_ms(1000); 
    }
    
}
void sys_init()
{
/*ALL INTERRUPTS INITIALIZED HERE & SYSTEM RELATED INITIALISATIONS DONE HERE */
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}
void can_init()
{
    TRISBbits.RB2=0;  /*tx pins by defalut to pic controller*/
    TRISBbits.RB3=1;  /*rx pins by defalut to pic controller*/
    
    TRISBbits.RB7= 0; /*LED IS CONNECTING AT PORTA BIT 7 O/P for checking interrupt */
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

