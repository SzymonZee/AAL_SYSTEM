typedef struct
{


	 uint8_t Role;

	 //Power output
	 uint8_t TxPower;
	 uint8_t PowerAmpliferLevel;

	 //Device characteristic
	 char* 	DeviceName;
	 uint8_t DeviceAddres[5];
	 uint8_t Privacy_enabled;
	 uint8_t Device_Name_Char_Len;
	 uint16_t Service_Handle;
	 uint16_t Dev_Name_Char_Handle;
	 uint16_t Appearance_Char_Handle;


}BLE_MCU;



typedef struct
{

	 uint8_t Bonding_Mode;
	 uint8_t MITM_Mode;
	 uint8_t SC_Support;
	 uint8_t KeyPress_Notification_Support;
	 uint8_t Min_Encryption_Key_Size;
	 uint8_t Max_Encryption_Key_Size;
	 uint8_t Use_Fixed_Pin;
	 uint32_t Fixed_Pin;
	 uint8_t Identity_Address_Type;

}BLE_Security_Prams;



typedef struct
{

	uint8_t IO_Capability;
	BLE_MCU BLE_MCU;
	BLE_Security_Prams BLE_Security_Prams;
	SHCI_C2_Ble_Init_Cmd_Packet_t pCmdPacket;
}BLE_APP_Params;
