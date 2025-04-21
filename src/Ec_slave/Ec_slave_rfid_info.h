#ifndef EC_SLAVE_RFID_INFO_H
#define EC_SLAVE_RFID_INFO_H

#include <stdint.h>
#include <ecrt.h>

uint16_t alias = 0;
uint16_t position = 7;
uint32_t vendor_id = 0x00006000;
uint32_t product_code = 0x00004000;

ec_pdo_entry_info_t slave_3_pdo_entries[40] = {
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

ec_pdo_info_t slave_3_pdos[2] = {
    {0x1600, 19, slave_3_pdo_entries + 0},  /* Outputs */
    {0x1a00, 21, slave_3_pdo_entries + 19}, /* Inputs */
};

ec_sync_info_t slave_3_syncs[3] = {
    {0, EC_DIR_OUTPUT, 1, slave_3_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_3_pdos + 1, EC_WD_DISABLE},
    {0xff}};

#endif // EC_SLAVE_RFID_INFO_H
