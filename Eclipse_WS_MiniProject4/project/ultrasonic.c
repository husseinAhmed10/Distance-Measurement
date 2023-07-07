/*
 * ultrasonic.c
 *
 *  Created on: May 22, 2023
 *      Author: T.S
 */


#include "ultrasonic.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <util/delay.h>

/*Data Type*/
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

/*Function Definition*/

void Ultrasonic_init(void){

	/*ICU_init and ICU_setCallBack functions should be called inside the Ultrasonic_init
	function.*/

	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};

	Icu_init(&Icu_Config);

	Icu_setCallBack(Ultrasonic_edgeProcessing);

	/* Setup the direction for the trigger pin as output pin through the
	GPIO driver*/

	GPIO_setupPinDirection(trigger_PORT, trigger_PIN, PIN_OUTPUT);

}


void Ultrasonic_Trigger(void){

	//************msh mot2kd
	//Icu_setEdgeDetectionType(RISING);
	//GPIO_writePin(trigger_PORT,trigger_PIN,1);
	//**************
	//Icu_clearTimerValue();
	GPIO_writePin(PORTB_ID,PIN5_ID,1);
	_delay_ms(1);
	GPIO_writePin(PORTB_ID,PIN5_ID,0);

}

uint16 Ultrasonic_readDistance(void){

	if(g_edgeCount == 0)
		Ultrasonic_Trigger();
	else if(g_edgeCount == 2)
		g_edgeCount = 0;

	return (((float32)17000 * g_timeHigh)/1000000);

}

void Ultrasonic_edgeProcessing(void){

	/*Calculate high time of pulse*/
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the High time value */
		g_timeHigh = Icu_getInputCaptureValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
		/*g_edgeCount = 0;*/
	}


}
