#ifndef EC_SLAVE_EL_2008_H
#define EC_SLAVE_EL_2008_H

#include "../Ec_slave_base_digital_out/Ec_slave_base_digital_out.h"

class Ec_slave_el_2008 : public Ec_slave_base_digital_out
{
public:
    Ec_slave_el_2008(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_el_2008();

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
    #include "Ec_slave_el_2008_info.h"

    unsigned int off_1;
    ec_pdo_entry_reg_t domain_regs[2] = {
        {0, 1, 0x00000002, 0x07d83052, 0x7000, 0x01, &off_1},
        {}};

    unsigned long time_stamp = 0;
};

#endif // EC_SLAVE_EL_2008_H
