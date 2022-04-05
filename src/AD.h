#ifndef _AD_H
#define _AD_H

#include "headfile.h"

#define uchar unsigned char
#define uint  unsigned int

#define MIDDLELINE		0		//ï¿½ï¿½ï¿½ï¿½Î»ï¿½ï¿½

void delay_ms(unsigned int ms);
void allControl(void);

/*---------------Ñ­¼£²¿·Ö---------------*/
sbit rightOne   = P2^3;
sbit rightTwo   = P2^2;
sbit rightThree = P2^1;
sbit rightFour  = P2^0;
sbit leftOne    = P2^4;
sbit leftTwo    = P2^5;
sbit leftThree  = P2^6;
sbit leftFour   = P2^7;

#endif