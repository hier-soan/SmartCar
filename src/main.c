#include "headfile.h"

sbit buzzer = P0^6;
sbit key = P3^2;
sbit servoPwm = P1^6;

int keyDownFlag = 0;
int buzzerOnFlag = 0;
int angle;



//��������
void keyScan(void);
void buzzerOn(void);

int temp = 0; //����

void main (void){
	//error = 0;
	temp = 0;
	P0 = 0XF0;
	keyScan();

	if (keyDownFlag == 1){
		TMOD = 0X11;		    //������ʱ�������ڷ�ʽ1��16λ��ʱ��
		//pitInit(0,0XFC,0X18);  //�趨��ֵΪFC18H��1ms��ʱ���ж�
		EA = 1;
		pitInit(1,0XFF,0XA3);  //�趨��ֵΪFFA3H��0.1ms��ʱ���ж�
			  
	}
	while (1){
		//	allControl();
		//	findRoad();
		//	moveMotorServo(0);
		   angle = 12;
		} 	
}

//����������
void buzzerOn (void){
	buzzer = 0;
	delay_ms(50);
	buzzer = 1;
}

//�жϰ���
void keyScan (void){
	while (keyDownFlag == 0){
		if (key == 0){
			delay_ms(20);
			if (key == 0){
				keyDownFlag = 1;
				buzzerOn();
			    
			}
		}
	}
}


/*--------------�����ʱ���жϷ������-----------------
   @0.1ms���붨ʱ���жϷ������һ��
   @����Ƕȷ�Χ��[0~180]	��������>  20ms������ռ�ձȾ���
   			0.5ms �������� 0��
			2.5ms �������� 180��
		ͳһ�Ƕȹ�ʽ�� = 90T - 45
   		   1ms = 10temp
		   20ms = 200temp
		ת��Ϊ�������ԣ�
				�� = 9angleSet - 45  ����angleSet��[5,25]
	�ɸ�������Ħ�ֵȷ��angleSet��ֵ

	�����ֵΪangleSet = 15
------------------------------------------------------*/
void pit1Interrupt() interrupt 3{
	TH1 = 0XFF;
	TL1 = 0XA3;
	if(temp < angle){
		servoPwm = 1;
	}else{
		servoPwm = 0;
	}
	temp ++;
	temp = temp%40;		//20ms�����������
} 
