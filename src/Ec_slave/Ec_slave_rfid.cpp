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

    register_pdo(&m_tx_pdo.Device_ID);
    register_pdo(&m_tx_pdo.Second);
    register_pdo(&m_tx_pdo.Minute);
    register_pdo(&m_tx_pdo.Hour);
    register_pdo(&m_tx_pdo.Day);
    register_pdo(&m_tx_pdo.Month);
    register_pdo(&m_tx_pdo.Year);
    register_pdo(&m_tx_pdo.Roll_Offset);
    register_pdo(&m_tx_pdo.Pitch_Offset);
    register_pdo(&m_tx_pdo.Yaw_Offset);
    register_pdo(&m_tx_pdo.Grip_Offset);
    register_pdo(&m_tx_pdo.No_of_Usages);
    register_pdo(&m_tx_pdo.Max_Usages);
    register_pdo(&m_tx_pdo.Digital_Inputs);
    register_pdo(&m_tx_pdo.Grip_Counts);
    register_pdo(&m_tx_pdo.System_Number);
    register_pdo(&m_tx_pdo.Device_UID);
    register_pdo(&m_tx_pdo.Spare_Bytes);
    register_pdo(&m_tx_pdo.MFG_Day);
    register_pdo(&m_tx_pdo.MFG_Month);
    register_pdo(&m_tx_pdo.MFG_Year);

    register_pdo(&m_rx_pdo.Acknowledge);
    register_pdo(&m_rx_pdo.Second);
    register_pdo(&m_rx_pdo.Minute);
    register_pdo(&m_rx_pdo.Hour);
    register_pdo(&m_rx_pdo.Day);
    register_pdo(&m_rx_pdo.Month);
    register_pdo(&m_rx_pdo.Year);
    register_pdo(&m_rx_pdo.No_of_Usages);
    register_pdo(&m_rx_pdo.Digital_Outputs);
    register_pdo(&m_rx_pdo.Grip_Counts);
    register_pdo(&m_rx_pdo.System_Number);
    register_pdo(&m_rx_pdo.Led_Red);
    register_pdo(&m_rx_pdo.Led_Green);
    register_pdo(&m_rx_pdo.Led_Blue);
    register_pdo(&m_rx_pdo.Spare_Bytes);
    register_pdo(&m_rx_pdo.Roll_Offset);
    register_pdo(&m_rx_pdo.Pitch_Offset);
    register_pdo(&m_rx_pdo.Yaw_Offset);
    register_pdo(&m_rx_pdo.Grip_Offset);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::transfer_tx_pdo()
{
    m_tx_pdo.Device_ID.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Device_ID.offset);
    m_tx_pdo.Second.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Second.offset);
    m_tx_pdo.Minute.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Minute.offset);
    m_tx_pdo.Hour.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Hour.offset);
    m_tx_pdo.Day.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Day.offset);
    m_tx_pdo.Month.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Month.offset);
    m_tx_pdo.Year.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Year.offset);
    m_tx_pdo.Roll_Offset.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Roll_Offset.offset);
    m_tx_pdo.Pitch_Offset.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Pitch_Offset.offset);
    m_tx_pdo.Yaw_Offset.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Yaw_Offset.offset);
    m_tx_pdo.Grip_Offset.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Grip_Offset.offset);
    m_tx_pdo.No_of_Usages.value = EC_READ_U16(domain_i_pd + m_tx_pdo.No_of_Usages.offset);
    m_tx_pdo.Max_Usages.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Max_Usages.offset);
    m_tx_pdo.Digital_Inputs.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Digital_Inputs.offset);
    m_tx_pdo.Grip_Counts.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Grip_Counts.offset);
    m_tx_pdo.System_Number.value = EC_READ_U16(domain_i_pd + m_tx_pdo.System_Number.offset);
    m_tx_pdo.Device_UID.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Device_UID.offset);
    m_tx_pdo.Spare_Bytes.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Spare_Bytes.offset);
    m_tx_pdo.MFG_Day.value = EC_READ_U16(domain_i_pd + m_tx_pdo.MFG_Day.offset);
    m_tx_pdo.MFG_Month.value = EC_READ_U16(domain_i_pd + m_tx_pdo.MFG_Month.offset);
    m_tx_pdo.MFG_Year.value = EC_READ_U16(domain_i_pd + m_tx_pdo.MFG_Year.offset);
    
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::transfer_rx_pdo()
{
    EC_WRITE_U16(domain_i_pd + m_rx_pdo.Led_Red.offset, m_rx_pdo.Led_Red.value);
    EC_WRITE_U16(domain_i_pd + m_rx_pdo.Led_Green.offset, m_rx_pdo.Led_Green.value);
    EC_WRITE_U16(domain_i_pd + m_rx_pdo.Led_Blue.offset, m_rx_pdo.Led_Blue.value);

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
        m_rx_pdo.Led_Red.value = 1;
        m_rx_pdo.Led_Green.value = 0;
        m_rx_pdo.Led_Blue.value = 0;
    }
    else if ((1000 <= t_stamp) && (t_stamp <= 2000))
    {
        m_rx_pdo.Led_Red.value = 0;
        m_rx_pdo.Led_Green.value = 1;
        m_rx_pdo.Led_Blue.value = 0;
    }
    else if ((2000 <= t_stamp) && (t_stamp <= 3000))
    {
        m_rx_pdo.Led_Red.value = 0;
        m_rx_pdo.Led_Green.value = 0;
        m_rx_pdo.Led_Blue.value = 1;
    }
    else if ((3000 <= t_stamp) && (t_stamp <= 4000))
    {
        m_rx_pdo.Led_Red.value = 1;
        m_rx_pdo.Led_Green.value = 1;
        m_rx_pdo.Led_Blue.value = 0;
    }
    else if ((4000 <= t_stamp) && (t_stamp <= 5000))
    {
        m_rx_pdo.Led_Red.value = 1;
        m_rx_pdo.Led_Green.value = 0;
        m_rx_pdo.Led_Blue.value = 1;
    }
    else if ((5000 <= t_stamp) && (t_stamp <= 6000))
    {
        m_rx_pdo.Led_Red.value = 0;
        m_rx_pdo.Led_Green.value = 1;
        m_rx_pdo.Led_Blue.value = 1;
    }
    else if ((6000 <= t_stamp) && (t_stamp <= 7000))
    {
        m_rx_pdo.Led_Red.value = 1;
        m_rx_pdo.Led_Green.value = 1;
        m_rx_pdo.Led_Blue.value = 1;
    }
    else if (7000 <= t_stamp)
    {
        m_rx_pdo.Led_Red.value = 0;
        m_rx_pdo.Led_Green.value = 0;
        m_rx_pdo.Led_Blue.value = 0;
    }

    return Ec_callback_status::SUCCESS;
}
