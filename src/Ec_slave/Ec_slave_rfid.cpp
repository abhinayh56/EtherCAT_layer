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

    m_tx_pdo.Device_ID.offset = register_pdo(m_tx_pdo.Device_ID);
    m_tx_pdo.Second.offset = register_pdo(m_tx_pdo.Second);
    m_tx_pdo.Minute.offset = register_pdo(m_tx_pdo.Minute);
    m_tx_pdo.Hour.offset = register_pdo(m_tx_pdo.Hour);
    m_tx_pdo.Day.offset = register_pdo(m_tx_pdo.Day);
    m_tx_pdo.Month.offset = register_pdo(m_tx_pdo.Month);
    m_tx_pdo.Year.offset = register_pdo(m_tx_pdo.Year);
    m_tx_pdo.Roll_Offset.offset = register_pdo(m_tx_pdo.Roll_Offset);
    m_tx_pdo.Pitch_Offset.offset = register_pdo(m_tx_pdo.Pitch_Offset);
    m_tx_pdo.Yaw_Offset.offset = register_pdo(m_tx_pdo.Yaw_Offset);
    m_tx_pdo.Grip_Offset.offset = register_pdo(m_tx_pdo.Grip_Offset);
    m_tx_pdo.No_of_Usages.offset = register_pdo(m_tx_pdo.No_of_Usages);
    m_tx_pdo.Max_Usages.offset = register_pdo(m_tx_pdo.Max_Usages);
    m_tx_pdo.Digital_Inputs.offset = register_pdo(m_tx_pdo.Digital_Inputs);
    m_tx_pdo.Grip_Counts.offset = register_pdo(m_tx_pdo.Grip_Counts);
    m_tx_pdo.System_Number.offset = register_pdo(m_tx_pdo.System_Number);
    m_tx_pdo.Device_UID.offset = register_pdo(m_tx_pdo.Device_UID);
    m_tx_pdo.Spare_Bytes.offset = register_pdo(m_tx_pdo.Spare_Bytes);
    m_tx_pdo.MFG_Day.offset = register_pdo(m_tx_pdo.MFG_Day);
    m_tx_pdo.MFG_Month.offset = register_pdo(m_tx_pdo.MFG_Month);
    m_tx_pdo.MFG_Year.offset = register_pdo(m_tx_pdo.MFG_Year);

    m_rx_pdo.Acknowledge.offset = register_pdo(m_rx_pdo.Acknowledge);
    m_rx_pdo.Second.offset = register_pdo(m_rx_pdo.Second);
    m_rx_pdo.Minute.offset = register_pdo(m_rx_pdo.Minute);
    m_rx_pdo.Hour.offset = register_pdo(m_rx_pdo.Hour);
    m_rx_pdo.Day.offset = register_pdo(m_rx_pdo.Day);
    m_rx_pdo.Month.offset = register_pdo(m_rx_pdo.Month);
    m_rx_pdo.Year.offset = register_pdo(m_rx_pdo.Year);
    m_rx_pdo.No_of_Usages.offset = register_pdo(m_rx_pdo.No_of_Usages);
    m_rx_pdo.Digital_Outputs.offset = register_pdo(m_rx_pdo.Digital_Outputs);
    m_rx_pdo.Grip_Counts.offset = register_pdo(m_rx_pdo.Grip_Counts);
    m_rx_pdo.System_Number.offset = register_pdo(m_rx_pdo.System_Number);
    m_rx_pdo.Led_Red.offset = register_pdo(m_rx_pdo.Led_Red);
    m_rx_pdo.Led_Green.offset = register_pdo(m_rx_pdo.Led_Green);
    m_rx_pdo.Led_Blue.offset = register_pdo(m_rx_pdo.Led_Blue);
    m_rx_pdo.Spare_Bytes.offset = register_pdo(m_rx_pdo.Spare_Bytes);
    m_rx_pdo.Roll_Offset.offset = register_pdo(m_rx_pdo.Roll_Offset);
    m_rx_pdo.Pitch_Offset.offset = register_pdo(m_rx_pdo.Pitch_Offset);
    m_rx_pdo.Yaw_Offset.offset = register_pdo(m_rx_pdo.Yaw_Offset);
    m_rx_pdo.Grip_Offset.offset = register_pdo(m_rx_pdo.Grip_Offset);

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

    std::cout << slave_ns << ": " << 
        m_tx_pdo.Device_ID.value << ", " <<
        m_tx_pdo.Second.value << ", " <<
        m_tx_pdo.Minute.value << ", " <<
        m_tx_pdo.Hour.value << ", " <<
        m_tx_pdo.Day.value << ", " <<
        m_tx_pdo.Month.value << ", " <<
        m_tx_pdo.Year.value << ", " <<
        m_tx_pdo.Roll_Offset.value << ", " <<
        m_tx_pdo.Pitch_Offset.value << ", " <<
        m_tx_pdo.Yaw_Offset.value << ", " <<
        m_tx_pdo.Grip_Offset.value << ", " <<
        m_tx_pdo.No_of_Usages.value << ", " <<
        m_tx_pdo.Max_Usages.value << ", " <<
        m_tx_pdo.Digital_Inputs.value << ", " <<
        m_tx_pdo.Grip_Counts.value << ", " <<
        m_tx_pdo.System_Number.value << ", " <<
        m_tx_pdo.Device_UID.value << ", " <<
        m_tx_pdo.Spare_Bytes.value << ", " <<
        m_tx_pdo.MFG_Day.value << ", " <<
        m_tx_pdo.MFG_Month.value << ", " <<
        m_tx_pdo.MFG_Year.value << ", " <<
        std::endl;

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
