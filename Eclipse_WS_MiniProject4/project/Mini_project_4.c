/*
 * Mini_project_4.c
 *
 *  Created on: May 22, 2023
 *      Author: T.S
 */

#include "gpio.h"
#include "icu.h"
#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /* To use the SREG register */

int main(void) {

	/*Application initialization*/

	/* Enable Global Interrupt I-Bit */
	SREG |= (1 << 7);

	Ultrasonic_init();
	uint8 reading = 0;
	LCD_init();
	LCD_displayString("Distance=    cm");	//10,11,12

	/*Application*/
	while (1) {
		reading = Ultrasonic_readDistance();
		LCD_moveCursor(0, 10);
		LCD_intgerToString(reading);
		if(reading < 10)
			LCD_displayString("  ");
		else if(reading < 100)
			LCD_displayString(" ");

	}

	return 0;
}
