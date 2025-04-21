#ifndef EC_SLAVE_EL_2008_INFO_H
#define EC_SLAVE_EL_2008_INFO_H

#include <stdint.h>
#include <ecrt.h>

uint16_t alias = 0;
uint16_t position = 1;
uint32_t vendor_id = 0x00000002;
uint32_t product_code = 0x07d83052;

ec_pdo_entry_info_t slave_pdo_entries[8] = {
    {0x7000, 0x01, 1}, /* Output */
    {0x7010, 0x01, 1}, /* Output */
    {0x7020, 0x01, 1}, /* Output */
    {0x7030, 0x01, 1}, /* Output */
    {0x7040, 0x01, 1}, /* Output */
    {0x7050, 0x01, 1}, /* Output */
    {0x7060, 0x01, 1}, /* Output */
    {0x7070, 0x01, 1}, /* Output */
};

ec_pdo_info_t slave_pdos[8] = {
    {0x1600, 1, slave_pdo_entries + 0}, /* Channel 1 */
    {0x1601, 1, slave_pdo_entries + 1}, /* Channel 2 */
    {0x1602, 1, slave_pdo_entries + 2}, /* Channel 3 */
    {0x1603, 1, slave_pdo_entries + 3}, /* Channel 4 */
    {0x1604, 1, slave_pdo_entries + 4}, /* Channel 5 */
    {0x1605, 1, slave_pdo_entries + 5}, /* Channel 6 */
    {0x1606, 1, slave_pdo_entries + 6}, /* Channel 7 */
    {0x1607, 1, slave_pdo_entries + 7}, /* Channel 8 */
};

ec_sync_info_t slave_syncs[2] = {
    {0, EC_DIR_OUTPUT, 8, slave_pdos + 0, EC_WD_ENABLE},
    {0xff}};

#endif // EC_SLAVE_EL_2008_INFO_H