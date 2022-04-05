#include "AD.h"

/*--------------延时1ms--------------------*/
void delay_ms(unsigned int ms){
	unsigned int i;
	unsigned char j;
	for(i=0;i<ms;i++){
		for(j=0;j<200;j++);
			for(j=0;j<102;j++);
	}
}

/*--------------数据采集程序-----------------*/
int nowPosition = 0;
int lastPosition = 0;

void dataAcquire(void){
	lastPosition = nowPosition;

	if (leftOne == 0){
		nowPosition = 0;
	}else if(leftTwo == 0){
		nowPosition = -1;
	}else if(leftThree == 0){
		nowPosition = -2;
	}else if(leftFour == 0){
		nowPosition = -3;
	}else if(rightOne == 0){
		nowPosition = 0;
	}else if(rightTwo == 0){
		nowPosition = 1;
	}else if(rightThree == 0){
		nowPosition = 2;
	}else if(rightFour == 0){
		nowPosition = 3;
	}	
}



/*--------------误差输出程序-----------------*/
int errorOut(int nowPosition){
	int error = 0;
	error = nowPosition - MIDDLELINE;
	return error;
}


/*----------------------赛道元素处理-----------------------
	@inIslandFlag		圆环标志位
		0				正常赛道标志位
		1				检测到圆环下半圆，准备进环标志位
		2				检测到圆环上半圆，开始进环标志位
		3				环内循迹标志位
		4				检测到出环特征，开始出环标志位
		5				已经出环标志位
	
	@leftIslandFlag		左圆环标志位
	@rightIslandFlag	右圆环标志位
	@littleAngleFlag	锐角标志位
----------------------------------------------------------*/

int inIslandFlag = 0;
int leftIslandFlag = 0;
int rightIslandFlag = 0;
int littleAngleFlag = 0;

void islandJudgment(void){
	if (inIslandFlag == 0){  //未检测到圆环
		if ((leftOne == 0 || rightOne == 0) && (leftTwo  == 0|| leftThree  == 0|| leftFour == 0)){	//如果中间检测到黑线的同时；
			leftIslandFlag = 1;																//左边三段也检测到黑线，则判定为左圆环
			inIslandFlag = 1;
		}else if ((leftOne == 0 || rightOne == 0) && (rightTwo  == 0|| rightThree  == 0|| rightFour == 0)){		//与上检测左圆环同理
			rightIslandFlag = 1;
			inIslandFlag = 1;
		}
	}else if (inIslandFlag == 1){
		delay_ms(1000);			//延时一段时间，用于判断圆环的下一段弧，若有则是圆环，开始进环；若无，则判断为锐角
		if ((leftOne == 0 || rightOne == 0) && ((leftTwo  == 0|| leftThree  == 0|| leftFour == 0)
			||(rightTwo  == 0|| rightThree  == 0|| rightFour == 0))){
			inIslandFlag = 2;	 //圆环第二阶段，开始入环
		}else{
			littleAngleFlag = 1;	 //没判断到下一段弧，判断为锐角
			inIslandFlag = 0;
		}
	}else if (inIslandFlag ==2){
		delay_ms(1000);			//延时一段时间，使之完全进入圆环后，进入阶段三
		inIslandFlag = 3;
	}else if (inIslandFlag == 3){
		if (leftIslandFlag == 1){
			if ((leftOne == 0 || rightOne == 0) && (rightTwo  == 0|| rightThree  == 0|| rightFour == 0)){		//左环：如果中间检测到黑线的同时；
				inIslandFlag = 4;																//右边三段也检测到黑线，则判断为准备出环
			}
		}else if (rightIslandFlag == 1){
			if ((leftOne == 0 || rightOne == 0) && (leftTwo  == 0|| leftThree  == 0|| leftFour == 0)){		//与上检测出左环同理
				inIslandFlag = 4;
			}
		}
	}else if (inIslandFlag == 4){
		delay_ms(1000);			//延时一段时间，让其出环之后进入阶段五
		inIslandFlag = 5;
	}else if (inIslandFlag == 5){
		delay_ms(1000);			//延时一段时间，保证出环一定距离后清除标志位，准备之后的圆环
		inIslandFlag = 0;
		leftIslandFlag = 0;
		rightIslandFlag = 0;
	}
}


int error = 0;		//控制舵机的误差信号
void islandControl(void){
	if (inIslandFlag == 1){	//检测到圆环标志，准备入环
		error = 0;			//直行
	}else if (inIslandFlag == 2){
		if (leftIslandFlag == 1){
			error = -1;		//入环强制左打角
		}else if (rightIslandFlag == 1){
			error = 1;		//入环强制右打角
		}
	}else if (inIslandFlag == 3){
		error = errorOut;	//环内正常循迹
	}else if (inIslandFlag == 4){
		if (leftIslandFlag == 1){
			error = -1;		//出环强制左打角
		}else if (rightIslandFlag == 1){
			error = 1;		//出环强制右打角
		}
	}else if (inIslandFlag == 5){
		error = 0;			//出环后保持直行
	}else if (inIslandFlag == 0){
		error = errorOut;	//其他情况保持正常直行
	}
}

/*------------锐角判断---------------*/
void littleAngleJudgment(void){
	if(littleAngleFlag == 1){
		delay_ms(1000);	  
		littleAngleFlag = 0;
	}
}

/*------------锐角控制---------------*/
void littleAngleControl(void){
	if (littleAngleFlag == 1 && leftIslandFlag == 1){
		error = -3;
	}else if (littleAngleFlag == 1 && rightIslandFlag == 1){
		error = 3;
	}
}

/*------------总控制-----------------*/
void allControl(void){
	dataAcquire();
	error = errorOut() ;
	//islandJudgment();
	/*littleAngleJudgment();
	islandControl();
	littleAngleJudgment();	*/
}