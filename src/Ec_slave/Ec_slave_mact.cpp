#include "Ec_slave_mact.h"

Ec_slave_mact::Ec_slave_mact(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_mact::~Ec_slave_mact()
{
}

uint16_t Ec_slave_mact::set_info_from_eni()
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

uint16_t Ec_slave_mact::set_pdo()
{
    for (uint8_t i = 0; i < 15; i++)
    {
        domain_regs[i].position = slave_address;
    }
    domain_i_regs = domain_regs;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::transfer_tx_pdo()
{
    position_actual_value = EC_READ_S32(domain_i_pd + off_tx_pdo_1);
    status_word = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
    torque_actual_value = EC_READ_S16(domain_i_pd + off_tx_pdo_3);
    mode_of_operation_display = EC_READ_U8(domain_i_pd + off_tx_pdo_4);
    uint16_t ERROR_CODE = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
    uint8_t DIG_IN = EC_READ_U8(domain_i_pd + off_tx_pdo_6);
    velocity_actual_value = EC_READ_S32(domain_i_pd + off_tx_pdo_7);
    int16_t ADC_VAL = EC_READ_S16(domain_i_pd + off_tx_pdo_8);
    check_status();

    if (enable_status == Motor_drive::Enable_status::DISABLE)
    {
        offset = position_actual_value;
    }

    // std::cout << "MACT_TXPDO: " << slave_ns << " | " << position_actual_value << ", " << status_word << ", " << torque_actual_value << ", " << uint16_t(mode_of_operation_display) << ", " << ERROR_CODE << ", " << uint16_t(DIG_IN) << ", " << velocity_actual_value << ", " << ADC_VAL << std::endl;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::transfer_rx_pdo()
{
    EC_WRITE_S32(domain_i_pd + off_rx_pdo_1, target_position);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_2, control_word);
    EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, mode_of_operation);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::main_process()
{
    t_stamp += 1;
    Motor_drive::Enable_status enable_status = Motor_drive::Enable_status::DISABLE;
    // std::cout << ": " << t_stamp << " | " << enable_status;
    if (t_stamp <= 10000)
    {
        if (enable_status == Motor_drive::Enable_status::DISABLE)
        {
            mode_of_operation = 8;
            enable();
            target_position = offset;
            // std::cout << ", " << "inside enable" << std::endl;
        }
    }
    else
    {
        enable();
        // std::cout << ", " << "outside enable" << std::endl;
        mode_of_operation = 8;
        double A = 8191.0*0.5;
        double T = 3.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 10000.0) * 0.001;
        target_position = A * std::sin(w * t) + offset;
    }

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::reset()
{
    offset = position_actual_value;
    t_stamp = 0;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::init()
{
    // sync_position();
    // sync_velocity();
    // sync_torque();
    offset = position_actual_value;
    t_stamp = 0;

    return Ec_callback_status::SUCCESS;
}
