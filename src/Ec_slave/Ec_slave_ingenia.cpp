#include "Ec_slave_ingenia.h"

Ec_slave_ingenia::Ec_slave_ingenia(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_ingenia::~Ec_slave_ingenia()
{
}

void Ec_slave_ingenia::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_12_pdo_entries;
    slave_info.slave_pdos = slave_12_pdos;
    slave_info.slave_syncs = slave_12_syncs;
}

void Ec_slave_ingenia::set_pdo()
{
    for (uint8_t i = 0; i < 9; i++)
    {
        domain_regs[i].position = slave_address;
    }
    domain_i_regs = domain_regs;
}

void Ec_slave_ingenia::monitor_status()
{
}

void Ec_slave_ingenia::transfer_tx_pdo()
{
    uint16_t Status_Word = EC_READ_U16(domain_i_pd + off_tx_pdo_1);
    int32_t Actual_position = EC_READ_S32(domain_i_pd + off_tx_pdo_2);
    int32_t Actual_velocity = EC_READ_S32(domain_i_pd + off_tx_pdo_3);
    uint8_t Operation_mode_display = EC_READ_U8(domain_i_pd + off_tx_pdo_4);

    // std::cout << "INGENIA_TXPDO: " << slave_ns << " | " << Status_Word << ", " << Actual_position << ", " << Actual_velocity << ", " << uint16_t(Operation_mode_display) << std::endl;
}

void Ec_slave_ingenia::transfer_rx_pdo()
{
    t_stamp += 4;

    if (t_stamp <= 2500)
    {
        OP_MODE = 0;
        CONTROL_WD = 128;
    }
    else if ((2500 <= t_stamp) && (t_stamp <= 5000))
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
        double A = 200000.0;
        double T = 10.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 15000.0) * 0.001;
        TARGET_POS = A * std::sin(w * t);
    }

    EC_WRITE_U16(domain_i_pd + off_rx_pdo_1, CONTROL_WD); // UINT16
    EC_WRITE_S32(domain_i_pd + off_rx_pdo_2, TARGET_POS); // SINT32
    EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, OP_MODE);     // UIN8T
}

void Ec_slave_ingenia::process_tx_pdo()
{
}

void Ec_slave_ingenia::process_rx_pdo()
{
}

void Ec_slave_ingenia::config_data_transfer()
{
}

void Ec_slave_ingenia::publish_data()
{
}

void Ec_slave_ingenia::subscribe_data()
{
}
