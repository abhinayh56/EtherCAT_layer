#ifndef EC_SLAVE_RFID_H
#define EC_SLAVE_RFID_H

#include "Ec_slave_base.h"

class Ec_slave_rfid : public Ec_slave_base
{
public:
    Ec_slave_rfid(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_rfid();

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
#include "Ec_slave_rfid_info.h"


    struct Tx_pdo
    {
        Pdo_variable<uint16_t> Device_ID      = {0x0006, 0x01};
        Pdo_variable<uint16_t> Second         = {0x0006, 0x02};
        Pdo_variable<uint16_t> Minute         = {0x0006, 0x03};
        Pdo_variable<uint16_t> Hour           = {0x0006, 0x04};
        Pdo_variable<uint16_t> Day            = {0x0006, 0x05};
        Pdo_variable<uint16_t> Month          = {0x0006, 0x06};
        Pdo_variable<uint16_t> Year           = {0x0006, 0x07};
        Pdo_variable<uint16_t> Roll_Offset    = {0x0006, 0x08};
        Pdo_variable<uint16_t> Pitch_Offset   = {0x0006, 0x09};
        Pdo_variable<uint16_t> Yaw_Offset     = {0x0006, 0x0a};
        Pdo_variable<uint16_t> Grip_Offset    = {0x0006, 0x0b};
        Pdo_variable<uint16_t> No_of_Usages   = {0x0006, 0x0c};
        Pdo_variable<uint16_t> Max_Usages     = {0x0006, 0x0d};
        Pdo_variable<uint16_t> Digital_Inputs = {0x0006, 0x0e};
        Pdo_variable<uint16_t> Grip_Counts    = {0x0006, 0x0f};
        Pdo_variable<uint16_t> System_Number  = {0x0006, 0x10};
        Pdo_variable<uint16_t> Device_UID     = {0x0006, 0x11};
        Pdo_variable<uint16_t> Spare_Bytes    = {0x0006, 0x12};
        Pdo_variable<uint16_t> MFG_Day        = {0x0006, 0x13};
        Pdo_variable<uint16_t> MFG_Month      = {0x0006, 0x14};
        Pdo_variable<uint16_t> MFG_Year       = {0x0006, 0x15};
    } m_tx_pdo;

    struct Rx_pdo
    {
        Pdo_variable<uint16_t> Acknowledge     = {0x0005, 0x01};
        Pdo_variable<uint16_t> Second          = {0x0005, 0x02};
        Pdo_variable<uint16_t> Minute          = {0x0005, 0x03};
        Pdo_variable<uint16_t> Hour            = {0x0005, 0x04};
        Pdo_variable<uint16_t> Day             = {0x0005, 0x05};
        Pdo_variable<uint16_t> Month           = {0x0005, 0x06};
        Pdo_variable<uint16_t> Year            = {0x0005, 0x07};
        Pdo_variable<uint16_t> No_of_Usages    = {0x0005, 0x08};
        Pdo_variable<uint16_t> Digital_Outputs = {0x0005, 0x09};
        Pdo_variable<uint16_t> Grip_Counts     = {0x0005, 0x0a};
        Pdo_variable<uint16_t> System_Number   = {0x0005, 0x0b};
        Pdo_variable<uint16_t> Led_Red         = {0x0005, 0x0c};
        Pdo_variable<uint16_t> Led_Green       = {0x0005, 0x0d};
        Pdo_variable<uint16_t> Led_Blue        = {0x0005, 0x0e};
        Pdo_variable<uint16_t> Spare_Bytes     = {0x0005, 0x0f};
        Pdo_variable<uint16_t> Roll_Offset     = {0x0005, 0x10};
        Pdo_variable<uint16_t> Pitch_Offset    = {0x0005, 0x11};
        Pdo_variable<uint16_t> Yaw_Offset      = {0x0005, 0x12};
        Pdo_variable<uint16_t> Grip_Offset     = {0x0005, 0x13};
    } m_rx_pdo;

    unsigned long t_stamp = 0;
};

#endif // EC_SLAVE_RFID_H
