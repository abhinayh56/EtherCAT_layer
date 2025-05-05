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

uint16_t Ec_slave_base::set_info_from_eni()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::config_slave(ec_master_t *master)
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    sc = ecrt_master_slave_config(master, slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code);

    if (sc)
    {
        ret_val |= Ec_callback_status::SUCCESS;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Slave configuration fetch successful", 1);
    }
    else
    {
        ret_val |= Ec_callback_status::FAILURE;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to fetch slave configuration", 1);
    }

    int32_t slave_config_pdo = ecrt_slave_config_pdos(sc, EC_END, slave_info.slave_syncs);
    if (slave_config_pdo == 0)
    {
        ret_val |= Ec_callback_status::SUCCESS;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Slave sync manager configuration successful", 1);
    }
    else
    {
        ret_val |= Ec_callback_status::FAILURE;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to configure slave sync manager", 1);
    }

    return ret_val;
}

uint16_t Ec_slave_base::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::register_pdo_to_domain(ec_domain_t *domain_i)
{
    if (ecrt_domain_reg_pdo_entry_list(domain_i, domain_i_regs))
    {
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "PDO entry registration failed for slave address ", 0);
        LOG_CONSOLE(slave_address, 1);
        return Ec_callback_status::FAILURE;
    }
    else
    {
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "PDO entry registration successful for slave address ", 0);
        LOG_CONSOLE(slave_address, 1);
        return Ec_callback_status::SUCCESS;
    }
}

uint16_t Ec_slave_base::set_domain(uint8_t *domain_i_pd_)
{
    domain_i_pd = domain_i_pd_;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::monitor_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    ec_slave_config_state_t s;

    if (ecrt_slave_config_state(sc, &s) != 0)
    {
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to monitor slave state of address", 0);
        LOG_CONSOLE(slave_address, 1);
        return Ec_callback_status::FAILURE;
    }

    if (s.online != sc_state.online)
    {
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Online status: ", 0);
        if (s.online)
        {
            LOG_CONSOLE("online", 1);
        }
        else
        {
            LOG_CONSOLE("offline", 1);
        }
    }

    if (!s.online)
    {
        ret_val |= Ec_callback_status::FAILURE;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Slave is offline. Slave address is ", 0);
        LOG_CONSOLE(slave_address, 1);
    }

    if (s.al_state != sc_state.al_state)
    {
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "AL status: ", 0);

        if (s.al_state == 1)
        {
            LOG_CONSOLE("INIT", 1);
        }
        else if (s.al_state == 2)
        {
            LOG_CONSOLE("PREOP", 1);
        }
        else if (s.al_state == 4)
        {
            LOG_CONSOLE("SAFEOP", 1);
        }
        else if (s.al_state == 8)
        {
            LOG_CONSOLE("OP", 1);
        }
        else
        {
            LOG_CONSOLE("UNKNOWN", 1);
        }
    }

    if (s.operational != sc_state.operational)
    {
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Operational status: ", 0);
        if (s.operational)
        {
            // ret_val |= Ec_callback_status::SUCCESS;
            LOG_CONSOLE("true", 1);
        }
        else
        {
            // ret_val |= Ec_callback_status::FAILURE;
            LOG_CONSOLE("false", 1);
        }
    }

    sc_state = s;

    return ret_val;
}

bool Ec_slave_base::is_operational()
{
    if (sc_state.operational == 1)
    {
        return true;
    }
    else
    {
        return true;
    }
}

uint16_t Ec_slave_base::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::main_process()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::reset()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::init()
{
    return Ec_callback_status::SUCCESS;
}
