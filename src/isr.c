#include "isr.h"
/*----------------中断开关----------------
	@i	true为开中断，false为关中断
------------------------------------------*/
void interruptSwitch(int i){
	switch (i){
		case 1:	EA = 1;	break;
		case 0: EA = 0; break;
		default:break;
	}
}

/*---------------定时器初始化函数---------------
	@tim		定时器选择						    
	@th		定时器高位写入数据		     	    
	@tl		定时器低位写入数据					
------------------------------------------------*/							 
void pitInit(int tim, int th, int tl){
	switch (tim){
		case 0: TH0 = th;
				TL0 = tl;
				TR0 = 1;
				ET0 = 1;break;
		case 1: TH1 = th;
				TL1 = tl;
				TR1 = 1;
				ET1 = 1;break;
		default:break;
	}
}

/*---------------定时器开启函数---------------
	@tim		定时器选择						    
----------------------------------------------*/
void pitStart(int tim){
	switch (tim){
		case 0:	TR0 = 1;
				ET0 = 1;
		case 1: TR1 = 1;
				ET1 = 1;
	}
}