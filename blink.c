#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#define USART_BAUDRATE  9600
#define UBRR_VALUE      (((F_CPU/(USART_BAUDRATE*16UL)))-1)
#define RX_BUFFER_SIZE  512
#define RX_LINE_SIZE    128

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>


void serial_init(){
	// Initialize USART
	UBRR0=UBRR_VALUE;			// set baud rate
	UCSR0B|=(1<<TXEN0);			// enable TX
	UCSR0B|=(1<<RXEN0);			// enable RX
	UCSR0B|=(1<<RXCIE0);			// RX complete interrupt
	UCSR0C|=(1<<UCSZ01)|(1<<UCSZ01); 	// no parity, 1 stop bit, 8-bit data
}

void serial_char(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void serial_string(char* s) {
	while (*s != '\0')
		serial_char(*s++);
}

unsigned char get_char(){
	while ((UCSR0A & (1 << RXC0)) == 0);
	return(UDR0);
}


int main(){
    DDRD |= 0b11111100;
    DDRB |= 0b00000011;

	serial_init();

    char c = 0x00;

	while(1){
        PORTD &= 0b00000011;
        PORTB &= 0b11111100;

        PORTD |= (c & 0b00000001) << PORTB2;
        PORTD |= (c & 0b00000010) << (PORTB3 - 1);
        PORTD |= (c & 0b00000100) << (PORTB4 - 2);
        PORTD |= (c & 0b00001000) << (PORTB5 - 3);
        PORTD |= (c & 0b00010000) << (PORTB6 - 4);
        PORTD |= (c & 0b00100000) << (PORTB7 - 5);
        PORTB |= (c & 0b01000000) >> 6;
        PORTB |= (c & 0b10000000) >> 6;

		c = get_char();
	}	
}