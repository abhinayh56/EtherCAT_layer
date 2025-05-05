#include "Ec_slave_base_rs232.h"

Ec_slave_base_rs232::Ec_slave_base_rs232()
{
}

Ec_slave_base_rs232::~Ec_slave_base_rs232()
{
}

uint16_t Ec_slave_base_rs232::set_info()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::monitor_status()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::main_process()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::reset()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_rs232::init()
{
    return Ec_callback_status::SUCCESS;
}
