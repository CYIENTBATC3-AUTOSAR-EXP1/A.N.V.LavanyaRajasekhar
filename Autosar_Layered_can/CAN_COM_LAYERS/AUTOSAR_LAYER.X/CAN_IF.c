/*
 * File:   ECAL.c
 * Author: an69572
 *
 * Created on October 20, 2022, 12:02 PM
 */

/*  ECU ABSRTACTION LAYER */
#include <xc.h>
#define _XTAL_FREQ 20000000
#include "CAN_DRIVER.h"
#include "CAN_IF.h"
#include "PDUR.h"
#include "CAN_IF_CONFIG.h"

void CAN_IF(PDUR_COM_MSg_list_E Msg_no,int CAN_ID,char CAN_DLC,char CAN_SEND_MESSAGE[])
{
    CAN_DRIVER(PDUR_Frame[Msg_no],CAN_ID,CAN_DLC,CAN_SEND_MESSAGE);
    return;
}
