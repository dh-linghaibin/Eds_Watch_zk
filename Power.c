/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��
* ��    �ߣ�lhb Steven
* ������ڣ�2016/6/18
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "Power.h"

//�󲦵�Դ����
#define READ PB_ODR_ODR1

static u8 batter_level = 0;

#define CLK_ADC1   0

#define BATTERY_EN PB_ODR_ODR4
#define COM_EN PB_ODR_ODR0
/**********************************************��������***************************************************** 
* ��������: void PowerInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/18
************************************************************************************************************/ 
void PowerInit(void) {
    //�󲦵�Դʹ��
    PB_DDR_DDR1 = 1;
    PB_CR1_C11 = 1;
    PB_CR2_C21 = 0;
    //�����򿪺󲦵�Դ
    PowerSet(1);
    
    //��ѹ���ʹ��
    PB_DDR_DDR4 = 1;
    PB_CR1_C14 = 1;
    PB_CR2_C24 = 0;
    //��ѹ���PB3
    PB_DDR_DDR3 = 0;
    PB_CR1_C13 = 0;
    PB_CR2_C23 = 0;
    
    //����ͨѶ����
    PB_DDR_DDR0 = 1;
    PB_CR1_C10 = 1;
    PB_CR2_C20 = 0;
    
    BATTERY_EN = 1;
    COM_EN = 1;
    
    CLK_PCKENR2 |= 1<<CLK_ADC1; //��ADC1ιʱ�ӣ�����ADC��������
    ADC1_CR1 = 0x01 ;//����ADC��· + ����ȡ��
    ADC1_CR2 = 0x82; //0..23ͨ����ȡ��16��Ƶ 
    ADC1_CR3 = 0x40; //24,TS,Vref ͨ����ȡ��16��Ƶ
    
//    ADC1_SR &= ~BIT(6);
//	ADC1_SR &= ~BIT(4);
//	ADC1_CR1 |= BIT(1);
//	ADC1_CR2 |= BIT(1);
	//ADC1_TDRL = 0x01;
}
/**********************************************��������***************************************************** 
* ��������: void PowerSet(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��: ���ú󲦵�Դ  
* ��    ��: by lhb_steven
* ��    ��: 2016/6/18
************************************************************************************************************/ 
void PowerSet(u8 cmd) { 
    if(cmd == 0) {
        READ = 0;//0�ر� դ����ѹ ���� Դ����ѹ
    } else {
        READ = 1;//3.3V�� ����դ����ѹ
    }
}



float PowerGetVolate(u8 chx) {
    float volate = 0;
    u16 ad_value;
    u8 ad_h = 0;
    u8 ad_l = 0;
	u8 i;
	ADC1_SQR4 = ADC1_SQR3 = ADC1_SQR2 = ADC1_SQR1 = 0;
    if (chx<=7)
    ADC1_SQR4 |= (1<<chx);
    else if (chx<=15)
    ADC1_SQR3 |= (1<<(chx-8));
    else if (chx<=23)
    ADC1_SQR2 |= (1<<(chx-16));
    ADC1_CR1 |= (1<<1);
    for (i=0  ; i<100; i++); //����ʱ��
    while ((ADC1_SR & (1<<0))==0); //�ȴ�ȡ������
    ADC1_SR &= (~(1<<0));          //�������־λ
    ad_h = ADC1_DRH;
    ad_l = ADC1_DRL;
	ad_value = (ad_h<<8) + ad_l;
    volate = (15.95*ad_value)/0xffff*10;
    return volate;
}


void PowerGet(void) {
    float bat = 0;
    bat = PowerGetVolate(15);
    if(bat > 8.2) {
    
            batter_level = 5;
   
    } else if(bat > 7.9) {
        
            batter_level = 4;
       
    } else if(bat > 7.6) {
        
            batter_level = 3;
       
    } else if(bat > 7.2) {
       
            batter_level = 2;
        
    } else if(bat > 6.8) {
        
            batter_level = 1;
     
    } else {
       
            batter_level = 0;
        
    }
}

u8 BattertGetLevel(void) {
    return batter_level;
}

/**********************************************��������***************************************************** 
* ��������: void PowerSetGet(u8 cmd) 
* �������: u8 cmd 
* ���ز���: void  
* ��    ��:   
* ��    ��: by lhb_steven
* ��    ��: 2016/6/18
************************************************************************************************************/ 
void PowerSetGet(u8 cmd) { 
    BATTERY_EN = cmd;
    if(cmd == 0) {
        //����ͨѶ����
        PB_DDR_DDR0 = 1;
        PB_CR1_C10 = 1;
        COM_EN = 0;
        //Ϊ�˵͹��� �ĳ����ģʽ
        PB_DDR_DDR3 = 1;
        PB_CR1_C13 = 1;
        //����
        PA_DDR = 0XFF;
        PA_CR1 = 0XFF;
        PB_DDR = 0XFF;
        PB_CR1 = 0XFF;
        PC_DDR = 0XFF;
        PC_CR1 = 0XFF;
        PD_DDR = 0XFF;
        PD_CR1 = 0XFF;
        
        PB_DDR_DDR7 = 0; //ǰ����
        PB_CR1_C17 = 1;
        PB_CR2_C27 = 1;
        
        PB_DDR_DDR5 = 0;//ǰ����
        PB_CR1_C15 = 1;
        PB_CR2_C25 = 1;
        
        //�ر�ADC
        ADC1_CR1 = 0x00;//����ADC��· + ����ȡ��
        TIM4_CR1 = 0x00;
        USART1_CR2 = 0x00;
        CLK_PCKENR2 = 0X00; //��ADC1ιʱ�ӣ�����ADC��������
        CLK_PCKENR1 = 0X00;
    } else {
        //Ϊ�˵͹��� �ĳ����ģʽ
        PB_DDR_DDR3 = 0;
        PB_CR1_C13 = 0;
        
        //�ָ�������״̬
        PA_DDR_DDR2 = 0;
        PA_CR1_C12 = 0;
        PA_CR2_C22 = 1;
        
        //��ADC
        CLK_PCKENR1 = 0X04;
        CLK_PCKENR2 |= 1<<CLK_ADC1; //��ADC1ιʱ�ӣ�����ADC��������
        ADC1_CR1 = 0x01 ;//����ADC��· + ����ȡ��
        USART1_CR2 = 0x2c;
        TIM4_CR1 = 0x01;
        //����ͨѶ����
        PB_DDR_DDR0 = 1;
        PB_CR1_C10 = 1;
        COM_EN = 1;
    }
} 



