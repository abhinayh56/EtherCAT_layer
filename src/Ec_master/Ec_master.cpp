#include "Ec_master.h"

Ec_master::Ec_master()
{
}

Ec_master::~Ec_master()
{
}

void Ec_master::add_slave(Ec_slave_base *new_slave)
{
}

int Ec_master::start()
{
    master = ecrt_request_master(0);
    if (!master)
    {
        return -1;
    }
    else
    {
        std::cout << "Master handle: " << master << std::endl;
        return 0;
    }
}

bool Ec_master::stop()
{
    return true;
}

void Ec_master::config()
{
}

void Ec_master::cyclic_task()
{
}

bool Ec_master::is_running()
{
    return run;
}

void Ec_master::config_slaves_data_transfer()
{
}

bool Ec_master::create_domain()
{
    return true;
}

void Ec_master::config_slaves()
{
}

void Ec_master::register_slaves_pdo_to_domain()
{
}

bool Ec_master::activate()
{
    return true;
}

bool Ec_master::get_domain_process_data()
{
    return true;
}

void Ec_master::set_domain_process_data()
{
}

void Ec_master::monitor_status()
{
}

void Ec_master::transfer_tx_pdo()
{
}

void Ec_master::process_tx_pdo()
{
}

void Ec_master::publish_data()
{
}

void Ec_master::subscribe_data()
{
}

void Ec_master::process_rx_pdo()
{
}

void Ec_master::transfer_rx_pdo()
{
}
