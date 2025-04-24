#include "Ec_slave_ingenia.h"

Ec_slave_ingenia::Ec_slave_ingenia(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_ingenia::~Ec_slave_ingenia()
{
}

uint16_t Ec_slave_ingenia::set_info()
{
    slave_info.alias = alias;
    slave_info.position = slave_address;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_pdo_entries;
    slave_info.slave_pdos = slave_pdos;
    slave_info.slave_syncs = slave_syncs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::set_pdo()
{
    for (uint8_t i = 0; i < 9; i++)
    {
        domain_regs[i].position = slave_address;
    }
    domain_i_regs = domain_regs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::transfer_tx_pdo()
{
    status_word = EC_READ_U16(domain_i_pd + off_tx_pdo_1);
    position_actual_value = EC_READ_S32(domain_i_pd + off_tx_pdo_2);
    velocity_actual_value = EC_READ_S32(domain_i_pd + off_tx_pdo_3);
    mode_of_operation_display = EC_READ_U8(domain_i_pd + off_tx_pdo_4);

    check_status();

    // std::cout << "INGENIA_TXPDO: " << slave_ns << " | " << status_word << ", " << position_actual_value << ", " << velocity_actual_value << ", " << uint16_t(mode_of_operation_display) << std::endl;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::transfer_rx_pdo()
{
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_1, control_word);     // UINT16
    EC_WRITE_S32(domain_i_pd + off_rx_pdo_2, target_position);  // SINT32
    EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, mode_of_operation); // UIN8T

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::main_process()
{
    t_stamp += 2;

    if (t_stamp <= 10000)
    {
        mode_of_operation = 10;
        enable();
    }
    else
    {
        enable();
        double A = 200000.0;
        double T = 10.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 15000.0) * 0.001;
        target_position = A * std::sin(w * t);
    }

    return Ec_callback_status::SUCCESS;
}
