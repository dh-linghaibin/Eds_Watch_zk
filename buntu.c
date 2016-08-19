/*******************************************************************************
* Copyright 2016 HangZhou ���ݾ���Ƽ����޹�˾
* All right reserved
*
* �ļ����ƣ�buntu.h
*
* �ļ���ʶ��
* ժ    Ҫ��
*
*
* ��ǰ�汾��v1.1
* ��    �ߣ�lhb Steven
* ������ڣ�2016/3/14
* ���뻷����C:\Program Files (x86)\IAR Systems\Embedded Workbench 6.5\stm8        
*
* ��ʷ��Ϣ��
*******************************************************************************/
#include "buntu.h"
#include "Delay.h"
#include "Time.h"
#include "Power.h"
#include "Led.h"

#define BUNTU_REAR1     PB_IDR_IDR7
#define BUNTU_REAR2     PB_IDR_IDR5
#define BUNTU_BEHIND1   PB_IDR_IDR5
#define BUNTU_BEHIND2   PB_IDR_IDR5
#define BUNTU_MODE      PB_IDR_IDR5

#define Mountain_Bike   0x01 //ɽ�س�
#define Road_Bike       0x00//��·�� 

#define BACK Mountain_Bike  //ѡ�����г��汾

typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;

typedef enum
{
  EXTI_Pin_0 = (uint8_t)0x00, /*!< GPIO Pin 0 */
  EXTI_Pin_1 = (uint8_t)0x02, /*!< GPIO Pin 1 */
  EXTI_Pin_2 = (uint8_t)0x04, /*!< GPIO Pin 2 */
  EXTI_Pin_3 = (uint8_t)0x06, /*!< GPIO Pin 3 */
  EXTI_Pin_4 = (uint8_t)0x10, /*!< GPIO Pin 4 */
  EXTI_Pin_5 = (uint8_t)0x12, /*!< GPIO Pin 5 */
  EXTI_Pin_6 = (uint8_t)0x14, /*!< GPIO Pin 6 */
  EXTI_Pin_7 = (uint8_t)0x16  /*!< GPIO Pin 7 */
} EXTI_Pin_TypeDef;

typedef enum
{
  EXTI_Trigger_Falling_Low    = (uint8_t)0x00, /*!< Interrupt on Falling edge and Low level */
  EXTI_Trigger_Rising         = (uint8_t)0x01, /*!< Interrupt on Rising edge only */
  EXTI_Trigger_Falling        = (uint8_t)0x02, /*!< Interrupt on Falling edge only */
  EXTI_Trigger_Rising_Falling = (uint8_t)0x03  /*!< Interrupt on Rising and Falling edges */
} EXTI_Trigger_TypeDef;


void EXTI_SetPinSensitivity(EXTI_Pin_TypeDef EXTI_Pin, EXTI_Trigger_TypeDef EXTI_Trigger)
{

  /* Check function parameters */
 // assert_param(IS_EXTI_PINNUM(EXTI_Pin));
  //assert_param(IS_EXTI_TRIGGER(EXTI_Trigger));

  /* Clear port sensitivity bits */
  switch (EXTI_Pin)
  {
    case EXTI_Pin_0:
      EXTI_CR1 &=  (uint8_t)(~0x03);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_1:
      EXTI_CR1 &=  (uint8_t)(~0x0C);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_2:
      EXTI_CR1 &=  (uint8_t)(~0x30);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_3:
      EXTI_CR1 &=  (uint8_t)(~0xC0);
      EXTI_CR1 |= (uint8_t)((uint8_t)(EXTI_Trigger) << EXTI_Pin);
      break;
    case EXTI_Pin_4:
      EXTI_CR2 &=  (uint8_t)(~0x03);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_5:
      EXTI_CR2 &=  (uint8_t)(~0x0C);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_6:
      EXTI_CR2 &=  (uint8_t)(~0x30);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    case EXTI_Pin_7:
      EXTI_CR2 &=  (uint8_t)(~0xC0);
      EXTI_CR2 |= (uint8_t)((uint8_t)(EXTI_Trigger) << ((uint8_t)EXTI_Pin & (uint8_t)0xEF));
      break;
    default:
      break;
  }
}
#define assert_param(expr) ((void)0)
typedef enum
{
  EXTI_IT_Pin0    = (uint16_t)0x0001, /*!< GPIO Pin pos 0 */
  EXTI_IT_Pin1    = (uint16_t)0x0002, /*!< GPIO Pin pos 1 */
  EXTI_IT_Pin2    = (uint16_t)0x0004, /*!< GPIO Pin pos 2 */
  EXTI_IT_Pin3    = (uint16_t)0x0008, /*!< GPIO Pin pos 3 */
  EXTI_IT_Pin4    = (uint16_t)0x0010, /*!< GPIO Pin pos 4 */
  EXTI_IT_Pin5    = (uint16_t)0x0020, /*!< GPIO Pin pos 5 */
  EXTI_IT_Pin6    = (uint16_t)0x0040, /*!< GPIO Pin pos 6 */
  EXTI_IT_Pin7    = (uint16_t)0x0080, /*!< GPIO Pin pos 7 */
  EXTI_IT_PortB   = (uint16_t)0x0101, /*!< GPIO Port B    */
  EXTI_IT_PortD   = (uint16_t)0x0102, /*!< GPIO Port D    */
  EXTI_IT_PortE   = (uint16_t)0x0104, /*!< GPIO Port E    */
  EXTI_IT_PortF   = (uint16_t)0x0108, /*!< GPIO Port F    */
  EXTI_IT_PortG   = (uint16_t)0x0110, /*!< GPIO Port G    */
  EXTI_IT_PortH   = (uint16_t)0x0120  /*!< GPIO Port H    */
} EXTI_IT_TypeDef;

void EXTI_ClearITPendingBit(EXTI_IT_TypeDef EXTI_IT)
{
  uint16_t tempvalue = 0;

  /* Check function parameters */
  assert_param(IS_EXTI_ITPENDINGBIT(EXTI_IT));

  tempvalue = ((uint16_t)EXTI_IT & (uint16_t)0xFF00);

  if ( tempvalue == 0x0100)
  {
    EXTI_SR2 = (uint8_t)((uint16_t)EXTI_IT & (uint16_t)0x00FF);
  }
  else
  {
    EXTI_SR1 = (uint8_t) (EXTI_IT);
  }
}

/**********************************************��������***************************************************** 
* ��������: void BuntuInit(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ������ʼ��  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/14
************************************************************************************************************/ 
void BuntuInit(void) { 
    PB_DDR_DDR7 = 0; //ǰ����
    PB_CR1_C17 = 1;
    PB_CR2_C27 = 0;
    
    PB_DDR_DDR5 = 0;//ǰ����
    PB_CR1_C15 = 1;
    PB_CR2_C25 = 0;
    
//    PB_DDR_DDR6 = 0;//�󲦼�
//    PB_CR1_C16 = 1;
//    PB_CR2_C26 = 0;
//    
//    PB_DDR_DDR7 = 0;//�󲦼�
//    PB_CR1_C17 = 1;
//    PB_CR2_C27 = 0;
//    
//    PB_DDR_DDR0 = 0;//����
//    PB_CR1_C10 = 1;
//    PB_CR2_C20 = 0;
    
    //EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Falling); 
    //EXTI_SetPinSensitivity(EXTI_Pin_4,EXTI_Trigger_Falling); 
    EXTI_SetPinSensitivity(EXTI_Pin_5,EXTI_Trigger_Falling); 
    //EXTI_SetPinSensitivity(EXTI_Pin_6,EXTI_Trigger_Falling);
    EXTI_SetPinSensitivity(EXTI_Pin_7,EXTI_Trigger_Falling); 
    
    //�����Ǹ�ͨѶʹ�õ� 
    EXTI_SetPinSensitivity(EXTI_Pin_2,EXTI_Trigger_Falling); //pa2
}


/**********************************************��������***************************************************** 
* ��������: u8 BuntuRead(void) 
* �������: void 
* ���ز���: u8  
* ��    ��: ��ȡ����״̬  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/14
************************************************************************************************************/ 
u8 BuntuRead(void) { 
    static u16 count1 = 0;
    static u16 count2 = 0;
    static u16 long_count = 0;//������������
    static u8 count_small1 = 0;
    static u8 count_small2 = 0;
    static u8 mode_count = 0;//ģʽ
    static u8 teae_flag = 0;//����ϱ�־
    if(BUNTU_REAR1 == 0) {//�󲦰�ť1
        TimerSetSec(0);//�������״̬
        if(count_small1 < 30) {
            count_small1++;
        } else {
            count_small1 = 0;
            if(count1 < 6000) {
                count1++;
            }
            if(count1 == 100) {//�������¾ʹ���
                if(count2 == 0) {//���Ű���Ҫͬʱ���²���Ч
                   if(mode_count == 0) {//δ����һ���µ�ģʽ
                        return 0x11;
                    }
                }
            }
            if( (count1 == 2000) && (teae_flag == 0x00) ){
                //��������
                if(count2 == 0) {//���Ű���Ҫͬʱ���²���Ч
                    if(mode_count == 0) {//δ����һ���µ�ģʽ
                        teae_flag = 0x01;
                        return 0x01;
                    }
                }
            }
            //�ж��ǲ��ǽ��볤��ģʽ
            if(teae_flag == 0x01) {
                if(count2 > 10) {
                    teae_flag = 0;
                    return 0x21;
                }
            }
        }
    } else {
        if(count1 > 1500) {//ֻҪ��һ���ɿ��ͽ���
            teae_flag = 0x00;
            count1 = 0;
            return 0x21;
        }
       // teae_flag = 0;
        count_small1 = 0;
        count1 = 0;
    }
    
    if(BUNTU_REAR2 == 0) {//�󲦰�ť2   
        TimerSetSec(0);//�������״̬
        if(count_small2 < 30) {
            count_small2++;
        } else {
            count_small2 = 0;
            if(count2 < 3000) {
                count2++;
            }
            if(count2 == 100) {
                if(count1 == 0) {//С�İ������ܰ���
                    if(mode_count == 0) {//δ����һ���µ�ģʽ
                        return 0x12;    
                    }
                }   
            }
            if( (count2 == 2000)  && (teae_flag == 0x00) ){
                //��������
                if(count1 == 0) {//С�İ������ܰ���
                    if(mode_count == 0) {//δ����һ���µ�ģʽ
                        teae_flag = 0x02;
                        return 0x02;    
                    }
                }
            }
            //�ж��ǲ��ǽ��볤��ģʽ
            if(teae_flag == 0x02) {
                if(count1 > 10) {
                    teae_flag = 0;
                    return 0x22;
                }
            }
        }
    } else {
        if(count2 > 1500) {
            count2 = 0;
            return 0x22;
        }
        //teae_flag = 0;
        count_small2 = 0;
        count2 = 0;
    }
    //��ϰ���
    if( (count1 > 2500) && (count2 > 2500) ) {
        if(teae_flag == 0) {
            if(long_count < 5000) {
                long_count++;
            } else {
                TimerSetSec(0);
                long_count = 0;
                teae_flag = 0x30;
                return 0x30;
            }
        }
    } else {
        long_count = 0;
        //˵�������
        if(teae_flag == 0x30) {
            teae_flag = 0x00;
            return 0x40;
        }
    }
    
    return 0x00;
}
/**********************************************��������***************************************************** 
* ��������: void BuntuSleep(void) 
* �������: void 
* ���ز���: void  
* ��    ��: ˯��ʡ��  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/18
************************************************************************************************************/ 
void BuntuSleep(void) { 
    //PB_CR2_C24 = 1;
    PB_CR2_C25 = 1;
    //PB_CR2_C26 = 1;
    PB_CR2_C27 = 1;
    //PB_CR2_C20 = 1;
    PowerSet(0);//�رպ󲦵�Դ
    PA_CR2_C22 = 0;//�ر�ͨѶ�ж� ֻ���ܰ���
    PowerSetGet(0);
    LedSetPower(0);//�ر�LED
    DelayMs(100);
    MCUSLEEP
}
/**********************************************��������***************************************************** 
* ��������: void BuntuOpen(void) 
* �������: void 
* ���ز���: void  
* ��    ��: �˳�����״̬  
* ��    ��: by lhb_steven
* ��    ��: 2016/3/18
************************************************************************************************************/ 
void BuntuOpen(void) { 
    //PB_CR2_C24 = 0;
    PowerSet(1);//�򿪺󲦵�Դ
    PowerSetGet(1);
    PB_CR2_C25 = 0;
    //PB_CR2_C26 = 0;
    PB_CR2_C27 = 0;
    //PB_CR2_C20 = 0;
    EXTI_SR1 = 0xff;
    PA_CR2_C22 = 1;//��ͨѶ�ж� ֻ���ܰ���
}

#pragma vector=10
__interrupt void EXTI0_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin0);
    BuntuOpen();
    INTEN
    return;
}

#pragma vector=14
__interrupt void EXTI4_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin4);
    BuntuOpen();
    INTEN
    return;
}


#pragma vector=15
__interrupt void EXTI5_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin5);
    BuntuOpen();
    INTEN
    return;
}

#pragma vector=16
__interrupt void EXTI6_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin6);
    BuntuOpen();
    INTEN
    return;
}

#pragma vector=17
__interrupt void EXTI7_IRQHandler(void)
{
    INTOFF
    EXTI_ClearITPendingBit(EXTI_IT_Pin7);
    BuntuOpen();
    INTEN
    return;
}


//#pragma vector=8
//__interrupt void EXTIB6_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=13
//__interrupt void EXTIB1_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=14
//__interrupt void EXTIB2_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=15
//__interrupt void EXTIB3_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=16
//__interrupt void EXTIB4_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//#pragma vector=17
//__interrupt void EXTIB5_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=9
//__interrupt void EXTIB7_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=10
//__interrupt void EXTIB8_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=11
//__interrupt void EXTIB9_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=18
//__interrupt void EXTIB10_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=19
//__interrupt void EXTIB11_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=20
//__interrupt void EXTIB12_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=21
//__interrupt void EXTIB13_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}
//
//#pragma vector=22
//__interrupt void EXTIB14_IRQHandler(void)
//{
//    INTOFF
//    BuntuOpen();
//    INTEN
//    return;
//}

