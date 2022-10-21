/* 
 * File:   CAN_IF_CONFIG.h
 * Author: an69572
 *
 * Created on October 21, 2022, 12:16 AM
 */

#ifndef CAN_IF_CONFIG_H
#define	CAN_IF_CONFIG_H
#include "PDUR_CONFIG.h"
#include "COM_CONFIG.h"
const char Driver_Sel[4]={
        1,
        1,
        1,
        1
    }; 
void CAN_FRAME(PDUR_COM_MSg_list_E Msg_no,char* Data);


void   CAN_DRIVER(PDUR_COM_MSg_list_E Msg_no,int CAN_ID,char CAN_DLC,char* Data);
#endif	/* CAN_IF_CONFIG_H */

