#include "Ec_slave_el_1008.h"

Ec_slave_el_1008::Ec_slave_el_1008(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_el_1008::~Ec_slave_el_1008()
{
}

void Ec_slave_el_1008::set_info()
{
    slave_info.alias = alias;
    slave_info.position = slave_address;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_pdo_entries;
    slave_info.slave_pdos = slave_pdos;
    slave_info.slave_syncs = slave_syncs;
}

void Ec_slave_el_1008::set_pdo()
{
    domain_i_regs = domain_regs;
}

// void Ec_slave_el_1008::monitor_status() 
// {
// }

void Ec_slave_el_1008::transfer_tx_pdo()
{
    uint16_t dig_input = EC_READ_U8(domain_i_pd + off_1);
    // std::cout << "dig_input: " << dig_input <<  ",     |               ";
}

void Ec_slave_el_1008::transfer_rx_pdo()
{
}

void Ec_slave_el_1008::process_tx_pdo()
{
}

void Ec_slave_el_1008::process_rx_pdo()
{
}

void Ec_slave_el_1008::config_data_transfer()
{
}

void Ec_slave_el_1008::publish_data()
{
}

void Ec_slave_el_1008::subscribe_data()
{
}

void Ec_slave_el_1008::main_process()
{
}
