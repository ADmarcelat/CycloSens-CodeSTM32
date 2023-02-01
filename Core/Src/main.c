/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
 COMP_HandleTypeDef hcomp2;

IPCC_HandleTypeDef hipcc;

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_lpuart1_tx;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;

RNG_HandleTypeDef hrng;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim17;

/* USER CODE BEGIN PV */
int nbBat;
int bpm;
int test = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_RF_Init(void);
static void MX_RTC_Init(void);
static void MX_IPCC_Init(void);
static void MX_RNG_Init(void);
static void MX_TIM17_Init(void);
static void MX_COMP2_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
uint8_t My_Value_Spy[30];
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	HAL_StatusTypeDef UART_error;
	HAL_StatusTypeDef LPUART_error;
	HAL_UART_StateTypeDef UART_State;
	nbBat=0;
	bpm=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Config code for STM32_WPAN (HSE Tuning must be done before system clock configuration) */
  MX_APPE_Config();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* IPCC initialisation */
   MX_IPCC_Init();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RF_Init();
  MX_RTC_Init();
  MX_RNG_Init();
  MX_TIM17_Init();
  MX_COMP2_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  MX_USART1_UART_Init();
//  printf("Hello World!\n");
  Set_LED('A');
  //HAL_Delay(200);

  char *msg = "Hello Nucleo Fun!\n\r";
  char *msg2 = "Hello Nucleo !\n\r";


//  HAL_UART_Transmit(&huart1, (uint8_t*)msg2, strlen(msg2), 0x1000);

  /* USER CODE END 2 */

  /* Init code for STM32_WPAN */
  MX_APPE_Init();

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  UART_State=HAL_UART_GetState(&huart1);

//  while(UART_State!=HAL_UART_STATE_READY)
//  {
//	  UART_State=HAL_UART_GetState(&huart1);
//  }


 HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 0x1000);
  //UART_error=HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 0x10);
  Clear_LED('A');
  while (1)
  {
    /* USER CODE END WHILE */
    MX_APPE_Process();

    /* USER CODE BEGIN 3 */
    printf( "Timer 2 initialized\n");
    	TIM2->CR1 = TIM2->CR1 | ( 1 << 0);
  	    //HAL_TIM_Base_Start_IT(&htim2);
    printf( "Timer 2 enabled\n");

    printf( "Timer 17 initialized\n");
    	TIM17->CR1 = TIM17->CR1 | ( 1 << 0);
  	   //HAL_TIM_Base_Start_IT(&htim17);
    printf( "Timer 17 enabled\n");

    	   HAL_COMP_Start (&hcomp2);
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

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
                              |RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS|RCC_PERIPHCLK_RFWAKEUP;
  PeriphClkInitStruct.RFWakeUpClockSelection = RCC_RFWKPCLKSOURCE_LSE;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSE;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE1;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN Smps */

  /* USER CODE END Smps */
}

/**
  * @brief COMP2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_COMP2_Init(void)
{

  /* USER CODE BEGIN COMP2_Init 0 */

  /* USER CODE END COMP2_Init 0 */

  /* USER CODE BEGIN COMP2_Init 1 */

  /* USER CODE END COMP2_Init 1 */
  hcomp2.Instance = COMP2;
  hcomp2.Init.InputMinus = COMP_INPUT_MINUS_IO4;
  hcomp2.Init.InputPlus = COMP_INPUT_PLUS_IO1;
  hcomp2.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
  hcomp2.Init.Hysteresis = COMP_HYSTERESIS_HIGH;
  hcomp2.Init.BlankingSrce = COMP_BLANKINGSRC_NONE;
  hcomp2.Init.Mode = COMP_POWERMODE_ULTRALOWPOWER;
  hcomp2.Init.WindowMode = COMP_WINDOWMODE_DISABLE;
  hcomp2.Init.TriggerMode = COMP_TRIGGERMODE_IT_RISING;
  if (HAL_COMP_Init(&hcomp2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN COMP2_Init 2 */

  /* USER CODE END COMP2_Init 2 */

}

/**
  * @brief IPCC Initialization Function
  * @param None
  * @retval None
  */
static void MX_IPCC_Init(void)
{

  /* USER CODE BEGIN IPCC_Init 0 */

  /* USER CODE END IPCC_Init 0 */

  /* USER CODE BEGIN IPCC_Init 1 */

  /* USER CODE END IPCC_Init 1 */
  hipcc.Instance = IPCC;
  if (HAL_IPCC_Init(&hipcc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IPCC_Init 2 */

  /* USER CODE END IPCC_Init 2 */

}

/**
  * @brief LPUART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_LPUART1_UART_Init(void)
{

  /* USER CODE BEGIN LPUART1_Init 0 */

  /* USER CODE END LPUART1_Init 0 */

  /* USER CODE BEGIN LPUART1_Init 1 */

  /* USER CODE END LPUART1_Init 1 */
  hlpuart1.Instance = LPUART1;
  hlpuart1.Init.BaudRate = 115200;
  hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
  hlpuart1.Init.StopBits = UART_STOPBITS_1;
  hlpuart1.Init.Parity = UART_PARITY_NONE;
  hlpuart1.Init.Mode = UART_MODE_TX_RX;
  hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
  if (HAL_UART_Init(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPUART1_Init 2 */

  /* USER CODE END LPUART1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_8;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */
//  HAL_HalfDuplex_EnableTransmitter(&huart1);
//  HAL_HalfDuplex_EnableReceiver(&huart1);
  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief RF Initialization Function
  * @param None
  * @retval None
  */
static void MX_RF_Init(void)
{

  /* USER CODE BEGIN RF_Init 0 */

  /* USER CODE END RF_Init 0 */

  /* USER CODE BEGIN RF_Init 1 */

  /* USER CODE END RF_Init 1 */
  /* USER CODE BEGIN RF_Init 2 */

  /* USER CODE END RF_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  hrng.Init.ClockErrorDetection = RNG_CED_ENABLE;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = CFG_RTC_ASYNCH_PRESCALER;
  hrtc.Init.SynchPrediv = CFG_RTC_SYNCH_PRESCALER;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  sSlaveConfig.InputTrigger = TIM_TS_ETRF;
  sSlaveConfig.TriggerPolarity = TIM_TRIGGERPOLARITY_NONINVERTED;
  sSlaveConfig.TriggerPrescaler = TIM_TRIGGERPRESCALER_DIV1;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim2, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIMEx_RemapConfig(&htim2, TIM_TIM2_ETR_COMP2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM17 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM17_Init(void)
{

  /* USER CODE BEGIN TIM17_Init 0 */

  /* USER CODE END TIM17_Init 0 */

  /* USER CODE BEGIN TIM17_Init 1 */

  /* USER CODE END TIM17_Init 1 */
  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 32000;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 10000;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM17_Init 2 */

  /* USER CODE END TIM17_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMAMUX1_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA2_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Channel4_IRQn, 15, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel4_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Green_LED_Pin|Red_LED_Pin|Blue_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LOm_Pin LOp_Pin */
  GPIO_InitStruct.Pin = LOm_Pin|LOp_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : SW1_Pin */
  GPIO_InitStruct.Pin = SW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SW1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Green_LED_Pin Red_LED_Pin Blue_LED_Pin */
  GPIO_InitStruct.Pin = Green_LED_Pin|Red_LED_Pin|Blue_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : SW2_Pin SW3_Pin */
  GPIO_InitStruct.Pin = SW2_Pin|SW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

}

/* USER CODE BEGIN 4 */
void BeginNotification (void)
{
	HAL_TIM_Base_Start_IT(&htim17);
	//char *msg = "C3: start notification !\n\r";
	//HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 0x100);
	htim17.Instance->DIER=1; //UIE 1
	//HAL_TIM_Base_Start(&htim17);
	Set_LED('B');

	//htim17->Instance->SR=1; //UIF 1
}

void FinishNotification(void)
{
	//char *msg = "C3: stop notification !\n\r";
	//HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 0x100);
	//HAL_TIM_Base_Stop(&htim17);
	HAL_TIM_Base_Stop_IT(&htim17);
	Clear_LED('B');
}

void TimerIRQ(void)
{

	char *msg = "Timer 17 IRQ!\n\r";
	HAL_UART_Transmit(&huart1, (uint8_t*)msg, strlen(msg), 0x100);
	C3_NOTIFICATION(&bpm,1);

	// UTIL_SEQ_SetTask(1<<CFG_TASK_MY_ACTION,CFG_SCH_PRIO_0);//HW semaphore
	bpm = TimerBPM();
}

int TimerBPM(void) {
	nbBat = htim2.Instance->CNT ;

	char * str = (char*) malloc(sizeof(char));
	sprintf(str, "bpm per minute : %d\n",nbBat);
	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 0x100);

	int bpmM = compteurBpm(nbBat); //We convert the number of beat/10sec to number of beat/min
	htim2.Instance->CNT = 0;

	free(str);

	/*if (test == 90) {
		test = 92;
	} else {
		test=90;
	}

	char * str = (char*) malloc(sizeof(char));
	sprintf(str, "bpm per minute : %d\n",test);
	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), 0x100);
	free(str);*/

	return test;
}
//to include in dbg_trace.c
/*


  //int _write(int file, char *ptr, int len)
   //{
   	int DataIdx;
   	SendUART(buf, bufSize);
   	for (DataIdx = 0; DataIdx < bufSize; DataIdx++)
   	{
   		//__io_putchar(*ptr++);
   		ITM_SendChar(*buf++);
   	}
   //	return len;
   //}


*/

HAL_StatusTypeDef SendUART(const unsigned char * buf, size_t bufSize)
{
	HAL_StatusTypeDef UART_error;

	 //UART_error=HAL_UART_Transmit(&huart1, (uint8_t*)buf, strlen(msg), 0x100);
	UART_error=HAL_UART_Transmit(&huart1, (uint8_t*)buf, bufSize, 0x100);

	 return UART_error;
}

int __io_putchar(int ch)
{
// uint8_t c[1];
// c[0] = ch & 0x00FF;
// HAL_UART_Transmit(&huart1, &*c, 1, 10);
HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0x10);
 return ch;
}
void Clear_LED(char data)
{
	switch(data){

	case 'R' :
		HAL_GPIO_WritePin(Red_LED_GPIO_Port, Red_LED_Pin, GPIO_PIN_RESET);
		break;

	case 'B' :
		HAL_GPIO_WritePin(Blue_LED_GPIO_Port, Blue_LED_Pin, GPIO_PIN_RESET);
		break;

	case 'G' :
		HAL_GPIO_WritePin(Green_LED_GPIO_Port, Green_LED_Pin, GPIO_PIN_RESET);
		break;

	case 'A' :
		HAL_GPIO_WritePin(Green_LED_GPIO_Port, Green_LED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Blue_LED_GPIO_Port, Blue_LED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Red_LED_GPIO_Port, Red_LED_Pin, GPIO_PIN_RESET);
		break;

	default :
		break;

				}
}

void Set_LED(char data)
{
	switch(data){

	case 'R' :
		HAL_GPIO_WritePin(Red_LED_GPIO_Port, Red_LED_Pin, GPIO_PIN_SET);
		break;

	case 'B' :
		HAL_GPIO_WritePin(Blue_LED_GPIO_Port, Blue_LED_Pin, GPIO_PIN_SET);
		break;

	case 'G' :
		HAL_GPIO_WritePin(Green_LED_GPIO_Port, Green_LED_Pin, GPIO_PIN_SET);
		break;

	case 'A' :
		HAL_GPIO_WritePin(Green_LED_GPIO_Port, Green_LED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Blue_LED_GPIO_Port, Blue_LED_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Red_LED_GPIO_Port, Red_LED_Pin, GPIO_PIN_SET);
		break;

	default :
		break;

				}
}

void Toggle_LED(char data)
{
	switch(data){

	case 'R' :
		HAL_GPIO_TogglePin(Red_LED_GPIO_Port, Red_LED_Pin);
		break;

	case 'B' :
		HAL_GPIO_TogglePin(Blue_LED_GPIO_Port, Blue_LED_Pin);
		break;

	case 'G' :
		HAL_GPIO_TogglePin(Green_LED_GPIO_Port, Green_LED_Pin);
		break;

	case 'A' :
		HAL_GPIO_TogglePin(Green_LED_GPIO_Port, Green_LED_Pin);
		HAL_GPIO_TogglePin(Blue_LED_GPIO_Port, Blue_LED_Pin);
		HAL_GPIO_TogglePin(Red_LED_GPIO_Port, Red_LED_Pin);
		break;

	default :
		break;

				}
}


void gestionConsoSTM(void) {
	HAL_GPIO_TogglePin(Green_LED_GPIO_Port, Green_LED_Pin);
	Clear_LED('B');
	/*if (etatSTM == 0) {
		MX_APPE_Init();
	    MX_APPE_Process();
		etatSTM=1;
	}*/
}



void SEND_MES_BLESTATUS(tBleStatus Status)
{

	APP_DBG_MSG("\r\n\r */*/*/*/ ");

	switch(Status){

	case BLE_STATUS_SUCCESS :
			APP_DBG_MSG("\r\n\r BLE_STATUS_SUCCESS ");
	break;

	case BLE_STATUS_UNKNOWN_CONNECTION_ID :
			APP_DBG_MSG("\r\n\r BLE_STATUS_UNKNOWN_CONNECTION_ID ");
	break;

	case BLE_STATUS_FAILED :
			APP_DBG_MSG("\r\n\r BLE_STATUS_FAILED ");
	break;

	case BLE_STATUS_INVALID_PARAMS :
			APP_DBG_MSG("\r\n\r BLE_STATUS_INVALID_PARAMS ");
	break;

	case BLE_STATUS_BUSY :
			APP_DBG_MSG("\r\n\r BLE_STATUS_BUSY ");
	break;

	case BLE_STATUS_PENDING :
			APP_DBG_MSG("\r\n\r BLE_STATUS_PENDING ");
	break;

	case BLE_STATUS_NOT_ALLOWED :
			APP_DBG_MSG("\r\n\r BLE_STATUS_NOT_ALLOWED ");
	break;

	case BLE_STATUS_ERROR :
			APP_DBG_MSG("\r\n\r BLE_STATUS_ERROR ");
	break;

	case BLE_STATUS_OUT_OF_MEMORY :
			APP_DBG_MSG("\r\n\r BLE_STATUS_OUT_OF_MEMORY ");
	break;

	case BLE_STATUS_INVALID_CID :
			APP_DBG_MSG("\r\n\r BLE_STATUS_INVALID_CID ");
	break;

	case BLE_STATUS_DEV_IN_BLACKLIST :
			APP_DBG_MSG("\r\n\r BLE_STATUS_DEV_IN_BLACKLIST ");
	break;

	case BLE_STATUS_DEV_NOT_BONDED :
			APP_DBG_MSG("\r\n\r BLE_STATUS_DEV_NOT_BONDED ");
	break;

	case BLE_STATUS_CSRK_NOT_FOUND :
			APP_DBG_MSG("\r\n\r BLE_STATUS_CSRK_NOT_FOUND ");
	break;

	case BLE_STATUS_IRK_NOT_FOUND :
			APP_DBG_MSG("\r\n\r BLE_STATUS_IRK_NOT_FOUND ");
	break;

	case BLE_STATUS_INSUFFICIENT_ENC_KEYSIZE :
			APP_DBG_MSG("\r\n\r BLE_STATUS_INSUFFICIENT_ENC_KEYSIZE ");
	break;

	case BLE_STATUS_SEC_DB_FULL :
			APP_DBG_MSG("\r\n\r BLE_STATUS_SEC_DB_FULL ");
	break;

	case BLE_STATUS_INVALID_HANDLE :
			APP_DBG_MSG("\r\n\r BLE_STATUS_INVALID_HANDLE ");
	break;

	case BLE_STATUS_OUT_OF_HANDLE :
			APP_DBG_MSG("\r\n\r BLE_STATUS_OUT_OF_HANDLE ");
	break;

	case BLE_STATUS_INVALID_OPERATION :
			APP_DBG_MSG("\r\n\r BLE_STATUS_INVALID_OPERATION ");
	break;

	case BLE_STATUS_CHARAC_ALREADY_EXISTS :
			APP_DBG_MSG("\r\n\r BLE_STATUS_CHARAC_ALREADY_EXISTS ");
	break;

	case BLE_STATUS_INSUFFICIENT_RESOURCES :
			APP_DBG_MSG("\r\n\r BLE_STATUS_INSUFFICIENT_RESOURCES ");
	break;

	case BLE_STATUS_SEC_PERMISSION_ERROR :
			APP_DBG_MSG("\r\n\r BLE_STATUS_SEC_PERMISSION_ERROR ");
	break;

	case BLE_STATUS_ADDRESS_NOT_RESOLVED :
			APP_DBG_MSG("\r\n\r BLE_STATUS_ADDRESS_NOT_RESOLVED ");
	break;

	case BLE_STATUS_NO_VALID_SLOT :
			APP_DBG_MSG("\r\n\r BLE_STATUS_NO_VALID_SLOT ");
	break;

	case BLE_STATUS_SCAN_WINDOW_SHORT :
			APP_DBG_MSG("\r\n\r BLE_STATUS_SCAN_WINDOW_SHORT ");
	break;

	case BLE_STATUS_NEW_INTERVAL_FAILED :
			APP_DBG_MSG("\r\n\r BLE_STATUS_NEW_INTERVAL_FAILED ");
	break;

	case BLE_STATUS_TIMEOUT :
			APP_DBG_MSG("\r\n\r BLE_STATUS_TIMEOUT ");
	break;

	case BLE_STATUS_LENGTH_FAILED :
			APP_DBG_MSG("\r\n\r BLE_STATUS_LENGTH_FAILED ");
	break;

	case BLE_STATUS_INTERVAL_TOO_LARGE :
			APP_DBG_MSG("\r\n\r BLE_STATUS_INTERVAL_TOO_LARGE ");
	break;

	default :
		APP_DBG_MSG("\r\n\r Unknow error ");
	break;
	}

	APP_DBG_MSG("\r\n\r */*/*/*/ ");
}


//int _write(int file, char *ptr, int len)
//{
//	int DataIdx;
//
//	for (DataIdx = 0; DataIdx < len; DataIdx++)
//	{
//		//__io_putchar(*ptr++);
//		ITM_SendChar(*ptr++);
//	}
//	return len;
//}
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
