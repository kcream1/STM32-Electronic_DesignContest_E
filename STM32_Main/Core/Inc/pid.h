#ifndef __PID_H
#define __PID_H



typedef struct 
{
	float X_Kp;
	float X_Ki;
	float X_Kd;
	float X_err;
	float X_err_sum;
	float X_err_last;	
	
	float Y_Kp;
	float Y_Ki;
	float Y_Kd;
	float Y_err;
	float Y_err_sum;
	float Y_err_last;	
}PID;

void PID_Init(void);
int PID_Level(int x);
int PID_vertical(int y);
void implement(float Openmv_X_1,float Openmv_Y_1);
void PID_Init_3();
//void Servo_Control_sx(float angle);
//void Servo_Control_zy(float angle);
#endif


