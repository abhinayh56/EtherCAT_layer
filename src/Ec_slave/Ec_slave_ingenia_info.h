#ifndef EC_SLAVE_INGENIA_INFO_H
#define EC_SLAVE_INGENIA_INFO_H

#include <stdint.h>
#include <ecrt.h>

uint16_t alias = 0;
uint16_t position = 12;
uint32_t vendor_id = 0x0000029c;
uint32_t product_code = 0x03811002;

ec_pdo_entry_info_t slave_pdo_entries[8] = {
    {0x6040, 0x00, 16},
    {0x607a, 0x00, 32},
    {0x60ff, 0x00, 32},
    {0x6060, 0x00, 8},
    {0x6041, 0x00, 16}, /* Status Word */
    {0x6064, 0x00, 32}, /* Actual position */
    {0x606c, 0x00, 32}, /* Actual velocity */
    {0x6061, 0x00, 8},  /* Operation mode display */
};

ec_pdo_info_t slave_pdos[2] = {
    {0x1600, 4, slave_pdo_entries + 0},
    {0x1a00, 4, slave_pdo_entries + 4}, /* TPDO 1 mapping parameter */
};

ec_sync_info_t slave_syncs[5] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, slave_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, slave_pdos + 1, EC_WD_DISABLE},
    {0xff}};

#endif // EC_SLAVE_INGENIA_INFO_H
