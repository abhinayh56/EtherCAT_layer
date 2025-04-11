#include "Ec_master.h"

Ec_master::Ec_master()
{
    LOG_CONSOLE_INFO("Object of master created", 1);
}

Ec_master::~Ec_master()
{
    LOG_CONSOLE_INFO("Object of master destroyed", 1);
    stop();
}

void Ec_master::add_slave(Ec_slave_base *new_slave)
{
    LOG_CONSOLE_INFO("Assigning new slave to master", 1);
    slave_base_arr.push_back(new_slave);
    num_slaves = slave_base_arr.size();
    LOG_CONSOLE_INFO("Total number of slaves assigned to master are ", 0);
    LOG_CONSOLE_INFO(num_slaves, 1);
}

bool Ec_master::start()
{
    LOG_CONSOLE_INFO("Creating master...", 1);

    master = ecrt_request_master(0);
    if (master)
    {
        LOG_CONSOLE_INFO("Master creation successful", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_ERROR("Master creation failed", 1);
        return false;
    }
}

bool Ec_master::stop()
{
    return true;
}

void Ec_master::config()
{
    LOG_CONSOLE_ERROR("Configuring all slaves starts...", 1);
    config_slaves_data_transfer();
    create_domain();
    config_slaves();
    register_slaves_pdo_to_domain();
    activate();
    get_domain_process_data();
    set_domain_process_data();
    LOG_CONSOLE_ERROR("Configurating all slaves done", 1);

    run = true;
}

void Ec_master::cyclic_task()
{
    if (run)
    {
        // 1. Fetches received frames from the hardware and processes the datagrams
        ecrt_master_receive(master);

        // 2. Determines the states of the domain's datagrams
        ecrt_domain_process(domain_i);

        // 3. Reads the state of a domain
        ecrt_domain_state(domain_i, &domain_i_state);

#ifdef CYCLIC_SLAVE_CALL_PARALLEL
        monitor_status();
        transfer_tx_pdo();
        process_tx_pdo();
        publish_data();
        subscribe_data();
        process_rx_pdo();
        transfer_rx_pdo();
#endif // CYCLIC_SLAVE_CALL_PARALLEL

#ifdef CYCLIC_SLAVE_CALL_SEQUENTIAL
        for (int i = 0; i < num_slaves; i++)
        {
            slave_base_arr[i]->monitor_status();
            slave_base_arr[i]->transfer_tx_pdo();
            slave_base_arr[i]->process_tx_pdo();
            slave_base_arr[i]->publish_data();
            slave_base_arr[i]->subscribe_data();
            slave_base_arr[i]->process_rx_pdo();
            slave_base_arr[i]->transfer_rx_pdo();
        }
#endif // CYCLIC_SLAVE_CALL_SEQUENTIAL

        // 11. Send process data
        ecrt_domain_queue(domain_i);
        ecrt_master_send(master);

        // 9. Check master state
        ecrt_master_state(master, &master_state);
    }
    else
    {
        stop();
    }
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
