#include "Ec_slave_el_1008.h"

Ec_slave_el_1008::Ec_slave_el_1008(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_el_1008::~Ec_slave_el_1008()
{
}

uint16_t Ec_slave_el_1008::set_info_from_eni()
{
    slave_info.alias = alias;
    slave_info.position = slave_address;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;
    slave_info.slave_syncs = slave_syncs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::set_pdo()
{
    register_pdo(&m_tx_pdo.Input);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::transfer_tx_pdo()
{
    transfer_tx_pdo_U8(&m_tx_pdo.Input);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_el_1008::main_process()
{
    return Ec_callback_status::SUCCESS;
}
