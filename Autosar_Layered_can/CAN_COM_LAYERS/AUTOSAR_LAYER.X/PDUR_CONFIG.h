/* 
 * File:   PDUR_CONFIG.h
 * Author: an69572
 *
 * Created on October 20, 2022, 11:27 PM
 */

#ifndef PDUR_CONFIG_H
#define	PDUR_CONFIG_H
const int PDUR_MSG_ID[4] = {
        0x100,
        0x010,
        0x150,
        0x200
    };
    /* Data Length Code */
     const int PDUR_DLC[4] = {
        5,
        7,
        8,
        4
    };
     
     const char PDUR_Frame[4]={
         1,
         1,
         1,
         1
     };
    
/* Function Definitions */
//void Take_CAN_RX_Index(int ID,char DLC,char* Data);


#endif	/* PDUR_CONFIG_H */

