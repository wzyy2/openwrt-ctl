#include "MotorCtl.h"

//********************************************************************
// 函数名: PWMInit() 
// 说  明: 单片机PWM波产生初始化配置函数
// 时  间: 2011.10.29  
// 输  入: 无
// 输  出: 无
// 返  回: 无
// 注  意: PWM波频率 5-20K
//********************************************************************    
// 修改者:
// 时  间:
// 描  述:
//********************************************************************
void TIM2_PWM_Init(u16 arr,u16 psc)
{  	
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	u16 CCR3_Val = 0;
	u16 CCR4_Val = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_Cmd(TIM2, DISABLE);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //TIM_CH2
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2);
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
 /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
//TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	
	
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //使能通道1

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //使能通道2

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //使能通道3

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);	//使能通道4


 
	TIM_Cmd(TIM2, ENABLE);  //使能TIM3
	//TIM_CtrlPWMOutputs(TIM2, ENABLE);

}

void PWMInit(void)
{
		TIM2_PWM_Init(10000,0);
		//TIM_SetCompare3(TIM3,2000);	
}

void TIM3_PWM_Init()
{  	
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	u16 CCR3_Val = 0;
	u16 CCR4_Val = 0;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_Cmd(TIM3, DISABLE);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH2
	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
  GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM3);
 GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);
	
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = 13125; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =255; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
 /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //配置为PWM模式1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;	   //设置跳变值，当计数器计数到这个值时，电平发生跳变
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平
//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
//TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	
	
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //使能通道1

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	  //设置通道2的电平跳变值，输出另外一个占空比的PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	  //使能通道2

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	//设置通道3的电平跳变值，输出另外一个占空比的PWM
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);	 //使能通道3

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//设置通道4的电平跳变值，输出另外一个占空比的PWM
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);	//使能通道4


 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3

}


//********************************************************************
// 函数名: MotorInit() 
// 说  明: 电机控制初始化函数
// 时  间: 2011.10.29    
// 输  入: 无
// 输  出: 无
// 返  回: 无
// 注  意: 
//********************************************************************    
// 修改者:
// 时  间:
// 描  述:
//********************************************************************
void MotorInit(void)
{
   PWMInit();

   // ********* 用户补充控制电机转向IO口初始化的代码 **********

}


//********************************************************************
// 函数名: MotorLCtl()/MotorRCtl() 
// 说  明: 左/右 电机控制函数
// 时  间: 2011.10.29    
// 输  入: speed: 转速，取值: 0至100
//         direction: 转向，取值: 1:正转  2:反转（以使车向前为正）
// 输  出: 无
// 返  回: 无
// 注  意: 
//********************************************************************    
// 修改者:
// 时  间:
// 描  述:
//********************************************************************
void MotorRCtl(int16_t speed,unsigned char direction)
{


  // ********* 用户补充左边电机调速代码 **********
  
  if(direction == 1) //正传
    {
      TIM_SetCompare1(TIM2,speed);	
			TIM_SetCompare2(TIM2,0);	
    }
   
  else if(direction == 2)
    {
      TIM_SetCompare1(TIM2,0);	
			TIM_SetCompare2(TIM2,speed);	
    }
  else
    {
      // ********* 用户补充错误代码 **********
      // 提醒：参赛队可以在机器人电路上多焊几个LED作为错误指示灯，
      // 以不同的指示灯亮来指示程序或者硬件发生的相应错误，方便调
      // 试，使程序更加严谨
      while(1);
    }
}

void MotorLCtl(int16_t speed,unsigned char direction)
{


  // ********* 用户补充右边电机调速代码 **********
  
  if(direction == 1)
    {
      TIM_SetCompare3(TIM2,speed);	
			TIM_SetCompare4(TIM2,0);	
    }
   
  else if(direction == 2)
    {
      TIM_SetCompare3(TIM2,0);	
			TIM_SetCompare4(TIM2,speed);	
    }
  else
    {
      // ********* 用户补充错误代码 **********
      // 提醒：参赛队可以在机器人电路上多焊几个LED作为错误指示灯，
      // 以不同的指示灯亮来指示程序或者硬件发生的相应错误，方便调
      // 试，使程序更加严谨
      while(1);
    }

}


//********************************************************************
// 函数名: STOP() 
// 说  明: 停车函数
// 时  间: 2011.10.29    
// 输  入: 无
// 输  出: 无
// 返  回: 无
// 注  意: 
//********************************************************************    
// 修改者:
// 时  间:
// 描  述:
//********************************************************************
void STOP(void)
{
   PWMInit();
}


//********************************************************************
// 函数名: MotorCtl() 
// 说  明: 总体控制函数
// 时  间: 2011.10.29    
// 输  入: speed: 巡线机器人基础运行速度,取值: 0至100
//         PIDCtlOut: PID算法控制输出，取值: -100至+100
// 输  出: 无
// 返  回: 无
// 注  意: 注意检查，可能方向有问题！
//********************************************************************    
// 修改者:
// 时  间:
// 描  述:
//********************************************************************


void MotorCtl( int16_t speed,int16_t PIDCtlOut)// PIDz正 往做转
{
   int16_t speedL = 0,
                 speedR = 0;
   speedL = speed - PIDCtlOut;
   speedR = speed + PIDCtlOut;
   
   if(speedL < 0)
     {
        MotorLCtl(-speedL,2);
     }
   else
    {  
       MotorLCtl(speedL,1);
    }

   if(speedR < 0)
   {
      MotorRCtl(-speedR,2);
   }
   else
    {  
       MotorRCtl(speedR,1);
    }
}
