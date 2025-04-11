#ifndef EC_SLAVE_3_H
#define EC_SLAVE_3_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_3 : public Ec_slave_base
{
public:
    Ec_slave_3(uint16_t slave_address_, const std::string &slave_name_)
    {
        slave_address = slave_address_;
        slave_name = slave_name_;
    }

    ~Ec_slave_3() {}

    virtual void set_info()
    {
        slave_info.alias = alias;
        slave_info.position = position;
        slave_info.vendor_id = vendor_id;
        slave_info.product_code = product_code;

        slave_info.slave_pdo_entries = slave_3_pdo_entries;
        slave_info.slave_pdos = slave_3_pdos;
        slave_info.slave_syncs = slave_3_syncs;
    }

    virtual void set_pdo()
    {
        domain_i_regs = domain_regs;
    }

    virtual void monitor_status() {}

    virtual void transfer_tx_pdo()
    {
        uint16_t Device_ID = EC_READ_U16(domain_i_pd + off_tx_pdo_1);
        uint16_t Second = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
        uint16_t Minute = EC_READ_U16(domain_i_pd + off_tx_pdo_3);
        uint16_t Hour = EC_READ_U16(domain_i_pd + off_tx_pdo_4);
        uint16_t Day = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
        uint16_t Month = EC_READ_U16(domain_i_pd + off_tx_pdo_6);
        uint16_t Year = EC_READ_U16(domain_i_pd + off_tx_pdo_7);
        uint16_t Roll_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_8);
        uint16_t Pitch_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_9);
        uint16_t Yaw_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_10);
        uint16_t Grip_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_11);
        uint16_t No_of_Usages = EC_READ_U16(domain_i_pd + off_tx_pdo_12);
        uint16_t Max_Usages = EC_READ_U16(domain_i_pd + off_tx_pdo_13);
        uint16_t Digital_Inputs = EC_READ_U16(domain_i_pd + off_tx_pdo_14);
        uint16_t Grip_Counts = EC_READ_U16(domain_i_pd + off_tx_pdo_15);
        uint16_t System_Number = EC_READ_U16(domain_i_pd + off_tx_pdo_16);
        uint16_t Device_UID = EC_READ_U16(domain_i_pd + off_tx_pdo_17);
        uint16_t Spare_Bytes = EC_READ_U16(domain_i_pd + off_tx_pdo_18);
        uint16_t MFG_Day = EC_READ_U16(domain_i_pd + off_tx_pdo_19);
        uint16_t MFG_Month = EC_READ_U16(domain_i_pd + off_tx_pdo_20);
        uint16_t MFG_Year = EC_READ_U16(domain_i_pd + off_tx_pdo_21);

        std::cout << "RFID_TXPDO: " << Device_ID << ", " << Second << ", " << Minute << ", " << Hour << ", " << Day << ", " << Month << ", " << Year << ", " << Roll_Offset << ", " << Pitch_Offset << ", " << Yaw_Offset << ", " << Grip_Offset << ", " << No_of_Usages << ", " << Max_Usages << ", " << Digital_Inputs << ", " << Grip_Counts << ", " << System_Number << ", " << Device_UID << ", " << Spare_Bytes << ", " << MFG_Day << ", " << MFG_Month << ", " << MFG_Year << std::endl;
    }

    virtual void transfer_rx_pdo()
    {
        uint16_t Led_Red = 0;
        uint16_t Led_Green = 0;
        uint16_t Led_Blue = 1;

        t_stamp += 4;
        if(t_stamp>=8000)
        {
            t_stamp = 0;
        }

        if(t_stamp <= 1000)
        {
            Led_Red = 1;
            Led_Green = 0;
            Led_Blue = 0;
        }
        else if((1000 <= t_stamp) && (t_stamp <= 2000))
        {
            Led_Red = 0;
            Led_Green = 1;
            Led_Blue = 0;
        }
        else if((2000 <= t_stamp) && (t_stamp <= 3000))
        {
            Led_Red = 0;
            Led_Green = 0;
            Led_Blue = 1;
        }
        else if((3000 <= t_stamp) && (t_stamp <= 4000))
        {
            Led_Red = 1;
            Led_Green = 1;
            Led_Blue = 0;
        }
        else if((4000 <= t_stamp) && (t_stamp <= 5000))
        {
            Led_Red = 1;
            Led_Green = 0;
            Led_Blue = 1;
        }
        else if((5000 <= t_stamp) && (t_stamp <= 6000))
        {
            Led_Red = 0;
            Led_Green = 1;
            Led_Blue = 1;
        }
        else if((6000 <= t_stamp) && (t_stamp <= 7000))
        {
            Led_Red = 1;
            Led_Green = 1;
            Led_Blue = 1;
        }
        else if(7000 <= t_stamp)
        {
            Led_Red = 0;
            Led_Green = 0;
            Led_Blue = 0;
        }

        EC_WRITE_U16(domain_i_pd + off_rx_pdo_12, Led_Red);
        EC_WRITE_U16(domain_i_pd + off_rx_pdo_13, Led_Green);
        EC_WRITE_U16(domain_i_pd + off_rx_pdo_14, Led_Blue);
    }

    virtual void process_tx_pdo() {}
    virtual void process_rx_pdo() {}
    virtual void config_data_transfer() {}
    virtual void publish_data() {}
    virtual void subscribe_data() {}

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

        unsigned long t_stamp = 0;
};

#endif // EC_SLAVE_3_H
