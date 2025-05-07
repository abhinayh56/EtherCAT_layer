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

    unsigned int off_rx_pdo_1;
    unsigned int off_rx_pdo_2;
    unsigned int off_rx_pdo_3;
    unsigned int off_rx_pdo_4;
    unsigned int off_rx_pdo_5;
    unsigned int off_rx_pdo_6;
    unsigned int off_rx_pdo_7;
    unsigned int off_rx_pdo_8;
    unsigned int off_rx_pdo_9;
    unsigned int off_rx_pdo_10;
    unsigned int off_rx_pdo_11;
    unsigned int off_rx_pdo_12;
    unsigned int off_rx_pdo_13;
    unsigned int off_rx_pdo_14;
    unsigned int off_rx_pdo_15;
    unsigned int off_rx_pdo_16;
    unsigned int off_rx_pdo_17;
    unsigned int off_rx_pdo_18;
    unsigned int off_rx_pdo_19;
    unsigned int off_tx_pdo_1;
    unsigned int off_tx_pdo_2;
    unsigned int off_tx_pdo_3;
    unsigned int off_tx_pdo_4;
    unsigned int off_tx_pdo_5;
    unsigned int off_tx_pdo_6;
    unsigned int off_tx_pdo_7;
    unsigned int off_tx_pdo_8;
    unsigned int off_tx_pdo_9;
    unsigned int off_tx_pdo_10;
    unsigned int off_tx_pdo_11;
    unsigned int off_tx_pdo_12;
    unsigned int off_tx_pdo_13;
    unsigned int off_tx_pdo_14;
    unsigned int off_tx_pdo_15;
    unsigned int off_tx_pdo_16;
    unsigned int off_tx_pdo_17;
    unsigned int off_tx_pdo_18;
    unsigned int off_tx_pdo_19;
    unsigned int off_tx_pdo_20;
    unsigned int off_tx_pdo_21;

    ec_pdo_entry_reg_t domain_regs[41] = {
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x01, &off_rx_pdo_1},  /* Acknowledge */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x02, &off_rx_pdo_2},  /* Second */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x03, &off_rx_pdo_3},  /* Minute */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x04, &off_rx_pdo_4},  /* Hour */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x05, &off_rx_pdo_5},  /* Day */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x06, &off_rx_pdo_6},  /* Month */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x07, &off_rx_pdo_7},  /* Year */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x08, &off_rx_pdo_8},  /* No_of_Usages */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x09, &off_rx_pdo_9},  /* Digital_Outputs */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x0a, &off_rx_pdo_10}, /* Grip_Counts */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x0b, &off_rx_pdo_11}, /* System_Number */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x0c, &off_rx_pdo_12}, /* Led_Red */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x0d, &off_rx_pdo_13}, /* Led_Green */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x0e, &off_rx_pdo_14}, /* Led_Blue */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x0f, &off_rx_pdo_15}, /* Spare_Bytes */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x10, &off_rx_pdo_16}, /* Roll_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x11, &off_rx_pdo_17}, /* Pitch_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x12, &off_rx_pdo_18}, /* Yaw_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0005, 0x13, &off_rx_pdo_19}, /* Grip_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x01, &off_tx_pdo_1},  /* Device_ID */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x02, &off_tx_pdo_2},  /* Second */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x03, &off_tx_pdo_3},  /* Minute */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x04, &off_tx_pdo_4},  /* Hour */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x05, &off_tx_pdo_5},  /* Day */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x06, &off_tx_pdo_6},  /* Month */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x07, &off_tx_pdo_7},  /* Year */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x08, &off_tx_pdo_8},  /* Roll_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x09, &off_tx_pdo_9},  /* Pitch_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x0a, &off_tx_pdo_10}, /* Yaw_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x0b, &off_tx_pdo_11}, /* Grip_Offset */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x0c, &off_tx_pdo_12}, /* No_of_Usages */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x0d, &off_tx_pdo_13}, /* Max_Usages */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x0e, &off_tx_pdo_14}, /* Digital_Inputs */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x0f, &off_tx_pdo_15}, /* Grip_Counts */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x10, &off_tx_pdo_16}, /* System_Number */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x11, &off_tx_pdo_17}, /* Device_UID */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x12, &off_tx_pdo_18}, /* Spare_Bytes */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x13, &off_tx_pdo_19}, /* MFG_Day */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x14, &off_tx_pdo_20}, /* MFG_Month */
        {0, 7, 0x00006000, 0x00004000, 0x0006, 0x15, &off_tx_pdo_21}, /* MFG_Year */
        {}};

    struct Tx_pdo_value
    {
        uint16_t Device_ID;
        uint16_t Second;
        uint16_t Minute;
        uint16_t Hour;
        uint16_t Day;
        uint16_t Month;
        uint16_t Year;
        uint16_t Roll_Offset;
        uint16_t Pitch_Offset;
        uint16_t Yaw_Offset;
        uint16_t Grip_Offset;
        uint16_t No_of_Usages;
        uint16_t Max_Usages;
        uint16_t Digital_Inputs;
        uint16_t Grip_Counts;
        uint16_t System_Number;
        uint16_t Device_UID;
        uint16_t Spare_Bytes;
        uint16_t MFG_Day;
        uint16_t MFG_Month;
        uint16_t MFG_Year;
    } m_tx_pdo_value;

    struct Rx_pdo_value
    {
        uint16_t Acknowledge;
        uint16_t Second;
        uint16_t Minute;
        uint16_t Hour;
        uint16_t Day;
        uint16_t Month;
        uint16_t Year;
        uint16_t No_of_Usages;
        uint16_t Digital_Outputs;
        uint16_t Grip_Counts;
        uint16_t System_Number;
        uint16_t Led_Red;
        uint16_t Led_Green;
        uint16_t Led_Blue;
        uint16_t Spare_Bytes;
        uint16_t Roll_Offset;
        uint16_t Pitch_Offset;
        uint16_t Yaw_Offset;
        uint16_t Grip_Offset;
    } m_rx_pdo_value;

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
