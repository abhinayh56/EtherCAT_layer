#include "Ec_slave_mact_2.h"

Ec_slave_mact_2::Ec_slave_mact_2(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_mact_2::~Ec_slave_mact_2()
{
}

void Ec_slave_mact_2::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_4_pdo_entries;
    slave_info.slave_pdos = slave_4_pdos;
    slave_info.slave_syncs = slave_4_syncs;
}

void Ec_slave_mact_2::set_pdo()
{
    for (uint8_t i = 0; i < 15; i++)
    {
        domain_regs[i].position = slave_address;
    }
    domain_i_regs = domain_regs;
}

void Ec_slave_mact_2::monitor_status()
{
    check_status();
}

void Ec_slave_mact_2::transfer_tx_pdo()
{
    int32_t ACT_POS = EC_READ_S32(domain_i_pd + off_tx_pdo_1);
    uint16_t status_word = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
    int16_t ACT_TOR = EC_READ_S16(domain_i_pd + off_tx_pdo_3);
    uint8_t mode_of_operation_display = EC_READ_U8(domain_i_pd + off_tx_pdo_4);
    uint16_t ERROR_CODE = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
    uint8_t DIG_IN = EC_READ_U8(domain_i_pd + off_tx_pdo_6);
    int32_t ACT_VEL = EC_READ_S32(domain_i_pd + off_tx_pdo_7);
    int16_t ADC_VAL = EC_READ_S16(domain_i_pd + off_tx_pdo_8);

    // std::cout << "MACT_TXPDO: " << slave_ns << " | " << ACT_POS << ", " << status_word << ", " << ACT_TOR << ", " << uint16_t(mode_of_operation_display) << ", " << ERROR_CODE << ", " << uint16_t(DIG_IN) << ", " << ACT_VEL << ", " << ADC_VAL << std::endl;
}

void Ec_slave_mact_2::transfer_rx_pdo()
{
    EC_WRITE_S32(domain_i_pd + off_rx_pdo_1, target_position);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_2, control_word);
    EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, mode_of_operation);
}

void Ec_slave_mact_2::process_tx_pdo()
{
}

void Ec_slave_mact_2::process_rx_pdo()
{
}

void Ec_slave_mact_2::config_data_transfer()
{
}

void Ec_slave_mact_2::publish_data()
{
}

void Ec_slave_mact_2::subscribe_data()
{
}

void Ec_slave_mact_2::main_process()
{
    t_stamp += 4;
    if (t_stamp <= 10000)
    {
        if (enable_status == false)
        {
            mode_of_operation = 8;
            enable();
        }
    }
    else
    {
        mode_of_operation = 8;
        double A = 8192.0;
        double T = 2.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 10000.0) * 0.001;
        target_position = A * std::sin(w * t);
    }
}
