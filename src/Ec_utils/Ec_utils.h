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

struct Slave_status
{
    bool is_connected = false;
    bool is_online = false;
    bool is_configured = false;
    bool is_operational = false;
    uint16_t slave_state = 0;
    bool is_pdo_registered = false;
};

enum Callback_status : uint16_t
{
    FAILURE = 0,
    SUCCESS = 1,
    IN_PROGRESS = 2
};

#endif // EC_UTILS_H
