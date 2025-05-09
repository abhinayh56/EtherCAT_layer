#ifndef EC_SLAVE_INGENIA_H
#define EC_SLAVE_INGENIA_H

#include <cmath>
#include "../Ec_slave_base_motor_drive/Ec_slave_base_motor_drive.h"

class Ec_slave_ingenia : public Ec_slave_base_motor_drive
{
public:
    Ec_slave_ingenia(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_ingenia();

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
    virtual uint16_t reset();
    virtual uint16_t init();

private:
    #include "Ec_slave_ingenia_info.h"

    struct Tx_pdo
    {
        Pdo_variable<uint16_t> Status_Word            = {0x6041, 0x00};
        Pdo_variable<int32_t>  Actual_position        = {0x6064, 0x00};
        Pdo_variable<int32_t>  Actual_velocity        = {0x606c, 0x00};
        Pdo_variable<uint8_t>  Operation_mode_display = {0x6061, 0x00};
    } m_tx_pdo;
    
    struct Rx_pdo
    {
        Pdo_variable<uint16_t> CONTROL_WD  = {0x6040, 0x00};
        Pdo_variable<int32_t>  TARGET_POS  = {0x607a, 0x00};
        Pdo_variable<int32_t>  TARGET_VEL  = {0x60ff, 0x00};
        Pdo_variable<uint8_t>  OP_MODE     = {0x6060, 0x00};
    } m_rx_pdo;

    unsigned long t_stamp = 0;
    int32_t offset = 0;
};

#endif // EC_SLAVE_INGENIA_H
