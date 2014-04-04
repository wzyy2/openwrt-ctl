#ifndef _ADC_H_
#define _ADC_H_
#include "MyF4Config.h"

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t z;
	uint16_t g;
	uint16_t ang;
} xyz ;




void ADC_INIT(void);
xyz * adcfilter_get(void);


#endif//_ADC_H_

