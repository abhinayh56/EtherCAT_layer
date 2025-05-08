#include "Ec_slave_el_2008.h"

Ec_slave_el_2008::Ec_slave_el_2008(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_el_2008::~Ec_slave_el_2008()
{
}

uint16_t Ec_slave_el_2008::set_info_from_eni()
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

uint16_t Ec_slave_el_2008::set_pdo()
{
    register_pdo(&m_rx_pdo.Output);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::transfer_rx_pdo()
{
    transfer_rx_pdo_U8(&m_rx_pdo.Output);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_2008::main_process()
{
    time_stamp += 1;

    if (time_stamp >= 2000)
    {
        time_stamp = 0;
    }

    if (time_stamp <= 1000)
    {
        m_rx_pdo.Output.value = 0xAA;
    }
    else
    {
        m_rx_pdo.Output.value = 0x55;
    }

    return Ec_callback_status::SUCCESS;
}
