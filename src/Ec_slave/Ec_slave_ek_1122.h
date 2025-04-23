#ifndef EC_SLAVE_EK_1122_H
#define EC_SLAVE_EK_1122_H

#include <stdint.h>
#include "../Ec_slave_base_junction/Ec_slave_base_junction.h"

class Ec_slave_ek_1122 : public Ec_slave_base_junction
{
public:
    Ec_slave_ek_1122(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_ek_1122();

    virtual void set_info();
    virtual void set_pdo();
    // virtual void monitor_status();
    virtual void transfer_tx_pdo();
    virtual void transfer_rx_pdo();
    virtual void process_tx_pdo();
    virtual void process_rx_pdo();
    virtual void config_data_transfer();
    virtual void publish_data();
    virtual void subscribe_data();
    virtual void main_process();

private:
    #include "Ec_slave_ek_1122_info.h"

    unsigned int off_1;
    ec_pdo_entry_reg_t domain_regs[1] = {
        {}};
    
    unsigned long time_stamp = 0;
};

#endif // EC_SLAVE_EK_1122_H
