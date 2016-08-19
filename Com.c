

#include "Com.h"
#include "Delay.h"
#include "Time.h"

//PA2 ͨѶ-��
//PA3 ͨѶ-���

void ComInit(void) {
    //Watch
    PA_DDR_DDR2 = 0;
    PA_CR1_C12 = 0;
    PA_CR2_C22 = 1;
    
    //�ⲿ�жϳ�ʼ��
	EXTI_CR1 &= ~BIT(2);//����PA���ж�
	EXTI_CR1 &= ~BIT(3);
}

#define COM_BIT_OUT 	PA_ODR_ODR2
#define COM_BIT_IN 	    PA_IDR_IDR2
#define COM_BIT_DR      PA_DDR_DDR2
#define COM_BIT_INT     PA_CR2_C22

u8 ComSend(u8 data[]) {
	u16 wait = 0;
	u8 data_t = 0;//������ʱֵ
	u8 i = 0,j = 0;
	
	COM_BIT_INT = 0;//�ж�
	COM_BIT_DR = 1;//����Ϊ���
	COM_BIT_OUT = 0;
	DelayUs(100);//����20ms˵�����߿�ʼ
	COM_BIT_DR = 0;//����Ϊ����
	DelayUs(1);
	while(COM_BIT_IN == 1) {//�ȴ��ӻ�����
		if(wait < 100) {
			wait++;
		} else {//��ʱ���˳�
		
			COM_BIT_INT = 1;//�ж�
			return 0;
		}
	}
	wait = 0;
	while(COM_BIT_IN == 0) {
		if(wait < 100) {
			wait++;
		} else {//��ʱ���˳�
		
			return 0;
		}
	}
	COM_BIT_DR = 1;//����Ϊ���
	for(j = 0;j < 5;j++) {
		data_t = data[j];
		for(i=0;i<8;i++) {
			COM_BIT_OUT = 0;
			if(data_t&0x80) {
				DelayUs(80);
			} else {
				DelayUs(40);
			}
			COM_BIT_OUT = 1;
			DelayUs(20);
			data_t<<=1;
		}
	}
	DelayUs(60);
	COM_BIT_OUT = 1;
	COM_BIT_INT = 1;//�ж�
	COM_BIT_DR = 0;//����Ϊ����
	return 0;
}

u8 ComRead(u8 data_s[]) {
    static u16 wait = 0;
    u8 i = 0,j = 0;
	u8 data = 0;
	wait = 0;

	COM_BIT_DR = 0;//����Ϊ����
	while(COM_BIT_IN == 0) {
		if(wait < 60) {
			wait++;
		} else {
			return 0x44;
		}
	}
	if(wait > 25) {
		wait = 0;
		COM_BIT_DR = 1;//����Ϊ���
		COM_BIT_OUT = 0;
		DelayUs(1);
		COM_BIT_DR = 0;//����Ϊ����
		//��ʼ��������
		for(j = 0;j < 5;j++) {
			for(i=0;i<8;i++) {  
				data<<=1; 
				while(COM_BIT_IN == 1) {
					if(wait < 200) {
						wait++;
					} else {
						return 0x44;
					}
				}
				wait = 0;
				while(COM_BIT_IN == 0) {
					if(wait < 200) {
						wait++;
					} else {
						return 0x44;
					}
				}
				if(wait > 30) {//Ϊ1
					data|=0x01;  
				}
				wait = 0;					
			}
			data_s[j] = data;
			data = 0;
		}
		if(data_s[4] == (data_s[0]+data_s[1]+data_s[2]+data_s[3])) {//�ۼ�У��
			if(data_s[4] != 0) {
				return 0x88;
			} else {
				return 0x44;
			}
		} else {
			return 0x44;
		}
	} else {//ʱ�䲻�� �Ƴ�
		return 0x44;
	}
} 


static u8 com_date[5];
static u8 rs_ok = 0;//whether it has received data

u8 ComGetData(u8 num) {
    return com_date[num];
}

u8 ComGetFlag(void) {
    return rs_ok;
}

void ComClearFlag(void) {
    rs_ok = 0;
}

static u8 com_ask_data[5];//��������l;
static u8 ask_flag = 0;//�Ƿ�Ҫ���ر�־λ

static u8 ask_count = 0;//�ط�����

void ComSendCmdWatch(u8 cmd,u8 par1,u8 par2,u8 par3) {
    u8 com_t_data[5] = {0,0,0,0,0};//ǰ��
    //u8 com_t_data2[5] = {0,0,0,0,0};//ǰ��
	com_t_data[0] = cmd; //cmd
	com_t_data[1] = par1;
	com_t_data[2] = par2;
	com_t_data[3] = par3;
    com_t_data[4] = com_t_data[0]+com_t_data[1]+com_t_data[2]
                                    +com_t_data[3];
    for(u8 i = 0; i < 5; i++) {//��������
        com_ask_data[i] = com_t_data[i];
    }
    if( (cmd == add_stal) || (cmd == sub_stal) ) {
        ask_flag = 1;
        ask_count = 0;
    }
    INTOFF
    //ComSend(com_t_data2);
	ComSend(com_t_data);
    INTEN
}


/**********************************************��������***************************************************** 
* ��������: void ComAskCmd(void) 
* �������: void 
* ���ز���: void  
* ��    ��: //��������  
* ��    ��: by lhb_steven
* ��    ��: 2016/5/20
************************************************************************************************************/ 
void ComAskCmd(void) { 
    static u16 time_count = 0;//ʱ��
    
    if(ask_flag == 1) {//��������Ҫ����
        if(time_count < 5000) {
            time_count++;
        } else {
            time_count = 0;
            TimerSetSec(0);//���ʱ��
            ComSend(com_ask_data);//���·���
            if(ask_count < 10) {
                ask_count++;
            } else {
                ask_count = 0;
                ask_flag = 0;//����
            }
        }
    } else {
        time_count = 0;
    }
}

#pragma vector=12
__interrupt void EXTI2_IRQHandler(void)
{
    INTOFF
    TimerSetSec(0);//�������
    if(ComRead(com_date) == 0x88) {
        rs_ok = 0x80;
        ask_flag = 0;
    }
    EXTI_SR1 = 0xff;
    INTEN
}




