#ifndef _FILTER_H_
#define _FILTER_H_
#include "MyF4Config.h"
#include "adc.h"



uint16_t comple_filter(const xyz *temp,int16_t GYRO_center);
xyz * adcfilter_getCurrent(void);
void filter_input(xyz *adc);
void filter_init(void) ;
#endif//_FILTER_H_

