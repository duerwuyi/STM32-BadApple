/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ����SD����FATFS�ļ�ϵͳ��ֲ
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
/**
  ******************************************************************************
  *                              ͷ�ļ�
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "led/bsp_led.h" 
#include "usart/bsp_debug_usart.h"
#include "sdram/bsp_sdram.h"   
#include "systick/bsp_systick.h"
#include "lcd/bsp_lcd.h"  
#include "ff.h"
/**
  ******************************************************************************
  *                              �������
  ******************************************************************************
  */
#define len1 38400
#define len2 9600
FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL fnew;													/* �ļ����� */
FRESULT res_flash;                /* �ļ�������� */
UINT fnum;            					  /* �ļ��ɹ���д���� */
BYTE ReadBuffer[len1]={0};        /* �������� */  

//1.���SDIO����
//2.��diskio.c�ļ����sdio�����ӿ�
//3.���ffconf.h�ļ�
//4.�����ַ4�ֽڶ���

/**
	*********************************************************************************************************
	* Description : ��ʼ��BL8782 WiFiģ��ʹ�����ţ�������WiFiģ��
	* Argument(s) : none.
	* Return(s)   : none.
	*********************************************************************************************************
	*/
static void BL8782_PDN_INIT(void)
{
  /*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOG, &GPIO_InitStructure);	
  
  GPIO_ResetBits(GPIOG,GPIO_Pin_9);  //����WiFiģ��
}

/**
  ******************************************************************************
  *                                ������
  ******************************************************************************
  */
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    /* ����WiFiģ�� */
	BL8782_PDN_INIT();
  
	/* ��ʼ��LED */
	SDRAM_Init();
	LED_GPIO_Config();	
	LCD_Init();
	//SysTick_Init();
	
	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();	
  printf("****** ����һ�� SD �ļ�ϵͳʵ�� ******\r\n");
  
	//���ⲿSD�����ļ�ϵͳ���ļ�ϵͳ����ʱ���SD�豸��ʼ��
	res_flash = f_mount(&fs,"0:",1);
	
/*----------------------- ��ʽ������ ---------------------------*/  
	if(res_flash!=FR_OK)
  {
    printf("�����ⲿSD�����ļ�ϵͳʧ�ܡ�(%d)\r\n",res_flash);
    printf("��������ԭ��SD��ʼ�����ɹ���\r\n");
		while(1);
  }
  else
  {
    printf("���ļ�ϵͳ���سɹ������Խ��ж��ļ�\r\n");
  }
/*------------------- �ļ�ϵͳ���� ------------------------------------*/
	printf("****** ���������ļ���ȡ... ******\r\n");
	res_flash = f_open(&fnew, "0:badapple640^480_20fps.bin", FA_OPEN_EXISTING | FA_READ); 	
  // res_flash = f_open(&fnew, "BadApple_10fps_320X240.bin", FA_OPEN_EXISTING | FA_READ); 	
	if(res_flash == FR_OK)
	{
		LED_GREEN;
		printf("�����ļ��ɹ���\r\n");
		//LCD_clear();
		//while(1){
    while(f_read(&fnew, ReadBuffer, len1, &fnum) ==0 ){
			//printf("%d \r\n",ReadBuffer[1000]);
			Bad_Apple(ReadBuffer);
			//Bad_Apple2(ReadBuffer);
			//DIS_Line();
			//LED2_TOGGLE;
			//Delay_ms(40);
		}
    //printf("�����ļ���ȡ������(%d)\n",res_flash);	
	}
	else
	{
		LED_RED;
		printf("�������ļ�ʧ�ܡ�\r\n");
	}
	/* ���ٶ�д���ر��ļ� */
	f_close(&fnew);	
  
	/* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
	f_mount(NULL,"0:",1);
  
  /* ������ɣ�ͣ�� */
	while(1)
	{
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
