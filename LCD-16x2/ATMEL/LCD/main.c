/*
 * LCD.c
 *
 * Created: 08/09/2019 19:54:42
 * Author : elyss
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void envia_comando(char comando){
	PORTB = comando;
	PORTD &= ~(0x04);
	PORTD &= ~(0x02);
	PORTD |= (0x01);
	_delay_ms(10);
	PORTD &= ~(0x01);	
}

void envia_dado(char dado){
	PORTB = dado;
	PORTD |= (0x04);
	PORTD &= ~(0x02);
	PORTD |= (0x01);
	_delay_ms(10);
	PORTD &= ~(0x01);
	
}

void inicializa(){
	envia_comando(0x38);
	envia_comando(0x0E);
	envia_comando(0x06);
	envia_comando(0x01);
	envia_comando(0x80);
}

int i;

void envia_mensagem(char mensagem[]){
	for (i=0; i<strlen(mensagem); i++)
	{
		envia_dado(mensagem[i]);
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRB = 0xff;
	DDRD = 0x07;
	inicializa();
    while (1) 
    {
		envia_comando(0x81);
		envia_mensagem("TESTE - ELYSSON");
		envia_comando(0xc4);
		envia_mensagem(__TIME__);
    }
}

