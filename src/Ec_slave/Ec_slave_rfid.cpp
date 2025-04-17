#include "Ec_slave_rfid.h"

Ec_slave_rfid::Ec_slave_rfid(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_rfid::~Ec_slave_rfid()
{
}

void Ec_slave_rfid::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_3_pdo_entries;
    slave_info.slave_pdos = slave_3_pdos;
    slave_info.slave_syncs = slave_3_syncs;
}

void Ec_slave_rfid::set_pdo()
{
    for (uint8_t i = 0; i < 41; i++)
    {
        domain_regs[i].position = slave_address;
    }
    domain_i_regs = domain_regs;
}

void Ec_slave_rfid::monitor_status()
{
}

void Ec_slave_rfid::transfer_tx_pdo()
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

    // std::cout << "RFID_TXPDO: " << Device_ID << ", " << Second << ", " << Minute << ", " << Hour << ", " << Day << ", " << Month << ", " << Year << ", " << Roll_Offset << ", " << Pitch_Offset << ", " << Yaw_Offset << ", " << Grip_Offset << ", " << No_of_Usages << ", " << Max_Usages << ", " << Digital_Inputs << ", " << Grip_Counts << ", " << System_Number << ", " << Device_UID << ", " << Spare_Bytes << ", " << MFG_Day << ", " << MFG_Month << ", " << MFG_Year << std::endl;
}

void Ec_slave_rfid::transfer_rx_pdo()
{
    uint16_t Led_Red = 0;
    uint16_t Led_Green = 0;
    uint16_t Led_Blue = 1;

    t_stamp += 4;
    if (t_stamp >= 8000)
    {
        t_stamp = 0;
    }

    if (t_stamp <= 1000)
    {
        Led_Red = 1;
        Led_Green = 0;
        Led_Blue = 0;
    }
    else if ((1000 <= t_stamp) && (t_stamp <= 2000))
    {
        Led_Red = 0;
        Led_Green = 1;
        Led_Blue = 0;
    }
    else if ((2000 <= t_stamp) && (t_stamp <= 3000))
    {
        Led_Red = 0;
        Led_Green = 0;
        Led_Blue = 1;
    }
    else if ((3000 <= t_stamp) && (t_stamp <= 4000))
    {
        Led_Red = 1;
        Led_Green = 1;
        Led_Blue = 0;
    }
    else if ((4000 <= t_stamp) && (t_stamp <= 5000))
    {
        Led_Red = 1;
        Led_Green = 0;
        Led_Blue = 1;
    }
    else if ((5000 <= t_stamp) && (t_stamp <= 6000))
    {
        Led_Red = 0;
        Led_Green = 1;
        Led_Blue = 1;
    }
    else if ((6000 <= t_stamp) && (t_stamp <= 7000))
    {
        Led_Red = 1;
        Led_Green = 1;
        Led_Blue = 1;
    }
    else if (7000 <= t_stamp)
    {
        Led_Red = 0;
        Led_Green = 0;
        Led_Blue = 0;
    }

    EC_WRITE_U16(domain_i_pd + off_rx_pdo_12, Led_Red);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_13, Led_Green);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_14, Led_Blue);
}

void Ec_slave_rfid::process_tx_pdo()
{
}

void Ec_slave_rfid::process_rx_pdo()
{
}

void Ec_slave_rfid::config_data_transfer()
{
}

void Ec_slave_rfid::publish_data()
{
}

void Ec_slave_rfid::subscribe_data()
{
}

void Ec_slave_rfid::main_process()
{
}