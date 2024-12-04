/*
 * CANRxIsr.c
 *
 *  Created on: Nov 29, 2024
 *      Author: YiJie
 */

#include "CANRxIsr.h"
#include "DAVE.h"

void CanRxIsr(void  *arg){
	 static uint8_t inBlowerSpeedCmd;
	 static uint8_t inRightTempCmd;
     static uint8_t inLeftTempCmd;

     int32_t CANstatus;
     extern osMessageQId message_q_id;

     CANstatus = CAN_NODE_MO_GetStatus(&BcmNode_LMO_01_Config);


     if (CANstatus & XMC_CAN_MO_STATUS_RX_PENDING){
    	 CAN_NODE_MO_ClearStatus(&BcmNode_LMO_01_Config, XMC_CAN_MO_RESET_STATUS_RX_PENDING);

         CAN_NODE_MO_Receive(&BcmNode_LMO_01_Config);

         inLeftTempCmd = BcmNode_LMO_01_Config.mo_ptr->can_data_byte[4] & 0x3F;
       	 inRightTempCmd = BcmNode_LMO_01_Config.mo_ptr->can_data_byte[5]  & 0x3F;
       	 inBlowerSpeedCmd = BcmNode_LMO_01_Config.mo_ptr->can_data_byte[6] & 0x0F;
      	 inBlowerSpeedCmd &= 0x07;

      	 osMessagePut(message_q_id, inBlowerSpeedCmd, 0);
     }
}
