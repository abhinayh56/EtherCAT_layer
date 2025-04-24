#ifndef EC_SLAVE_EL_1008_H
#define EC_SLAVE_EL_1008_H

#include "../Ec_slave_base_digital_in/Ec_slave_base_digital_in.h"

class Ec_slave_el_1008 : public Ec_slave_base_digital_in
{
public:
    Ec_slave_el_1008(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_el_1008();

    virtual uint16_t set_info();
    virtual uint16_t set_pdo();
    virtual uint16_t transfer_tx_pdo();
    virtual uint16_t transfer_rx_pdo();
    virtual uint16_t process_tx_pdo();
    virtual uint16_t process_rx_pdo();
    virtual uint16_t config_data_transfer();
    virtual uint16_t publish_data();
    virtual uint16_t subscribe_data();
    virtual uint16_t main_process();

private:
    #include "Ec_slave_el_1008_info.h"

    unsigned int off_1;
    ec_pdo_entry_reg_t domain_regs[2] = {
        {0, 2, 0x00000002, 0x03f03052, 0x6000, 0x01, &off_1},
        {}};
};

#endif // EC_SLAVE_EL_1008_H
