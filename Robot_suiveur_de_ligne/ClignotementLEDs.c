//TRAN Vincent ANASTHASE AXEL
//Clignotement LED_modulo_0
//29_11_2018
#include<p18cxxx.h>
#include"config.h"
#include<delays.h>


unsigned char x;
void setup(void);
void clignotement(unsigned char);

void main(void)
{
 	setup();
 	while(1)
 	{
	 	clignotement(x);
	}
}

void setup(void)
{
	TRISB = 0b11000111;
	LED_DROITE=LED_MILIEU=LED_GAUCHE=0;
}


void clignotement(unsigned char x)
{
	LED_GAUCHE= 1;
	LED_MILIEU= 1;
	LED_DROITE= 1;
	Delay10KTCYx(125);
	LED_GAUCHE = 0;
	LED_MILIEU = 0;
	LED_DROITE = 0;
    Delay10KTCYx(125);
}


