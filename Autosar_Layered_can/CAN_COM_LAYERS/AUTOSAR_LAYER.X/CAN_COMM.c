/*
 * File:   com.c
 * Author: an69572
 *
 * Created on October 20, 2022, 12:30 PM
 */

/* SERVICE LAYER  COMMUNICATION SUB LAYER  AUTOSAR COM MODULE*/
#include <xc.h>
#define _XTAL_FREQ 20000000
#include "RTE.h"
#include "CAN_COM.h"
#include "COM_CONFIG.h"
#include "PDUR.h"

void AUTOSAR_COM(int CAN_SIG,int Value)
{
    CAN_FRAME(PDUR_COM_MSg_list_E Msg_no,char CAN_SEND_MESSAGE[]);
}

