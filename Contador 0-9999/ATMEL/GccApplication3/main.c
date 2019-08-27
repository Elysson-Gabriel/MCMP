/*
 * GccApplication3.c
 *
 * Created: 25/08/2019 10:54:39
 * Author : elyss
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

char seletor[4] = {0x07, 0x0B, 0x0D, 0x0E};
char numeros[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66,
					0x6d, 0x7d, 0x07, 0x7f, 0x6f};
int i, j, k;

void mostraDisplay(int contador)
{
	j = 10;
	k = 1;
	for (i=0; i<4; i++)
	{
		_delay_ms(5);
		PORTC = seletor[i];
		PORTB = numeros[(contador % j)/k];
		j *= 10;
		k *= 10;
	}
	_delay_ms(5);
}

int main(void)
{
    /* Replace with your application code */
	DDRC = 0x0f;
	DDRD = 0x01;
	DDRB = 0x7f;
	PORTB = 0x3f;
	
	int contador = 0, botao = 0;
	
    while (1) 
    {
		if(contador > 9999){
			contador = 0;
		}
		mostraDisplay(contador);
		if(botao != (PIND&0x01)){
			botao = PIND&0x01;
			if (botao)
			{
				contador++;
			}
		}
    }
}

