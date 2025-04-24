#ifndef EC_SLAVE_BASE_DIGITAL_IN_H
#define EC_SLAVE_BASE_DIGITAL_IN_H

#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"

namespace Digital_input
{
    enum Bit_flags : uint32_t
    {
        DIN_0 = 1u << 0,
        DIN_1 = 1u << 1,
        DIN_2 = 1u << 2,
        DIN_3 = 1u << 3,
        DIN_4 = 1u << 4,
        DIN_5 = 1u << 5,
        DIN_6 = 1u << 6,
        DIN_7 = 1u << 7,
        DIN_8 = 1u << 8,
        DIN_9 = 1u << 9,
        DIN_10 = 1u << 10,
        DIN_11 = 1u << 11,
        DIN_12 = 1u << 12,
        DIN_13 = 1u << 13,
        DIN_14 = 1u << 14,
        DIN_15 = 1u << 15,
        DIN_16 = 1u << 16,
        DIN_17 = 1u << 17,
        DIN_18 = 1u << 18,
        DIN_19 = 1u << 19,
        DIN_20 = 1u << 20,
        DIN_21 = 1u << 21,
        DIN_22 = 1u << 22,
        DIN_23 = 1u << 23,
        DIN_24 = 1u << 24,
        DIN_25 = 1u << 25,
        DIN_26 = 1u << 26,
        DIN_27 = 1u << 27,
        DIN_28 = 1u << 28,
        DIN_29 = 1u << 29,
        DIN_30 = 1u << 30,
        DIN_31 = 1u << 31
    };
}

class Ec_slave_base_digital_in : public Ec_slave_base
{
public:
    Ec_slave_base_digital_in();
    ~Ec_slave_base_digital_in();

    virtual uint16_t set_info();
    virtual uint16_t set_pdo();
    virtual uint16_t monitor_status();
    virtual uint16_t transfer_tx_pdo();
    virtual uint16_t transfer_rx_pdo();
    virtual uint16_t process_tx_pdo();
    virtual uint16_t process_rx_pdo();
    virtual uint16_t config_data_transfer();
    virtual uint16_t publish_data();
    virtual uint16_t subscribe_data();
    virtual uint16_t main_process();
};

#endif // EC_SLAVE_BASE_DIGITAL_IN_H
