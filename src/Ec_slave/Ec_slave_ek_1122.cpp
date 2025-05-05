#include "Ec_slave_ek_1122.h"

Ec_slave_ek_1122::Ec_slave_ek_1122(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_ek_1122::~Ec_slave_ek_1122()
{
}

uint16_t Ec_slave_ek_1122::set_info_from_eni()
{
    slave_info.alias = alias;
    slave_info.position = slave_address;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries;
    slave_info.slave_pdos;
    slave_info.slave_syncs = slave_syncs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::set_pdo()
{
    domain_i_regs = domain_regs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ek_1122::main_process()
{
    return Ec_callback_status::SUCCESS;
}
