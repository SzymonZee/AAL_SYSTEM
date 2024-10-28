typedef struct
{



	Service_UUID_t  ServiceUuid;
	uint8_t ServiceUUIDType;

	///Handles
	uint16_t ServiceHandle;
	//Service properities
	uint8_t ServiceType;

	uint8_t CharCount;
	uint8_t  MaxAttributeRecords;


}Service;

typedef struct
{

    //Uuid
	Char_UUID_t  CharUuid;
	uint8_t CharUuidType;
	// Handles
    uint16_t ServiceHandle;
	uint16_t CharHandle;

	uint8_t *DataBuff;
    uint16_t BuffLen;
    //Charasteristic  properities
    uint8_t CharProperties;
    uint8_t CharSecurityPermissions;
    uint8_t CharGattEvtMask;
    uint8_t CharEncKeySize;
    uint8_t  CharFixed;

}Characteristic;


