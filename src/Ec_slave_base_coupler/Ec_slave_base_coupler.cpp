#include "Ec_slave_base_coupler.h"

Ec_slave_base_coupler::Ec_slave_base_coupler()
{
}

Ec_slave_base_coupler::~Ec_slave_base_coupler()
{
}

uint16_t Ec_slave_base_coupler::set_info()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::monitor_status()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_coupler::main_process()
{
    return Ec_callback_status::SUCCESS;
}
