/*
 * GccApplication1.c
 *
 * Created: 20/08/2019 18:53:04
 * Author : elyss
 */ 

#include <avr/io.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = 0x7f;
	DDRD = 0x7f;
	PORTC = 0x01;
	
	int contador = 0;
	
	char numeros[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66,
					  0x6d, 0x7d, 0x07, 0x7f, 0x6f};
					  
    while (1) 
    {
		if(contador > 99){
			contador = 0;
		}
		
		if((PINC&0x01) == 0){
			while((PINC&0x01) == 0);
			contador++;
		}
		
		PORTD = numeros[contador / 10];
		PORTB = numeros[contador % 10];
		
    }
}

