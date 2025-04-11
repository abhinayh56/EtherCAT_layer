#include "Ec_slave_base.h"

Ec_slave_base::Ec_slave_base()
{
}

Ec_slave_base::~Ec_slave_base()
{
}

void Ec_slave_base::set_slave_name(const std::string &slave_name_)
{
    slave_name = slave_name_;
}

const std::string &Ec_slave_base::get_slave_name()
{
    return slave_name;
}

void Ec_slave_base::set_slave_address(uint16_t slave_address_)
{
    slave_address = slave_address_;
}

uint16_t Ec_slave_base::get_slave_address()
{
    return slave_address;
}

void Ec_slave_base::config_slave(ec_master_t *master)
{
    if (!(sc = ecrt_master_slave_config(master, slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code)))
    {
        std::cout << "configuring failed for slaves " << std::endl;
    }
    else
    {
        std::cout << "configuring done for slaves " << std::endl;
    }

    if (ecrt_slave_config_pdos(sc, EC_END, slave_info.slave_syncs))
    {
        std::cout << "configuring pdo failed for slave " << std::endl;
    }
    else
    {
        std::cout << "configuring pdo done for slave " << std::endl;
    }
}

void Ec_slave_base::config_data_transfer()
{
}

void Ec_slave_base::publish_data()
{
}

void Ec_slave_base::subscribe_data()
{
}
