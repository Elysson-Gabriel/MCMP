/*
 * Keypad.c
 *
 * Created: 01/09/2019 20:12:48
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

int teclado[4][4] = {{ 7, 8,  9, -6},
					 { 4, 5,  6, -5},
					 { 1, 2,  3, -4},
					 {-1, 0, -2, -3}};

int i, j, k;
int coluna = 1, linha = 3;
int entrada = 0, atualizou = 0;
long atual = 0;

void mostraDisplay(int numero)
{
	j = 10;
	k = 1;
	for (i=0; i<4; i++)
	{
		_delay_ms(5);
		PORTC = seletor[i];
		PORTD = numeros[(numero % j)/k];
		j *= 10;
		k *= 10;
	}
	_delay_ms(5);
}

int pressionou_tecla()
{
	DDRB = 0xf0;
	PORTB = 0x0f;
	for(i = 0; i < 4; i++)
	{
		if (!(PINB & (1<<i))){
			linha = i;
			DDRB = 0x0f;
			PORTB = 0xf0;
			for(i = 4; i < 8; i++)
			{
				if (!(PINB & (1<<i))){
					coluna = i-4;
					atualizou = 1;
					return 1;
					break;
				}
			}
		}
	}
	return 0;
}

void atualiza_display(){
	entrada = teclado[linha][coluna];
	if (entrada == -1)
	{
		atual = 0;
	}
	if(atualizou && ((atual * 10) + entrada) < 10000){
		atual = (atual * 10) + entrada;
		atualizou = 0;
	}
}

void ler_teclado(){
	while (pressionou_tecla())
	{
		mostraDisplay(atual);
	}
}

int main(void)
{
	/* Replace with your application code */
	DDRC = 0x0f;
	DDRD = 0x7f;
	PORTD = numeros[0];
	
	while (1)
	{
		ler_teclado();
		atualiza_display();
		mostraDisplay(atual);
	}
}