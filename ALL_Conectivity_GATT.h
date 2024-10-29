Service Service_Init(Service_UUID_t* ServiceUuid, uint8_t service_uuid_type, uint16_t service_handle,
                     uint8_t service_type, uint8_t max_attribute_records) {
    Service self;

    if (service_uuid_type == UUID_TYPE_128) {
        memcpy(&(self.ServiceUuid), ServiceUuid, sizeof(Service_UUID_t));
    } else {
        // Handle UUID_TYPE_16 if necessary
    }

    self.ServiceUUIDType = service_uuid_type;
    self.ServiceHandle = service_handle;
    self.ServiceType = service_type;
    self.CharCount = 0;
    self.MaxAttributeRecords = max_attribute_records;

    return self;
}

Characteristic Characteristic_Init(Service* self_service, uint16_t char_handle, Char_UUID_t CharUuid,
                                   uint8_t* char_buff, uint16_t BuffLen, uint8_t char_uuid_type, uint8_t CharProperties,
                                   uint8_t CharSecurityPermissions, uint8_t CharGattEvtMask, uint8_t CharEncKeySize, uint8_t CharFixed) {
    Characteristic self;

    if (char_uuid_type == UUID_TYPE_128) {
        memcpy(&(self.CharUuid), &CharUuid, sizeof(Char_UUID_t));
    } else {
        // Handle UUID_TYPE_16 if necessary
    }

    self.CharUuidType = char_uuid_type;
    self.CharHandle = char_handle;
    self.DataBuff = char_buff;
    self.BuffLen = BuffLen;
    self.ServiceHandle = self_service->ServiceHandle;
    self.CharProperties = CharProperties;
    self.CharSecurityPermissions = CharSecurityPermissions;
    self.CharGattEvtMask = CharGattEvtMask;
    self.CharEncKeySize = CharEncKeySize;
    self.CharFixed = CharFixed;
    self_service->CharCount++;

    return self;
}

tBleStatus Add_Service(Service* self) {
    tBleStatus ret;
    ret = aci_gatt_add_service(self->ServiceUUIDType, &(self->ServiceUuid), self->ServiceType,
                               self->MaxAttributeRecords, &(self->ServiceHandle));

    if (ret != BLE_STATUS_SUCCESS) {
        APP_DBG_MSG("Fail: failed at aci_gatt_add_service\n\r");

    } else {
        APP_DBG_MSG("Success: aci_gatt_add_service\n\r");
    }

    return ret;
}

tBleStatus Add_Characteristic(Characteristic* self) {
    tBleStatus ret;
    ret = aci_gatt_add_char(self->ServiceHandle, self->CharUuidType, &(self->CharUuid), self->BuffLen,
                            self->CharProperties, self->CharSecurityPermissions, self->CharGattEvtMask,
                            self->CharEncKeySize, self->CharFixed, &(self->CharHandle));

    if (ret != BLE_STATUS_SUCCESS) {
        APP_DBG_MSG("Fail: failed at aci_gatt_add_char\n\r");
    } else {
        APP_DBG_MSG("Success: aci_gatt_add_char\n\r");
    }

    return ret;
}
