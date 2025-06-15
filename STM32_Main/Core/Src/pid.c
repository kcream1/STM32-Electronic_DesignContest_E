#include "pid.h"
#include "tim.h"
PID pid;
#include "usart.h"
extern float pwm_sx,pwm_zy;
float Openmv_X; /*OPENMV X 轴反馈坐标*/
float Openmv_Y; /*OPENMV X 轴反馈坐标*/
float out_x = 150,out_y = 150;
float out_x_last = 150,out_y_last = 150;
//void Servo_Control_sx(float angle)
//{
//	float temp;
////	u16 led0pwmval=0;
////	temp = 195- 0.11*(float)angle;
////	TIM_SetCompare2(TIM3, (float)temp);
//	 pwm_sx = (int)(2000*(1-((0.5+angle/90.0)/20.0))) -5;
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx);
//	printf("pys");
//}

//void Servo_Control_zy(float angle)
//{
//	float temp;
////	u16 led0pwmval=0;
////	temp = 195- 0.11*(float)angle;
////	TIM_SetCompare2(TIM3, (float)temp);
//	 pwm_zy = (int)(2000*(1-((0.5+angle/90.0)/20.0))) -5;
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy);
//}


void implement(float Openmv_X_1,float Openmv_Y_1)
{
	float ccrx,ccry;
	int n,m;

	ccrx = PID_Level(Openmv_Y_1);
	ccry = PID_vertical(Openmv_X_1);
	
	out_x = out_x - ccrx;
	out_y = out_y - ccry;
	
	if(out_x>=165)out_x=165;
	else if(out_x<=135) out_x=135;
	if(out_y>=165)out_y=165;
	else if(out_y<=135) out_y=135;
	
	
	if(out_x_last<=out_x&&out_y_last<=out_y)
	{
		for(n = out_x_last,m = out_y_last;n<=out_x||m<=out_y;n++,m++)
		{
			if(out_x_last>out_x)
			{
				out_x_last = out_x_last;
			}else{
				out_x_last += 1;
			}
			
			if(out_y_last>out_y)
			{
				out_y_last = out_y_last;
			}else{
				out_y_last += 1;
			}
			
			
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, out_x_last);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, out_y_last);
			HAL_Delay(80);
		}
	HAL_Delay(200);
	printf("x:%f  ",out_x);
	printf("y:%f  \r\n",out_y);
		return;
	}
	
	if(out_x_last<=out_x&&out_y_last>=out_y)
	{
		for(n = out_x_last,m = out_y_last;n<=out_x||m>=out_y;n++,m--)
		{
			if(out_x_last>out_x)
			{
				out_x_last = out_x_last;
			}else{
				out_x_last += 1;
			}
			
			if(out_y_last<out_y)
			{
				out_y_last = out_y_last;
			}else{
				out_y_last -= 1;
			}
			
			
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, out_x_last);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, out_y_last);
			HAL_Delay(80);
		}
		HAL_Delay(200);
		printf("x:%f  ",out_x);
		printf("y:%f  \r\n",out_y);
		return;
	}
	
	if(out_x_last>=out_x&&out_y_last<=out_y)
	{
		for(n = out_x_last,m = out_y_last;n>=out_x||m<=out_y;n--,m++)
		{
			if(out_x_last<out_x)
			{
				out_x_last = out_x_last;
			}else{
				out_x_last -= 1;
			}
			
			if(out_y_last>out_y)
			{
				out_y_last = out_y_last;
			}else{
				out_y_last += 1;
			}
			
			
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, out_x_last);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, out_y_last);
			HAL_Delay(80);
		}
		HAL_Delay(200);
	  printf("x:%f  ",out_x);
	  printf("y:%f  \r\n",out_y);
		return;
	}
	
	if(out_x_last>=out_x&&out_y_last>=out_y)
	{
		for(n = out_x_last,m = out_y_last;n>=out_x||m>=out_y;n--,m--)
		{
			if(out_x_last<out_x)
			{
				out_x_last = out_x_last;
			}else{
				out_x_last -= 1;
			}
			
			if(out_y_last<out_y)
			{
				out_y_last = out_y_last;
			}else{
				out_y_last -= 1;
			}
			
			
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, out_x_last);
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, out_y_last);
			HAL_Delay(80);
		}
		HAL_Delay(100);
	  printf("x:%f  ",out_x);
	  printf("y:%f  \r\n",out_y);
		return;
	}
	
	
	
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, out_x);
//	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, out_y);
	
//	out_x_last = out_x;
//	out_y_last = out_y;
	
//	HAL_Delay(200);
//	printf("x:%f  ",out_x);
//	printf("y:%f  \r\n",out_y);

//		TIM_SetCompare1(TIM3,out_x);
//		TIM_SetCompare2(TIM3,out_y);
	
}

void PID_Init()
{
	pid.X_Kp = 0.20;//上下
	pid.X_Ki = 0.03;
	pid.X_Kd = 0;
	pid.X_err = 0;
	pid.X_err_sum = 0;
	pid.X_err_last = 0;
	
	pid.Y_Kp=0.19;//左右
	pid.Y_Ki=0.01;
	pid.Y_Kd=0;
	pid.Y_err=0;
	pid.Y_err_sum=0;
	pid.Y_err_last=0;
}

void PID_Init_3()
{
	pid.X_Kp = 0.26;//上下
	pid.X_Ki = 0.06;
	pid.X_Kd = 0.02;
	pid.X_err = 5;
	pid.X_err_sum = 0;
	pid.X_err_last = 0;
	
	pid.Y_Kp=0.25;//左右
	pid.Y_Ki=0.08;
	pid.Y_Kd=0.02;
	pid.Y_err=0;
	pid.Y_err_sum=0;
	pid.Y_err_last=0;
}

//水平方向
int PID_Level(int x)
{
	int out;
	
	pid.X_err = x - 0;
	pid.X_err_sum += pid.X_err;
	out = pid.X_Kp*(pid.X_err)
		+ pid.X_Ki*(pid.X_err_sum)
		+ pid.X_Kd*(pid.X_err - pid.X_err_last);
	pid.X_err_last = pid.X_err;
	
	return out;
}

//垂直方向
int PID_vertical(int y)
{
	int out;
		
	pid.Y_err = y - 0;
	pid.Y_err_sum += pid.Y_err;
	out = pid.Y_Kp*(pid.Y_err)
		+ pid.Y_Ki*(pid.Y_err_sum)
		+ pid.Y_Kd*(pid.Y_err - pid.Y_err_last);
	pid.Y_err_last = pid.Y_err;
	
	return out;
}

