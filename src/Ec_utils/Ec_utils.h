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
    bool is_connected = false;      // done
    bool is_online = false;         // done
    bool is_configured = false;     // done
    bool is_operational = false;    // done
    uint16_t slave_state = 0;       // done
    bool is_pdo_registered = false; // done
};

struct Master_status
{
    bool running = false;
    bool domain_health = false;
    bool master_health = false;
    bool slaves_health = false;
};

enum Ec_callback_status : uint16_t
{
    SUCCESS = 0,
    FAILURE = 1,
    IN_PROGRESS = 2,
    UNKNOWN = 4
};

#endif // EC_UTILS_H
