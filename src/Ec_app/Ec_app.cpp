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

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Requesting master for realtime operation...", 1);

    master = ecrt_request_master(0);
    if (master)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master realtime operation started", 1);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master started successfully", 1);
        ret_val |= Ec_callback_status::SUCCESS;
    }
    else
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Master realtime operation failed", 1);
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Master failed to start", 1);
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to create instance of master", 1);
        ret_val |= Ec_callback_status::FAILURE;
    }

    return ret_val;
}

uint16_t Ec_app::stop()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Executing reset function of all slaves...", 1);
    ret_val |= reset();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to execute reset function of all slaves", 1);
    }
    else
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Reset function of all slaves executed successfully", 1);
    }

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Stopping app...", 1);
    ecrt_release_master(master);
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Master released", 1);
    LOG_CONSOLE_SOURCE_INFO(master_ns, "App stopped", 1);

    return ret_val;
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

    ret_val = set_domain();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to set domain to slaves", 1);
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

    uint16_t ret_val_monitor = Ec_callback_status::SUCCESS;

    ret_val_monitor |= monitor_master_status();
    if (ret_val_monitor == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor master status failed", 1);
    }

    ret_val_monitor |= monitor_slave_status();
    if (ret_val_monitor == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor slave status failed", 1);
    }

    ret_val |= ret_val_monitor;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Executing init function of all slaves...", 1);
    ret_val |= init();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to execute init function of all slaves", 1);
    }
    else
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Init function of all slaves executed successfully", 1);
    }

    return ret_val;
}

uint16_t Ec_app::cyclic_task()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    // 1. Fetches received frames from the hardware and processes the datagrams
    if (ecrt_master_receive(master) != 0)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to receive frame from hardware", 1);
        ret_val |= Ec_callback_status::FAILURE;
        return ret_val;
    }

    // 2. Determines the states of the domain's datagrams
    if (ecrt_domain_process(domain_i) != 0)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to return result of last process data exchange", 1);
        ret_val |= Ec_callback_status::FAILURE;
        return ret_val;
    }

    uint16_t ret_val_monitor = Ec_callback_status::SUCCESS;

    ret_val_monitor |= monitor_master_status();
    if (ret_val_monitor == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor master status failed", 1);
    }

    ret_val_monitor |= monitor_slave_status();
    if (ret_val_monitor == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor master status failed", 1);
    }

    if (ret_val_monitor == Ec_callback_status::FAILURE)
    {
        return ret_val_monitor;
    }

    ret_val |= ret_val_monitor;

#ifdef CYCLIC_SLAVE_CALL_PARALLEL
    ret_val |= transfer_tx_pdo();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to transfer tx_pdo", 1);
        return ret_val;
    }

    ret_val |= process_tx_pdo();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to process tx_pdo", 1);
        return ret_val;
    }

    ret_val |= publish_data();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to publish data", 1);
        return ret_val;
    }

    ret_val |= subscribe_data();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to subscribe data", 1);
        return ret_val;
    }

    ret_val |= main_process();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to run main process", 1);
        return ret_val;
    }

    ret_val |= process_rx_pdo();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to process rx_pdo", 1);
        return ret_val;
    }

    ret_val |= transfer_rx_pdo();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to transfer rx_pdo", 1);
        return ret_val;
    }
#endif // CYCLIC_SLAVE_CALL_PARALLEL

#ifdef CYCLIC_SLAVE_CALL_SEQUENTIAL
    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->transfer_tx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to transfer tx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }

        ret_val |= slave_base_arr[i]->process_tx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to process tx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }

        ret_val |= slave_base_arr[i]->publish_data();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to publish data of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }

        ret_val |= slave_base_arr[i]->subscribe_data();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to subscribe data of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }

        ret_val |= slave_base_arr[i]->main_process();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to run main of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }

        ret_val |= slave_base_arr[i]->process_rx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to process rx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }

        ret_val |= slave_base_arr[i]->transfer_rx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to transfer rx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }
#endif // CYCLIC_SLAVE_CALL_SEQUENTIAL

    // 11. Send process data
    if (ecrt_domain_queue(domain_i) != 0)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to queue all domain datagrams in the master's datagram queue", 1);
        ret_val |= Ec_callback_status::FAILURE;
        return ret_val;
    }

    if (ecrt_master_send(master) != 0)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to put all datagrams into frames and / or pass them to the Ethernet device for sending", 1);
        ret_val |= Ec_callback_status::FAILURE;
        return ret_val;
    }

    ret_val |= monitor_domain_i_status();
    if (ret_val == Ec_callback_status::FAILURE)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor domain failed", 1);
        return ret_val;
    }

    return ret_val;
}

uint16_t Ec_app::get_num_slaves()
{
    return num_slaves;
}

uint16_t Ec_app::monitor_domain_i_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    ec_domain_state_t ds;

    if (ecrt_domain_state(domain_i, &ds) != 0)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to monitor process data exchange", 1);
        ret_val |= Ec_callback_status::FAILURE;
        return ret_val;
    }

    if (ds.working_counter != domain_i_state.working_counter)
    {
        printf("Domain1: WC %u.\n", ds.working_counter);
    }

    if (ds.wc_state != domain_i_state.wc_state)
    {
        printf("Domain1: State %u.\n", ds.wc_state);
    }

    if (ds.redundancy_active != domain_i_state.redundancy_active)
    {
        printf("Domain1: Redundancy %u.\n", ds.redundancy_active);
    }

    if (ds.wc_state == EC_WC_ZERO)
    {
        LOG_CONSOLE_SOURCE_WARNING(master_ns, "No registered process data were exchanged", 1);
    }
    else if (ds.wc_state == EC_WC_INCOMPLETE)
    {
        LOG_CONSOLE_SOURCE_WARNING(master_ns, "Some of the registered process data were exchanged", 1);
    }
    // else if (ds.wc_state == EC_WC_COMPLETE)
    // {
    //     LOG_CONSOLE_SOURCE_INFO(master_ns, "All registered process data were exchanged", 1);
    // }

    if (ds.wc_state != EC_WC_COMPLETE)
    {
        process_data_exchange_complete = false;
        num_process_data_exchange_error++;
    }
    else
    {
        process_data_exchange_complete = true;
    }

    domain_i_state = ds;

    return ret_val;
}

uint16_t Ec_app::monitor_master_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    ec_master_state_t ms;
    if (ecrt_master_state(master, &ms) != 0)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to monitor master state", 1);
        ret_val |= Ec_callback_status::FAILURE;
        return ret_val;
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
        }
    }

    if (!ms.link_up)
    {
        ret_val |= Ec_callback_status::FAILURE;
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "Link is down", 1);
        return ret_val;
    }

    if (ms.slaves_responding != master_state.slaves_responding)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Slaves responding: ", 0);
        LOG_CONSOLE(ms.slaves_responding, 1);
    }

    if (ms.slaves_responding < num_slaves)
    {
        LOG_CONSOLE_SOURCE_ERROR(master_ns, "All slaves not responding", 1);
        ret_val |= Ec_callback_status::FAILURE;
        return ret_val;
    }

    if (ms.al_states != master_state.al_states)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "AL state: ", 0);
        LOG_CONSOLE(ms.al_states, 1);
    }

    master_state = ms;

    return ret_val;
}

bool Ec_app::is_link_up()
{
    if (master_state.link_up)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint32_t Ec_app::num_slaves_responding()
{
    return master_state.slaves_responding;
}

uint16_t Ec_app::monitor_slave_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;
    all_slaves_operational = true;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->monitor_status();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Monitor slave failed for slave number ", 0);
            LOG_CONSOLE(slave_base_arr[i]->get_slave_address(), 1)
            return ret_val;
        }

        all_slaves_operational = (all_slaves_operational && slave_base_arr[i]->is_operational());
        if (all_slaves_operational == false)
        {
            LOG_CONSOLE_SOURCE_WARNING(master_ns, "All slave not operational. Slave address: ", 0);
            LOG_CONSOLE(slave_base_arr[i]->get_slave_address(), 1);
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
        ret_val |= slave_base_arr[i]->set_pdo();
        // LOG_CONSOLE_SOURCE_INFO(master_ns, "Pdo list is set", 1);
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Registering tx,rx_pdos to domain", 1);
        // ret_val |= slave_base_arr[i]->register_pdo_to_domain(domain_i);
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Registered all pdos", 1);

    return ret_val;
}

uint16_t Ec_app::activate()
{
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
        ret_val |= slave_base_arr[i]->set_domain_ptr(domain_i_pd);
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting domain process data address to slaves successful", 1);

    return ret_val;
}

uint16_t Ec_app::set_domain()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting domain to slaves...", 1);
    for (int i = 0; i < num_slaves; i++)
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Providing domain to slave ", 0);
        LOG_CONSOLE(i + 1, 0);
        LOG_CONSOLE(" of ", 0);
        LOG_CONSOLE(num_slaves, 1);
        ret_val |= slave_base_arr[i]->set_domain(domain_i);
    }
    LOG_CONSOLE_SOURCE_INFO(master_ns, "Setting domain to slaves successful", 1);

    return ret_val;
}

uint16_t Ec_app::transfer_tx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->transfer_tx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to transfer tx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::process_tx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->process_tx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to process tx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::publish_data()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->publish_data();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to publish data of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::subscribe_data()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->subscribe_data();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to subscribe data of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::main_process()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->main_process();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to run main of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::process_rx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->process_rx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to process rx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::transfer_rx_pdo()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->transfer_rx_pdo();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to transfer rx_pdo of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::reset()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->reset();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to execute reset function of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}

uint16_t Ec_app::init()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    for (int i = 0; i < num_slaves; i++)
    {
        ret_val |= slave_base_arr[i]->init();
        if (ret_val == Ec_callback_status::FAILURE)
        {
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to execute initialization function of slave address ", 0);
            LOG_CONSOLE(i + 1, 1);
            return ret_val;
        }
    }

    return ret_val;
}
