#include "filter.h"
#include "adc.h"





static uint16_t angle=0;
uint16_t comple_filter(const xyz *temp,int16_t GYRO_center)
{
	angle = 0.98*(angle + (GYRO_center - temp->g)*0.04) + 0.02*temp->z;
	return angle;
}



 //¾ùÖµÂË²¨


#define ADCFILTER_AVG_NUM 16

static xyz adcfilter_history[ADCFILTER_AVG_NUM];
static xyz adcfilter_current;
static char adcfilter_index;


void filter_init() 
{
	char i;
	for(i = 0; i < ADCFILTER_AVG_NUM; i++ )
	{
		adcfilter_history[i].x = 0;
		adcfilter_history[i].y = 0;
		adcfilter_history[i].z = 0;
		adcfilter_history[i].g = 0;
		adcfilter_history[i].ang = 0;
	}
	adcfilter_index = 0;
}

void equal(xyz *to,xyz *temp)
{
	to->x = temp->x;
	to->y = temp->y;
	to->z = temp->z;
	to->g = temp->g;
	to->ang = temp->ang;
}

void filter_input(xyz *adc)
{	
	char i ;
	float sum[5]={0,0,0,0,0};
	//a=b;
	equal(& (adcfilter_history[adcfilter_index]) , adc) ;	
	adcfilter_index++;
	if(adcfilter_index >= ADCFILTER_AVG_NUM)
		adcfilter_index = 0;		
  
   for(i=0;i<ADCFILTER_AVG_NUM;i++)
   {
        sum[0] += adcfilter_history[i].x;
        sum[1] += adcfilter_history[i].y;
        sum[2] += adcfilter_history[i].z;
				sum[3] += adcfilter_history[i].g;
				sum[4] += adcfilter_history[i].ang;
    }
		
	adcfilter_current.x = (u16) (sum[0] * (1.0f/ADCFILTER_AVG_NUM));
	adcfilter_current.y = (u16) (sum[1] * (1.0f/ADCFILTER_AVG_NUM));
	adcfilter_current.z =(u16) (sum[2] * (1.0f/ADCFILTER_AVG_NUM));
	adcfilter_current.g = (u16) (sum[3] * (1.0f/ADCFILTER_AVG_NUM));
	adcfilter_current.ang = (u16) (sum[4] * (1.0f/ADCFILTER_AVG_NUM));
	sum[1] = sum[0];
}
xyz * adcfilter_getCurrent(void)
{
    return &adcfilter_current;
}

