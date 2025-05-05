#ifndef EC_SLAVE_BASE_RS232_H
#define EC_SLAVE_BASE_RS232_H

#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"

class Ec_slave_base_rs232 : public Ec_slave_base
{
public:
    Ec_slave_base_rs232();
    ~Ec_slave_base_rs232();

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
    virtual uint16_t reset();
    virtual uint16_t init();
};

#endif // EC_SLAVE_BASE_RS232_H
