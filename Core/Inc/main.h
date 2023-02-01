/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal.h"
#include "app_conf.h"
#include "app_entry.h"
#include "app_common.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "stdlib.h"
#include "dbg_trace.h"
#include "custom_stm.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
#include "ble_types.h"
void BeginNotification (void);
void FinishNotification(void);
void TimerIRQ(void);
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
int _write(int file, char *ptr, int len);
int compteurBpm(int nbBat);

int TimerBPM(void);

int _write(int file, char *ptr, int len);
HAL_StatusTypeDef SendUART(const unsigned char * buf, size_t bufSize);
void SEND_MES_BLESTATUS(tBleStatus Status);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define My_BLE_cst 0xAB
#define LOm_Pin GPIO_PIN_5
#define LOm_GPIO_Port GPIOA
#define LOp_Pin GPIO_PIN_6
#define LOp_GPIO_Port GPIOA
#define SW1_Pin GPIO_PIN_4
#define SW1_GPIO_Port GPIOC
#define SW1_EXTI_IRQn EXTI4_IRQn
#define Green_LED_Pin GPIO_PIN_0
#define Green_LED_GPIO_Port GPIOB
#define Red_LED_Pin GPIO_PIN_1
#define Red_LED_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_0
#define SW2_GPIO_Port GPIOD
#define SW2_EXTI_IRQn EXTI0_IRQn
#define SW3_Pin GPIO_PIN_1
#define SW3_GPIO_Port GPIOD
#define SW3_EXTI_IRQn EXTI1_IRQn
#define Blue_LED_Pin GPIO_PIN_5
#define Blue_LED_GPIO_Port GPIOB
void   MX_LPUART1_UART_Init(void);
void   MX_USART1_UART_Init(void);
/* USER CODE BEGIN Private defines */
void Toggle_LED(char data);
void Set_LED(char data);
void Clear_LED(char data);
HAL_StatusTypeDef SendUART(const unsigned char * buf, size_t bufSize);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
