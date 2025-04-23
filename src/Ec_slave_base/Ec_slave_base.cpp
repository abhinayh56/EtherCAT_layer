#include "Ec_slave_base.h"

Ec_slave_base::Ec_slave_base()
{
}

Ec_slave_base::~Ec_slave_base()
{
}

void Ec_slave_base::set_slave_ns(const std::string &slave_ns_)
{
    slave_ns = slave_ns_;
}

const std::string &Ec_slave_base::get_slave_ns()
{
    return slave_ns;
}

void Ec_slave_base::set_slave_address(uint16_t slave_address_)
{
    slave_address = slave_address_;
}

uint16_t Ec_slave_base::get_slave_address()
{
    return slave_address;
}

void Ec_slave_base::set_info() {}

void Ec_slave_base::config_slave(ec_master_t *master)
{
    sc = ecrt_master_slave_config(master, slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code);

    if (sc)
    {
        slave_status.is_connected = true;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Slave configuration fetch successful", 1);
    }
    else
    {
        slave_status.is_connected = false;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to fetch slave configuration", 1);
    }

    int32_t slave_config_pdo = ecrt_slave_config_pdos(sc, EC_END, slave_info.slave_syncs);
    if (slave_config_pdo == 0)
    {
        slave_status.is_configured = true;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Slave sync manager configuration successful", 1);
    }
    else
    {
        slave_status.is_configured = false;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to configure slave sync manager", 1);
    }
}

void Ec_slave_base::set_pdo() {}

void Ec_slave_base::register_pdo_to_domain(ec_domain_t *domain_i)
{
    if (ecrt_domain_reg_pdo_entry_list(domain_i, domain_i_regs))
    {
        slave_status.is_pdo_registered = false;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "PDO entry registration failed", 1);
    }
    else
    {
        slave_status.is_pdo_registered = true;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "PDO entry registration successful", 1);
    }
}

void Ec_slave_base::set_domain(uint8_t *domain_i_pd_)
{
    domain_i_pd = domain_i_pd_;
}

void Ec_slave_base::monitor_status()
{
    if (ecrt_slave_config_state(sc, &sc_state) == 0)
    {
        slave_status.is_online = sc_state.online == 1;
        slave_status.is_operational = sc_state.operational == 1;

        slave_status.slave_state = sc_state.al_state;

        // std::cout << slave_ns;
        // if (slave_address <= 9)
        // {
        //     for (int i = slave_ns.length(); i <= 10; i++)
        //     {
        //         std::cout << " ";
        //     }
        // }
        // else if ((10 <= slave_address) && (slave_address <= 99))
        // {
        //     for (int i = slave_ns.length(); i <= 9; i++)
        //     {
        //         std::cout << " ";
        //     }
        // }
        // else
        // {
        //     for (int i = slave_ns.length(); i <= 8; i++)
        //     {
        //         std::cout << " ";
        //     }
        // }

        // std::cout << slave_address;

        // LOG_CONSOLE(" : Status -> online: ", 0);
        // LOG_CONSOLE(sc_state.online, 0);

        // LOG_CONSOLE(", operational: ", 0);
        // LOG_CONSOLE(sc_state.operational, 0);

        // LOG_CONSOLE(", al_state: ", 0);
        // if (sc_state.al_state == 0)
        // {
        //     LOG_CONSOLE("UNKNOWN", 1);
        // }
        // if (sc_state.al_state == 1)
        // {
        //     LOG_CONSOLE("INIT", 1);
        // }
        // if (sc_state.al_state == 2)
        // {
        //     LOG_CONSOLE("PREOP", 1);
        // }
        // if (sc_state.al_state == 4)
        // {
        //     LOG_CONSOLE("SAFEOP", 1);
        // }
        // if (sc_state.al_state == 8)
        // {
        //     LOG_CONSOLE("OP", 1);
        // }
    }
    else
    {
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to read slave configuration", 1);
    }
}

void Ec_slave_base::transfer_tx_pdo() {}

void Ec_slave_base::transfer_rx_pdo() {}

void Ec_slave_base::process_tx_pdo() {}

void Ec_slave_base::process_rx_pdo() {}

void Ec_slave_base::config_data_transfer() {}

void Ec_slave_base::publish_data() {}

void Ec_slave_base::subscribe_data() {}

void Ec_slave_base::main_process() {}
