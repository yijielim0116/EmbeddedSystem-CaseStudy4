/*
 * main.c
 *
 *  Created on: 2024 Sep 26 15:31:53
 *  Author: YiJie
 */




#include "DAVE.h"
#include <BlowerSpeedCtrl.h>
#include <BlowerTest.h>
#include <CANRxIsr.h>
#include <AdcVoltage.h>
//Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
osThreadId tid_BlowerSpeedCtrlThread;
osThreadId tid_BlowerTestThread;
osThreadId tid_AdcVoltageThread;

osMessageQDef(message_q, 5, uint32_t);   //Declare a message queue
osMessageQId message_q_id;               //Declare an ID for the message queue

osThreadDef ( runBlowerSpeedCtrl, osPriorityNormal, 1, 1024);
osThreadDef ( runBlowerTest, osPriorityNormal, 1, 1024);
osThreadDef ( runAdcVoltage, osPriorityLow, 1, 1024);

int main(void)
{
	DAVE_STATUS_t status;
	status = DAVE_Init();

	#ifndef TESTMODE

	  /* Disable the CAN node for the test application to conserve energy if not operating in test mode. */

	  CAN_NODE_Disable( &TestNode );

	#endif

	  if (status != DAVE_STATUS_SUCCESS)
	  {
	    /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
	    XMC_DEBUG("DAVE APPs initialization failed\n");

	    while(1U)
	    {

	    }
	  }


  message_q_id = osMessageCreate(osMessageQ(message_q), runBlowerSpeedCtrl);

  tid_BlowerSpeedCtrlThread = osThreadCreate(osThread(runBlowerSpeedCtrl), NULL);

  tid_AdcVoltageThread = osThreadCreate(osThread(runAdcVoltage), NULL);

#ifdef TESTMODE
  tid_BlowerTestThread = osThreadCreate(osThread(runBlowerTest),NULL);
#endif

  osKernelStart();


  /* Placeholder for user application code. The while loop below can be replaced with user application code. */
  while(1U)
  {
	  __WFI();

  }
}

volatile uint32_t g_stat_timer_ticks;

void FreeRtosTraceIsr( void )
{
	g_stat_timer_ticks++;
}

