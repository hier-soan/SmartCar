#include "servo.h"




int angleSet;			//�趨Ŀ����ת���Ƕ�
extern int error;

//ȡ����ֵ
void abs(int i){
	if (i < 0){
		i = -i;
	}else{
		i = i;
	}
}

/*----------------------���ѭ��-----------------------
	@��angleSet��[6,24]�����Ƕȷ�ΧΪ[9,171]
		 angleSet = 3*error+15;
	@��angleSet��[9,21]�����Ƕȷ�ΧΪ[36,144]
		 angleSet = 2*error+15;
-----------------------------------------------------*/
int kp = 0;
int kd = 0;
int nowError = 4;
int lastError = 2;
void findRoad(void){
	angleSet = 12; //3*error+
	//ģ�¼���PID
	nowError = error;
//	angleSet = kp*nowError + kd*abs((nowError-lastError));
	lastError = nowError;
}

