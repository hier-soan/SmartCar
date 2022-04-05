#include "motor.h"

sbit leftINForward = P0^0;		  //FB=10ʱǰ����FB=01ʱ����
sbit leftINBackward = P0^1;
	
sbit rightINForward = P0^2;		  //FB=10ʱǰ����FB=01ʱ����
sbit rightINBackward = P0^3;

sbit leftEN = P0^4;				  //EN=0ʱ���ֹͣ
sbit rightEN = P0^5;

/*---------------�˶�����---------------*/

/*--------------------------------------*/
#define goAhead		0
#define	goLeft		1
#define	goRight		2
#define	goBack		3
#define stop		4

int leftVal = 0;
int rightVal = 0;

//�������ҵ��pwmԤ��ռ�ձ�
void motorValSet(int lVal, int rVal){
	if (lVal != 0 && rVal !=0){
		leftVal = lVal;
		rightVal = rVal;
		leftEN = 1;
		rightEN = 1;
	}else if (lVal == 0 && rVal ==0){
		leftEN = 0;
		rightEN = 0;
	}	
}

void forward(void){		//ǰ��
	leftINForward = 1;	leftINBackward = 0;
	rightINForward = 1;	rightINBackward = 0;
}

void backward(void){	//����
	leftINForward = 0;	leftINBackward = 1;
	rightINForward = 0;	rightINBackward = 1;
}

void leftward(void){	//��ת
	leftINForward = 0;	leftINBackward = 1;
	rightINForward = 1;	rightINBackward = 0;
}

void rightward(void){	//��ת
	leftINForward = 1;	leftINBackward = 0;
	rightINForward = 0;	rightINBackward = 1;
}

//�������ת�򣬵��ȫ�ٳ�
void moveMotorServo(int status){ 
	if (status == 0){
		motorValSet(20,20);
		forward();
	}else if (status == 3){
		motorValSet(20,20);
		backward();
	}else if (status == 4){
		motorValSet(0,0);
	}
}

//���ٿ���ת��
void moveMotorDiff(int status){
	if (status == 0){
		motorValSet(20,20);
		forward();
	}else if (status == 1){
		motorValSet(20,20);
		leftward();
	}else if (status == 2){
		motorValSet(20,20);
		rightward();
	}else if (status == 3){
		motorValSet(20,20);
		backward();
	}else if (status == 4){
		motorValSet(0,0);
	}
}

/*-------------------PWM---------------------
@pwmSetVal		pwm�趨ֵ	            
@val			pwm���

@function		ͨ��pwm���ƿ��Ƶ����ѹռ�ձ� 				            	            
@ex				pwmMotorOut(liftVal,leftEN)	    
---------------------------------------------*/
int pwmLNowVal = 0;
int pwmRNowVal = 0;
int Flag = 1;

void pwmMotorOut(int pwmNowVal, int pwmSetVal, int* val){
	pwmNowVal++;
	if (Flag){
		if (pwmNowVal <= pwmSetVal){
			val = 1;
		}else {
			val = 0;
		}
		if (pwmNowVal >= 20){
			pwmNowVal = 0;
		}
	}else {
		pwmNowVal = 0;
	}
}	

/*--------------��ʱ��0�жϷ������-----------------
		1ms��ʱ���ж�
	@leftMid
	@rightMid	  �м��������������ENʹ��				
---------------------------------------------------*/
int leftMid = 0;			
int rightMid = 0;

void pit0Interrupt() interrupt 1{
	TR0 = 0;
	TH0 = 0xFC;
	TL0 = 0x18;
	pwmMotorOut(pwmLNowVal,leftVal,&leftMid);
	pwmMotorOut(pwmRNowVal,rightVal,&rightMid);
	leftEN = leftMid;
	rightEN = rightMid;
	TR0 = 1;
}