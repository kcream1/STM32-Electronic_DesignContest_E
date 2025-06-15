/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "string.h"
#include "stdio.h"
#include "tim.h"

//串口接收缓存（1字节）
uint8_t buf=0;
extern float pwm_sx,pwm_zy;
//定义最大接收字节数 200，可根据需求调整
#define UART1_REC_LEN 200

// 接收缓冲, 串口接收到的数据放在这个数组里，最大UART1_REC_LEN个字节
uint8_t UART1_RX_Buffer[UART1_REC_LEN];

//  接收状态
//  bit15，      接收完成标志
//  bit14，      接收到0x0d
//  bit13~0，    接收到的有效字节数目
uint16_t UART1_RX_STA=0;

#define SIZE 12

char buffer[SIZE];

// 接收完成回调函数，收到一个数据后，在这里处理
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// 判断中断是由哪个串口触发的
	if(huart->Instance == USART1)
	{
		// 判断接收是否完成（UART1_RX_STA bit15 位是否为1）
		if((UART1_RX_STA & 0x8000) == 0)
		{
			// 如果已经收到了 0x0d （回车），
			if(UART1_RX_STA & 0x4000)
			{
				// 则接着判断是否收到 0x0a （换行）
				if(buf == 0x0a)
				{
					// 如果 0x0a 和 0x0d 都收到，则将 bit15 位置为1
					UART1_RX_STA |= 0x8000;

					// 灯控指令
					if(!strcmp(UART1_RX_Buffer, "M1"))
					{
						pwm_sx += 1; 
						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx);
						printf("sx=%f\r\n",pwm_sx);
					}
					else if(!strcmp(UART1_RX_Buffer, "M2"))
					{
						pwm_sx -= 1; 
						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx);
						printf("sx=%f\r\n",pwm_sx);
					}
					else if(!strcmp(UART1_RX_Buffer, "M3"))
					{
						pwm_zy += 1; 
						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy);
						printf("zy=%f\r\n",pwm_zy);
					}
					else if(!strcmp(UART1_RX_Buffer, "M4"))
					{
						pwm_zy -= 1; 
						__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy);
						printf("sx=%f\r\n",pwm_zy);
					}
					else if(!strcmp(UART1_RX_Buffer, "M5"))
					{
						pwm_sx = 150,pwm_zy = 150;
					__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm_sx); //90
					__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, pwm_zy); //90
					printf("sx=%f  zy=%f\r\n",pwm_sx,pwm_zy);
					}
						
					
					memset(UART1_RX_Buffer, 0, UART1_REC_LEN);
					UART1_RX_STA = 0;
				}
				else
					// 否则认为接收错误，重新开始
					UART1_RX_STA = 0;
			}
			else	// 如果没有收到了 0x0d （回车）
			{
				//则先判断收到的这个字符是否是 0x0d （回车）
				if(buf == 0x0d)
				{
					// 是的话则将 bit14 位置为1
					UART1_RX_STA |= 0x4000;
				}
				else
				{
					// 否则将接收到的数据保存在缓存数组里
					UART1_RX_Buffer[UART1_RX_STA & 0X3FFF] = buf;
					UART1_RX_STA++;
					
					// 如果接收数据大于UART1_REC_LEN（200字节），则重新开始接收
					if(UART1_RX_STA > UART1_REC_LEN - 1)
						UART1_RX_STA = 0;
				}
			}
		}
		// 重新开启中断
		HAL_UART_Receive_IT(&huart1, &buf, 1);
	}
}

int fputc(int ch, FILE *f)
{      
	unsigned char temp[1]={ch};
	HAL_UART_Transmit(&huart1,temp,1,0xffff);  
	return ch;
}
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
