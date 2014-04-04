#include "adc.h"




xyz adc;


void ADC_INIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef ADC_InitStructyre;
	DMA_InitTypeDef DMA_InitStructure;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 , ENABLE);
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;     
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_BASE+0x4C;  //ADC1 DATA ADDRESS
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&adc;    //DMA memory base address 
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; 
	DMA_InitStructure.DMA_BufferSize = 5;  
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   //periphera inc mode: when have multi peripheras need to use DMA  
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  //need  continue visit  
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;   
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull; 
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;  
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);  
	DMA_Cmd(DMA2_Stream0, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3|GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;  
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
	ADC_CommonInitStructure.ADC_DMAAccessMode =  ADC_DMAAccessMode_1;  //??DMA
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;  //????
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;  //??????
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_10Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);	
	ADC_InitStructyre.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructyre.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructyre.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructyre.ADC_NbrOfConversion = 5;  //???
	ADC_InitStructyre.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructyre.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1,&ADC_InitStructyre);  	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,2,ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,3,ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,4,ADC_SampleTime_144Cycles);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,5,ADC_SampleTime_144Cycles);
	//ADC_SoftwareStartConv(ADC1);
	
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE); //????????DMA??
	ADC_DMACmd(ADC1,ENABLE);//??ADC?DMA??
	
	ADC_Cmd(ADC1,ENABLE);
	ADC_SoftwareStartConv(ADC1);  
}




xyz * adcfilter_get(void)
{
    return &adc;
}


