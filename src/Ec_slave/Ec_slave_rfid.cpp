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
    m_tx_pdo_value.Device_ID = EC_READ_U16(domain_i_pd + off_tx_pdo_1);
    m_tx_pdo_value.Second = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
    m_tx_pdo_value.Minute = EC_READ_U16(domain_i_pd + off_tx_pdo_3);
    m_tx_pdo_value.Hour = EC_READ_U16(domain_i_pd + off_tx_pdo_4);
    m_tx_pdo_value.Day = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
    m_tx_pdo_value.Month = EC_READ_U16(domain_i_pd + off_tx_pdo_6);
    m_tx_pdo_value.Year = EC_READ_U16(domain_i_pd + off_tx_pdo_7);
    m_tx_pdo_value.Roll_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_8);
    m_tx_pdo_value.Pitch_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_9);
    m_tx_pdo_value.Yaw_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_10);
    m_tx_pdo_value.Grip_Offset = EC_READ_U16(domain_i_pd + off_tx_pdo_11);
    m_tx_pdo_value.No_of_Usages = EC_READ_U16(domain_i_pd + off_tx_pdo_12);
    m_tx_pdo_value.Max_Usages = EC_READ_U16(domain_i_pd + off_tx_pdo_13);
    m_tx_pdo_value.Digital_Inputs = EC_READ_U16(domain_i_pd + off_tx_pdo_14);
    m_tx_pdo_value.Grip_Counts = EC_READ_U16(domain_i_pd + off_tx_pdo_15);
    m_tx_pdo_value.System_Number = EC_READ_U16(domain_i_pd + off_tx_pdo_16);
    m_tx_pdo_value.Device_UID = EC_READ_U16(domain_i_pd + off_tx_pdo_17);
    m_tx_pdo_value.Spare_Bytes = EC_READ_U16(domain_i_pd + off_tx_pdo_18);
    m_tx_pdo_value.MFG_Day = EC_READ_U16(domain_i_pd + off_tx_pdo_19);
    m_tx_pdo_value.MFG_Month = EC_READ_U16(domain_i_pd + off_tx_pdo_20);
    m_tx_pdo_value.MFG_Year = EC_READ_U16(domain_i_pd + off_tx_pdo_21);

    std::cout << slave_ns << ": " << m_tx_pdo_value.Device_ID << ", " << m_tx_pdo_value.Second << ", " << m_tx_pdo_value.Minute << ", " << m_tx_pdo_value.Hour << ", " << m_tx_pdo_value.Day << ", " << m_tx_pdo_value.Month << ", " << m_tx_pdo_value.Year << ", " << m_tx_pdo_value.Roll_Offset << ", " << m_tx_pdo_value.Pitch_Offset << ", " << m_tx_pdo_value.Yaw_Offset << ", " << m_tx_pdo_value.Grip_Offset << ", " << m_tx_pdo_value.No_of_Usages << ", " << m_tx_pdo_value.Max_Usages << ", " << m_tx_pdo_value.Digital_Inputs << ", " << m_tx_pdo_value.Grip_Counts << ", " << m_tx_pdo_value.System_Number << ", " << m_tx_pdo_value.Device_UID << ", " << m_tx_pdo_value.Spare_Bytes << ", " << m_tx_pdo_value.MFG_Day << ", " << m_tx_pdo_value.MFG_Month << ", " << m_tx_pdo_value.MFG_Year << std::endl;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::transfer_rx_pdo()
{
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_12, m_rx_pdo_value.Led_Red);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_13, m_rx_pdo_value.Led_Green);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_14, m_rx_pdo_value.Led_Blue);

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
        m_rx_pdo_value.Led_Red = 1;
        m_rx_pdo_value.Led_Green = 0;
        m_rx_pdo_value.Led_Blue = 0;
    }
    else if ((1000 <= t_stamp) && (t_stamp <= 2000))
    {
        m_rx_pdo_value.Led_Red = 0;
        m_rx_pdo_value.Led_Green = 1;
        m_rx_pdo_value.Led_Blue = 0;
    }
    else if ((2000 <= t_stamp) && (t_stamp <= 3000))
    {
        m_rx_pdo_value.Led_Red = 0;
        m_rx_pdo_value.Led_Green = 0;
        m_rx_pdo_value.Led_Blue = 1;
    }
    else if ((3000 <= t_stamp) && (t_stamp <= 4000))
    {
        m_rx_pdo_value.Led_Red = 1;
        m_rx_pdo_value.Led_Green = 1;
        m_rx_pdo_value.Led_Blue = 0;
    }
    else if ((4000 <= t_stamp) && (t_stamp <= 5000))
    {
        m_rx_pdo_value.Led_Red = 1;
        m_rx_pdo_value.Led_Green = 0;
        m_rx_pdo_value.Led_Blue = 1;
    }
    else if ((5000 <= t_stamp) && (t_stamp <= 6000))
    {
        m_rx_pdo_value.Led_Red = 0;
        m_rx_pdo_value.Led_Green = 1;
        m_rx_pdo_value.Led_Blue = 1;
    }
    else if ((6000 <= t_stamp) && (t_stamp <= 7000))
    {
        m_rx_pdo_value.Led_Red = 1;
        m_rx_pdo_value.Led_Green = 1;
        m_rx_pdo_value.Led_Blue = 1;
    }
    else if (7000 <= t_stamp)
    {
        m_rx_pdo_value.Led_Red = 0;
        m_rx_pdo_value.Led_Green = 0;
        m_rx_pdo_value.Led_Blue = 0;
    }

    return Ec_callback_status::SUCCESS;
}
