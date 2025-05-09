#ifndef EC_SLAVE_EL_1008_H
#define EC_SLAVE_EL_1008_H

#include "../Ec_slave_base_digital_in/Ec_slave_base_digital_in.h"

class Ec_slave_el_1008 : public Ec_slave_base_digital_in
{
public:
    Ec_slave_el_1008(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_el_1008();

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
    #include "Ec_slave_el_1008_info.h"

    struct Tx_pdo
    {
        Pdo_variable<uint8_t> Input = {0x6000, 0x01};
    } m_tx_pdo;
};

#endif // EC_SLAVE_EL_1008_H
