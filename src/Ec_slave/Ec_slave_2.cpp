#include "Ec_slave_2.h"

Ec_slave_2::Ec_slave_2(uint16_t slave_address_, const std::string &slave_name_)
{
    slave_address = slave_address_;
    slave_name = slave_name_;
}

Ec_slave_2::~Ec_slave_2()
{
}

void Ec_slave_2::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_2_pdo_entries;
    slave_info.slave_pdos = slave_2_pdos;
    slave_info.slave_syncs = slave_2_syncs;
}

void Ec_slave_2::set_pdo()
{
    domain_i_regs = domain_regs;
}

void Ec_slave_2::monitor_status() {}

void Ec_slave_2::transfer_tx_pdo()
{
    uint16_t dig_input = EC_READ_U8(domain_i_pd + off_1);
    // std::cout << "dig_input: " << dig_input <<  ",     |               ";
}

void Ec_slave_2::transfer_rx_pdo()
{
}

void Ec_slave_2::process_tx_pdo()
{
}

void Ec_slave_2::process_rx_pdo()
{
}

void Ec_slave_2::config_data_transfer()
{
}

void Ec_slave_2::publish_data()
{
}

void Ec_slave_2::subscribe_data()
{
}
