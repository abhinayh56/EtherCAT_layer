#ifndef EC_UTILS_H
#define EC_UTILS_H

#include <ecrt.h>
#include <stdint.h>

struct Slave_info
{
    uint16_t alias;
    uint16_t position;
    uint32_t vendor_id;
    uint32_t product_code;

    ec_pdo_entry_info_t *slave_pdo_entries;
    ec_pdo_info_t *slave_pdos;
    ec_sync_info_t *slave_syncs;
};

#endif // EC_UTILS_H
