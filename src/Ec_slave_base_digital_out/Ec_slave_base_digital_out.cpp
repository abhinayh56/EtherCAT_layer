#include "Ec_slave_base_digital_out.h"

Ec_slave_base_digital_out::Ec_slave_base_digital_out()
{
}

Ec_slave_base_digital_out::~Ec_slave_base_digital_out()
{
}

uint16_t Ec_slave_base_digital_out::set_info()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::monitor_status()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_digital_out::main_process()
{
    return Ec_callback_status::SUCCESS;
}
