/*
 * AdcVoltage.c
 *
 *  Created on: Nov 29, 2024
 *      Author: YiJie
 */

#include "AdcVoltage.h"
#include "DAVE.h"

void runAdcVoltage (void *arg){

	    static uint8_t adc_led_value;

	    int32_t adc_value;
	    uint8_t can_data_arr[8] = {0};

	    while(1)
	    {
	        // Read ADC value (assuming a simple single channel measurement)
	        adc_value = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A);  // Replace with your ADC channel
	        adc_led_value = (adc_value >> 8) & 0x03;  // Map ADC value to LED control (example)

	        // Control LEDs based on ADC value
	        if(adc_led_value == 0)
	        {
	            DIGITAL_IO_SetOutputHigh(&LED_0);
	            DIGITAL_IO_SetOutputLow(&LED_1);
	            DIGITAL_IO_SetOutputLow(&LED_2);
	        }
	        else if(adc_led_value == 1)
	        {
	            DIGITAL_IO_SetOutputLow(&LED_0);
	            DIGITAL_IO_SetOutputHigh(&LED_1);
	            DIGITAL_IO_SetOutputLow(&LED_2);
	        }
	        else if(adc_led_value == 2)
	        {
	            DIGITAL_IO_SetOutputLow(&LED_0);
	            DIGITAL_IO_SetOutputLow(&LED_1);
	            DIGITAL_IO_SetOutputHigh(&LED_2);
	        }

	        // Example CAN message update based on ADC value (optional)
	        can_data_arr[6] = adc_value & 0xFF;  // Store lower byte of ADC value for CAN transmission
	        CAN_NODE_MO_UpdateData(&BcmNode_LMO_01_Config, can_data_arr);
	        CAN_NODE_MO_Transmit(&BcmNode_LMO_01_Config);

	        osDelay(200);  // Delay for the task (adjust polling frequency)
	    }
}
