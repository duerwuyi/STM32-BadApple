/**
  ******************************************************************************
  * @file    bsp_sdram.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   LCD驱动接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火  STM32 F429 开发板  
  * 论坛    :http://www.chuxue123.com
  * 淘宝    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./lcd/bsp_lcd.h"   


//1.初始化LCD驱动的引脚
//2.使用LTDC初始化结构体，配置液晶屏的控制参数
//3.使用LTDC的层级初始化结构体，配置各层的控制参数
//4.直接操控显存，控制液晶屏显示图形
//5.使用DMA2D快速绘制直线及矩形



//1.初始化LCD驱动的引脚

static void LCD_GPIO_Config(void)
{
 GPIO_InitTypeDef GPIO_InitStruct;

 /* 使能LCD使用到的引脚时钟 */
                         //红色数据线
 RCC_AHB1PeriphClockCmd(LTDC_R0_GPIO_CLK | LTDC_R1_GPIO_CLK | LTDC_R2_GPIO_CLK|
                        LTDC_R3_GPIO_CLK | LTDC_R4_GPIO_CLK | LTDC_R5_GPIO_CLK|
                        LTDC_R6_GPIO_CLK | LTDC_R7_GPIO_CLK |
                         //绿色数据线
                         LTDC_G0_GPIO_CLK|LTDC_G1_GPIO_CLK|LTDC_G2_GPIO_CLK|
                         LTDC_G3_GPIO_CLK|LTDC_G4_GPIO_CLK|LTDC_G5_GPIO_CLK|
                         LTDC_G6_GPIO_CLK|LTDC_G7_GPIO_CLK|
                         //蓝色数据线
                         LTDC_B0_GPIO_CLK|LTDC_B1_GPIO_CLK|LTDC_B2_GPIO_CLK|
                         LTDC_B3_GPIO_CLK|LTDC_B4_GPIO_CLK|LTDC_B5_GPIO_CLK|
                         LTDC_B6_GPIO_CLK|LTDC_B7_GPIO_CLK|
                         //控制信号线
                         LTDC_CLK_GPIO_CLK | LTDC_HSYNC_GPIO_CLK |LTDC_VSYNC_GPIO_CLK|
                         LTDC_DE_GPIO_CLK  | LTDC_BL_GPIO_CLK    |LTDC_DISP_GPIO_CLK ,ENABLE);


/* GPIO配置 */

/* 红色数据线 */
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

 //绿色数据线
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

 //蓝色数据线
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

 //控制信号线
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

 //拉高使能lcd
 GPIO_SetBits(LTDC_DISP_GPIO_PORT,LTDC_DISP_GPIO_PIN);
 GPIO_SetBits(LTDC_BL_GPIO_PORT,LTDC_BL_GPIO_PIN);
}  



#define HSW    2
#define VSW    2
#define HBP    46
#define VBP    23
#define HFP    210 
#define VFP     22






//2.使用LTDC初始化结构体，配置液晶屏的控制参数
static void LCD_Mode_Config(void)
{
  LTDC_InitTypeDef LTDC_InitTypeStruct;  
  
    //CLK输出25 MHz 
  //N =200
  //Q = 20 //不重要
  //R= 2
  //DIV =4
  
  RCC_PLLSAIConfig(200,20,2);
  
  RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div4);
  
  RCC_PLLSAICmd (ENABLE );
  
  
  //等待RCC时钟使能完成
  while(RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC,ENABLE);
  
  RCC_AHB1PeriphClockCmd (RCC_AHB1Periph_DMA2D,ENABLE);
  
  //引脚极性
  LTDC_InitTypeStruct.LTDC_HSPolarity = LTDC_HSPolarity_AL ; //HSYNC低电平有效
  LTDC_InitTypeStruct.LTDC_VSPolarity = LTDC_VSPolarity_AL  ;//VSYNC低电平有效
  LTDC_InitTypeStruct.LTDC_DEPolarity = LTDC_DEPolarity_AL; //DE低电平有效
  LTDC_InitTypeStruct.LTDC_PCPolarity = LTDC_PCPolarity_IPC ;//上升沿采集数据
  
  //时间参数
  LTDC_InitTypeStruct.LTDC_HorizontalSync = HSW - 1;
  LTDC_InitTypeStruct.LTDC_VerticalSync = VSW - 1;
  LTDC_InitTypeStruct.LTDC_AccumulatedHBP = HSW+HBP -1 ; 
  LTDC_InitTypeStruct.LTDC_AccumulatedVBP = VSW +VBP -1;
  
  LTDC_InitTypeStruct.LTDC_AccumulatedActiveW = HSW+HBP + LCD_WIDTH  -1;
  LTDC_InitTypeStruct.LTDC_AccumulatedActiveH = VSW+VBP+LCD_HEIGHT -1;
  
  LTDC_InitTypeStruct.LTDC_TotalWidth =  HSW+HBP + LCD_WIDTH + HFP -1;; 
  LTDC_InitTypeStruct.LTDC_TotalHeigh = VSW+VBP+LCD_HEIGHT + VFP -1;
  
  
  //最底下的背景层颜色
  LTDC_InitTypeStruct.LTDC_BackgroundRedValue = 0;
  LTDC_InitTypeStruct.LTDC_BackgroundBlueValue = 0;
  LTDC_InitTypeStruct.LTDC_BackgroundGreenValue = 0;  
  
  LTDC_Init(&LTDC_InitTypeStruct);
    
}

//3.使用LTDC的层级初始化结构体，配置各层的控制参数
static void LCD_Layer_Init(void)
{
  LTDC_Layer_InitTypeDef LTDC_Layer_InitTypeStruct;
  
  
  //配置层级输出窗口
  LTDC_Layer_InitTypeStruct.LTDC_HorizontalStart = HBP + HSW;
  LTDC_Layer_InitTypeStruct.LTDC_HorizontalStop = HSW+HBP + LCD_WIDTH  -1;  
  LTDC_Layer_InitTypeStruct.LTDC_VerticalStart = VBP + VSW;
  LTDC_Layer_InitTypeStruct.LTDC_VerticalStop =  VSW+VBP+LCD_HEIGHT -1;
  
  LTDC_Layer_InitTypeStruct.LTDC_PixelFormat = LTDC_Pixelformat_RGB565;
  
  //0为透明，0xFF为不透明
  LTDC_Layer_InitTypeStruct.LTDC_ConstantAlpha = 0xFF;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorRed = 0;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorGreen = 0;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorBlue = 0;
  LTDC_Layer_InitTypeStruct.LTDC_DefaultColorAlpha = 0;
  
  //混合因子
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_CA  ;
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_CA  ;

  //配置显存相关的参数
  LTDC_Layer_InitTypeStruct.LTDC_CFBStartAdress  = LCD_LAYER1_START_ADDR;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineLength = LCD_WIDTH * 2 +3;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineNumber = LCD_HEIGHT;  
  LTDC_Layer_InitTypeStruct.LTDC_CFBPitch = LCD_WIDTH * 2;
  
  //LTDC_LayerInit(LTDC_Layer1,&LTDC_Layer_InitTypeStruct); 
  
  
  //配置第二层
  
  LTDC_Layer_InitTypeStruct.LTDC_PixelFormat = LTDC_Pixelformat_ARGB8888;

  //混合因子
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_PAxCA  ;
  LTDC_Layer_InitTypeStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA  ;

  //配置显存相关的参数
  LTDC_Layer_InitTypeStruct.LTDC_CFBStartAdress  = LCD_LAYER2_START_ADDR;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineLength = LCD_WIDTH * 4 +3;
  LTDC_Layer_InitTypeStruct.LTDC_CFBLineNumber = LCD_HEIGHT;  
  LTDC_Layer_InitTypeStruct.LTDC_CFBPitch = LCD_WIDTH * 4;
  
  LTDC_LayerInit(LTDC_Layer2,&LTDC_Layer_InitTypeStruct); 

  //使能两层数据源
  LTDC_LayerCmd (LTDC_Layer1,ENABLE);
  LTDC_LayerCmd (LTDC_Layer2,ENABLE);

  //更新配置参数
  LTDC_ReloadConfig (LTDC_IMReload);
  
  //使能抖动单元
  LTDC_DitherCmd(ENABLE);
  
  //使能LTDC
  LTDC_Cmd(ENABLE);
}


//初始化函数
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

