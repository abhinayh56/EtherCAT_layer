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
    LOG_CONSOLE_INFO("Total number of slaves assigned to master: ", 0);
    LOG_CONSOLE(num_slaves, 1);
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
    LOG_CONSOLE_INFO("Stopping master...", 1);
    if (run)
    {
        ecrt_release_master(master);
    }
    LOG_CONSOLE_INFO("Master stopped", 1);
    run = false;
    return true;
}

void Ec_master::config()
{
    LOG_CONSOLE_INFO("Configuring all slaves starts...", 1);
    config_slaves_data_transfer();
    create_domain();
    set_slave_info();
    config_slaves();
    register_slaves_pdo_to_domain();
    activate();
    get_domain_process_data();
    set_domain_process_data();
    LOG_CONSOLE_INFO("Configurating all slaves done", 1);

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
        main_process();
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
            slave_base_arr[i]->main_process();
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
    LOG_CONSOLE_INFO("Configuring data transfer of slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_INFO("Configuring data transfer of slave ", 0);
        LOG_CONSOLE(i, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->config_data_transfer();
    }
    LOG_CONSOLE_INFO("Configured data transfer of all slave ", 1);
}

bool Ec_master::create_domain()
{
    LOG_CONSOLE_INFO("Creating domain...", 1);
    domain_i = ecrt_master_create_domain(master);
    if (domain_i)
    {
        LOG_CONSOLE_INFO("Domain creation successful", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_ERROR("Domain creation failed", 1);
        return false;
    }
}

void Ec_master::set_slave_info()
{
    LOG_CONSOLE_INFO("Setting slaves info...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_INFO("Setting slave info ", 0);
        LOG_CONSOLE(i, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->set_info();
    }
    LOG_CONSOLE_INFO("Configured all slaves", 1);
}

void Ec_master::config_slaves()
{
    LOG_CONSOLE_INFO("Configuring slave---", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_INFO("Configuring slave ", 0);
        LOG_CONSOLE(i, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->config_slave(master);
    }
    LOG_CONSOLE_INFO("Configured slaves---", 1);
}

void Ec_master::register_slaves_pdo_to_domain()
{
    LOG_CONSOLE_INFO("Registering pdos", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_INFO("Registering pdos for slave ", 0);
        LOG_CONSOLE(i, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        LOG_CONSOLE_INFO("Setting slave pdos", 1);
        slave_base_arr[i]->set_pdo();
        LOG_CONSOLE_INFO("Pdo list is set", 1);
        LOG_CONSOLE_INFO("Registering tx,rx_pdos to domain", 1);
        slave_base_arr[i]->register_pdo_to_domain(domain_i);
    }
    LOG_CONSOLE_INFO("Registered all pdos", 1);
}

bool Ec_master::activate()
{
    LOG_CONSOLE_INFO("Activating master...", 1);
    if (!ecrt_master_activate(master))
    {
        LOG_CONSOLE_INFO("Master activated successfully", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_ERROR("Failed to activate master", 1);
        return false;
    }
}

bool Ec_master::get_domain_process_data()
{
    LOG_CONSOLE_INFO("Getting pointer to domain process data...", 1);
    domain_i_pd = ecrt_domain_data(domain_i);
    if (domain_i_pd)
    {
        LOG_CONSOLE_INFO("Domain process data pointer get successful", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_ERROR("Failed to get domain process data pointer", 1);
        return false;
    }
}

void Ec_master::set_domain_process_data()
{
    LOG_CONSOLE_INFO("Providing pointer to domain process data...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_INFO("Providing pointer to domain process data to slave ", 0);
        LOG_CONSOLE(i, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->set_domain(domain_i_pd);
    }
}

void Ec_master::monitor_status()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->monitor_status();
    }
}

void Ec_master::transfer_tx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->transfer_tx_pdo();
    }
}

void Ec_master::process_tx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->process_tx_pdo();
    }
}

void Ec_master::publish_data()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->publish_data();
    }
}

void Ec_master::subscribe_data()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->subscribe_data();
    }
}

void Ec_master::main_process()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->main_process();
    }
}

void Ec_master::process_rx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->process_rx_pdo();
    }
}

void Ec_master::transfer_rx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->transfer_rx_pdo();
    }
}
