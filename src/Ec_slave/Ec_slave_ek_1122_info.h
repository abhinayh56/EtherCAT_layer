#ifndef EC_SLAVE_EK_1122_INFO_H
#define EC_SLAVE_EK_1122_INFO_H

#include <stdint.h>
#include <ecrt.h>

uint16_t alias = 0;
uint16_t position = 0;
uint32_t vendor_id = 0x00000002;
uint32_t product_code = 0x04622c52;

ec_pdo_entry_info_t slave_pdo_entries[0] = {};

ec_pdo_info_t slave_pdos[0] = {};

ec_sync_info_t slave_syncs[1] = {
    {0xff}};

#endif // EC_SLAVE_EK_1122_INFO_H
