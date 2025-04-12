#include "Ec_slave_7.h"

Ec_slave_7::Ec_slave_7(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_7::~Ec_slave_7()
{
}

void Ec_slave_7::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_4_pdo_entries;
    slave_info.slave_pdos = slave_4_pdos;
    slave_info.slave_syncs = slave_4_syncs;
}

void Ec_slave_7::set_pdo()
{
    domain_i_regs = domain_regs;
}

void Ec_slave_7::monitor_status()
{
}

void Ec_slave_7::transfer_tx_pdo()
{
    int32_t ACT_POS = EC_READ_S32(domain_i_pd + off_tx_pdo_1);
    uint16_t STATUS_WD = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
    int16_t ACT_TOR = EC_READ_S16(domain_i_pd + off_tx_pdo_3);
    uint8_t OPMODE_DISP = EC_READ_U8(domain_i_pd + off_tx_pdo_4);
    uint16_t ERROR_CODE = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
    uint8_t DIG_IN = EC_READ_U8(domain_i_pd + off_tx_pdo_6);
    int32_t ACT_VEL = EC_READ_S32(domain_i_pd + off_tx_pdo_7);
    int16_t ADC_VAL = EC_READ_S16(domain_i_pd + off_tx_pdo_8);

    // std::cout << "MACT_TXPDO: " << ACT_POS << ", " << STATUS_WD << ", " << ACT_TOR << ", " << uint16_t(OPMODE_DISP) << ", " << ERROR_CODE << ", " << uint16_t(DIG_IN) << ", " << ACT_VEL << ", " << ADC_VAL << std::endl;
}

void Ec_slave_7::transfer_rx_pdo()
{
    t_stamp += 4;

    if ((2500 <= t_stamp) && (t_stamp <= 5000))
    {
        OP_MODE = 8;
        CONTROL_WD = 0;
    }
    else if ((5000 <= t_stamp) && (t_stamp <= 7000))
    {
        CONTROL_WD = 6;
    }
    else if ((7000 <= t_stamp) && (t_stamp <= 9000))
    {
        CONTROL_WD = 7;
    }
    else if ((9000 <= t_stamp) && (t_stamp <= 11000))
    {
        CONTROL_WD = 15;
    }
    else if ((11000 <= t_stamp) && (t_stamp <= 15000))
    {
        TARGET_POS = 0;
    }
    else
    {
        double A = 8192.0;
        double T = 2.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 15000.0) * 0.001;
        TARGET_POS = A * std::sin(w * t);
    }

    EC_WRITE_S32(domain_i_pd + off_rx_pdo_1, TARGET_POS);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_2, CONTROL_WD);
    EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, OP_MODE);
}

void Ec_slave_7::process_tx_pdo()
{
}

void Ec_slave_7::process_rx_pdo()
{
}

void Ec_slave_7::config_data_transfer()
{
}

void Ec_slave_7::publish_data()
{
}

void Ec_slave_7::subscribe_data()
{
}
