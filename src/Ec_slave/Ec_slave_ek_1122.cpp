#include "Ec_slave_ek_1122.h"

Ec_slave_ek_1122::Ec_slave_ek_1122(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_ek_1122::~Ec_slave_ek_1122()
{
}

void Ec_slave_ek_1122::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries;
    slave_info.slave_pdos;
    slave_info.slave_syncs = slave_2_syncs;
}

void Ec_slave_ek_1122::set_pdo()
{
    domain_i_regs = domain_regs;
}

void Ec_slave_ek_1122::monitor_status() {}

void Ec_slave_ek_1122::transfer_tx_pdo()
{
    time_stamp += 4;
    if (time_stamp >= 2000)
    {
        time_stamp = 0;
    }
}

void Ec_slave_ek_1122::transfer_rx_pdo()
{
}

void Ec_slave_ek_1122::process_tx_pdo()
{
}

void Ec_slave_ek_1122::process_rx_pdo()
{
}

void Ec_slave_ek_1122::config_data_transfer()
{
}

void Ec_slave_ek_1122::publish_data()
{
}

void Ec_slave_ek_1122::subscribe_data()
{
}

void Ec_slave_ek_1122::main_process()
{
}
