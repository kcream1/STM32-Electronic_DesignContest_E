/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pid.h" 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern uint8_t buf;
float pwm_sx = 0,pwm_zy = 0;
int flag_3 = 0,flag_3_pr = 0;
float Openmv_X1,Openmv_Y2,Openmv_X3,Openmv_Y4,Openmv_X5,Openmv_Y6,Openmv_X7,Openmv_Y8,Openmv_X9,Openmv_Y0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int flag_2 = 0,flag_2_sw = 0;

	int num = 0;
	unsigned char ch[20] = {0};
	int pwmval;
	float i;

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
	HAL_UART_Receive_IT(&huart1, &buf, 1);
	PID_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		/********************第一题**********************************/
		
//		for(i=0;i<=249;i++)
//		{
//			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, i);
//			HAL_Delay(40);
//		}
//		for(i=250;i>=1;i--)
//		{
//			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, i);
//			HAL_Delay(40);
//		}
//		HAL_Delay(1000);
//		pwmval = (int)((1-((0.5+0/90.0)/20.0))) -5;
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwmval); //180
//		printf("%d\r\n",pwmval);
//		HAL_Delay(1000);
//		pwmval = (int)((1-((0.5+45/90.0)/20.0))) -5;
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwmval); //0
//		printf("%d\r\n",pwmval);
//		HAL_Delay(1000);
//		pwmval = (int)((1-((0.5+90/90.0)/20.0))) -5;
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwmval); //45
//		printf("%d\r\n",pwmval);
//		HAL_Delay(1000);
//		pwmval = (int)((1-((0.5+135/90.0)/20.0))) -5;
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwmval); //90
//		printf("%d\r\n",pwmval);
//		HAL_Delay(1000);
//		pwmval = (int)((1-((0.5+180/90.0)/20.0))) -5;
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwmval); //135
//		printf("%d\r\n",pwmval);
		
		
//		for(i=0;i<=179;i++)
//		{
//			Servo_Control_sx(i);
//			HAL_Delay(2);
//		}
//		HAL_Delay(2);
//		for(i=180;i>=1;i--)					
//		{		
//			Servo_Control_sx(i);
//			HAL_Delay(2);													
//		}  
//		HAL_Delay(2);
		
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_5) == GPIO_PIN_RESET)
		{
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 140); //90
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 160); //90
			HAL_Delay(1000);
			//pwm_sx = 149,pwm_zy = 149;
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 149); //90
			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 149); //90
		}
		
		/********************第一题**********************************/
		
		/********************第二题**********************************/
		
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6) == GPIO_PIN_RESET)
		{	
			flag_2 = 1;
		}
		
		if(flag_2 == 1)
		{
			for(i=150;i>=135;i--)//中间到中下
			{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, i);
				HAL_Delay(20);
			}
			
			for(i=150;i<=165;i++)//中下到左下
			{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, i);
				HAL_Delay(20);
			}
			
			for(i=135;i<=166;i++)//左下到左上
			{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, i);
				HAL_Delay(20);
			}
			
			for(i=165;i>=134;i--)//左上到右上
			{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, i);
				HAL_Delay(20);
			}
			
			for(i=166;i>=135;i--)//右上到右下
			{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, i);
				HAL_Delay(20);
			}
			
			for(i=134;i<=150;i++)//右下到中下
			{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, i);
				HAL_Delay(20);
				
			}
			
			for(i=135;i<=150;i++)//中下到中间
			{
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, i);
				HAL_Delay(20);
			}
			flag_2 = 0;
		}
		
		/********************第二题**********************************/
		
		
		/********************第三题**********************************/
		
		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7) == GPIO_PIN_RESET)
		{	
			flag_3 = 1;
			flag_3_pr = 6;
			PID_Init_3();
		}
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == GPIO_PIN_RESET)
		{
			flag_3 = 1;
			flag_3_pr = 1;
		}
		
		if(flag_3 == 1)
		{
			
			/**********写死***************/
			if(flag_3_pr == 6)
			{
				Openmv_X1 =-23;
				Openmv_Y2 = -17;
				implement(Openmv_X1,Openmv_Y2);
				flag_3_pr = 7;
				HAL_Delay(2000);
			}
			
			if(flag_3_pr == 7)
			{
				Openmv_X3=53;
				Openmv_Y4 = 3;
				implement(Openmv_X3,Openmv_Y4);
				flag_3_pr = 8;
				HAL_Delay(2000);
			}
			
			if(flag_3_pr == 8)
			{
				Openmv_X5 =0;
				Openmv_Y6 = 34;
				implement(Openmv_X5,Openmv_Y6);
				flag_3_pr = 9;
				HAL_Delay(2000);
			}
			
			if(flag_3_pr == 9)
			{
				Openmv_X5 =-57;
				Openmv_Y6 = 3;
				implement(Openmv_X5,Openmv_Y6);
				flag_3_pr = 10;
				HAL_Delay(2000);
			}
			
			if(flag_3_pr == 10)
			{
				Openmv_X9 =0;
				Openmv_Y0 =-36;
				implement(Openmv_X9,Openmv_Y0);
				flag_3_pr = 5;
				HAL_Delay(2000);
				PID_Init();
			}
			
			
//			/**********写死***************/
//			
//			
			if(flag_3_pr == 1)
			{
//				if(Openmv_X1==0)
//				{
//					HAL_UART_Transmit(&huart2, "1", strlen("1"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_X1 = (float)atof(ch);
//					printf("px1:%f\r\n",Openmv_X1);
//					memset(ch, 0, strlen(ch));
//				}
//				
//				if(Openmv_X1!=0)
//				{
//					HAL_UART_Transmit(&huart2, "2", strlen("2"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_Y2 = (float)atof(ch);
//					printf("py2:%f\r\n",Openmv_Y2);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_Y2!=0)
//				{
//					HAL_UART_Transmit(&huart2, "3", strlen("3"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_X3 = (float)atof(ch);
//					printf("px3:%f\r\n",Openmv_X3);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_X3!=0)
//				{
//					HAL_UART_Transmit(&huart2, "4", strlen("4"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_Y4 = (float)atof(ch);
//					printf("py4:%f\r\n",Openmv_Y4);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_Y4!=0)
//				{
//					HAL_UART_Transmit(&huart2, "5", strlen("5"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_X5 = (float)atof(ch);
//					printf("px5:%f\r\n",Openmv_X5);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_X5!=0)
//				{
//					HAL_UART_Transmit(&huart2, "6", strlen("6"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_Y6 = (float)atof(ch);
//					printf("py6:%f\r\n",Openmv_Y6);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_Y6!=0)
//				{
//					HAL_UART_Transmit(&huart2, "7", strlen("7"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_X7 = (float)atof(ch);
//					printf("px7:%f\r\n",Openmv_X7);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_X7!=0)
//				{
//					HAL_UART_Transmit(&huart2, "8", strlen("8"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_Y8 = (float)atof(ch);
//					printf("py8:%f\r\n",Openmv_Y8);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_Y8!=0)
//				{
//					HAL_UART_Transmit(&huart2, "9", strlen("9"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_X9 = (float)atof(ch);
//					printf("px9:%f\r\n",Openmv_X9);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_X9!=0)
//				{
//					HAL_UART_Transmit(&huart2, "0", strlen("0"),100);
//					HAL_UART_Receive(&huart2, ch, 19, 100);
//					Openmv_Y0 = (float)atof(ch);
//					printf("py0:%f\r\n",Openmv_Y0);
//					memset(ch, 0, strlen(ch));
//				}
//				if(Openmv_Y0!=0)
//				{
//					implement(Openmv_X1,Openmv_Y2);
//					HAL_Delay(1000);
//					implement(Openmv_X3,Openmv_Y4);
//					HAL_Delay(1000);
//					implement(Openmv_X5,Openmv_Y6);
//					HAL_Delay(1000);
//					implement(Openmv_X7,Openmv_Y8);
//					HAL_Delay(1000);
//					implement(Openmv_X9,Openmv_Y0);
//					HAL_Delay(1000);
//					Openmv_X1=0,Openmv_Y2=0,Openmv_X3=0,Openmv_Y4=0,Openmv_X5=0,Openmv_Y6=0,Openmv_X7=0,Openmv_Y8=0,Openmv_X9=0,Openmv_Y0=0;
//					flag_3_pr = 5;
//				}
				
				HAL_UART_Transmit(&huart2, "1", strlen("1"),120);
				for(i = 0;i<10;i++)
				{
					
					if(i==0)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_X1 = (float)atof(ch);
						printf("px1:%f\r\n",Openmv_X1);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==1)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_Y2 = (float)atof(ch);
						printf("py2:%f\r\n",Openmv_Y2);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==2)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_X3 = (float)atof(ch);
						printf("px3:%f\r\n",Openmv_X3);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==3)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_Y4 = (float)atof(ch);
						printf("py4:%f\r\n",Openmv_Y4);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==4)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_X5 = (float)atof(ch);
						printf("px5:%f\r\n",Openmv_X5);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==5)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_Y6 = (float)atof(ch);
						printf("py6:%f\r\n",Openmv_Y6);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==6)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_X7 = (float)atof(ch);
						printf("px7:%f\r\n",Openmv_X7);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==7)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_Y8 = (float)atof(ch);
						printf("py8:%f\r\n",Openmv_Y8);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==8)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_X9 = (float)atof(ch);
						printf("px9:%f\r\n",Openmv_X9);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
					if(i==9)
					{
						HAL_UART_Receive(&huart2, ch, 19, 100);
						Openmv_Y0 = (float)atof(ch);
						printf("py0:%f\r\n",Openmv_Y0);
						memset(ch, 0, strlen(ch));
						//HAL_Delay(100);
					}
				}
				
				HAL_Delay(100);
				
				
				implement(Openmv_X1,Openmv_Y2);
				HAL_Delay(2000);
				implement(Openmv_X3,Openmv_Y4);
				HAL_Delay(2000);
				implement(Openmv_X5,Openmv_Y6);
				HAL_Delay(2000);
				implement(Openmv_X7,Openmv_Y8);
				HAL_Delay(2000);
				implement(Openmv_X9,Openmv_Y0);
				HAL_Delay(2000);
				flag_3_pr = 5;
				
			}
			
			if(flag_3_pr == 5)
			{
				flag_3_pr = 0;
				flag_3 = 0;
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 150); //90
				__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 149); //90
			}
		}
		
//		
//		HAL_UART_Receive(&huart1, ch, 19, 100);
//		printf(ch);
//		if()
//		{
//			pwm_sx += 0.01;
//			__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx);
//			printf("sx=%f\r\n",pwm_sx);
//			printf("pys2");
//		}
//		memset(ch, 0, strlen(ch));
		
//		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6) == GPIO_PIN_RESET)
//		{
//			
//			flag_2 = 1;
//			flag_2_sw = 1;
//		}
//		

//		if(flag_2 == 1)
//		{
//			
//			switch(flag_2_sw)
//			{
//				case 1:			//从中心向下移动（迅速）
//				{
//					pwm_sx = 13.5;
//					__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx); //75左右
//					HAL_Delay(1000);
//					flag_2_sw = 2;
//					break;
//				}
//					
//				case 2:			//从中下向左移动（缓慢）
//				{

//					pwm_zy = 16.5;
//					__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy); //105
//					HAL_Delay(1000);
//					if(pwm_zy>17.5)
//					{
//						flag_2_sw = 3;
//						break;
//					}

//				}
//				
//				case 3:			//从左下角向上移动（缓慢）
//				{

//						pwm_sx = 16.5;
//						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx); //105
//						HAL_Delay(1000);
//						if(pwm_sx>17.5)
//						{
//							flag_2_sw = 4;
//							break;
//						}

//				}
//				
//				case 4:			//从左上角向右移动（缓慢）
//				{

//						pwm_zy = 13.5;
//						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy); //75
//						HAL_Delay(1000);
//						if(pwm_zy<12.5)
//						{
//							flag_2_sw = 5;
//							break;
//						}

//				}
//				
//				case 5:			//从右上角向下移动（缓慢）
//				{

//						pwm_sx = 13.5;
//						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx); //75
//						HAL_Delay(1000);
//						if(pwm_sx<12.5)
//						{
//							flag_2_sw = 6;
//							break;
//						}
//					
//				}

//				case 6:			//从右下角向中下移动（缓慢）
//				{

//						pwm_zy = 15;
//						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy); //90
//						HAL_Delay(1000);
//						if(pwm_zy>15)
//						{
//							flag_2_sw = 7;
//							break;
//						}
//					
//				}
//				
//				case 7:			//从中下向中心移动（迅速）
//				{
//					pwm_sx = 15,pwm_zy = 15;
//					__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx); //90
//					__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy); //90
//					HAL_Delay(1000);
//					flag_2 = 2;
//					break;
//				}
//			}
//			
//			
//		}
			
		
//		HAL_Delay(1000);
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 5); //0
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 5); //0
//		HAL_Delay(1000);
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 10); //45
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 10); //45
//		HAL_Delay(1000);
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 15); //90
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 15); //90
//		HAL_Delay(1000);
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 20); //135
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 20); //135
//		HAL_Delay(1000);
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 25); //180
//		__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 25); //180
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
