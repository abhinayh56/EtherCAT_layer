#include "Ec_app.h"

Ec_app::Ec_app(const std::string &master_ns_)
{
    master_ns = master_ns_;
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Using EtherCAT master IGH v", 0);
    LOG_CONSOLE(ECRT_VER_MAJOR, 0);
    LOG_CONSOLE(".", 0);
    LOG_CONSOLE(ECRT_VER_MINOR, 1);

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Object of master created", 1);
}

Ec_app::~Ec_app()
{
    stop();
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Object of master destroyed", 1);
}

void Ec_app::add_slave(Ec_slave_base *new_slave)
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Assigning new slave to master", 1);
    slave_base_arr.push_back(new_slave);
    num_slaves = slave_base_arr.size();
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Total number of slaves assigned to master: ", 0);
    LOG_CONSOLE(num_slaves, 1);
}

bool Ec_app::start()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Starting master ...", 1);

    int result = system("sudo /etc/init.d/ethercat start");
    if (result == 0)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master started", 1);
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to start master", 1);
    }

    return true;
}

bool Ec_app::restart()
{
    stop();
    start();

    return true;
}

bool Ec_app::deactivate()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Stopping master...", 1);
    if (run)
    {
        ecrt_release_master(master);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master released", 1);
    }

    if (ecrt_master_deactivate(master) == 0)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master deactivated", 1);
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to deactivate master", 1);
    }

    run = false;

    return true;
}

bool Ec_app::stop()
{
    deactivate();

    int result = system("sudo /etc/init.d/ethercat stop");
    if (result == 0)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master stopped", 1);
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to stop master", 1);
    }

    return true;
}

bool Ec_app::create_instance()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Requesting master for realtime operation...", 1);

    master = ecrt_request_master(0);
    if (master)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master realtime operation started", 1);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master started successfully", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master realtime operation failed", 1);
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Master failed to start", 1);
        return false;
    }
}

void Ec_app::config()
{
    create_instance();
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring slaves ...", 1);
    config_slaves_data_transfer();
    create_domain();
    set_slave_info();
    config_slaves();
    register_slaves_pdo_to_domain();
    activate();
    get_domain_process_data();
    set_domain_process_data();
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Slave configuration completed successfully", 1);
    monitor();

    run = true;
}

void Ec_app::cyclic_task()
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

bool Ec_app::is_running()
{
    return run;
}

uint16_t Ec_app::get_num_slaves()
{
    return num_slaves;
}

void Ec_app::monitor()
{
    if (ecrt_master_state(master, &master_state) == 0)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master state read successfully", 1);

        LOG_CONSOLE_SOURCE_INFO(master_ns, "Number of slaves responding: ", 0);
        LOG_CONSOLE(master_state.slaves_responding, 1);

        LOG_CONSOLE_SOURCE_INFO(master_ns, "AL states (at least one slave): ", 0);
        if (master_state.al_states == 0)
        {
            LOG_CONSOLE("INIT", 1);
        }
        if (master_state.al_states == 1)
        {
            LOG_CONSOLE("PREOP", 1);
        }
        if (master_state.al_states == 2)
        {
            LOG_CONSOLE("SAFEOP", 1);
        }
        if (master_state.al_states == 3)
        {
            LOG_CONSOLE("OP", 1);
        }

        LOG_CONSOLE_SOURCE_INFO(master_ns, "Link up status: ", 0);
        LOG_CONSOLE(master_state.link_up, 1);
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to read master state", 1);
    }
}

void Ec_app::config_slaves_data_transfer()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring data transfer of slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring data transfer of slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->config_data_transfer();
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configured data transfer of all slave ", 1);
}

bool Ec_app::create_domain()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Creating domain...", 1);
    domain_i = ecrt_master_create_domain(master);
    if (domain_i)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Domain creation successful", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Domain creation failed", 1);
        return false;
    }
}

void Ec_app::set_slave_info()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting slaves info...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting info of slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->set_info();
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Info of all slaves set", 1);
}

void Ec_app::config_slaves()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->config_slave(master);
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configured all slaves", 1);
}

void Ec_app::register_slaves_pdo_to_domain()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Registering pdo of slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Registering pdo for slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting slave pdos", 1);
        slave_base_arr[i]->set_pdo();
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Pdo list is set", 1);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Registering tx,rx_pdos to domain", 1);
        slave_base_arr[i]->register_pdo_to_domain(domain_i);
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Registered all pdos", 1);
}

bool Ec_app::activate()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Activating master...", 1);
    if (!ecrt_master_activate(master))
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master activation successful", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to activate master", 1);
        return false;
    }
}

bool Ec_app::get_domain_process_data()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Getting domain process data address ...", 1);
    domain_i_pd = ecrt_domain_data(domain_i);
    if (domain_i_pd)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Domain process data address fetch successful", 1);
        return true;
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to get domain process data address", 1);
        return false;
    }
}

void Ec_app::set_domain_process_data()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting domain process data address to slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Providing domain process data address to slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        slave_base_arr[i]->set_domain(domain_i_pd);
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting domain process data address to slaves successful", 1);
}

void Ec_app::monitor_status()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->monitor_status();
    }
}

void Ec_app::transfer_tx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->transfer_tx_pdo();
    }
}

void Ec_app::process_tx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->process_tx_pdo();
    }
}

void Ec_app::publish_data()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->publish_data();
    }
}

void Ec_app::subscribe_data()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->subscribe_data();
    }
}

void Ec_app::main_process()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->main_process();
    }
}

void Ec_app::process_rx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->process_rx_pdo();
    }
}

void Ec_app::transfer_rx_pdo()
{
    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->transfer_rx_pdo();
    }
}
