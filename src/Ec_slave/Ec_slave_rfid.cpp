#include "Ec_slave_rfid.h"

Ec_slave_rfid::Ec_slave_rfid(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_rfid::~Ec_slave_rfid()
{
}

uint16_t Ec_slave_rfid::set_info_from_eni()
{
    slave_info.alias = alias;
    slave_info.position = slave_address;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_pdo_entries;
    slave_info.slave_pdos = slave_pdos;
    slave_info.slave_syncs = slave_syncs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::set_pdo()
{
    for (uint8_t i = 0; i < 41; i++)
    {
        domain_regs[i].position = slave_address;
    }
    domain_i_regs = domain_regs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::transfer_tx_pdo()
{
    m_tx_pdo.Device_ID = EC_READ_U16(domain_i_pd + off_tx_pdo_1);
    m_tx_pdo.Second = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
    m_tx_pdo.Minute = EC_READ_U16(domain_i_pd + off_tx_pdo_3);
    m_tx_pdo.Hour = EC_READ_U16(domain_i_pd + off_tx_pdo_4);
    m_tx_pdo.Day = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
    m_tx_pdo.Month = EC_READ_U16(domain_i_pd + off_tx_pdo_6);
    m_tx_pdo.Year = EC_READ_U16(domain_i_pd + off_tx_pdo_7);
    m_tx_pdo.Roll_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_8);
    m_tx_pdo.Pitch_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_9);
    m_tx_pdo.Yaw_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_10);
    m_tx_pdo.Grip_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_11);
    m_tx_pdo.No_of_Usages = EC_READ_U16(domain_i_pd + off_tx_pdo_12);
    m_tx_pdo.Max_Usages = EC_READ_U16(domain_i_pd + off_tx_pdo_13);
    m_tx_pdo.Digital_Inputs = EC_READ_U16(domain_i_pd + off_tx_pdo_14);
    m_tx_pdo.Grip_Counts = EC_READ_U16(domain_i_pd + off_tx_pdo_15);
    m_tx_pdo.System_Number = EC_READ_U16(domain_i_pd + off_tx_pdo_16);
    m_tx_pdo.Device_UID = EC_READ_U16(domain_i_pd + off_tx_pdo_17);
    m_tx_pdo.Spare_Bytes = EC_READ_U16(domain_i_pd + off_tx_pdo_18);
    m_tx_pdo.MFG_Day = EC_READ_U16(domain_i_pd + off_tx_pdo_19);
    m_tx_pdo.MFG_Month = EC_READ_U16(domain_i_pd + off_tx_pdo_20);
    m_tx_pdo.MFG_Year = EC_READ_U16(domain_i_pd + off_tx_pdo_21);

    // std::cout << "RFID_TXPDO: " << m_tx_pdo.Device_ID << ", " << m_tx_pdo.Second << ", " << m_tx_pdo.Minute << ", " << m_tx_pdo.Hour << ", " << m_tx_pdo.Day << ", " << m_tx_pdo.Month << ", " << m_tx_pdo.Year << ", " << m_tx_pdo.Roll_Offset << ", " << m_tx_pdo.Pitch_Offset << ", " << m_tx_pdo.Yaw_Offset << ", " << m_tx_pdo.Grip_Offset << ", " << m_tx_pdo.No_of_Usages << ", " << m_tx_pdo.Max_Usages << ", " << m_tx_pdo.Digital_Inputs << ", " << m_tx_pdo.Grip_Counts << ", " << m_tx_pdo.System_Number << ", " << m_tx_pdo.Device_UID << ", " << m_tx_pdo.Spare_Bytes << ", " << m_tx_pdo.MFG_Day << ", " << m_tx_pdo.MFG_Month << ", " << m_tx_pdo.MFG_Year << std::endl;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::transfer_rx_pdo()
{
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_12, m_rx_pdo.Led_Red);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_13, m_rx_pdo.Led_Green);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_14, m_rx_pdo.Led_Blue);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::main_process()
{
    t_stamp += 4;
    if (t_stamp >= 8000)
    {
        t_stamp = 0;
    }

    if (t_stamp <= 1000)
    {
        m_rx_pdo.Led_Red = 1;
        m_rx_pdo.Led_Green = 0;
        m_rx_pdo.Led_Blue = 0;
    }
    else if ((1000 <= t_stamp) && (t_stamp <= 2000))
    {
        m_rx_pdo.Led_Red = 0;
        m_rx_pdo.Led_Green = 1;
        m_rx_pdo.Led_Blue = 0;
    }
    else if ((2000 <= t_stamp) && (t_stamp <= 3000))
    {
        m_rx_pdo.Led_Red = 0;
        m_rx_pdo.Led_Green = 0;
        m_rx_pdo.Led_Blue = 1;
    }
    else if ((3000 <= t_stamp) && (t_stamp <= 4000))
    {
        m_rx_pdo.Led_Red = 1;
        m_rx_pdo.Led_Green = 1;
        m_rx_pdo.Led_Blue = 0;
    }
    else if ((4000 <= t_stamp) && (t_stamp <= 5000))
    {
        m_rx_pdo.Led_Red = 1;
        m_rx_pdo.Led_Green = 0;
        m_rx_pdo.Led_Blue = 1;
    }
    else if ((5000 <= t_stamp) && (t_stamp <= 6000))
    {
        m_rx_pdo.Led_Red = 0;
        m_rx_pdo.Led_Green = 1;
        m_rx_pdo.Led_Blue = 1;
    }
    else if ((6000 <= t_stamp) && (t_stamp <= 7000))
    {
        m_rx_pdo.Led_Red = 1;
        m_rx_pdo.Led_Green = 1;
        m_rx_pdo.Led_Blue = 1;
    }
    else if (7000 <= t_stamp)
    {
        m_rx_pdo.Led_Red = 0;
        m_rx_pdo.Led_Green = 0;
        m_rx_pdo.Led_Blue = 0;
    }

    return Ec_callback_status::SUCCESS;
}
