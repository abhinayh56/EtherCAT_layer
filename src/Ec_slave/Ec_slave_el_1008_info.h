#ifndef EC_SLAVE_EL_1008_INFO_H
#define EC_SLAVE_EL_1008_INFO_H

#include <stdint.h>
#include <ecrt.h>

uint16_t alias = 0;
uint16_t position = 2;
uint32_t vendor_id = 0x00000002;
uint32_t product_code = 0x03f03052;

ec_pdo_entry_info_t slave_pdo_entries[8] = {
    {0x6000, 0x01, 1}, /* Input */
    {0x6010, 0x01, 1}, /* Input */
    {0x6020, 0x01, 1}, /* Input */
    {0x6030, 0x01, 1}, /* Input */
    {0x6040, 0x01, 1}, /* Input */
    {0x6050, 0x01, 1}, /* Input */
    {0x6060, 0x01, 1}, /* Input */
    {0x6070, 0x01, 1}, /* Input */
};

ec_pdo_info_t slave_pdos[8] = {
    {0x1a00, 1, slave_pdo_entries + 0}, /* Channel 1 */
    {0x1a01, 1, slave_pdo_entries + 1}, /* Channel 2 */
    {0x1a02, 1, slave_pdo_entries + 2}, /* Channel 3 */
    {0x1a03, 1, slave_pdo_entries + 3}, /* Channel 4 */
    {0x1a04, 1, slave_pdo_entries + 4}, /* Channel 5 */
    {0x1a05, 1, slave_pdo_entries + 5}, /* Channel 6 */
    {0x1a06, 1, slave_pdo_entries + 6}, /* Channel 7 */
    {0x1a07, 1, slave_pdo_entries + 7}, /* Channel 8 */
};

ec_sync_info_t slave_syncs[2] = {
    {0, EC_DIR_INPUT, 8, slave_pdos + 0, EC_WD_DISABLE},
    {0xff}};

#endif // EC_SLAVE_EL_1008_INFO_H