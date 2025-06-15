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

//���ڽ��ջ��棨1�ֽڣ�
uint8_t buf=0;
extern float pwm_sx,pwm_zy;
//�����������ֽ��� 200���ɸ����������
#define UART1_REC_LEN 200

// ���ջ���, ���ڽ��յ������ݷ��������������UART1_REC_LEN���ֽ�
uint8_t UART1_RX_Buffer[UART1_REC_LEN];

//  ����״̬
//  bit15��      ������ɱ�־
//  bit14��      ���յ�0x0d
//  bit13~0��    ���յ�����Ч�ֽ���Ŀ
uint16_t UART1_RX_STA=0;

#define SIZE 12

char buffer[SIZE];

// ������ɻص��������յ�һ�����ݺ������ﴦ��
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	// �ж��ж������ĸ����ڴ�����
	if(huart->Instance == USART1)
	{
		// �жϽ����Ƿ���ɣ�UART1_RX_STA bit15 λ�Ƿ�Ϊ1��
		if((UART1_RX_STA & 0x8000) == 0)
		{
			// ����Ѿ��յ��� 0x0d ���س�����
			if(UART1_RX_STA & 0x4000)
			{
				// ������ж��Ƿ��յ� 0x0a �����У�
				if(buf == 0x0a)
				{
					// ��� 0x0a �� 0x0d ���յ����� bit15 λ��Ϊ1
					UART1_RX_STA |= 0x8000;

					// �ƿ�ָ��
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
					// ������Ϊ���մ������¿�ʼ
					UART1_RX_STA = 0;
			}
			else	// ���û���յ��� 0x0d ���س���
			{
				//�����ж��յ�������ַ��Ƿ��� 0x0d ���س���
				if(buf == 0x0d)
				{
					// �ǵĻ��� bit14 λ��Ϊ1
					UART1_RX_STA |= 0x4000;
				}
				else
				{
					// ���򽫽��յ������ݱ����ڻ���������
					UART1_RX_Buffer[UART1_RX_STA & 0X3FFF] = buf;
					UART1_RX_STA++;
					
					// ����������ݴ���UART1_REC_LEN��200�ֽڣ��������¿�ʼ����
					if(UART1_RX_STA > UART1_REC_LEN - 1)
						UART1_RX_STA = 0;
				}
			}
		}
		// ���¿����ж�
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
