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

enum Ec_callback_status : uint16_t
{
    SUCCESS = 0,
    FAILURE = 1,
    IN_PROGRESS = 2,
    UNKNOWN = 4
};

template <typename T>
T SET_BIT(T value, uint16_t bit_index)
{
    value = value | (1 << bit_index);
}

template <typename T>
uint16_t GET_BIT(T value, uint16_t bit_index)
{
    value = value & (1 << bit_index);
    if (value == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

#endif // EC_UTILS_H
