#include "Ec_slave_base_analog_in.h"

Ec_slave_base_analog_in::Ec_slave_base_analog_in()
{
}

Ec_slave_base_analog_in::~Ec_slave_base_analog_in()
{
}

uint16_t Ec_slave_base_analog_in::set_info()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::monitor_status()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_analog_in::main_process()
{
    return Ec_callback_status::SUCCESS;
}
