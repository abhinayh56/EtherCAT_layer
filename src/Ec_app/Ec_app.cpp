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
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Object of master destroyed", 1);
}

uint16_t Ec_app::add_slave(Ec_slave_base *new_slave)
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Assigning new slave to master", 1);
    slave_base_arr.push_back(new_slave);
    num_slaves = slave_base_arr.size();
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Total number of slaves assigned to master: ", 0);
    LOG_CONSOLE(num_slaves, 1);

    return ret_val;
}

uint16_t Ec_app::start()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    ret_val |= create_instance();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to create instance of master", 1);
    }

    return ret_val;
}

uint16_t Ec_app::stop()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Stopping master...", 1);
    ecrt_release_master(master);
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Master released", 1);

    return ret_val;
}

uint16_t Ec_app::create_instance()
{
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Requesting master for realtime operation...", 1);

    master = ecrt_request_master(0);
    if (master)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master realtime operation started", 1);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master started successfully", 1);
        return Ec_callback_status::SUCCESS;
    }
    else
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master realtime operation failed", 1);
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Master failed to start", 1);
        return Ec_callback_status::FAILURE;
    }
}

uint16_t Ec_app::config()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring slaves ...", 1);

    ret_val |= config_slaves_data_transfer();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to configure slaves data transfer", 1);
        return ret_val;
    }

    ret_val |= set_slaves_info_from_eni();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to set slaves info from eni", 1);
        return ret_val;
    }

    ret_val |= create_domain();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to create domain", 1);
        return ret_val;
    }

    ret_val |= config_slaves();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to configure slaves", 1);
        return ret_val;
    }

    ret_val |= register_slaves_pdo_to_domain();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to register slaves pdo to domain", 1);
        return ret_val;
    }

    ret_val |= activate();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to activate master", 1);
        return ret_val;
    }

    ret_val |= get_domain_process_data();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to get domain process data", 1);
        return ret_val;
    }

    ret_val |= set_domain_process_data();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to set domain process data", 1);
        return ret_val;
    }

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Slave configuration completed successfully", 1);

    ret_val |= monitor_master_status();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor master status failed", 1);
        return ret_val;
    }

    ret_val |= monitor_slave_status();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor slave status failed", 1);
        return ret_val;
    }

    return ret_val;
}

uint16_t Ec_app::cyclic_task()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    // 1. Fetches received frames from the hardware and processes the datagrams
    ecrt_master_receive(master);

    // 2. Determines the states of the domain's datagrams
    ecrt_domain_process(domain_i);

    ret_val |= monitor_master_status();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor master status failed", 1);
        return ret_val;
    }

#ifdef CYCLIC_SLAVE_CALL_PARALLEL
    ret_val |= monitor_slave_status();
    ret_val |= transfer_tx_pdo();
    ret_val |= process_tx_pdo();
    ret_val |= publish_data();
    ret_val |= subscribe_data();
    ret_val |= main_process();
    ret_val |= process_rx_pdo();
    ret_val |= transfer_rx_pdo();
#endif // CYCLIC_SLAVE_CALL_PARALLEL

#ifdef CYCLIC_SLAVE_CALL_SEQUENTIAL
    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->monitor_status();
        ret_val |= slave_base_arr[i]->transfer_tx_pdo();
        ret_val |= slave_base_arr[i]->process_tx_pdo();
        ret_val |= slave_base_arr[i]->publish_data();
        ret_val |= slave_base_arr[i]->subscribe_data();
        ret_val |= slave_base_arr[i]->main_process();
        ret_val |= slave_base_arr[i]->process_rx_pdo();
        ret_val |= slave_base_arr[i]->transfer_rx_pdo();
    }
#endif // CYCLIC_SLAVE_CALL_SEQUENTIAL

    // 11. Send process data
    ecrt_domain_queue(domain_i);
    ecrt_master_send(master);

    ret_val |= monitor_domain_i_status();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor domain failed", 1);
        return ret_val;
    }

    return ret_val;
}

uint16_t Ec_app::get_running_status()
{
    return run_status;
}

void Ec_app::set_running_status(uint16_t run_status_)
{
    run_status = run_status_;
}

uint16_t Ec_app::get_num_slaves()
{
    return num_slaves;
}

uint16_t Ec_app::monitor_domain_i_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    ec_domain_state_t ds;

    ecrt_domain_state(domain_i, &ds);

    // if (ds.working_counter != domain_i_state.working_counter)
    // {
    //     printf("Domain1: WC %u.\n", ds.working_counter);
    // }
    // if (ds.wc_state != domain_i_state.wc_state)
    // {
    //     printf("Domain1: State %u.\n", ds.wc_state);
    // }

    domain_i_state = ds;

    return ret_val;
}

uint16_t Ec_app::monitor_master_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    ec_master_state_t ms;
    ecrt_master_state(master, &ms);

    if (ms.slaves_responding != master_state.slaves_responding)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Slaves responding: ", 0);
        LOG_CONSOLE(ms.slaves_responding, 1);

        if ((ms.slaves_responding >= num_slaves) || (ms.slaves_responding == 0))
        {
            ret_val |= Ec_callback_status::SUCCESS;
        }
        else
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "All slaves not responding", 1);
            ret_val |= Ec_callback_status::FAILURE;
            return ret_val;
        }
    }

    if (ms.al_states != master_state.al_states)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "AL state: ", 0);
        LOG_CONSOLE(ms.al_states, 1);
    }

    if (ms.link_up != master_state.link_up)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Link up status: ", 0);
        if (ms.link_up)
        {
            LOG_CONSOLE("up", 1);
        }
        else
        {
            LOG_CONSOLE("down", 1);
            ret_val |= Ec_callback_status::FAILURE;
            return ret_val;
        }
    }

    master_state = ms;

    return ret_val;
}

uint16_t Ec_app::monitor_slave_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->monitor_status();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor slave failed for slave number ", 0);
            LOG_CONSOLE(slave_base_arr[i]->get_slave_address(), 1)
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::config_slaves_data_transfer()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

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
    return ret_val;
}

uint16_t Ec_app::create_domain()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Creating domain...", 1);
    domain_i = ecrt_master_create_domain(master);
    if (domain_i)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Domain creation successful", 1);
        return Ec_callback_status::SUCCESS;
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Domain creation failed", 1);
        return Ec_callback_status::FAILURE;
    }
}

uint16_t Ec_app::set_slaves_info_from_eni()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting slaves info...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting info of slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        ret_val |= slave_base_arr[i]->set_info_from_eni();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to set info from eni for slave number ", 0);
            LOG_CONSOLE(i + 1, 0);
            LOG_CONSOLE(", ", 0);
            LOG_CONSOLE(slave_base_arr[i]->get_slave_address(), 1);
            return ret_val;
        }
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Info of all slaves set", 1);

    return ret_val;
}

uint16_t Ec_app::config_slaves()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Configuring slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        ret_val |= slave_base_arr[i]->config_slave(master);
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to configure slave", 1);
            return ret_val;
        }
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Configured all slaves", 1);

    return ret_val;
}

uint16_t Ec_app::register_slaves_pdo_to_domain()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Registering pdo of slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Registering pdo for slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        // LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting slave pdos", 1);
        slave_base_arr[i]->set_pdo();
        // LOG_CONSOLE_SOURCE_INFO(master_ns, "Pdo list is set", 1);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Registering tx,rx_pdos to domain", 1);
        slave_base_arr[i]->register_pdo_to_domain(domain_i);
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Registered all pdos", 1);

    return ret_val;
}

uint16_t Ec_app::activate()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Activating master...", 1);
    if (!ecrt_master_activate(master))
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master activation successful", 1);
        return Ec_callback_status::SUCCESS;
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to activate master", 1);
        return Ec_callback_status::FAILURE;
    }
}

uint16_t Ec_app::get_domain_process_data()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Getting domain process data address ...", 1);
    domain_i_pd = ecrt_domain_data(domain_i);
    if (domain_i_pd)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Domain process data address fetch successful", 1);
        return Ec_callback_status::SUCCESS;
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to get domain process data address", 1);
        return Ec_callback_status::FAILURE;
    }
}

uint16_t Ec_app::set_domain_process_data()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

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

    return ret_val;
}

uint16_t Ec_app::transfer_tx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->transfer_tx_pdo();
    }

    return ret_val;
}

uint16_t Ec_app::process_tx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->process_tx_pdo();
    }

    return ret_val;
}

uint16_t Ec_app::publish_data()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->publish_data();
    }

    return ret_val;
}

uint16_t Ec_app::subscribe_data()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->subscribe_data();
    }

    return ret_val;
}

uint16_t Ec_app::main_process()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->main_process();
    }

    return ret_val;
}

uint16_t Ec_app::process_rx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->process_rx_pdo();
    }

    return ret_val;
}

uint16_t Ec_app::transfer_rx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        slave_base_arr[i]->transfer_rx_pdo();
    }

    return ret_val;
}
