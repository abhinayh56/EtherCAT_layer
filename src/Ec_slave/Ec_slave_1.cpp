#include "Ec_slave_1.h"

Ec_slave_1::Ec_slave_1(uint16_t slave_address_, const std::string &slave_name_)
{
    slave_address = slave_address_;
    slave_name = slave_name_;
}

Ec_slave_1::~Ec_slave_1()
{
}

void Ec_slave_1::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_1_pdo_entries;
    slave_info.slave_pdos = slave_1_pdos;
    slave_info.slave_syncs = slave_1_syncs;
}

void Ec_slave_1::set_pdo()
{
    domain_i_regs = domain_regs;
}

void Ec_slave_1::monitor_status()
{
}

void Ec_slave_1::transfer_tx_pdo()
{
}

void Ec_slave_1::transfer_rx_pdo()
{
    time_stamp += 4;
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

void Ec_slave_1::process_tx_pdo()
{
}

void Ec_slave_1::process_rx_pdo()
{
}

void Ec_slave_1::config_data_transfer()
{
}

void Ec_slave_1::publish_data()
{
}

void Ec_slave_1::subscribe_data()
{
}
