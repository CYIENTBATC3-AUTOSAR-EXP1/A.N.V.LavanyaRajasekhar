/*
 * File:   pdur.c
 * Author: an69572
 *
 * Created on October 20, 2022, 12:28 PM
 */

#include <xc.h>
#define _XTAL_FREQ 20000000
#include "CAN_IF.h"
#include "PDUR.h"
#include "CAN_COM.h"
#include "PDUR_CONFIG.h"

void CAN_FRAME(PDUR_COM_MSg_list_E Msg_no,char CAN_SEND_MESSAGE[])
{
       CAN_IF(Msg_no,PDUR_MSG_ID[Msg_no],PDUR_DLC[Msg_no],CAN_SEND_MESSAGE);
       return;
}

