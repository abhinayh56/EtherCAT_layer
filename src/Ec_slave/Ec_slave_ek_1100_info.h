#ifndef EC_SLAVE_EK_1100_INFO_H
#define EC_SLAVE_EK_1100_INFO_H

#include <stdint.h>
#include <ecrt.h>

uint16_t alias = 0;
uint16_t position = 100;
uint32_t vendor_id = 0x00000002;
uint32_t product_code = 0x044c2c52;

ec_sync_info_t slave_2_syncs[1] = {
    {0xff}};

#endif // EC_SLAVE_EK_1100_INFO_H
