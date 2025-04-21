/* Master 0, Slave 1, "EL2008"
 * Vendor ID:       0x00000002
 * Product code:    0x07d83052
 * Revision number: 0x00120000
 */

ec_pdo_entry_info_t slave_1_pdo_entries[] = {
    {0x7000, 0x01, 1}, /* Output */
    {0x7010, 0x01, 1}, /* Output */
    {0x7020, 0x01, 1}, /* Output */
    {0x7030, 0x01, 1}, /* Output */
    {0x7040, 0x01, 1}, /* Output */
    {0x7050, 0x01, 1}, /* Output */
    {0x7060, 0x01, 1}, /* Output */
    {0x7070, 0x01, 1}, /* Output */
};

ec_pdo_info_t slave_1_pdos[] = {
    {0x1600, 1, slave_1_pdo_entries + 0}, /* Channel 1 */
    {0x1601, 1, slave_1_pdo_entries + 1}, /* Channel 2 */
    {0x1602, 1, slave_1_pdo_entries + 2}, /* Channel 3 */
    {0x1603, 1, slave_1_pdo_entries + 3}, /* Channel 4 */
    {0x1604, 1, slave_1_pdo_entries + 4}, /* Channel 5 */
    {0x1605, 1, slave_1_pdo_entries + 5}, /* Channel 6 */
    {0x1606, 1, slave_1_pdo_entries + 6}, /* Channel 7 */
    {0x1607, 1, slave_1_pdo_entries + 7}, /* Channel 8 */
};

ec_sync_info_t slave_1_syncs[] = {
    {0, EC_DIR_OUTPUT, 8, slave_1_pdos + 0, EC_WD_ENABLE},
    {0xff}
};

/* Master 0, Slave 2, "EL1008"
 * Vendor ID:       0x00000002
 * Product code:    0x03f03052
 * Revision number: 0x00120000
 */

ec_pdo_entry_info_t slave_2_pdo_entries[] = {
    {0x6000, 0x01, 1}, /* Input */
    {0x6010, 0x01, 1}, /* Input */
    {0x6020, 0x01, 1}, /* Input */
    {0x6030, 0x01, 1}, /* Input */
    {0x6040, 0x01, 1}, /* Input */
    {0x6050, 0x01, 1}, /* Input */
    {0x6060, 0x01, 1}, /* Input */
    {0x6070, 0x01, 1}, /* Input */
};

ec_pdo_info_t slave_2_pdos[] = {
    {0x1a00, 1, slave_2_pdo_entries + 0}, /* Channel 1 */
    {0x1a01, 1, slave_2_pdo_entries + 1}, /* Channel 2 */
    {0x1a02, 1, slave_2_pdo_entries + 2}, /* Channel 3 */
    {0x1a03, 1, slave_2_pdo_entries + 3}, /* Channel 4 */
    {0x1a04, 1, slave_2_pdo_entries + 4}, /* Channel 5 */
    {0x1a05, 1, slave_2_pdo_entries + 5}, /* Channel 6 */
    {0x1a06, 1, slave_2_pdo_entries + 6}, /* Channel 7 */
    {0x1a07, 1, slave_2_pdo_entries + 7}, /* Channel 8 */
};

ec_sync_info_t slave_2_syncs[] = {
    {0, EC_DIR_INPUT, 8, slave_2_pdos + 0, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave 6
 * Vendor ID:       0x0000029c
 * Product code:    0x03811002
 * Revision number: 0x0005000e
 */

ec_pdo_entry_info_t slave_6_pdo_entries[] = {
    {0x6040, 0x00, 16}, /* Control Word */
    {0x607a, 0x00, 32}, /* Position set-point */
    {0x60ff, 0x00, 32}, /* Velocity set-point */
    {0x6060, 0x00, 8}, /* Operation mode */
    {0x6041, 0x00, 16}, /* Status Word */
    {0x6064, 0x00, 32}, /* Actual position */
    {0x606c, 0x00, 32}, /* Actual velocity */
    {0x6061, 0x00, 8}, /* Operation mode display */
};

ec_pdo_info_t slave_6_pdos[] = {
    {0x1600, 4, slave_6_pdo_entries + 0}, /* Subindex 000 */
    {0x1a00, 4, slave_6_pdo_entries + 4}, /* Subindex 000 */
};

ec_sync_info_t slave_6_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, slave_6_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, slave_6_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave 8, "RfidSlave"
 * Vendor ID:       0x00006000
 * Product code:    0x00004000
 * Revision number: 0x00000004
 */

ec_pdo_entry_info_t slave_8_pdo_entries[] = {
    {0x0005, 0x01, 16}, /* Acknowledge */
    {0x0005, 0x02, 16}, /* Second */
    {0x0005, 0x03, 16}, /* Minute */
    {0x0005, 0x04, 16}, /* Hour */
    {0x0005, 0x05, 16}, /* Day */
    {0x0005, 0x06, 16}, /* Month */
    {0x0005, 0x07, 16}, /* Year */
    {0x0005, 0x08, 16}, /* No_of_Usages */
    {0x0005, 0x09, 16}, /* Digital_Outputs */
    {0x0005, 0x0a, 16}, /* Grip_Counts */
    {0x0005, 0x0b, 16}, /* System_Number */
    {0x0005, 0x0c, 16}, /* Led_Red */
    {0x0005, 0x0d, 16}, /* Led_Green */
    {0x0005, 0x0e, 16}, /* Led_Blue */
    {0x0005, 0x0f, 16}, /* Spare_Bytes */
    {0x0005, 0x10, 16}, /* Roll_Offset */
    {0x0005, 0x11, 16}, /* Pitch_Offset */
    {0x0005, 0x12, 16}, /* Yaw_Offset */
    {0x0005, 0x13, 16}, /* Grip_Offset */
    {0x0006, 0x01, 16}, /* Device_ID */
    {0x0006, 0x02, 16}, /* Second */
    {0x0006, 0x03, 16}, /* Minute */
    {0x0006, 0x04, 16}, /* Hour */
    {0x0006, 0x05, 16}, /* Day */
    {0x0006, 0x06, 16}, /* Month */
    {0x0006, 0x07, 16}, /* Year */
    {0x0006, 0x08, 16}, /* Roll_Offset */
    {0x0006, 0x09, 16}, /* Pitch_Offset */
    {0x0006, 0x0a, 16}, /* Yaw_Offset */
    {0x0006, 0x0b, 16}, /* Grip_Offset */
    {0x0006, 0x0c, 16}, /* No_of_Usages */
    {0x0006, 0x0d, 16}, /* Max_Usages */
    {0x0006, 0x0e, 16}, /* Digital_Inputs */
    {0x0006, 0x0f, 16}, /* Grip_Counts */
    {0x0006, 0x10, 16}, /* System_Number */
    {0x0006, 0x11, 16}, /* Device_UID */
    {0x0006, 0x12, 16}, /* Spare_Bytes */
    {0x0006, 0x13, 16}, /* MFG_Day */
    {0x0006, 0x14, 16}, /* MFG_Month */
    {0x0006, 0x15, 16}, /* MFG_Year */
};

ec_pdo_info_t slave_8_pdos[] = {
    {0x1600, 19, slave_8_pdo_entries + 0}, /* Outputs */
    {0x1a00, 21, slave_8_pdo_entries + 19}, /* Inputs */
};

ec_sync_info_t slave_8_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_8_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_8_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave 9, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_9_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_9_pdos[] = {
    {0x1600, 7, slave_9_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_9_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_9_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_9_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_9_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave a, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_10_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_10_pdos[] = {
    {0x1600, 7, slave_10_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_10_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_10_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_10_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_10_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave b, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_11_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_11_pdos[] = {
    {0x1600, 7, slave_11_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_11_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_11_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_11_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_11_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave c, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_12_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_12_pdos[] = {
    {0x1600, 7, slave_12_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_12_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_12_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_12_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_12_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave d, "RfidSlave"
 * Vendor ID:       0x00006000
 * Product code:    0x00004000
 * Revision number: 0x00000004
 */

ec_pdo_entry_info_t slave_13_pdo_entries[] = {
    {0x0005, 0x01, 16}, /* Acknowledge */
    {0x0005, 0x02, 16}, /* Second */
    {0x0005, 0x03, 16}, /* Minute */
    {0x0005, 0x04, 16}, /* Hour */
    {0x0005, 0x05, 16}, /* Day */
    {0x0005, 0x06, 16}, /* Month */
    {0x0005, 0x07, 16}, /* Year */
    {0x0005, 0x08, 16}, /* No_of_Usages */
    {0x0005, 0x09, 16}, /* Digital_Outputs */
    {0x0005, 0x0a, 16}, /* Grip_Counts */
    {0x0005, 0x0b, 16}, /* System_Number */
    {0x0005, 0x0c, 16}, /* Led_Red */
    {0x0005, 0x0d, 16}, /* Led_Green */
    {0x0005, 0x0e, 16}, /* Led_Blue */
    {0x0005, 0x0f, 16}, /* Spare_Bytes */
    {0x0005, 0x10, 16}, /* Roll_Offset */
    {0x0005, 0x11, 16}, /* Pitch_Offset */
    {0x0005, 0x12, 16}, /* Yaw_Offset */
    {0x0005, 0x13, 16}, /* Grip_Offset */
    {0x0006, 0x01, 16}, /* Device_ID */
    {0x0006, 0x02, 16}, /* Second */
    {0x0006, 0x03, 16}, /* Minute */
    {0x0006, 0x04, 16}, /* Hour */
    {0x0006, 0x05, 16}, /* Day */
    {0x0006, 0x06, 16}, /* Month */
    {0x0006, 0x07, 16}, /* Year */
    {0x0006, 0x08, 16}, /* Roll_Offset */
    {0x0006, 0x09, 16}, /* Pitch_Offset */
    {0x0006, 0x0a, 16}, /* Yaw_Offset */
    {0x0006, 0x0b, 16}, /* Grip_Offset */
    {0x0006, 0x0c, 16}, /* No_of_Usages */
    {0x0006, 0x0d, 16}, /* Max_Usages */
    {0x0006, 0x0e, 16}, /* Digital_Inputs */
    {0x0006, 0x0f, 16}, /* Grip_Counts */
    {0x0006, 0x10, 16}, /* System_Number */
    {0x0006, 0x11, 16}, /* Device_UID */
    {0x0006, 0x12, 16}, /* Spare_Bytes */
    {0x0006, 0x13, 16}, /* MFG_Day */
    {0x0006, 0x14, 16}, /* MFG_Month */
    {0x0006, 0x15, 16}, /* MFG_Year */
};

ec_pdo_info_t slave_13_pdos[] = {
    {0x1600, 19, slave_13_pdo_entries + 0}, /* Outputs */
    {0x1a00, 21, slave_13_pdo_entries + 19}, /* Inputs */
};

ec_sync_info_t slave_13_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_13_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_13_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave e, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_14_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_14_pdos[] = {
    {0x1600, 7, slave_14_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_14_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_14_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_14_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_14_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave f, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_15_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_15_pdos[] = {
    {0x1600, 7, slave_15_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_15_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_15_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_15_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_15_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave 10, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_16_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_16_pdos[] = {
    {0x1600, 7, slave_16_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_16_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_16_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_16_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_16_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

/* Master 0, Slave 11, "SSI_BRDB_UNO_2.1.1"
 * Vendor ID:       0x00113322
 * Product code:    0x00001022
 * Revision number: 0x00000001
 */

ec_pdo_entry_info_t slave_17_pdo_entries[] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8}, /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8}, /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8}, /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8}, /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_17_pdos[] = {
    {0x1600, 7, slave_17_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_17_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_17_syncs[] = {
    {0, EC_DIR_OUTPUT, 1, slave_17_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_17_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

