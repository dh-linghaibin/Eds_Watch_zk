

#ifndef COM_H
#define COM_H

#include "Type.h"

void ComInit(void);
u8 ComGetData(u8 num);
u8 ComGetFlag(void);
void ComClearFlag(void);
void ComSendCmdWatch(u8 cmd,u8 par1,u8 par2,u8 par3);

void ComAskCmd(void);

#define add_stal 0xe1//�ӵ�
#define sub_stal 0xe2//����
#define sub_exchange 0xe3//����
#define add_setp 0x03//������
#define sub_setp 0x04//������
#define dce_gear 0x05//��ѯ��ǰ��λ
#define dce_powe 0x06//��ѯ����
#define set_inti 0x07//���ó�ʼλ
#define set_end 0x08//���ý���λ
#define reset 0x09//��λ
#define stuck 0x0a//����

#define front 0x0b //ǰ��
#define behind 0x0c //��
#define stopwatch 0x0d //���
#define null 0x00 //���κ�

#define set_up 0xb1//ǿ��������
#define set_down 0xb0//

#endif
