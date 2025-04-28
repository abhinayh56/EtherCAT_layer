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
    uint16_t return_status = Ec_callback_status::SUCCESS;

    sc = ecrt_master_slave_config(master, slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code);

    if (sc)
    {
        return_status |= Ec_callback_status::SUCCESS;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Slave configuration fetch successful", 1);
    }
    else
    {
        return_status |= Ec_callback_status::FAILURE;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to fetch slave configuration", 1);
    }

    int32_t slave_config_pdo = ecrt_slave_config_pdos(sc, EC_END, slave_info.slave_syncs);
    if (slave_config_pdo == 0)
    {
        return_status |= Ec_callback_status::SUCCESS;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "Slave sync manager configuration successful", 1);
    }
    else
    {
        return_status |= Ec_callback_status::FAILURE;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "Failed to configure slave sync manager", 1);
    }

    return return_status;
}

uint16_t Ec_slave_base::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::register_pdo_to_domain(ec_domain_t *domain_i)
{
    uint16_t return_status = Ec_callback_status::SUCCESS;

    if (ecrt_domain_reg_pdo_entry_list(domain_i, domain_i_regs))
    {
        return_status |= Ec_callback_status::FAILURE;
        LOG_CONSOLE_SOURCE_ERROR(slave_ns, "PDO entry registration failed", 1);
    }
    else
    {
        return_status |= Ec_callback_status::SUCCESS;
        LOG_CONSOLE_SOURCE_INFO(slave_ns, "PDO entry registration successful", 1);
    }

    return return_status;
}

uint16_t Ec_slave_base::set_domain(uint8_t *domain_i_pd_)
{
    domain_i_pd = domain_i_pd_;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base::monitor_status()
{
    uint16_t return_status = Ec_callback_status::SUCCESS;

    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc, &s);

    if (s.al_state != sc_state.al_state)
    {
        printf("AnaIn: State 0x%02X.\n", s.al_state);
    }
    if (s.online != sc_state.online)
    {
        printf("AnaIn: %s.\n", s.online ? "online" : "offline");
    }
    if (s.operational != sc_state.operational)
    {
        printf("AnaIn: %soperational.\n", s.operational ? "" : "Not ");
    }

    sc_state = s;

    return return_status;
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
