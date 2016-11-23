/*
 * HC595.c
 *
 * Created: 23.11.2016 15:46:47
 * Author : maxi
 */ 

#include <avr/io.h>
#include "HC595.h"

	uint8_t daten = 1;

int main(void)
{
DDRD = 0b01100000;
HC595_init();




while (1) {
	PORTD = (1<<PD6);
	
	HC595_setBit(daten);
	HC595_update();

	HC595_cycle();
	
	PORTD = (1<<PD5);
}
return 1;
}

