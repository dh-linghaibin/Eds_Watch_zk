/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�Menu.c
*
* �ļ���ʶ��V
* ժ    Ҫ���˵��ں�
*
*
* ��ǰ�汾��V1.0
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/17
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Menu.h"
#include "Led.h"
#include "Com.h"
#include "Power.h"//��ʾ��ѹ��

typedef struct DataNode
{
    u8 mode;
    u8 continuous;
    u8 behind_set_up;//�ӵ���־λ
    u8 behind_set_up_count;//�ӵ���־λ
    u8 beind_sta;//ǰ����λ
    
} tDataNode;
/***********************************************��������*****************************************************
* ��    ��: caidan  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/17
************************************************************************************************************/ 
static tDataNode menu;
/**********************************************��������***************************************************** 
* ��������: void MenuInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �˵�������ʼ��  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/17
************************************************************************************************************/ 
void MenuInit(void) { 
    menu.mode = 0x00;
    menu.continuous = 0x00;
    menu.behind_set_up = 0x00;
}
/**********************************************��������***************************************************** 
* ��������: u8 MenuGetMode(void) 
* �������: void 
* ���ز���: u8  
* ��    ��: ģʽ״̬  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/26
************************************************************************************************************/ 
u8 MenuGetMode(void) { 
    return menu.mode;
}
/**********************************************��������***************************************************** 
* ��������: void MenuModeSet(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��: ������Ӧģʽ������Ӧ����  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/17
************************************************************************************************************/ 
void MenuModeSet(u8 cmd) { 
    switch( cmd ) {
        case 0x01://�󲦼�������
        if(menu.mode == 0) {//��������
            menu.continuous = 2;
            LedSetModeFlicker(11);//��ʾ�����Զ�����
        } else if(1 == menu.mode) {//�����΢��ģʽ
            menu.mode = 2;
            LedSetPower(2);
        }
        break;
        case 0x02://�󲦳�������
        if(menu.mode == 0) {//��������
            menu.continuous = 1;
            LedSetModeFlicker(11);//��ʾ�����Զ�����
        } else if(1 == menu.mode) {//�����΢��ģʽ
            menu.mode = 2;
            LedSetPower(2);
        }
        break;
        case 0x03://ǰ����������
        if(menu.mode == 0) {//��������
         
        } else if(1 == menu.mode) {//����ǰ��΢��ģʽ
            menu.mode = 3;
            LedSetPower(3);
        }
        break;
        case 0x04:
        break;
        case 0x05:
        break;
        case 0x06:
        break;
        case 0x11://�󲦼�
        LedSetModeFlicker(1);
        if(menu.mode == 0) {//�ӵ�
            //ComSendCmdWatch(front,add_stal,0x00,0x00);//�󲦼ӵ�
            ComSendCmdWatch(add_stal,0x00,0x00,0x00);//ֱ�ӿ��ƺ� ����������
        } else if(menu.mode == 2) {//��΢��
            //ComSendCmdWatch(front,add_setp,0x00,0x00);//�󲦼ӵ�
            ComSendCmdWatch(add_setp,0x00,0x00,0x00);
        } else if(menu.mode == 3) {//ǰ��΢��
            ComSendCmdWatch(behind,add_setp,0x00,0x00);//�󲦼ӵ�
        }
        PowerGet();
        LedSetMode(BattertGetLevel()+1);
        LedSetPowerFlag(1);
        
        break;
        case 0x12://�󲦼�
        LedSetModeFlicker(1);
        if(menu.mode == 0) {//����
            //ComSendCmdWatch(front,sub_stal,0x00,0x00);//�󲦼���
             ComSendCmdWatch(sub_stal,0x00,0x00,0x00);//ֱ�ӿ��ƺ� ����������
        } else if(menu.mode == 2) {//��΢��
            //ComSendCmdWatch(front,sub_setp,0x00,0x00);//�󲦼ӵ�
            ComSendCmdWatch(sub_setp,0x00,0x00,0x00);
        } else if(menu.mode == 3) {//ǰ��΢��
            ComSendCmdWatch(behind,sub_setp,0x00,0x00);//�󲦼ӵ�
        }
        PowerGet();
        LedSetMode(BattertGetLevel()+1);
        LedSetPowerFlag(1);
        
        break;
        case 0x13://ǰ������
        LedSetModeFlicker(1);
        if(menu.mode == 0) {//ֻ��������ģʽ��ʱ��ſ��Ի���
            menu.behind_set_up_count = 0;
            if(menu.behind_set_up == 0) {
                ComSendCmdWatch(behind,sub_exchange,0x00,0x00);//ǰ������
                menu.behind_set_up = 1;
            } else if(menu.behind_set_up == 1) {
                if(menu.beind_sta == 0) {
                    ComSendCmdWatch(behind,set_down,0x00,0x00);//ǰ������sub_exchange
                } else {
                    ComSendCmdWatch(behind,set_up,0x00,0x00);//ǰ������sub_exchange 
                }
            } else if(menu.behind_set_up == 2) {
                ComSendCmdWatch(behind,set_down,0x00,0x00);//ǰ������sub_exchange
            }
        }
        //ComSendCmdWatch(front,sub_stal,0x00,0x00);
        break;
        case 0x14:
        break;
        case 0x15:
        break;
        case 0x16:
        break;
        case 0x21://�����Զ��˳�
            menu.continuous = 0;//ֹͣ
            LedSetModeFlicker(0);//�Զ���������
        break;
        case 0x22://�Զ������˳�
            menu.continuous = 0;//ֹͣ
            LedSetModeFlicker(0);//�Զ���������
        break;    
        case 0x23://�Զ������Ƴ�
        break;    
        case 0x24:
        break;    
        case 0x25:
        break;    
        case 0x26:
        break; 
        case 0x30://����5s
        LedSetModeFlicker(100);
        break;
        case 0x40://����5s�ſ�
        if(menu.mode == 0) {
            menu.mode = 1;
            LedSetPower(1);
        } else if(menu.mode == 1) {//�ص�����ģʽ
            menu.mode = 0;
        } else if(menu.mode == 2) {//���ú�΢����λֵ
            menu.mode = 0;
            LedSetPower(0);
            ComSendCmdWatch(set_inti,0x00,0x00,0x00);
        } else if(menu.mode == 3) {//����ǰ��΢����λֵ
            menu.mode = 0;
            LedSetPower(0);
            ComSendCmdWatch(set_inti,0x00,0x00,0x00);
        }
        LedSetModeFlicker(1);
        break;
        default:
        break;
    }
}
/**********************************************��������***************************************************** 
* ��������: void MenuServiceTime(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �˵�ʱ�����������Ҫ���ں󲦵��Զ�����  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/18
************************************************************************************************************/ 
void MenuServiceTime(void) { 
    static u16 time_count = 0;
    if(time_count < 10000) {
        time_count++;
    } else {
        time_count = 0;
        if(menu.continuous == 1) {
            ComSendCmdWatch(sub_stal,0x00,0x00,0x00);//�󲦼ӵ�
        } else if(menu.continuous == 2) {
            ComSendCmdWatch(add_stal,0x00,0x00,0x00);//�󲦼ӵ�
        }
        if(menu.behind_set_up == 1) {
            if(menu.behind_set_up_count < 19) {
                menu.behind_set_up_count++;
            } else {
                menu.behind_set_up_count = 0;
                menu.behind_set_up = 0;
            }
        } else if(menu.behind_set_up == 2){
            
        }
    }
}


/**********************************************��������***************************************************** 
* ��������: void MenuSetBeind(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��: ����ǰ����λ  
* ��    ��: by lhb_steven
* ��    ��: 2016/6/2
************************************************************************************************************/ 
void MenuSetBeind(u8 cmd) { 
    menu.beind_sta = cmd;
}






