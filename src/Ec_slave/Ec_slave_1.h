#ifndef EC_SLAVE_1_H
#define EC_SLAVE_1_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_1 : public Ec_slave_base
{
public:
    Ec_slave_1(uint16_t slave_address_, const std::string &slave_name_)
    {
        slave_address = slave_address_;
        slave_name = slave_name_;
    }

    ~Ec_slave_1() {}

    virtual void set_info() {}
    virtual void config_slave(ec_master_t *master) {}
    virtual void set_pdo() {}
    virtual void monitor_status() {}
    virtual void transfer_tx_pdo() {}
    virtual void transfer_rx_pdo() {}
    virtual void process_tx_pdo() {}
    virtual void process_rx_pdo() {}
    virtual void config_data_transfer() {}
    virtual void publish_data() {}
    virtual void subscribe_data() {}
};

#endif // EC_SLAVE_1_H