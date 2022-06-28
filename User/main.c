/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   基于SD卡的FATFS文件系统移植
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
/**
  ******************************************************************************
  *                              头文件
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
  *                              定义变量
  ******************************************************************************
  */
#define len1 38400
#define len2 9600
FATFS fs;													/* FatFs文件系统对象 */
FIL fnew;													/* 文件对象 */
FRESULT res_flash;                /* 文件操作结果 */
UINT fnum;            					  /* 文件成功读写数量 */
BYTE ReadBuffer[len1]={0};        /* 读缓冲区 */  

//1.添加SDIO驱动
//2.在diskio.c文件添加sdio操作接口
//3.检查ffconf.h文件
//4.处理地址4字节对齐

/**
	*********************************************************************************************************
	* Description : 初始化BL8782 WiFi模块使能引脚，并禁用WiFi模块
	* Argument(s) : none.
	* Return(s)   : none.
	*********************************************************************************************************
	*/
static void BL8782_PDN_INIT(void)
{
  /*定义一个GPIO_InitTypeDef类型的结构体*/
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOG, ENABLE); 							   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
  GPIO_Init(GPIOG, &GPIO_InitStructure);	
  
  GPIO_ResetBits(GPIOG,GPIO_Pin_9);  //禁用WiFi模块
}

/**
  ******************************************************************************
  *                                任务函数
  ******************************************************************************
  */
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    /* 禁用WiFi模块 */
	BL8782_PDN_INIT();
  
	/* 初始化LED */
	SDRAM_Init();
	LED_GPIO_Config();	
	LCD_Init();
	//SysTick_Init();
	
	/* 初始化调试串口，一般为串口1 */
	Debug_USART_Config();	
  printf("****** 这是一个 SD 文件系统实验 ******\r\n");
  
	//在外部SD挂载文件系统，文件系统挂载时会对SD设备初始化
	res_flash = f_mount(&fs,"0:",1);
	
/*----------------------- 格式化测试 ---------------------------*/  
	if(res_flash!=FR_OK)
  {
    printf("！！外部SD挂载文件系统失败。(%d)\r\n",res_flash);
    printf("！！可能原因：SD初始化不成功。\r\n");
		while(1);
  }
  else
  {
    printf("》文件系统挂载成功，可以进行读文件\r\n");
  }
/*------------------- 文件系统：读 ------------------------------------*/
	printf("****** 即将进行文件读取... ******\r\n");
	res_flash = f_open(&fnew, "0:badapple640^480_20fps.bin", FA_OPEN_EXISTING | FA_READ); 	
  // res_flash = f_open(&fnew, "BadApple_10fps_320X240.bin", FA_OPEN_EXISTING | FA_READ); 	
	if(res_flash == FR_OK)
	{
		LED_GREEN;
		printf("》打开文件成功。\r\n");
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
    //printf("！！文件读取结束：(%d)\n",res_flash);	
	}
	else
	{
		LED_RED;
		printf("！！打开文件失败。\r\n");
	}
	/* 不再读写，关闭文件 */
	f_close(&fnew);	
  
	/* 不再使用文件系统，取消挂载文件系统 */
	f_mount(NULL,"0:",1);
  
  /* 操作完成，停机 */
	while(1)
	{
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
