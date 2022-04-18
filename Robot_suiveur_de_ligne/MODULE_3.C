//TRAN Vincent ANASTHASE AXEL
//Conversion_Anal/moteur_modulo_3
//07_01_2019

#include <p18cxxx.h>
#include "config_3.h"
#include <delays.h>

void setup(void);
void clignotement(int x);
int CONVERSION(void);
void CAPTEUR_GAUCHE(void);
void CAPTEUR_MILIEU(void);
void CAPTEUR_DROITE(void);

void MOT_G(int z);
void MOT_D(int z);

void moteur(void);

void main(void)
{
 setup();
 clignotement(3);
 while(1)
 	{
	 CAPTEUR_GAUCHE();
     CAPTEUR_MILIEU();
     CAPTEUR_DROITE();
     moteur();
	}

}

void setup(void) //ligne 30
{
	TRISB = 0b11000000;
	TRISC = 0b11100000;
	ADCON0bits.ADON = 1;
    ADCON1bits.PCFG = 0b1100;
    ADCON1bits.VCFG = 0b00;
	ADCON2bits.ACQT = 0b010;
	ADCON2bits.ADCS = 0b010;
	ADCON2bits.ADFM = 1;
    T2CONbits.TMR2ON = 1;
	T2CONbits.T2CKPS = 0b01;
	CCP1CONbits.CCP1M = 0b1111;
	CCP2CONbits.CCP2M = 0b1111;
	PR2 = 249;
}

void clignotement(int x) //ligne 41
{
	int i;
	for(i=0;i<=1;i++)
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
}

int CONVERSION(void)
{
 int result;
 ADCON0bits.GO=1;
 while(ADCON0bits.GO==1){}
 result= 256*ADRESH + ADRESL;
 return(result);
}

void CAPTEUR_GAUCHE(void)
{
	int y;
	EMIR_G = 1;
    Delay1KTCYx(3);
	ADCON0bits.CHS=0b0010;
	y =CONVERSION();
    if (y < 600)     //ligne 65
	{
 	LED_GAUCHE = 1;
	}
	else
	{
	LED_GAUCHE = 0;
	}
    EMIR_G = 0;
}

void CAPTEUR_MILIEU(void)
{
	int y;
    EMIR_M = 1;
    Delay1KTCYx(3);
	ADCON0bits.CHS=0b0001;
    y = CONVERSION();
    if (y < 410)
	{
 	LED_MILIEU = 1;
	}
	else
	{
	LED_MILIEU = 0;
	}
    EMIR_M = 0;
}

void CAPTEUR_DROITE(void)
{
    int y;
	EMIR_D = 1;
    Delay1KTCYx(3);
	ADCON0bits.CHS=0b0000;
    y = CONVERSION();
    if (y < 500)
	{
 	LED_DROITE = 1;
	}
	else
	{
	LED_DROITE = 0;
	}
    EMIR_D = 0;
}

void moteur()
{
unsigned char position;
position=LED_GAUCHE*4 + LED_MILIEU*2 + LED_DROITE;
SENS_D=1;
SENS_G=1;
ENABLE = 0;

switch(position)
	{
	case 0b111: //Arrêt du moteur
    MOTD=1;
    MOTG=1;
    Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);
	Delay10KTCYx(250);
    while(1)
	{
    LED_GAUCHE=0;LED_MILIEU=0;LED_DROITE=0;
	ENABLE =0;
	}
    break;

    case 0b000: //Avancer le robot
	MOT_G(180);
	MOT_D(180);
    ENABLE=1;
	break;

	case 0b101: //Aller tout droit
	MOT_G(150);
	MOT_D(150);
	ENABLE=1;
	break;

	case 0b001: //Tourner à gauche
	MOT_G(200);
	MOT_D(100);
	ENABLE=1;
	break;

	case 0b011: //Tourner à gauche
	MOT_G(200);
	MOT_D(60);
    ENABLE=1;
    break;

	case 0b100: //Tourner à droite
	MOT_G(100);
	MOT_D(200);
	ENABLE=1;
	break;

	case 0b110: //Tourner à droite
    MOT_G(60);
	MOT_D(200);
	ENABLE=1;
	break;

	default:
	break;

	}
}

void MOT_G(int z)
	{
     CCPR1L = z>>2;
	 CCP1CONbits.DC1B = z&0b11;
	}

void MOT_D(int z)
	{
     CCPR2L = z>>2;
     CCP2CONbits.DC2B = z&0b11;
	}
