#ifndef _PID_H_
#define _PID_H_
#include "MyF4Config.h"


int32_t pid_init(void);
int32_t pid_iterate(float input);

#endif//_PID_H_

