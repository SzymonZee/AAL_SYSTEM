ervice SensorData;
Characteristic Pir;
Characteristic MotionSensor;
BLE_Security_Prams* AAL_Security;
Service BatteryService;
Characteristic BatterLvl;
Log_Buffer LogBuffer;
// coudl be extern
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/**
 * START of Section BLE_APP_CONTEXT
 */

static Custom_App_Context_t Custom_App_Context;

/**
 * END of Section BLE_APP_CONTEXT
 */

uint8_t UpdateCharData[247];
uint8_t NotifyCharData[247];

/* USER CODE BEGIN PV */



void Set_BLE_Device_Prams(BLE_APP_Params* ble_app_params,uint8_t role, uint8_t tx_power, uint8_t power_amplifier_lvl)
{

	ble_app_params->BLE_MCU.TxPower=tx_power;
	ble_app_params->BLE_MCU.PowerAmpliferLevel=power_amplifier_lvl;
	ble_app_params->BLE_MCU.Role=role;




	SHCI_C2_Ble_Init_Cmd_Packet_t pCmdPacket=
	  {
	    {{0,0,0}},                          /**< Header unused */
	    {0,                                 /** pBleBufferAddress not used */
	     0,                                 /** BleBufferSize not used */
	     CFG_BLE_NUM_GATT_ATTRIBUTES,
	     CFG_BLE_NUM_GATT_SERVICES,
	     CFG_BLE_ATT_VALUE_ARRAY_SIZE,
	     CFG_BLE_NUM_LINK,
	     CFG_BLE_DATA_LENGTH_EXTENSION,
	     CFG_BLE_PREPARE_WRITE_LIST_SIZE,
	     CFG_BLE_MBLOCK_COUNT,
	     CFG_BLE_MAX_ATT_MTU,
	     CFG_BLE_PERIPHERAL_SCA,
	     CFG_BLE_CENTRAL_SCA,
	     CFG_BLE_LS_SOURCE,
	     CFG_BLE_MAX_CONN_EVENT_LENGTH,
	     CFG_BLE_HSE_STARTUP_TIME,
	     CFG_BLE_VITERBI_MODE,
	     CFG_BLE_OPTIONS,
	     0,
	     CFG_BLE_MAX_COC_INITIATOR_NBR,
	     CFG_BLE_MIN_TX_POWER,
	     CFG_BLE_MAX_TX_POWER,
	     CFG_BLE_RX_MODEL_CONFIG,
	     CFG_BLE_MAX_ADV_SET_NBR,
	     CFG_BLE_MAX_ADV_DATA_LEN,
	     CFG_BLE_TX_PATH_COMPENS,
	     CFG_BLE_RX_PATH_COMPENS,
	     CFG_BLE_CORE_VERSION,
	     CFG_BLE_OPTIONS_EXT
	    }
	  };

	ble_app_params->pCmdPacket=pCmdPacket;
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* SIG_AMPLIFYING */

/* USER CODE BEGIN PFP */
tBleStatus BLE_App_Init(BLE_APP_Params* ble_app_params)
{

	SHCI_CmdStatus_t status;
	tBleStatus ret=0;

	Ble_Tl_Init();



	UTIL_SEQ_RegTask(1<<CFG_TASK_HCI_ASYNCH_EVT_ID, UTIL_SEQ_RFU, hci_user_evt_proc);

	status = SHCI_C2_BLE_Init(&(ble_app_params->pCmdPacket));//Inicjalizacja stacku BLE na drugim CPU //
	if (status != SHCI_Success)
	{
		APP_DBG_MSG("  Fail   : SHCI_C2_BLE_Init command, result: 0x%02x\n\r", status);
	    /* if you are here, maybe CPU2 doesn't contain STM32WB_Copro_Wireless_Binaries, see Release_Notes.html */
	    goto error;
	    Error_Handler();// Hanlder
	}
	else
	{
	    APP_DBG_MSG("  Success: SHCI_C2_BLE_Init command\n\r");
	}





  ret = aci_gatt_init();

  if (ret != BLE_STATUS_SUCCESS)
  {
    goto error;
  }





 uint8_t addr[]={0x12,0x34,0x00,0xE1,0x80,0x02};

 ret=aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, sizeof (addr), addr);

  if (ret!=BLE_STATUS_SUCCESS)
  {
	  goto error;
  }


 ret=aci_hal_set_tx_power_level(ble_app_params->BLE_MCU.TxPower, ble_app_params->BLE_MCU.PowerAmpliferLevel);

  if (ret!=BLE_STATUS_SUCCESS)
  {
	  goto error;
  }




ret= Ble_Hci_Gap_Gatt_Init_(ble_app_params);

	if (ret!=BLE_STATUS_SUCCESS)
	{
		goto error;
	}



ret=Add_Service(&SensorData);

	if (ret!=BLE_STATUS_SUCCESS)
	{
		goto error;
	}



ret=Add_Characteristic(&Pir);

	if (ret!=BLE_STATUS_SUCCESS)
	{
		goto error;
	}

ret=Add_Characteristic(&MotionSensor);

	if (ret!=BLE_STATUS_SUCCESS)
	{
		goto error;
	}

ret=Add_Service(&BatteryService);
	if (ret!=BLE_STATUS_SUCCESS)
	{
		goto error;
	}

ret=Add_Characteristic(&BatterLvl);

	if (ret!=BLE_STATUS_SUCCESS)
	{
	goto error;
	}




Log_Event(&LogBuffer,"ble_app_init", "BLE_APP_INITED",LOG_LEVEL_CRITICAL, ret);





error:
Log_Event(&LogBuffer,"ble_app_init", "BLE_APP_NOT_INITED",LOG_LEVEL_CRITICAL, ret);

return ret;


}
/* USER CODE END PFP */

/* Functions Definition ------------------------------------------------------*/
void Custom_STM_App_Notification(Custom_STM_App_Notification_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_1 */

  /* USER CODE END CUSTOM_STM_App_Notification_1 */
  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* USER CODE END CUSTOM_STM_App_Notification_Custom_Evt_Opcode */

    /* SIG_AMPLIFYING */
    case CUSTOM_STM_POT_SET_READ_EVT:
      /* USER CODE BEGIN CUSTOM_STM_POT_SET_READ_EVT */

      /* USER CODE END CUSTOM_STM_POT_SET_READ_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_STM_App_Notification_default */

      /* USER CODE END CUSTOM_STM_App_Notification_default */
      break;
  }
  /* USER CODE BEGIN CUSTOM_STM_App_Notification_2 */

  /* USER CODE END CUSTOM_STM_App_Notification_2 */
  return;
}

void Custom_APP_Notification(Custom_App_ConnHandle_Not_evt_t *pNotification)
{
  /* USER CODE BEGIN CUSTOM_APP_Notification_1 */

  /* USER CODE END CUSTOM_APP_Notification_1 */

  switch (pNotification->Custom_Evt_Opcode)
  {
    /* USER CODE BEGIN CUSTOM_APP_Notification_Custom_Evt_Opcode */

    /* USER CODE END P2PS_CUSTOM_Notification_Custom_Evt_Opcode */
    case CUSTOM_CONN_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_CONN_HANDLE_EVT */

      /* USER CODE END CUSTOM_CONN_HANDLE_EVT */
      break;

    case CUSTOM_DISCON_HANDLE_EVT :
      /* USER CODE BEGIN CUSTOM_DISCON_HANDLE_EVT */

      /* USER CODE END CUSTOM_DISCON_HANDLE_EVT */
      break;

    default:
      /* USER CODE BEGIN CUSTOM_APP_Notification_default */

      /* USER CODE END CUSTOM_APP_Notification_default */
      break;
  }

  /* USER CODE BEGIN CUSTOM_APP_Notification_2 */

  /* USER CODE END CUSTOM_APP_Notification_2 */

  return;
}
