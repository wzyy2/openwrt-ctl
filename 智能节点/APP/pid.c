#include"pid.h"

static float pid_pre = 0;
static float pid_accumulate = 0;
struct
{
	float p;
	float i;
	float d;
}pid;

int32_t pid_init(void)
{
  pid.p=20;
	pid.i=0;
	pid.d=0;
	return 0;
}


int32_t pid_iterate(float input)
{
				float output,p_o,i_o,d_o;
	
        p_o = input * pid.p;
        pid_accumulate += input * pid.i;
        i_o = pid_accumulate;
        if(i_o < -0.1)
            i_o = -0.1;
        if(i_o > 0.1)
            i_o = 0.1;
        d_o = (input - pid_pre) * pid.d;
        //
        output = p_o + i_o + d_o;
        //
        pid_pre = input;
    
    
    return output;
}
