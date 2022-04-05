#include "AD.h"

/*--------------��ʱ1ms--------------------*/
void delay_ms(unsigned int ms){
	unsigned int i;
	unsigned char j;
	for(i=0;i<ms;i++){
		for(j=0;j<200;j++);
			for(j=0;j<102;j++);
	}
}

/*--------------���ݲɼ�����-----------------*/
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



/*--------------����������-----------------*/
int errorOut(int nowPosition){
	int error = 0;
	error = nowPosition - MIDDLELINE;
	return error;
}


/*----------------------����Ԫ�ش���-----------------------
	@inIslandFlag		Բ����־λ
		0				����������־λ
		1				��⵽Բ���°�Բ��׼��������־λ
		2				��⵽Բ���ϰ�Բ����ʼ������־λ
		3				����ѭ����־λ
		4				��⵽������������ʼ������־λ
		5				�Ѿ�������־λ
	
	@leftIslandFlag		��Բ����־λ
	@rightIslandFlag	��Բ����־λ
	@littleAngleFlag	��Ǳ�־λ
----------------------------------------------------------*/

int inIslandFlag = 0;
int leftIslandFlag = 0;
int rightIslandFlag = 0;
int littleAngleFlag = 0;

void islandJudgment(void){
	if (inIslandFlag == 0){  //δ��⵽Բ��
		if ((leftOne == 0 || rightOne == 0) && (leftTwo  == 0|| leftThree  == 0|| leftFour == 0)){	//����м��⵽���ߵ�ͬʱ��
			leftIslandFlag = 1;																//�������Ҳ��⵽���ߣ����ж�Ϊ��Բ��
			inIslandFlag = 1;
		}else if ((leftOne == 0 || rightOne == 0) && (rightTwo  == 0|| rightThree  == 0|| rightFour == 0)){		//���ϼ����Բ��ͬ��
			rightIslandFlag = 1;
			inIslandFlag = 1;
		}
	}else if (inIslandFlag == 1){
		delay_ms(1000);			//��ʱһ��ʱ�䣬�����ж�Բ������һ�λ�����������Բ������ʼ���������ޣ����ж�Ϊ���
		if ((leftOne == 0 || rightOne == 0) && ((leftTwo  == 0|| leftThree  == 0|| leftFour == 0)
			||(rightTwo  == 0|| rightThree  == 0|| rightFour == 0))){
			inIslandFlag = 2;	 //Բ���ڶ��׶Σ���ʼ�뻷
		}else{
			littleAngleFlag = 1;	 //û�жϵ���һ�λ����ж�Ϊ���
			inIslandFlag = 0;
		}
	}else if (inIslandFlag ==2){
		delay_ms(1000);			//��ʱһ��ʱ�䣬ʹ֮��ȫ����Բ���󣬽���׶���
		inIslandFlag = 3;
	}else if (inIslandFlag == 3){
		if (leftIslandFlag == 1){
			if ((leftOne == 0 || rightOne == 0) && (rightTwo  == 0|| rightThree  == 0|| rightFour == 0)){		//�󻷣�����м��⵽���ߵ�ͬʱ��
				inIslandFlag = 4;																//�ұ�����Ҳ��⵽���ߣ����ж�Ϊ׼������
			}
		}else if (rightIslandFlag == 1){
			if ((leftOne == 0 || rightOne == 0) && (leftTwo  == 0|| leftThree  == 0|| leftFour == 0)){		//���ϼ�����ͬ��
				inIslandFlag = 4;
			}
		}
	}else if (inIslandFlag == 4){
		delay_ms(1000);			//��ʱһ��ʱ�䣬�������֮�����׶���
		inIslandFlag = 5;
	}else if (inIslandFlag == 5){
		delay_ms(1000);			//��ʱһ��ʱ�䣬��֤����һ������������־λ��׼��֮���Բ��
		inIslandFlag = 0;
		leftIslandFlag = 0;
		rightIslandFlag = 0;
	}
}


int error = 0;		//���ƶ��������ź�
void islandControl(void){
	if (inIslandFlag == 1){	//��⵽Բ����־��׼���뻷
		error = 0;			//ֱ��
	}else if (inIslandFlag == 2){
		if (leftIslandFlag == 1){
			error = -1;		//�뻷ǿ������
		}else if (rightIslandFlag == 1){
			error = 1;		//�뻷ǿ���Ҵ��
		}
	}else if (inIslandFlag == 3){
		error = errorOut;	//��������ѭ��
	}else if (inIslandFlag == 4){
		if (leftIslandFlag == 1){
			error = -1;		//����ǿ������
		}else if (rightIslandFlag == 1){
			error = 1;		//����ǿ���Ҵ��
		}
	}else if (inIslandFlag == 5){
		error = 0;			//�����󱣳�ֱ��
	}else if (inIslandFlag == 0){
		error = errorOut;	//���������������ֱ��
	}
}

/*------------����ж�---------------*/
void littleAngleJudgment(void){
	if(littleAngleFlag == 1){
		delay_ms(1000);	  
		littleAngleFlag = 0;
	}
}

/*------------��ǿ���---------------*/
void littleAngleControl(void){
	if (littleAngleFlag == 1 && leftIslandFlag == 1){
		error = -3;
	}else if (littleAngleFlag == 1 && rightIslandFlag == 1){
		error = 3;
	}
}

/*------------�ܿ���-----------------*/
void allControl(void){
	dataAcquire();
	error = errorOut() ;
	//islandJudgment();
	/*littleAngleJudgment();
	islandControl();
	littleAngleJudgment();	*/
}