#include "isr.h"
/*----------------�жϿ���----------------
	@i	trueΪ���жϣ�falseΪ���ж�
------------------------------------------*/
void interruptSwitch(int i){
	switch (i){
		case 1:	EA = 1;	break;
		case 0: EA = 0; break;
		default:break;
	}
}

/*---------------��ʱ����ʼ������---------------
	@tim		��ʱ��ѡ��						    
	@th		��ʱ����λд������		     	    
	@tl		��ʱ����λд������					
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

/*---------------��ʱ����������---------------
	@tim		��ʱ��ѡ��						    
----------------------------------------------*/
void pitStart(int tim){
	switch (tim){
		case 0:	TR0 = 1;
				ET0 = 1;
		case 1: TR1 = 1;
				ET1 = 1;
	}
}