#ifndef EC_SLAVE_RFID_H
#define EC_SLAVE_RFID_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_rfid : public Ec_slave_base
{
public:
    Ec_slave_rfid(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_rfid();

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
    uint16_t alias = 0;
    uint16_t position = 7;
    uint32_t vendor_id = 0x00006000;
    uint32_t product_code = 0x00004000;

    ec_pdo_entry_info_t slave_3_pdo_entries[40] = {
        {0x0005, 0x01, 16}, /* Acknowledge */
        {0x0005, 0x02, 16}, /* Second */
        {0x0005, 0x03, 16}, /* Minute */
        {0x0005, 0x04, 16}, /* Hour */
        {0x0005, 0x05, 16}, /* Day */
        {0x0005, 0x06, 16}, /* Month */
        {0x0005, 0x07, 16}, /* Year */
        {0x0005, 0x08, 16}, /* No_of_Usages */
        {0x0005, 0x09, 16}, /* Digital_Outputs */
        {0x0005, 0x0a, 16}, /* Grip_Counts */
        {0x0005, 0x0b, 16}, /* System_Number */
        {0x0005, 0x0c, 16}, /* Led_Red */
        {0x0005, 0x0d, 16}, /* Led_Green */
        {0x0005, 0x0e, 16}, /* Led_Blue */
        {0x0005, 0x0f, 16}, /* Spare_Bytes */
        {0x0005, 0x10, 16}, /* Roll_Offset */
        {0x0005, 0x11, 16}, /* Pitch_Offset */
        {0x0005, 0x12, 16}, /* Yaw_Offset */
        {0x0005, 0x13, 16}, /* Grip_Offset */
        {0x0006, 0x01, 16}, /* Device_ID */
        {0x0006, 0x02, 16}, /* Second */
        {0x0006, 0x03, 16}, /* Minute */
        {0x0006, 0x04, 16}, /* Hour */
        {0x0006, 0x05, 16}, /* Day */
        {0x0006, 0x06, 16}, /* Month */
        {0x0006, 0x07, 16}, /* Year */
        {0x0006, 0x08, 16}, /* Roll_Offset */
        {0x0006, 0x09, 16}, /* Pitch_Offset */
        {0x0006, 0x0a, 16}, /* Yaw_Offset */
        {0x0006, 0x0b, 16}, /* Grip_Offset */
        {0x0006, 0x0c, 16}, /* No_of_Usages */
        {0x0006, 0x0d, 16}, /* Max_Usages */
        {0x0006, 0x0e, 16}, /* Digital_Inputs */
        {0x0006, 0x0f, 16}, /* Grip_Counts */
        {0x0006, 0x10, 16}, /* System_Number */
        {0x0006, 0x11, 16}, /* Device_UID */
        {0x0006, 0x12, 16}, /* Spare_Bytes */
        {0x0006, 0x13, 16}, /* MFG_Day */
        {0x0006, 0x14, 16}, /* MFG_Month */
        {0x0006, 0x15, 16}, /* MFG_Year */
    };

    ec_pdo_info_t slave_3_pdos[2] = {
        {0x1600, 19, slave_3_pdo_entries + 0},  /* Outputs */
        {0x1a00, 21, slave_3_pdo_entries + 19}, /* Inputs */
    };

    ec_sync_info_t slave_3_syncs[3] = {
        {0, EC_DIR_OUTPUT, 1, slave_3_pdos + 0, EC_WD_ENABLE},
        {1, EC_DIR_INPUT, 1, slave_3_pdos + 1, EC_WD_DISABLE},
        {0xff}};

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
        {0, 8, 0x00006000, 0x00004000, 0x0005, 0x02, &off_rx_pdo_2},  /* Second */
        {0, 45, 0x00006000, 0x00004000, 0x0005, 0x03, &off_rx_pdo_3},  /* Minute */
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

    unsigned long t_stamp = 0;
};

#endif // EC_SLAVE_RFID_H
