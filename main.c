#define BAUD 437500
#define USE_2X

#define F_CPU 7000180

#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>

#include "pins.h"
#include "util.h"


void uart_putchar(char c, FILE * stream);
void uart_init(void);
char uart_getchar(void);

void writeToFlash(void);

static FILE out = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

int main(void){
	uart_init();

	stdout = &out;

	while(1){
		char option = uart_getchar();

		switch(option){
			case '\x00':
				printf("preparing to write to flash\n");
				writeToFlash();
				break;
			default:
				printf("%c is not a valid option\n", option);
		}
	}
}


void writeToFlash(void){
	uint32_t dataLength = 0;

	uint8_t a = 0;
	for(a = 0; a < 4; a++){
		dataLength |= ((uint32_t)uart_getchar()) << (a * 8);
	}

	printf("reading in %d bytes of actual data\n", dataLength);


}

void uart_init(void) {
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

char uart_getchar(void) {
	  loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	  return UDR0;
}

void uart_putchar(char c, FILE * stream) {
	if(c == '\n'){
		uart_putchar('\r', stream);
	}

	loop_until_bit_is_set(UCSR0A, UDRE0); /* Wait until transmission ready. */
	UDR0 = c;
}
