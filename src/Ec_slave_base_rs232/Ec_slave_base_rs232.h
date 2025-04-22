#ifndef EC_SLAVE_BASE_RS232_H
#define EC_SLAVE_BASE_RS232_H

#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"

class Ec_slave_base_rs232 : public Ec_slave_base
{
public:
    Ec_slave_base_rs232();
    ~Ec_slave_base_rs232();

    virtual void set_info();
    virtual void set_pdo();
    virtual void monitor_status();
    virtual void transfer_tx_pdo();
    virtual void transfer_rx_pdo();
    virtual void process_tx_pdo();
    virtual void process_rx_pdo();
    virtual void config_data_transfer();
    virtual void publish_data();
    virtual void subscribe_data();
    virtual void main_process();
};

#endif // EC_SLAVE_BASE_RS232_H
