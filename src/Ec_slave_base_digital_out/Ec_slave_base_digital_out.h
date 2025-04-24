#ifndef EC_SLAVE_BASE_DIGITAL_OUT_H
#define EC_SLAVE_BASE_DIGITAL_OUT_H

#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"

namespace digital_output
{
    enum Bit_flags : uint32_t
    {
        DOUT_0 = 1u << 0,
        DOUT_1 = 1u << 1,
        DOUT_2 = 1u << 2,
        DOUT_3 = 1u << 3,
        DOUT_4 = 1u << 4,
        DOUT_5 = 1u << 5,
        DOUT_6 = 1u << 6,
        DOUT_7 = 1u << 7,
        DOUT_8 = 1u << 8,
        DOUT_9 = 1u << 9,
        DOUT_10 = 1u << 10,
        DOUT_11 = 1u << 11,
        DOUT_12 = 1u << 12,
        DOUT_13 = 1u << 13,
        DOUT_14 = 1u << 14,
        DOUT_15 = 1u << 15,
        DOUT_16 = 1u << 16,
        DOUT_17 = 1u << 17,
        DOUT_18 = 1u << 18,
        DOUT_19 = 1u << 19,
        DOUT_20 = 1u << 20,
        DOUT_21 = 1u << 21,
        DOUT_22 = 1u << 22,
        DOUT_23 = 1u << 23,
        DOUT_24 = 1u << 24,
        DOUT_25 = 1u << 25,
        DOUT_26 = 1u << 26,
        DOUT_27 = 1u << 27,
        DOUT_28 = 1u << 28,
        DOUT_29 = 1u << 29,
        DOUT_30 = 1u << 30,
        DOUT_31 = 1u << 31
    };
}

class Ec_slave_base_digital_out : public Ec_slave_base
{
public:
    Ec_slave_base_digital_out();
    ~Ec_slave_base_digital_out();

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

#endif // EC_SLAVE_BASE_DIGITAL_OUT_H
