#ifndef EC_SLAVE_EK_1122_H
#define EC_SLAVE_EK_1122_H

#include "../Ec_slave_base_junction/Ec_slave_base_junction.h"

class Ec_slave_ek_1122 : public Ec_slave_base_junction
{
public:
    Ec_slave_ek_1122(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_ek_1122();

    virtual uint16_t set_info_from_eni();
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
    #include "Ec_slave_ek_1122_info.h"
};

#endif // EC_SLAVE_EK_1122_H
