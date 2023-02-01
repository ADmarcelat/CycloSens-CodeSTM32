/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : App/custom_app.c
 * Description        : Custom Example Application (Server)
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
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "custom_app.h"
#include "custom_stm.h"
#include "stm32_seq.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  /* My_P2P_Server */
  uint8_t               Switch_c_Notification_Status;
  uint8_t               Moc_Notification_Status;
  uint8_t               Moc_Indication_Status;
  /* My_Heart_Rate */
  uint8_t               Hrs_m_Notification_Status;
  /* CSCB_Service */
  uint8_t               C1_Notification_Status;
  /* USER CODE BEGIN CUSTOM_APP_Context_t */

  /* USER CODE END CUSTOM_APP_Context_t */

  uint16_t              ConnectionHandle;
} Custom_App_Context_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

PLACE_IN_SECTION("BLE_APP_CONTEXT") static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

/* USER CODE BEGIN PV */
uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

uint8_t SecureReadData;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
  /* My_P2P_Server */
static void Custom_Switch_c_Update_Char(void);
static void Custom_Switch_c_Send_Notification(void);
static void Custom_Moc_Update_Char(void);
static void Custom_Moc_Send_Notification(void);
static void Custom_Moc_Send_Indication(void);
  /* My_Heart_Rate */
static void Custom_Hrs_m_Update_Char(void);
static void Custom_Hrs_m_Send_Notification(void);
  /* CSCB_Service */
static void Custom_C1_Update_Char(void);
static void Custom_C1_Send_Notification(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */
	 APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_App_Notification_1\n");
  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch(pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */
  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_App_Notification_Custom_Evt_Opcode\n");
    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

  /* My_P2P_Server */
    case CUSTOM_STM_LED_C_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_LED_C_READ_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_LED_C_READ_EVT\n");
      /* USER CODE END CUSTOM_STM_LED_C_READ_EVT */
      break;

    case CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT\n");
      /* USER CODE END CUSTOM_STM_LED_C_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_MOC_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MOC_READ_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_MOC_READ_EVT\n");
      /* USER CODE END CUSTOM_STM_MOC_READ_EVT */
      break;

    case CUSTOM_STM_MOC_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MOC_WRITE_NO_RESP_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_MOC_WRITE_NO_RESP_EVT\n");
      /* USER CODE END CUSTOM_STM_MOC_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_MOC_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MOC_NOTIFY_ENABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_MOC_NOTIFY_ENABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_MOC_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_MOC_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MOC_NOTIFY_DISABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_MOC_NOTIFY_DISABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_MOC_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_MOC_INDICATE_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MOC_INDICATE_ENABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_MOC_INDICATE_ENABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_MOC_INDICATE_ENABLED_EVT */
      break;

    case CUSTOM_STM_MOC_INDICATE_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_MOC_INDICATE_DISABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_MOC_INDICATE_DISABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_MOC_INDICATE_DISABLED_EVT */
      break;

  /* My_Heart_Rate */
    case CUSTOM_STM_HRS_M_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_HRS_M_NOTIFY_ENABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_HRS_M_NOTIFY_ENABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_HRS_M_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_HRS_M_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_HRS_M_NOTIFY_DISABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_HRS_M_NOTIFY_DISABLED_EVT\n");
      /* USER CODE END CUSTOM_STM_HRS_M_NOTIFY_DISABLED_EVT */
      break;

    case CUSTOM_STM_HRS_SL_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_HRS_SL_READ_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_HRS_SL_READ_EVT\n");
      /* USER CODE END CUSTOM_STM_HRS_SL_READ_EVT */
      break;

    case CUSTOM_STM_HRS_CTRLP_WRITE_EVT:
      /* USER CODE BEGIN CUSTOM_STM_HRS_CTRLP_WRITE_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_HRS_CTRLP_WRITE_EVT\n");
      /* USER CODE END CUSTOM_STM_HRS_CTRLP_WRITE_EVT */
      break;

  /* CSCB_Service */
    case CUSTOM_STM_C1_WRITE_NO_RESP_EVT:
      /* USER CODE BEGIN CUSTOM_STM_C1_WRITE_NO_RESP_EVT */
    	Clear_LED('A');
    	Toggle_LED('B');
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_C1_WRITE_NO_RESP_EVT\n");
      /* USER CODE END CUSTOM_STM_C1_WRITE_NO_RESP_EVT */
      break;

    case CUSTOM_STM_C1_NOTIFY_ENABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_C1_NOTIFY_ENABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_C1_NOTIFY_ENABLED_EVT\n");
    	  BeginNotification();
      /* USER CODE END CUSTOM_STM_C1_NOTIFY_ENABLED_EVT */
      break;

    case CUSTOM_STM_C1_NOTIFY_DISABLED_EVT:
      /* USER CODE BEGIN CUSTOM_STM_C1_NOTIFY_DISABLED_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_C1_NOTIFY_DISABLED_EVT\n");
    	  FinishNotification();
      /* USER CODE END CUSTOM_STM_C1_NOTIFY_DISABLED_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_App_Notification_default\n");
      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */
  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_App_Notification_2\n");
  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */
	  APP_DBG_MSG("\r\n\r Entry CUSTOM_APP_Notification_1\n");
  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch(pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_CONN_HANDLE_EVT\n");
      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_DISCON_HANDLE_EVT\n");
      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */
    	  APP_DBG_MSG("\r\n\r Entry CUSTOM_APP_Notification_default\n");
      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */
  APP_DBG_MSG("\r\n\r Entry CUSTOM_APP_Notification_2\n");
  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}

void Custom_APP_Init(void)
{
  /* USER CODE BEGIN CUSTOM_APP_Init */
	  APP_DBG_MSG("\r\n\r Entry CUSTOM_APP_Init\n");
	  Custom_Updated_Characteristic1=0;
	  Custom_Updated_Characteristic2=0;
	  Custom_Updated_Characteristic3=0;
	  UTIL_SEQ_RegTask(1<<CFG_TASK_MY_ACTION, UTIL_SEQ_RFU, My_Action);
  /* USER CODE END CUSTOM_APP_Init */
  return;
}

/* USER CODE BEGIN FD */

/* USER CODE END FD */

/*************************************************************
 *
 * LOCAL FUNCTIONS
 *
 *************************************************************/

  /* My_P2P_Server */
void Custom_Switch_c_Update_Char(void) /* Property Read */
{
  Custom_STM_App_Update_Char(CUSTOM_STM_SWITCH_C, (uint8_t *)UpdateCharData);
  /* USER CODE BEGIN Switch_c_UC*/

  /* USER CODE END Switch_c_UC*/
  return;
}

void Custom_Switch_c_Send_Notification(void) /* Property Notification */
 {
  if(Custom_App_Context.Switch_c_Notification_Status)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_SWITCH_C, (uint8_t *)NotifyCharData);
    /* USER CODE BEGIN Switch_c_NS*/

    /* USER CODE END Switch_c_NS*/
  }
  else
  {
    APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n ");
  }
  return;
}

void Custom_Moc_Update_Char(void) /* Property Read */
{
  Custom_STM_App_Update_Char(CUSTOM_STM_MOC, (uint8_t *)UpdateCharData);
  /* USER CODE BEGIN Moc_UC*/

  /* USER CODE END Moc_UC*/
  return;
}

void Custom_Moc_Send_Notification(void) /* Property Notification */
 {
  if(Custom_App_Context.Moc_Notification_Status)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_MOC, (uint8_t *)NotifyCharData);
    /* USER CODE BEGIN Moc_NS*/

    /* USER CODE END Moc_NS*/
  }
  else
  {
    APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n ");
  }
  return;
}

void Custom_Moc_Send_Indication(void) /* Property Indication */
{
  if(Custom_App_Context.Moc_Indication_Status)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_MOC, (uint8_t *)NotifyCharData);
    /* USER CODE BEGIN Moc_IS*/

    /* USER CODE END Moc_IS*/
  }
  else
  {
    APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  INDICATION DISABLED\n ");
  }
  return;
}

  /* My_Heart_Rate */
void Custom_Hrs_m_Update_Char(void) /* Property Read */
{
  Custom_STM_App_Update_Char(CUSTOM_STM_HRS_M, (uint8_t *)UpdateCharData);
  /* USER CODE BEGIN Hrs_m_UC*/

  /* USER CODE END Hrs_m_UC*/
  return;
}

void Custom_Hrs_m_Send_Notification(void) /* Property Notification */
 {
  if(Custom_App_Context.Hrs_m_Notification_Status)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_HRS_M, (uint8_t *)NotifyCharData);
    /* USER CODE BEGIN Hrs_m_NS*/

    /* USER CODE END Hrs_m_NS*/
  }
  else
  {
    APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n ");
  }
  return;
}

  /* CSCB_Service */
void Custom_C1_Update_Char(void) /* Property Read */
{
  Custom_STM_App_Update_Char(CUSTOM_STM_C1, (uint8_t *)UpdateCharData);
  /* USER CODE BEGIN C1_UC*/
  APP_DBG_MSG("\r\n\r Entry Custom_C1_Update_Char\n");
  /* USER CODE END C1_UC*/
  return;
}

void Custom_C1_Send_Notification(void) /* Property Notification */
 {
  if(Custom_App_Context.C1_Notification_Status)
  {
    Custom_STM_App_Update_Char(CUSTOM_STM_C1, (uint8_t *)NotifyCharData);
    /* USER CODE BEGIN C1_NS*/
    APP_DBG_MSG("\r\n\r Entry Custom_C1_Send_Notification\n");
    /* USER CODE END C1_NS*/
  }
  else
  {
    APP_DBG_MSG("-- CUSTOM APPLICATION : CAN'T INFORM CLIENT -  NOTIFICATION DISABLED\n ");
  }
  return;
}

/* USER CODE BEGIN FD_LOCAL_FUNCTIONS*/
void My_Action(void)
{
	  APP_DBG_MSG("Welcome to My action\n");
	  if(Custom_Updated_Characteristic1==1)
	  	  {
		  APP_DBG_MSG("Custom_Characteristic 1 legnth : %d\n",Custom_Characteristic1.Length);
		  //Custom_STM_App_Update_Char(CUSTOM_STM_C1, Custom_Characteristic1.pPayload);
		  Custom_Characteristic_Send(CUSTOM_STM_C1, Custom_Characteristic1.pPayload,Custom_Characteristic1.Length,0);
		  Custom_Updated_Characteristic1=0;
	  	  }

}
void Ask_My_Action(void)
{
	  APP_DBG_MSG("Ask for My action/n");
	  UTIL_SEQ_SetTask(1<<CFG_TASK_MY_ACTION,CFG_SCH_PRIO_0);//HW semaphore
}
/* USER CODE END FD_LOCAL_FUNCTIONS*/
