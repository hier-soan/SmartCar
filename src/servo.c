#include "servo.h"




int angleSet;			//设定目标舵机转动角度
extern int error;

//取绝对值
void abs(int i){
	if (i < 0){
		i = -i;
	}else{
		i = i;
	}
}

/*----------------------误差循迹-----------------------
	@令angleSet∈[6,24]，即角度范围为[9,171]
		 angleSet = 3*error+15;
	@令angleSet∈[9,21]，即角度范围为[36,144]
		 angleSet = 2*error+15;
-----------------------------------------------------*/
int kp = 0;
int kd = 0;
int nowError = 4;
int lastError = 2;
void findRoad(void){
	angleSet = 12; //3*error+
	//模仿简易PID
	nowError = error;
//	angleSet = kp*nowError + kd*abs((nowError-lastError));
	lastError = nowError;
}

