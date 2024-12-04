/*
 * BlowerSpeedCtrl.c
 *
 *  Created on: Sep 26, 2024
 *      Author: YiJie
 */

#include "BlowerSpeedCtrl.h"
#include "DAVE.h"

void runBlowerSpeedCtrl(void *arg){

    static uint8_t inBlowerSpeedCmd;
	static uint8_t inRightTempCmd;
	static uint8_t inLeftTempCmd;
	osEvent event;
	extern osMessageQId message_q_id;

    int32_t CANstatus;

    while(1){
    	event = osMessageGet(message_q_id, osWaitForever);
    	inBlowerSpeedCmd = event.value.v;

    	if(inBlowerSpeedCmd & 0x01){
    		DIGITAL_IO_SetOutputLow(&LED_0);
    	}
    	else{
    		DIGITAL_IO_SetOutputHigh(&LED_0);
    	}

    	 if(inBlowerSpeedCmd & 0x02){
    		 DIGITAL_IO_SetOutputLow(&LED_1);
       	 }
    	 else{
    		 DIGITAL_IO_SetOutputHigh(&LED_1);
    	 }

    	 if(inBlowerSpeedCmd & 0x04){
    		 DIGITAL_IO_SetOutputLow(&LED_2);
    	 }
    	 else{
    		 DIGITAL_IO_SetOutputHigh(&LED_2);
    	 }

         PWM_SetDutyCycle(&BlowerPWM, inBlowerSpeedCmd * 1400);
       }
    osDelay(200);
}


