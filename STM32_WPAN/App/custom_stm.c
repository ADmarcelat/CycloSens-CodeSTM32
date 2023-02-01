/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : App/custom_stm.c
  * Description        : Custom Example Service.
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

/* Includes ------------------------------------------------------------------*/
#include "common_blesvc.h"
#include "custom_stm.h"

/* USER CODE BEGIN Includes */
#include "main.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef struct{
  uint16_t  CustomMy_P2PsHdle;                    /**< My_P2P_Server handle */
  uint16_t  CustomLed_CHdle;                  /**< My_LED_Char handle */
  uint16_t  CustomSwitch_CHdle;                  /**< My_Switch_Char handle */
  uint16_t  CustomMocHdle;                  /**< My_Own_Characteristic handle */
  uint16_t  CustomMy_HrsHdle;                    /**< My_Heart_Rate handle */
  uint16_t  CustomHrs_MHdle;                  /**< My_HRS_Meas handle */
  uint16_t  CustomHrs_SlHdle;                  /**< My_Sensor_Loc handle */
  uint16_t  CustomHrs_CtrlpHdle;                  /**< My_HRS_CTRL_Point handle */
  uint16_t  CustomTde_CsHdle;                    /**< CSCB_Service handle */
  uint16_t  CustomC1Hdle;                  /**< Characteristic1 handle */
}CustomContext_t;

/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private defines -----------------------------------------------------------*/
#define UUID_128_SUPPORTED  1

#if (UUID_128_SUPPORTED == 1)
#define BM_UUID_LENGTH  UUID_TYPE_128
#else
#define BM_UUID_LENGTH  UUID_TYPE_16
#endif

#define BM_REQ_CHAR_SIZE    (3)

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macros ------------------------------------------------------------*/
#define CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET         2
#define CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET              1
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
static const uint8_t SizeLed_C=2;
static const uint8_t SizeSwitch_C=2;
static const uint8_t SizeMoc=20;
static const uint8_t SizeHrs_M=5;
static const uint8_t SizeHrs_Sl=1;
static const uint8_t SizeHrs_Ctrlp=1;
static const uint8_t SizeC1=20;
/**
 * START of Section BLE_DRIVER_CONTEXT
 */
PLACE_IN_SECTION("BLE_DRIVER_CONTEXT") static CustomContext_t CustomContext;

/**
 * END of Section BLE_DRIVER_CONTEXT
 */

/* USER CODE BEGIN PV */
int Custom_Updated_Characteristic1;
int Custom_Updated_Characteristic2;
int Custom_Updated_Characteristic3;
Custom_STM_Data_t Custom_Characteristic1;
Custom_STM_Data_t Custom_Characteristic2;
Custom_STM_Data_t Custom_Characteristic3;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *pckt);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
/* USER CODE BEGIN PFD */

/* USER CODE END PFD */

/* Private functions ----------------------------------------------------------*/

#define COPY_UUID_128(uuid_struct, uuid_15, uuid_14, uuid_13, uuid_12, uuid_11, uuid_10, uuid_9, uuid_8, uuid_7, uuid_6, uuid_5, uuid_4, uuid_3, uuid_2, uuid_1, uuid_0) \
do {\
    uuid_struct[0] = uuid_0; uuid_struct[1] = uuid_1; uuid_struct[2] = uuid_2; uuid_struct[3] = uuid_3; \
        uuid_struct[4] = uuid_4; uuid_struct[5] = uuid_5; uuid_struct[6] = uuid_6; uuid_struct[7] = uuid_7; \
            uuid_struct[8] = uuid_8; uuid_struct[9] = uuid_9; uuid_struct[10] = uuid_10; uuid_struct[11] = uuid_11; \
                uuid_struct[12] = uuid_12; uuid_struct[13] = uuid_13; uuid_struct[14] = uuid_14; uuid_struct[15] = uuid_15; \
}while(0)

/* Hardware Characteristics Service */
/*
 The following 128bits UUIDs have been generated from the random UUID
 generator:
 D973F2E0-B19E-11E2-9E96-0800200C9A66: Service 128bits UUID
 D973F2E1-B19E-11E2-9E96-0800200C9A66: Characteristic_1 128bits UUID
 D973F2E2-B19E-11E2-9E96-0800200C9A66: Characteristic_2 128bits UUID
 */
#define COPY_MY_P2P_SERVER_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0xfe,0x40,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_MY_LED_CHAR_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xfe,0x41,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_MY_SWITCH_CHAR_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xfe,0x42,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_MY_OWN_CHARACTERISTIC_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xab,0xcd,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)
#define COPY_CSCB_SERVICE_UUID(uuid_struct)          COPY_UUID_128(uuid_struct,0x00,0x00,0x12,0x34,0xcc,0x7a,0x48,0x2a,0x98,0x4a,0x7f,0x2e,0xd5,0xb3,0xe5,0x8f)
#define COPY_CHARACTERISTIC1_UUID(uuid_struct)    COPY_UUID_128(uuid_struct,0x00,0x00,0xde,0xad,0x8e,0x22,0x45,0x41,0x9d,0x4c,0x21,0xed,0xae,0x82,0xed,0x19)

/* USER CODE BEGIN PF */

void Mirror(uint8_t *pPayload,uint8_t Length)
{
	//mirror function
	APP_DBG_MSG("\r\n\r Mirror\n");
	pPayload[Length-1]++;//increase last byte as use case specified
	Custom_Characteristic2.pPayload=pPayload;
	Custom_Characteristic2.Length=Length;
	Custom_Updated_Characteristic2=1;
	Ask_My_Action();
}
void C3_NOTIFICATION(uint8_t *pPayload,uint8_t Size)
{
	 tBleStatus result = BLE_STATUS_INVALID_PARAMS;
//    result = aci_gatt_update_char_value(CustomContext.CustomTde_CsHdle,
//                                        CustomContext.CustomC3Hdle,
//                                        0, /* charValOffset */
//										Size, /* charValueLen */
//										Data);
	 APP_DBG_MSG("\r\n\r C3_NOTIFICATION : update char\n");
//		while(result != BLE_STATUS_SUCCESS)
//			{
			Custom_Characteristic1.pPayload=pPayload;
			Custom_Characteristic1.Length=Size;
			Custom_Updated_Characteristic1=1;
//     result = aci_gatt_update_char_value(CustomContext.CustomTde_CsHdle,
//                                         CustomContext.CustomC1Hdle,
//                                         0, /* charValOffset */
//                                         Size, /* charValueLen */
//                                         (uint8_t *)  pPayload);

    //result=Custom_STM_App_Update_Char(CUSTOM_STM_C1,Data);

    SEND_MES_BLESTATUS(result);
    Ask_My_Action();
//			}
}
tBleStatus Custom_Characteristic_Send(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload,uint8_t Length,uint8_t Offset)
{
  tBleStatus result = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Custom_STM_App_Update_Char_1 */
  APP_DBG_MSG("\r\n\r Welcome to Custom_Characteristic_Send \n");
  /* USER CODE END Custom_STM_App_Update_Char_1 */

  switch(CharOpcode)
  {

    case CUSTOM_STM_C1:
      result = aci_gatt_update_char_value(CustomContext.CustomTde_CsHdle,
                                          CustomContext.CustomC1Hdle,
										  Offset, /* charValOffset */
										  Length, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1*/
      SEND_MES_BLESTATUS(result);
      /* USER CODE END CUSTOM_STM_Service_3_Char_1*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Custom_STM_App_Update_Char_2 */

  /* USER CODE END Custom_STM_App_Update_Char_2 */

  return result;
}
/* USER CODE END PF */

/**
 * @brief  Event handler
 * @param  Event: Address of the buffer holding the Event
 * @retval Ack: Return whether the Event has been managed or not
 */
static SVCCTL_EvtAckStatus_t Custom_STM_Event_Handler(void *Event)
{
  SVCCTL_EvtAckStatus_t return_value;
  hci_event_pckt *event_pckt;
  evt_blecore_aci *blecore_evt;
  aci_gatt_attribute_modified_event_rp0 *attribute_modified;
  aci_gatt_write_permit_req_event_rp0   *write_perm_req;
  aci_gatt_read_permit_req_event_rp0    *read_req;
  Custom_STM_App_Notification_evt_t     Notification;
  /* USER CODE BEGIN Custom_STM_Event_Handler_1 */
	  APP_DBG_MSG("\r\n\r Entry Custom_STM_Event_Handler\n");
	  tBleStatus My_Ble_Status;
	  uint8_t My_Data_Written[30];
	  uint8_t My_Data_Readen[30];
	  uint8_t My_Data_Written_Lenght;
	  uint8_t My_Data_Readen_Lenght;
	  int i;
  /* USER CODE END Custom_STM_Event_Handler_1 */

  return_value = SVCCTL_EvtNotAck;
  event_pckt = (hci_event_pckt *)(((hci_uart_pckt*)Event)->data);

  switch(event_pckt->evt)
  {
    case HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE:
      blecore_evt = (evt_blecore_aci*)event_pckt->data;
      switch(blecore_evt->ecode)
      {
        case ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */
	        	  APP_DBG_MSG("\r\n\r Entry EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN\n");
          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_BEGIN */
          attribute_modified = (aci_gatt_attribute_modified_event_rp0*)blecore_evt->data;
          if(attribute_modified->Attr_Handle == (CustomContext.CustomSwitch_CHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2 */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2\n");
            /* USER CODE END CUSTOM_STM_Service_1_Char_2 */
            switch(attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_attribute_modified */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2_attribute_modified\n");
              /* USER CODE END CUSTOM_STM_Service_1_Char_2_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_Disabled_BEGIN */
					 APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2_Disabled_BEGIN\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_2_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_SWITCH_C_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_Disabled_END */
	                APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2_Disabled_END\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_2_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_BEGIN */
	            	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_BEGIN\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_SWITCH_C_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_END */
	                APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_END\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_2_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2_default */
	            	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2_default\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_2_default */
              break;
            }
          }  /* if(attribute_modified->Attr_Handle == (CustomContext.CustomSwitch_CHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if(attribute_modified->Attr_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3 */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3\n");

            /* USER CODE END CUSTOM_STM_Service_1_Char_3 */

            switch(attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_attribute_modified  */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_attribute_modified\n");
              /* USER CODE END CUSTOM_STM_Service_1_Char_3_attribute_modified  */

              /* Disabled Notification and Indication management */
              case (!(COMSVC_Notification) | !(COMSVC_Indication)):
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_Disabled_BEGIN  */
			 APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_Disabled_BEGIN\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_3_Disabled_BEGIN  */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_MOC_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                Notification.Custom_Evt_Opcode = CUSTOM_STM_MOC_INDICATE_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_Disabled_END */
	                APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_Disabled_END\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_3_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_COMSVC_Notification_BEGIN */
	            	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_COMSVC_Notification_BEGIN\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_3_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_MOC_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_COMSVC_Notification_END */
	                APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_COMSVC_Notification_END\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_3_COMSVC_Notification_END */
                break;

              /* Enabled Indication management */
              case COMSVC_Indication:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_COMSVC_Indication_BEGIN */
	            	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_COMSVC_Indication_BEGIN\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_3_COMSVC_Indication_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_MOC_INDICATE_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_COMSVC_Indication_END */
	                APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_COMSVC_Indication_END\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_3_COMSVC_Indication_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_default */
	            	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_default\n");
                /* USER CODE END CUSTOM_STM_Service_1_Char_3_default */
                break;
            }
          }  /* if(attribute_modified->Attr_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if(attribute_modified->Attr_Handle == (CustomContext.CustomHrs_MHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1 */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1\n");
            /* USER CODE END CUSTOM_STM_Service_2_Char_1 */
            switch(attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_attribute_modified */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1_attribute_modified\n");
              /* USER CODE END CUSTOM_STM_Service_2_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_Disabled_BEGIN */
					 APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1_Disabled_BEGIN\n");
                /* USER CODE END CUSTOM_STM_Service_2_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_HRS_M_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_Disabled_END */
	                APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1_Disabled_END\n");
                /* USER CODE END CUSTOM_STM_Service_2_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_BEGIN */
	            	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_BEGIN\n");
                /* USER CODE END CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_HRS_M_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_END */
	                APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_END\n");
                /* USER CODE END CUSTOM_STM_Service_2_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1_default */
	            	  APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1_default\n");
                /* USER CODE END CUSTOM_STM_Service_2_Char_1_default */
              break;
            }
          }  /* if(attribute_modified->Attr_Handle == (CustomContext.CustomHrs_MHdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if(attribute_modified->Attr_Handle == (CustomContext.CustomC1Hdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1 */
            /* USER CODE END CUSTOM_STM_Service_3_Char_1 */
            switch(attribute_modified->Attr_Data[0])
            {
              /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_attribute_modified */

              /* USER CODE END CUSTOM_STM_Service_3_Char_1_attribute_modified */

              /* Disabled Notification management */
              case (!(COMSVC_Notification)):
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_Disabled_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_Disabled_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_C1_NOTIFY_DISABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_Disabled_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_Disabled_END */
                break;

              /* Enabled Notification management */
              case COMSVC_Notification:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_BEGIN */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_BEGIN */
                Notification.Custom_Evt_Opcode = CUSTOM_STM_C1_NOTIFY_ENABLED_EVT;
                Custom_STM_App_Notification(&Notification);
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_END */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_COMSVC_Notification_END */
                break;

              default:
                /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_default */

                /* USER CODE END CUSTOM_STM_Service_3_Char_1_default */
              break;
            }
          }  /* if(attribute_modified->Attr_Handle == (CustomContext.CustomC1Hdle + CHARACTERISTIC_DESCRIPTOR_ATTRIBUTE_OFFSET))*/

          else if(attribute_modified->Attr_Handle == (CustomContext.CustomLed_CHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE\n");
            /* USER CODE END CUSTOM_STM_Service_1_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if(attribute_modified->Attr_Handle == (CustomContext.CustomLed_CHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          else if(attribute_modified->Attr_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE\n");
            /* USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if(attribute_modified->Attr_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          else if(attribute_modified->Attr_Handle == (CustomContext.CustomC1Hdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_3_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE\n");
            /* USER CODE END CUSTOM_STM_Service_3_Char_1_ACI_GATT_ATTRIBUTE_MODIFIED_VSEVT_CODE */
          } /* if(attribute_modified->Attr_Handle == (CustomContext.CustomC1Hdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          /* USER CODE BEGIN EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */
	          APP_DBG_MSG("\r\n\r Entry EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END\n");
          /* USER CODE END EVT_BLUE_GATT_ATTRIBUTE_MODIFIED_END */
          break;

        case ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE :
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */
	        	 APP_DBG_MSG("\r\n\r Entry EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN\n");
          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_BEGIN */
          read_req = (aci_gatt_read_permit_req_event_rp0*)blecore_evt->data;
          if(read_req->Attribute_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /*USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1 */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1\n");
            /*USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_1*/
            aci_gatt_allow_read(read_req->Connection_Handle);
            /*USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2 */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2\n");
            /*USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_READ_PERMIT_REQ_VSEVT_CODE_2*/
          } /* if(read_req->Attribute_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/
          /* USER CODE BEGIN EVT_BLUE_GATT_READ_PERMIT_REQ_END */
	          APP_DBG_MSG("\r\n\r Entry EVT_BLUE_GATT_READ_PERMIT_REQ_END\n");
          /* USER CODE END EVT_BLUE_GATT_READ_PERMIT_REQ_END */
          break;

        case ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE:
          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */
	        	 APP_DBG_MSG("\r\n\r Entry EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN\n");
          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_BEGIN */
          write_perm_req = (aci_gatt_write_permit_req_event_rp0*)blecore_evt->data;
          if(write_perm_req->Attribute_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* Allow or reject a write request from a client using aci_gatt_write_resp(...) function */
            /*USER CODE BEGIN CUSTOM_STM_Service_1_Char_3_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE\n");
            /*USER CODE END CUSTOM_STM_Service_1_Char_3_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE*/
          } /*if(write_perm_req->Attribute_Handle == (CustomContext.CustomMocHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/

          else if(write_perm_req->Attribute_Handle == (CustomContext.CustomHrs_CtrlpHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* Allow or reject a write request from a client using aci_gatt_write_resp(...) function */
            /*USER CODE BEGIN CUSTOM_STM_Service_2_Char_3_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_3_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE\n");
            /*USER CODE END CUSTOM_STM_Service_2_Char_3_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE*/
          } /*if(write_perm_req->Attribute_Handle == (CustomContext.CustomHrs_CtrlpHdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/

          else if(write_perm_req->Attribute_Handle == (CustomContext.CustomC1Hdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))
          {
            return_value = SVCCTL_EvtAckFlowEnable;
            /* Allow or reject a write request from a client using aci_gatt_write_resp(...) function */
            /*USER CODE BEGIN CUSTOM_STM_Service_3_Char_1_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE */
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_3_Char_1_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE\n");
	            APP_DBG_MSG("\r\n\r Message :");
	            			My_Data_Written_Lenght=write_perm_req->Data_Length;
	            			i=0;
	            			while(i<My_Data_Written_Lenght)
	            			{
	            				My_Data_Written[i]=write_perm_req->Data[i];
	            				APP_DBG_MSG("%d",My_Data_Written[i++]);
	            			}
	            			Custom_Characteristic1.pPayload=write_perm_req->Data;
	            			Custom_Characteristic1.Length=write_perm_req->Data_Length;
	            			Custom_Updated_Characteristic1=1;
	            			Ask_My_Action();
	            			//Custom_STM_App_Update_Char(CustomContext.CustomC1Hdle,write_perm_req->Data);
	            			//C3_NOTIFICATION(write_perm_req->Data,write_perm_req->Data_Length);
            /*USER CODE END CUSTOM_STM_Service_3_Char_1_ACI_GATT_WRITE_PERMIT_REQ_VSEVT_CODE*/
          } /*if(write_perm_req->Attribute_Handle == (CustomContext.CustomC1Hdle + CHARACTERISTIC_VALUE_ATTRIBUTE_OFFSET))*/

          /* USER CODE BEGIN EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */
	          APP_DBG_MSG("\r\n\r Entry EVT_BLUE_GATT_WRITE_PERMIT_REQ_END\n");
          /* USER CODE END EVT_BLUE_GATT_WRITE_PERMIT_REQ_END */
          break;
        /* USER CODE BEGIN BLECORE_EVT */
	          APP_DBG_MSG("\r\n\r Entry BLECORE_EVT\n");
        /* USER CODE END BLECORE_EVT */
        default:
          /* USER CODE BEGIN EVT_DEFAULT */
	        	 APP_DBG_MSG("\r\n\r Entry EVT_DEFAULT\n");
          /* USER CODE END EVT_DEFAULT */
          break;
      }
      /* USER CODE BEGIN EVT_VENDOR*/
	      APP_DBG_MSG("\r\n\r Entry EVT_VENDOR\n");
      /* USER CODE END EVT_VENDOR*/
      break; /* HCI_VENDOR_SPECIFIC_DEBUG_EVT_CODE */

      /* USER CODE BEGIN EVENT_PCKT_CASES*/
	      APP_DBG_MSG("\r\n\r Entry EVENT_PCKT_CASES\n");
      /* USER CODE END EVENT_PCKT_CASES*/

    default:
      /* USER CODE BEGIN EVENT_PCKT*/
	    	 APP_DBG_MSG("\r\n\r Entry EVENT_PCKT\n");
      /* USER CODE END EVENT_PCKT*/
      break;
  }

  /* USER CODE BEGIN Custom_STM_Event_Handler_2 */
	  APP_DBG_MSG("\r\n\r Entry Custom_STM_Event_Handler_2\n");
  /* USER CODE END Custom_STM_Event_Handler_2 */

  return(return_value);
}/* end Custom_STM_Event_Handler */

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Service initialization
 * @param  None
 * @retval None
 */
void SVCCTL_InitCustomSvc(void)
{

  Char_UUID_t  uuid;
  /* USER CODE BEGIN SVCCTL_InitCustomSvc_1 */

  /* USER CODE END SVCCTL_InitCustomSvc_1 */

  /**
   *  Register the event handler to the BLE controller
   */
  SVCCTL_RegisterSvcHandler(Custom_STM_Event_Handler);

  /*
   *          My_P2P_Server
   *
   * Max_Attribute_Records = 1 + 2*3 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for My_P2P_Server +
   *                                2 for My_LED_Char +
   *                                2 for My_Switch_Char +
   *                                2 for My_Own_Characteristic +
   *                                1 for My_Switch_Char configuration descriptor +
   *                                1 for My_Own_Characteristic configuration descriptor +
   *                                1 for My_Own_Characteristic broadcast property +
   *                              = 10
   */

  COPY_MY_P2P_SERVER_UUID(uuid.Char_UUID_128);
  aci_gatt_add_service(UUID_TYPE_128,
                       (Service_UUID_t *) &uuid,
                       PRIMARY_SERVICE,
                       10,
                       &(CustomContext.CustomMy_P2PsHdle));

  /**
   *  My_LED_Char
   */
  COPY_MY_LED_CHAR_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomMy_P2PsHdle,
                    UUID_TYPE_128, &uuid,
                    SizeLed_C,
                    CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RESP,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE,
                    0x10,
                    CHAR_VALUE_LEN_VARIABLE,
                    &(CustomContext.CustomLed_CHdle));
  /**
   *  My_Switch_Char
   */
  COPY_MY_SWITCH_CHAR_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomMy_P2PsHdle,
                    UUID_TYPE_128, &uuid,
                    SizeSwitch_C,
                    CHAR_PROP_NOTIFY,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                    0x10,
                    CHAR_VALUE_LEN_VARIABLE,
                    &(CustomContext.CustomSwitch_CHdle));
  /**
   *  My_Own_Characteristic
   */
  COPY_MY_OWN_CHARACTERISTIC_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomMy_P2PsHdle,
                    UUID_TYPE_128, &uuid,
                    SizeMoc,
                    CHAR_PROP_BROADCAST | CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RESP | CHAR_PROP_NOTIFY | CHAR_PROP_INDICATE,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                    0x10,
                    CHAR_VALUE_LEN_VARIABLE,
                    &(CustomContext.CustomMocHdle));

  /*
   *          My_Heart_Rate
   *
   * Max_Attribute_Records = 1 + 2*3 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for My_Heart_Rate +
   *                                2 for My_HRS_Meas +
   *                                2 for My_Sensor_Loc +
   *                                2 for My_HRS_CTRL_Point +
   *                                1 for My_HRS_Meas configuration descriptor +
   *                              = 8
   */

  uuid.Char_UUID_16 = 0x180d;
  aci_gatt_add_service(UUID_TYPE_16,
                       (Service_UUID_t *) &uuid,
                       PRIMARY_SERVICE,
                       8,
                       &(CustomContext.CustomMy_HrsHdle));

  /**
   *  My_HRS_Meas
   */
  uuid.Char_UUID_16 = 0x2a37;
  aci_gatt_add_char(CustomContext.CustomMy_HrsHdle,
                    UUID_TYPE_16, &uuid,
                    SizeHrs_M,
                    CHAR_PROP_NOTIFY,
                    ATTR_PERMISSION_NONE,
                    GATT_DONT_NOTIFY_EVENTS,
                    0x10,
                    CHAR_VALUE_LEN_VARIABLE,
                    &(CustomContext.CustomHrs_MHdle));
  /**
   *  My_Sensor_Loc
   */
  uuid.Char_UUID_16 = 0x2a38;
  aci_gatt_add_char(CustomContext.CustomMy_HrsHdle,
                    UUID_TYPE_16, &uuid,
                    SizeHrs_Sl,
                    CHAR_PROP_READ,
                    ATTR_PERMISSION_NONE,
                    GATT_DONT_NOTIFY_EVENTS,
                    0x10,
                    CHAR_VALUE_LEN_CONSTANT,
                    &(CustomContext.CustomHrs_SlHdle));
  /**
   *  My_HRS_CTRL_Point
   */
  uuid.Char_UUID_16 = 0x2a39;
  aci_gatt_add_char(CustomContext.CustomMy_HrsHdle,
                    UUID_TYPE_16, &uuid,
                    SizeHrs_Ctrlp,
                    CHAR_PROP_WRITE,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP,
                    0x10,
                    CHAR_VALUE_LEN_CONSTANT,
                    &(CustomContext.CustomHrs_CtrlpHdle));

  /*
   *          CSCB_Service
   *
   * Max_Attribute_Records = 1 + 2*1 + 1*no_of_char_with_notify_or_indicate_property + 1*no_of_char_with_broadcast_property
   * service_max_attribute_record = 1 for CSCB_Service +
   *                                2 for Characteristic1 +
   *                                1 for Characteristic1 configuration descriptor +
   *                              = 4
   */

  COPY_CSCB_SERVICE_UUID(uuid.Char_UUID_128);
  aci_gatt_add_service(UUID_TYPE_128,
                       (Service_UUID_t *) &uuid,
                       PRIMARY_SERVICE,
                       4,
                       &(CustomContext.CustomTde_CsHdle));

  /**
   *  Characteristic1
   */
  COPY_CHARACTERISTIC1_UUID(uuid.Char_UUID_128);
  aci_gatt_add_char(CustomContext.CustomTde_CsHdle,
                    UUID_TYPE_128, &uuid,
                    SizeC1,
                    CHAR_PROP_WRITE_WITHOUT_RESP | CHAR_PROP_NOTIFY,
                    ATTR_PERMISSION_NONE,
                    GATT_NOTIFY_ATTRIBUTE_WRITE | GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP | GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                    0x10,
                    CHAR_VALUE_LEN_VARIABLE,
                    &(CustomContext.CustomC1Hdle));

  /* USER CODE BEGIN SVCCTL_InitCustomSvc_2 */

  /* USER CODE END SVCCTL_InitCustomSvc_2 */

  return;
}

/**
 * @brief  Characteristic update
 * @param  CharOpcode: Characteristic identifier
 * @param  Service_Instance: Instance of the service to which the characteristic belongs
 *
 */
tBleStatus Custom_STM_App_Update_Char(Custom_STM_Char_Opcode_t CharOpcode, uint8_t *pPayload)
{
  tBleStatus result = BLE_STATUS_INVALID_PARAMS;
  /* USER CODE BEGIN Custom_STM_App_Update_Char_1 */
  APP_DBG_MSG("\r\n\r Welcome to Custom_Characteristic_Send \n");
  /* USER CODE END Custom_STM_App_Update_Char_1 */

  switch(CharOpcode)
  {

    case CUSTOM_STM_LED_C:
      result = aci_gatt_update_char_value(CustomContext.CustomMy_P2PsHdle,
                                          CustomContext.CustomLed_CHdle,
                                          0, /* charValOffset */
                                          SizeLed_C, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_1*/
      APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_1\n");
      /* USER CODE END CUSTOM_STM_Service_1_Char_1*/
      break;

    case CUSTOM_STM_SWITCH_C:
      result = aci_gatt_update_char_value(CustomContext.CustomMy_P2PsHdle,
                                          CustomContext.CustomSwitch_CHdle,
                                          0, /* charValOffset */
                                          SizeSwitch_C, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_2*/
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_2\n");
      /* USER CODE END CUSTOM_STM_Service_1_Char_2*/
      break;

    case CUSTOM_STM_MOC:
      result = aci_gatt_update_char_value(CustomContext.CustomMy_P2PsHdle,
                                          CustomContext.CustomMocHdle,
                                          0, /* charValOffset */
                                          SizeMoc, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_1_Char_3*/
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_1_Char_3\n");

      /* USER CODE END CUSTOM_STM_Service_1_Char_3*/
      break;

    case CUSTOM_STM_HRS_M:
      result = aci_gatt_update_char_value(CustomContext.CustomMy_HrsHdle,
                                          CustomContext.CustomHrs_MHdle,
                                          0, /* charValOffset */
                                          SizeHrs_M, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_1*/
	            APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_1\n");
      /* USER CODE END CUSTOM_STM_Service_2_Char_1*/
      break;

    case CUSTOM_STM_HRS_SL:
      result = aci_gatt_update_char_value(CustomContext.CustomMy_HrsHdle,
                                          CustomContext.CustomHrs_SlHdle,
                                          0, /* charValOffset */
                                          SizeHrs_Sl, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_2*/
      APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_2\n");
      /* USER CODE END CUSTOM_STM_Service_2_Char_2*/
      break;

    case CUSTOM_STM_HRS_CTRLP:
      result = aci_gatt_update_char_value(CustomContext.CustomMy_HrsHdle,
                                          CustomContext.CustomHrs_CtrlpHdle,
                                          0, /* charValOffset */
                                          SizeHrs_Ctrlp, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_2_Char_3*/
      APP_DBG_MSG("\r\n\r Entry CUSTOM_STM_Service_2_Char_3\n");
      /* USER CODE END CUSTOM_STM_Service_2_Char_3*/
      break;

    case CUSTOM_STM_C1:
      result = aci_gatt_update_char_value(CustomContext.CustomTde_CsHdle,
                                          CustomContext.CustomC1Hdle,
                                          0, /* charValOffset */
                                          SizeC1, /* charValueLen */
                                          (uint8_t *)  pPayload);
      /* USER CODE BEGIN CUSTOM_STM_Service_3_Char_1*/
      SEND_MES_BLESTATUS(result);
      /* USER CODE END CUSTOM_STM_Service_3_Char_1*/
      break;

    default:
      break;
  }

  /* USER CODE BEGIN Custom_STM_App_Update_Char_2 */

  /* USER CODE END Custom_STM_App_Update_Char_2 */

  return result;
}
