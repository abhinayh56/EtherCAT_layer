#ifndef EC_MACT_INFO_H
#define EC_MACT_INFO_H

#include <stdint.h>
#include <ecrt.h>

uint16_t alias = 0;
uint16_t position = 8;
uint32_t vendor_id = 0x00113322;
uint32_t product_code = 0x00001022;

ec_pdo_entry_info_t slave_4_pdo_entries[15] = {
    {0x607a, 0x00, 32}, /* TARGET_POS */
    {0x6040, 0x00, 16}, /* CONTROL_WD */
    {0x6071, 0x00, 16}, /* TARGET_TORQ */
    {0x6060, 0x00, 8},  /* OP_MODE */
    {0x3004, 0x00, 16}, /* ERROR_CLEAR */
    {0x3001, 0x00, 8},  /* DIG_OUT */
    {0x60ff, 0x00, 32}, /* TARGET_VEL */
    {0x6064, 0x00, 32}, /* ACT_POS */
    {0x6041, 0x00, 16}, /* STATUS_WD */
    {0x6077, 0x00, 16}, /* ACT_TOR */
    {0x6061, 0x00, 8},  /* OPMODE_DISP */
    {0x603f, 0x00, 16}, /* ERROR_CODE */
    {0x3002, 0x00, 8},  /* DIG_IN */
    {0x606c, 0x00, 32}, /* ACT_VEL */
    {0x3007, 0x00, 16}, /* ADC_VAL */
};

ec_pdo_info_t slave_4_pdos[2] = {
    {0x1600, 7, slave_4_pdo_entries + 0}, /* Outputs */
    {0x1a00, 8, slave_4_pdo_entries + 7}, /* Inputs */
};

ec_sync_info_t slave_4_syncs[3] = {
    {0, EC_DIR_OUTPUT, 1, slave_4_pdos + 0, EC_WD_ENABLE},
    {1, EC_DIR_INPUT, 1, slave_4_pdos + 1, EC_WD_DISABLE},
    {0xff}};

#endif // EC_MACT_INFO_H