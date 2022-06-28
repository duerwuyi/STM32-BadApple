/**
  ******************************************************************************
  * @file    bsp_sdram.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   LCD�����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������  
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./lcd/bsp_lcd.h"   


//1.��ʼ��LCD����������
//2.ʹ��LTDC��ʼ���ṹ�壬����Һ�����Ŀ��Ʋ���
//3.ʹ��LTDC�Ĳ㼶��ʼ���ṹ�壬���ø���Ŀ��Ʋ���
//4.ֱ�Ӳٿ��Դ棬����Һ������ʾͼ��
//5.ʹ��DMA2D���ٻ���ֱ�߼�����



//1.��ʼ��LCD����������

static void LCD_GPIO_Config(void)
{
 GPIO_InitTypeDef GPIO_InitStruct;

 /* ʹ��LCDʹ�õ�������ʱ�� */
                         //��ɫ������
 RCC_AHB1PeriphClockCmd(LTDC_R0_GPIO_CLK | LTDC_R1_GPIO_CLK | LTDC_R2_GPIO_CLK|
                        LTDC_R3_GPIO_CLK | LTDC_R4_GPIO_CLK | LTDC_R5_GPIO_CLK|
                        LTDC_R6_GPIO_CLK | LTDC_R7_GPIO_CLK |
                         //��ɫ������
                         LTDC_G0_GPIO_CLK|LTDC_G1_GPIO_CLK|LTDC_G2_GPIO_CLK|
                         LTDC_G3_GPIO_CLK|LTDC_G4_GPIO_CLK|LTDC_G5_GPIO_CLK|
                         LTDC_G6_GPIO_CLK|LTDC_G7_GPIO_CLK|
                         //��ɫ������
                         LTDC_B0_GPIO_CLK|LTDC_B1_GPIO_CLK|LTDC_B2_GPIO_CLK|
                         LTDC_B3_GPIO_CLK|LTDC_B4_GPIO_CLK|LTDC_B5_GPIO_CLK|
                         LTDC_B6_GPIO_CLK|LTDC_B7_GPIO_CLK|
                         //�����ź���
                         LTDC_CLK_GPIO_CLK | LTDC_HSYNC_GPIO_CLK |LTDC_VSYNC_GPIO_CLK|
                         LTDC_DE_GPIO_CLK  | LTDC_BL_GPIO_CLK    |LTDC_DISP_GPIO_CLK ,ENABLE);


/* GPIO���� */

/* ��ɫ������ */
 GPIO_InitStruct.GPIO_Pin = LTDC_R0_GPIO_PIN;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

 GPIO_Init(LTDC_R0_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R0_GPIO_PORT, LTDC_R0_PINSOURCE, LTDC_R0_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_R1_GPIO_PIN;
 GPIO_Init(LTDC_R1_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R1_GPIO_PORT, LTDC_R1_PINSOURCE, LTDC_R1_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_R2_GPIO_PIN;
 GPIO_Init(LTDC_R2_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R2_GPIO_PORT, LTDC_R2_PINSOURCE, LTDC_R2_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_R3_GPIO_PIN;
 GPIO_Init(LTDC_R3_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R3_GPIO_PORT, LTDC_R3_PINSOURCE, LTDC_R3_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_R4_GPIO_PIN;
 GPIO_Init(LTDC_R4_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R4_GPIO_PORT, LTDC_R4_PINSOURCE, LTDC_R4_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_R5_GPIO_PIN;
 GPIO_Init(LTDC_R5_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R5_GPIO_PORT, LTDC_R5_PINSOURCE, LTDC_R5_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_R6_GPIO_PIN;
 GPIO_Init(LTDC_R6_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R6_GPIO_PORT, LTDC_R6_PINSOURCE, LTDC_R6_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_R7_GPIO_PIN;
 GPIO_Init(LTDC_R7_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_R7_GPIO_PORT, LTDC_R7_PINSOURCE, LTDC_R7_AF);

 //��ɫ������
 GPIO_InitStruct.GPIO_Pin = LTDC_G0_GPIO_PIN;
 GPIO_Init(LTDC_G0_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G0_GPIO_PORT, LTDC_G0_PINSOURCE, LTDC_G0_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_G1_GPIO_PIN;
 GPIO_Init(LTDC_G1_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G1_GPIO_PORT, LTDC_G1_PINSOURCE, LTDC_G1_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_G2_GPIO_PIN;
 GPIO_Init(LTDC_G2_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G2_GPIO_PORT, LTDC_G2_PINSOURCE, LTDC_G2_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_G3_GPIO_PIN;
 GPIO_Init(LTDC_G3_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G3_GPIO_PORT, LTDC_G3_PINSOURCE, LTDC_G3_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_G4_GPIO_PIN;
 GPIO_Init(LTDC_G4_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G4_GPIO_PORT, LTDC_G4_PINSOURCE, LTDC_G4_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_G5_GPIO_PIN;
 GPIO_Init(LTDC_G5_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G5_GPIO_PORT, LTDC_G5_PINSOURCE, LTDC_G5_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_G6_GPIO_PIN;
 GPIO_Init(LTDC_G6_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G6_GPIO_PORT, LTDC_G6_PINSOURCE, LTDC_G6_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_G7_GPIO_PIN;
 GPIO_Init(LTDC_G7_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_G7_GPIO_PORT, LTDC_G7_PINSOURCE, LTDC_G7_AF);

 //��ɫ������
 GPIO_InitStruct.GPIO_Pin = LTDC_B0_GPIO_PIN;
 GPIO_Init(LTDC_B0_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B0_GPIO_PORT, LTDC_B0_PINSOURCE, LTDC_B0_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_B1_GPIO_PIN;
 GPIO_Init(LTDC_B1_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B1_GPIO_PORT, LTDC_B1_PINSOURCE, LTDC_B1_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_B2_GPIO_PIN;
 GPIO_Init(LTDC_B2_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B2_GPIO_PORT, LTDC_B2_PINSOURCE, LTDC_B2_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_B3_GPIO_PIN;
 GPIO_Init(LTDC_B3_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B3_GPIO_PORT, LTDC_B3_PINSOURCE, LTDC_B3_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_B4_GPIO_PIN;
 GPIO_Init(LTDC_B4_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B4_GPIO_PORT, LTDC_B4_PINSOURCE, LTDC_B4_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_B5_GPIO_PIN;
 GPIO_Init(LTDC_B5_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B5_GPIO_PORT, LTDC_B5_PINSOURCE, LTDC_B5_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_B6_GPIO_PIN;
 GPIO_Init(LTDC_B6_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B6_GPIO_PORT, LTDC_B6_PINSOURCE, LTDC_B6_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_B7_GPIO_PIN;
 GPIO_Init(LTDC_B7_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_B7_GPIO_PORT, LTDC_B7_PINSOURCE, LTDC_B7_AF);

 //�����ź���
 GPIO_InitStruct.GPIO_Pin = LTDC_CLK_GPIO_PIN;
 GPIO_Init(LTDC_CLK_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_CLK_GPIO_PORT, LTDC_CLK_PINSOURCE, LTDC_CLK_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_HSYNC_GPIO_PIN;
 GPIO_Init(LTDC_HSYNC_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_HSYNC_GPIO_PORT, LTDC_HSYNC_PINSOURCE, LTDC_HSYNC_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_VSYNC_GPIO_PIN;
 GPIO_Init(LTDC_VSYNC_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_VSYNC_GPIO_PORT, LTDC_VSYNC_PINSOURCE, LTDC_VSYNC_AF);

 GPIO_InitStruct.GPIO_Pin = LTDC_DE_GPIO_PIN;
 GPIO_Init(LTDC_DE_GPIO_PORT, &GPIO_InitStruct);
 GPIO_PinAFConfig(LTDC_DE_GPIO_PORT, LTDC_DE_PINSOURCE, LTDC_DE_AF);

 //BL DISP
 GPIO_InitStruct.GPIO_Pin = LTDC_DISP_GPIO_PIN;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
 GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

 GPIO_Init(LTDC_DISP_GPIO_PORT, &GPIO_InitStruct);


 GPIO_InitStruct.GPIO_Pin = LTDC_BL_GPIO_PIN;
 GPIO_Init(LTDC_BL_GPIO_PORT, &GPIO_InitStruct);

 //����ʹ��lcd
 GPIO_SetBits(LTDC_DISP_GPIO_PORT,LTDC_DISP_GPIO_PIN);
 GPIO_SetBits(LTDC_BL_GPIO_PORT,LTDC_BL_GPIO_PIN);
}  



#define HSW    2
#define VSW    2
#define HBP    46
#define VBP    23
#define HFP    210 
#define VFP     22






//2.ʹ��LTDC��ʼ���ṹ�壬����Һ�����Ŀ��Ʋ���
static void LCD_Mode_Config(void)
{
  LTDC_InitTypeDef LTDC_InitTypeStruct;  
  
    //CLK���25 MHz 
  //N =200
  //Q = 20 //����Ҫ
  //R= 2
  //DIV =4
  
  RCC_PLLSAIConfig(200,20,2);
  
  RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div4);
  
  RCC_PLLSAICmd (ENABLE );
  
  
  //�ȴ�RCCʱ��ʹ�����
  while(RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC,ENABLE);
  
  RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_DMA2D,ENABLE);
  
  //���ż���
  LTDC_InitTypeStruct.LTDC_HSPolarity = LTDC_HSPolarity_AL ; //HSYNC�͵�ƽ��Ч
  LTDC_InitTypeStruct.LTDC_VSPolarity = LTDC_VSPolarity_AL  ;//VSYNC�͵�ƽ��Ч
  LTDC_InitTypeStruct.LTDC_DEPolarity = LTDC_DEPolarity_AL; //DE�͵�ƽ��Ч
  LTDC_InitTypeStruct.LTDC_PCPolarity = LTDC_PCPolarity_IPC ;//�����زɼ�����
  
  //ʱ�����
  LTDC_InitTypeStruct.LTDC_HorizontalSync = HSW - 1;
  LTDC_InitTypeStruct.LTDC_VerticalSync = VSW - 1;
  LTDC_InitTypeStruct.LTDC_AccumulatedHBP = HSW+HBP -1 ; 
  LTDC_InitTypeStruct.LTDC_AccumulatedVBP = VSW +VBP -1;
  
  LTDC_InitTypeStruct.LTDC_AccumulatedActiveW = HSW+HBP + LCD_WIDTH  -1;
  LTDC_InitTypeStruct.LTDC_AccumulatedActiveH = VSW+VBP+LCD_HEIGHT -1;
  
  LTDC_InitTypeStruct.LTDC_TotalWidth =  HSW+HBP + LCD_WIDTH + HFP -1;; 
  LTDC_InitTypeStruct.LTDC_TotalHeigh = VSW+VBP+LCD_HEIGHT + VFP -1;
  
  
  //����µı�������ɫ
  LTDC_InitTypeStruct.LTDC_BackgroundRedValue = 0;
  LTDC_InitTypeStruct.LTDC_BackgroundBlueValue = 0;
  LTDC_InitTypeStruct.LTDC_BackgroundGreenValue = 0;  
  
  LTDC_Init(&LTDC_InitTypeStruct);
    
}

//3.ʹ��LTDC�Ĳ㼶��ʼ���ṹ�壬���ø���Ŀ��Ʋ���
static void LCD_Layer_Init(void)
{
  LTDC_Layer_InitTypeDef LTDC_Layer_InitTypeStruct;
  
  
  //���ò㼶�������
  LTDC_Layer_InitTypeStruct.LTDC_HorizontalStart = HBP + HSW;
  LTDC_Layer_InitTypeStruct.LTDC_HorizontalStop = HSW+HBP + LCD_WIDTH  -1;  
  LTDC_Layer_InitTypeStruct.LTDC_VerticalStart = VBP + VSW;
  LTDC_Layer_InitTypeStruct.LTDC_VerticalStop =  VSW+VBP+LCD_HEIGHT -1;
  
  LTDC_Layer_InitTypeStruct.LTDC_PixelFormat = LTDC_Pixelformat_RGB565;
  
  //0Ϊ͸����0xFFΪ��͸��
  LTDC_Layer_InitTypeStruct.LTDC_ConstantAlpha = 0xFF;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorRed = 0;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorGreen = 0;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorBlue = 0;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorAlpha = 0;
  
  //�������
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_CA  ;
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_CA  ;

  //�����Դ���صĲ���
  LTDC_Layer_InitTypeStruct.LTDC_CFBStartAdress  = LCD_LAYER1_START_ADDR;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineLength = LCD_WIDTH * 2 +3;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineNumber = LCD_HEIGHT;  
  LTDC_Layer_InitTypeStruct.LTDC_CFBPitch = LCD_WIDTH * 2;
  
  //LTDC_LayerInit(LTDC_Layer1,&LTDC_Layer_InitTypeStruct); 
  
  
  //���õڶ���
  
  LTDC_Layer_InitTypeStruct.LTDC_PixelFormat = LTDC_Pixelformat_ARGB8888;

  //�������
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_PAxCA  ;
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA  ;

  //�����Դ���صĲ���
  LTDC_Layer_InitTypeStruct.LTDC_CFBStartAdress  = LCD_LAYER2_START_ADDR;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineLength = LCD_WIDTH * 4 +3;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineNumber = LCD_HEIGHT;  
  LTDC_Layer_InitTypeStruct.LTDC_CFBPitch = LCD_WIDTH * 4;
  
  LTDC_LayerInit(LTDC_Layer2,&LTDC_Layer_InitTypeStruct); 

  //ʹ����������Դ
  LTDC_LayerCmd (LTDC_Layer1,ENABLE);
  LTDC_LayerCmd (LTDC_Layer2,ENABLE);

  //�������ò���
  LTDC_ReloadConfig (LTDC_IMReload);
  
  //ʹ�ܶ�����Ԫ
  LTDC_DitherCmd(ENABLE);
  
  //ʹ��LTDC
  LTDC_Cmd(ENABLE);
}


//��ʼ������
void LCD_Init(void)
{ 

  LCD_GPIO_Config();
  LCD_Mode_Config();
  LCD_Layer_Init();
}
 

void Bad_Apple(unsigned char* buf){
	uint16_t i,j,k;
	
  uint32_t *p = (uint32_t *)(LCD_LAYER2_START_ADDR + 320);
	unsigned char* t =buf;
  
  for(j=0;j<480;j++){
  for(i=0;i<80;i++)
  {
		for(k=0;k<8;k++){
			if( (((*t)>>(7-k))&0X01) ==  0X01){
				*p = 0xFF000000;
			}else{
				*p = 0xFFFFFFFF;
			}
			p++;
		}
		t++;
    //ARGB8888 
    }
		p += 160;
		}
}

void Bad_Apple2(unsigned char* buf){
	uint16_t i,j,k;
	
  uint32_t *p = (uint32_t *)(LCD_LAYER2_START_ADDR ) ;
	unsigned char* t =buf;
  
  for(j=0;j<240;j++){
  for(i=0;i<40;i++)
  {
		for(k=0;k<8;k++){
			if( (((*t)>>(7-k))&0X01) ==  0X01){
				*p = 0xFF000000;
			}else{
				*p = 0xFFFFFFFF;
			}
			p++;
		}
		t++;
    //ARGB8888 
    }
		p += 480;
		}
}


void LCD_clear(void){
  uint16_t i,j;
	
  uint32_t *p = (uint32_t *)(LCD_LAYER2_START_ADDR ) ;
  
  for(j=0;j<240;j++){
  for(i=0;i<800;i++)
  {
			*p = 0xFF000000;
			p++;
		}
    }
}

/*********************************************END OF FILE**********************/

