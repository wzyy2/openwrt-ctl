#include "dcmi_ov7620.h"

#define DCMI_TIMEOUT_MAX  10000


void OV7620_HW_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /*** Configures the DCMI GPIOs to interface with the OV9655 camera module ***/
  /* Enable DCMI GPIOs clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
                         RCC_AHB1Periph_GPIOC, ENABLE);
	
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PE5:PWRDOWN
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; 
    GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);//power on
	

  /* Connect DCMI pins to AF13 */
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);//DCMI_HSYNC 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_PIXCLK
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_D5 			  
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);//DCMI_VSYNC 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);//DCMI_D6 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_D7 			  
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);//DCMI_D0 
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);//DCMI_D1 			  
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI);//DCMI_D2 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI);//DCMI_D3 
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);//DCMI_D4 

  
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; 
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6; 
    GPIO_Init(GPIOE, &GPIO_InitStructure);     
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);		 
}

#define DCMI_DR_ADDRESS       0x50050028

void OV7620_Init(u8 *image)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;  
	
  /*** Configures the DCMI to interface with the OV9655 camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
  /* DCMI configuration */ 
DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous  ;//????
DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;//????
DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;//???
DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;//????
DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;//????
DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;//???
DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;//8?????
DCMI_Init(&DCMI_InitStructure);//???????????
  
  	DCMI_CaptureCmd(ENABLE); 
  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	 // DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE); 
    DCMI_ITConfig(DCMI_IT_LINE, ENABLE); 
    DCMI_ITConfig(DCMI_IT_FRAME, ENABLE); 
    //DCMI_ITConfig(DCMI_IT_ERR, ENABLE); 
		

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
    NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);    
		
		
DMA_InitStructure.DMA_Channel = DMA_Channel_1;//DMA???
DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;//??????
DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)image;//????
DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//??????????
DMA_InitStructure.DMA_BufferSize = 19200;//????320??,???????????????  //19200
DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//???????
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//????????????
DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;//???????_Word?32?
DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//???????_HalfWord?16?
DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//????,??
DMA_InitStructure.DMA_Priority = DMA_Priority_High;//????,?
DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;//????????
DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;//FIFO????
DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//?????
DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//?????
DMA_Init(DMA2_Stream1, &DMA_InitStructure);//??????DMA??


	/* DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular;//DCMI_CaptureMode_SnapShot;//// First take one picture
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; */
  /* DCMI configuration */ 
}




void OV_qvga(u8 *image)
{
	OV7620_HW_Init();	
	OV7620_Init(image);
	  DMA_Cmd(DMA2_Stream1, ENABLE); 
  	DCMI_Cmd(ENABLE); 
  	DCMI_CaptureCmd(ENABLE); 
  //OV7620_WriteReg(0x14, 0x24);// 0x24
}

