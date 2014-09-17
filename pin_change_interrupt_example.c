#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define LED0	PORTB4
#define LED1 	PORTB5

volatile bool a = false;
volatile bool b = false;

ISR(PCINT0_vect) 
{
	if (PINB & (1<<PORTB0)) a = true;
	if (PINB & (1<<PORTB1)) b = true;
}

int main(void) 
{
	DDRB |= (1<<LED0); // set LED output
	PORTB &= ~(1<<LED0); // clear LED
	DDRB |= (1<<LED1); // set LED output
	PORTB &= ~(1<<LED1); // clear LED
 
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<PCINT0)|(1<<PCINT1); //enable pins as interrupt sources
 
	sei();
 
	while(1) 
	{
			if (a) // if a = true
			{
				PORTB ^= (1<<LED0); 	// Toggle LED
				a = false;
			}
			if (b) // if b = true
			{
				PORTB ^= (1<<LED1); 	// Toggle LED
				b = false;
			}
	}
 
}

//avr-gcc -mmcu=atmega328p -Wall -Os -o pin_change_interrupt_example.elf pin_change_interrupt_example.c

//avr-objcopy -j .text -j .data -O ihex pin_change_interrupt_example.elf pin_change_interrupt_example.hex

//sudo avrdude -p m328p -c usbtiny -e -U flash:w:pin_change_interrupt_example.hex
