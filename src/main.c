#include "headfile.h"

sbit buzzer = P0^6;
sbit key = P3^2;
sbit servoPwm = P1^6;

int keyDownFlag = 0;
int buzzerOnFlag = 0;
int angle;



//函数声明
void keyScan(void);
void buzzerOn(void);

int temp = 0; //计数

void main (void){
	//error = 0;
	temp = 0;
	P0 = 0XF0;
	keyScan();

	if (keyDownFlag == 1){
		TMOD = 0X11;		    //两个定时器工作在方式1：16位定时器
		//pitInit(0,0XFC,0X18);  //设定初值为FC18H，1ms定时器中断
		EA = 1;
		pitInit(1,0XFF,0XA3);  //设定初值为FFA3H，0.1ms定时器中断
			  
	}
	while (1){
		//	allControl();
		//	findRoad();
		//	moveMotorServo(0);
		   angle = 12;
		} 	
}

//蜂鸣器函数
void buzzerOn (void){
	buzzer = 0;
	delay_ms(50);
	buzzer = 1;
}

//判断按键
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


/*--------------舵机定时器中断服务程序-----------------
   @0.1ms进入定时器中断服务程序一次
   @舵机角度范围：[0~180]	————>  20ms周期内占空比决定
   			0.5ms ———— 0°
			2.5ms ———— 180°
		统一角度公式θ = 90T - 45
   		   1ms = 10temp
		   20ms = 200temp
		转化为代码语言：
				θ = 9angleSet - 45  其中angleSet∈[5,25]
	可根据需求的θ值确定angleSet的值

	舵机中值为angleSet = 15
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
	temp = temp%40;		//20ms舵机控制周期
} 
