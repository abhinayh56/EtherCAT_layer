#include "Ec_slave_el_2008.h"

Ec_slave_el_2008::Ec_slave_el_2008(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_el_2008::~Ec_slave_el_2008()
{
}

void Ec_slave_el_2008::set_info()
{
    slave_info.alias = alias;
    slave_info.position = slave_address;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_1_pdo_entries;
    slave_info.slave_pdos = slave_1_pdos;
    slave_info.slave_syncs = slave_1_syncs;
}

void Ec_slave_el_2008::set_pdo()
{
    domain_i_regs = domain_regs;
}

void Ec_slave_el_2008::monitor_status()
{
}

void Ec_slave_el_2008::transfer_tx_pdo()
{
}

void Ec_slave_el_2008::transfer_rx_pdo()
{
    time_stamp += 2;
    if (time_stamp >= 2000)
    {
        time_stamp = 0;
    }

    if (time_stamp <= 1000)
    {
        // led on
        EC_WRITE_U8(domain_i_pd + off_1, 0xAA);
    }
    else
    {
        // led off
        EC_WRITE_U8(domain_i_pd + off_1, 0x55);
    }
}

void Ec_slave_el_2008::process_tx_pdo()
{
}

void Ec_slave_el_2008::process_rx_pdo()
{
}

void Ec_slave_el_2008::config_data_transfer()
{
}

void Ec_slave_el_2008::publish_data()
{
}

void Ec_slave_el_2008::subscribe_data()
{
}

void Ec_slave_el_2008::main_process()
{
}
