#ifndef EC_SLAVE_EL_1008_H
#define EC_SLAVE_EL_1008_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_el_1008 : public Ec_slave_base
{
public:
    Ec_slave_el_1008(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_el_1008();

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

private:
    #include "Ec_slave_el_1008_info.h"

    unsigned int off_1;
    ec_pdo_entry_reg_t domain_regs[2] = {
        {0, 2, 0x00000002, 0x03f03052, 0x6000, 0x01, &off_1},
        {}};
};

#endif // EC_SLAVE_EL_1008_H
