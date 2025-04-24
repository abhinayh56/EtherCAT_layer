#include "Ec_slave_base_junction.h"

Ec_slave_base_junction::Ec_slave_base_junction()
{
}

Ec_slave_base_junction::~Ec_slave_base_junction()
{
}

uint16_t Ec_slave_base_junction::set_info()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::monitor_status()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_junction::main_process()
{
    return Ec_callback_status::SUCCESS;
}
