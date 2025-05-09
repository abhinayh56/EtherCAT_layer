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
    transfer_tx_pdo_U16(&m_tx_pdo.Device_ID);
    transfer_tx_pdo_U16(&m_tx_pdo.Second);
    transfer_tx_pdo_U16(&m_tx_pdo.Minute);
    transfer_tx_pdo_U16(&m_tx_pdo.Hour);
    transfer_tx_pdo_U16(&m_tx_pdo.Day);
    transfer_tx_pdo_U16(&m_tx_pdo.Month);
    transfer_tx_pdo_U16(&m_tx_pdo.Year);
    transfer_tx_pdo_U16(&m_tx_pdo.Roll_Offset);
    transfer_tx_pdo_U16(&m_tx_pdo.Pitch_Offset);
    transfer_tx_pdo_U16(&m_tx_pdo.Yaw_Offset);
    transfer_tx_pdo_U16(&m_tx_pdo.Grip_Offset);
    transfer_tx_pdo_U16(&m_tx_pdo.No_of_Usages);
    transfer_tx_pdo_U16(&m_tx_pdo.Max_Usages);
    transfer_tx_pdo_U16(&m_tx_pdo.Digital_Inputs);
    transfer_tx_pdo_U16(&m_tx_pdo.Grip_Counts);
    transfer_tx_pdo_U16(&m_tx_pdo.System_Number);
    transfer_tx_pdo_U16(&m_tx_pdo.Device_UID);
    transfer_tx_pdo_U16(&m_tx_pdo.Spare_Bytes);
    transfer_tx_pdo_U16(&m_tx_pdo.MFG_Day);
    transfer_tx_pdo_U16(&m_tx_pdo.MFG_Month);
    transfer_tx_pdo_U16(&m_tx_pdo.MFG_Year);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_rfid::transfer_rx_pdo()
{
    transfer_rx_pdo_U16(&m_rx_pdo.Acknowledge);
    transfer_rx_pdo_U16(&m_rx_pdo.Second);
    transfer_rx_pdo_U16(&m_rx_pdo.Minute);
    transfer_rx_pdo_U16(&m_rx_pdo.Hour);
    transfer_rx_pdo_U16(&m_rx_pdo.Day);
    transfer_rx_pdo_U16(&m_rx_pdo.Month);
    transfer_rx_pdo_U16(&m_rx_pdo.Year);
    transfer_rx_pdo_U16(&m_rx_pdo.No_of_Usages);
    transfer_rx_pdo_U16(&m_rx_pdo.Digital_Outputs);
    transfer_rx_pdo_U16(&m_rx_pdo.Grip_Counts);
    transfer_rx_pdo_U16(&m_rx_pdo.System_Number);
    transfer_rx_pdo_U16(&m_rx_pdo.Led_Red);
    transfer_rx_pdo_U16(&m_rx_pdo.Led_Green);
    transfer_rx_pdo_U16(&m_rx_pdo.Led_Blue);
    transfer_rx_pdo_U16(&m_rx_pdo.Spare_Bytes);
    transfer_rx_pdo_U16(&m_rx_pdo.Roll_Offset);
    transfer_rx_pdo_U16(&m_rx_pdo.Pitch_Offset);
    transfer_rx_pdo_U16(&m_rx_pdo.Yaw_Offset);
    transfer_rx_pdo_U16(&m_rx_pdo.Grip_Offset);

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
