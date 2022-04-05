#include "motor.h"

sbit leftINForward = P0^0;		  //FB=10时前进；FB=01时后退
sbit leftINBackward = P0^1;
	
sbit rightINForward = P0^2;		  //FB=10时前进；FB=01时后退
sbit rightINBackward = P0^3;

sbit leftEN = P0^4;				  //EN=0时电机停止
sbit rightEN = P0^5;

/*---------------运动函数---------------*/

/*--------------------------------------*/
#define goAhead		0
#define	goLeft		1
#define	goRight		2
#define	goBack		3
#define stop		4

int leftVal = 0;
int rightVal = 0;

//设置左右电机pwm预定占空比
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

void forward(void){		//前进
	leftINForward = 1;	leftINBackward = 0;
	rightINForward = 1;	rightINBackward = 0;
}

void backward(void){	//后退
	leftINForward = 0;	leftINBackward = 1;
	rightINForward = 0;	rightINBackward = 1;
}

void leftward(void){	//左转
	leftINForward = 0;	leftINBackward = 1;
	rightINForward = 1;	rightINBackward = 0;
}

void rightward(void){	//右转
	leftINForward = 1;	leftINBackward = 0;
	rightINForward = 0;	rightINBackward = 1;
}

//舵机控制转向，电机全速冲
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

//差速控制转向
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
@pwmSetVal		pwm设定值	            
@val			pwm输出

@function		通过pwm调制控制电机电压占空比 				            	            
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

/*--------------定时器0中断服务程序-----------------
		1ms定时器中断
	@leftMid
	@rightMid	  中间变量，用来控制EN使能				
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