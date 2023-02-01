/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : App/custom_stm.h
  * Description        : Header for custom_stm.c module.
  *
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
#ifndef __CUSTOM_STM_H
#define __CUSTOM_STM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "custom_app.h"
#include "common_blesvc.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  /* My_P2P_Server */
  CUSTOM_STM_LED_C,
  CUSTOM_STM_SWITCH_C,
  CUSTOM_STM_MOC,
  /* My_Heart_Rate */
  CUSTOM_STM_HRS_M,
  CUSTOM_STM_HRS_SL,
  CUSTOM_STM_HRS_CTRLP,
  /* CSCB_Service */
  CUSTOM_STM_C1,
} Custom_STM_Char_Opcode_t;

typedef enum
{
  /* My_LED_Char */
  CUSTOM_STM_LED_C_READ_EVT,
  CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT,
  /* My_Switch_Char */
  CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT,
  /* My_Own_Characteristic */
  CUSTOM_STM_MOC_READ_EVT,
  CUSTOM_STM_MOC_WRITE_NO_RESP_EVT,
  CUSTOM_STM_MOC_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_MOC_NOTIFY_DISABLED_EVT,
  CUSTOM_STM_MOC_INDICATE_ENABLED_EVT,
  CUSTOM_STM_MOC_INDICATE_DISABLED_EVT,
  /* My_HRS_Meas */
  CUSTOM_STM_HRS_M_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_HRS_M_NOTIFY_DISABLED_EVT,
  /* My_Sensor_Loc */
  CUSTOM_STM_HRS_SL_READ_EVT,
  /* My_HRS_CTRL_Point */
  CUSTOM_STM_HRS_CTRLP_WRITE_EVT,
  /* Characteristic1 */
  CUSTOM_STM_C1_WRITE_NO_RESP_EVT,
  CUSTOM_STM_C1_NOTIFY_ENABLED_EVT,
  CUSTOM_STM_C1_NOTIFY_DISABLED_EVT,

  CUSTOM_STM_BOOT_REQUEST_EVT
} Custom_STM_Opcode_evt_t;

typedef struct
{
  uint8_t * pPayload;
  uint8_t   Length;
} Custom_STM_Data_t;

typedef struct
{
  Custom_STM_Opcode_evt_t       Custom_Evt_Opcode;
  Custom_STM_Data_t             DataTransfered;
  uint16_t                      ConnectionHandle;
  uint8_t                       ServiceInstance;
} Custom_STM_App_Notification_evt_t;

/* USER CODE BEGIN ET */
extern int Custom_Updated_Characteristic1;
extern int Custom_Updated_Characteristic2;
extern int Custom_Updated_Characteristic3;
extern Custom_STM_Data_t Custom_Characteristic1;
extern Custom_STM_Data_t Custom_Characteristic2;
extern Custom_STM_Data_t Custom_Characteristic3;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Exported macros -----------------------------------------------------------*/
/* USER CODE BEGIN EM */
void Mirror(uint8_t *pPayload,uint8_t Length);
void C3_NOTIFICATION(uint8_t *Data,uint8_t Size);
tBleStatus Custom_Characteristic_Send(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload,uint8_t Length,uint8_t Offset);
/* USER CODE END EM */

/* Exported functions ------------------------------------------------------- */
void SVCCTL_InitCustomSvc( void );
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification);
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode,  uint8_t *pPayload);
/* USER CODE BEGIN EF */

/* USER CODE END EF */

#ifdef __cplusplus
}
#endif

#endif /*__CUSTOM_STM_H */
