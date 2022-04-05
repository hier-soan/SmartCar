#ifndef _ISR_H
#define _ISR_H

#include "headfile.h"

void interruptSwitch(int i);
void pitInit(int tim, int th, int tl);
void pitStart(int tim);

#endif