#include "Ec_slave_mact.h"

Ec_slave_mact::Ec_slave_mact(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_mact::~Ec_slave_mact()
{
}

void Ec_slave_mact::set_info()
{
    slave_info.alias = alias;
    slave_info.position = position;
    slave_info.vendor_id = vendor_id;
    slave_info.product_code = product_code;

    slave_info.slave_pdo_entries = slave_4_pdo_entries;
    slave_info.slave_pdos = slave_4_pdos;
    slave_info.slave_syncs = slave_4_syncs;
}

void Ec_slave_mact::set_pdo()
{
    for (uint8_t i = 0; i < 15; i++)
    {
        domain_regs[i].position = slave_address;
    }
    domain_i_regs = domain_regs;
}

void Ec_slave_mact::monitor_status()
{
}

void Ec_slave_mact::transfer_tx_pdo()
{
    int32_t ACT_POS = EC_READ_S32(domain_i_pd + off_tx_pdo_1);
    uint16_t STATUS_WD = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
    int16_t ACT_TOR = EC_READ_S16(domain_i_pd + off_tx_pdo_3);
    uint8_t OPMODE_DISP = EC_READ_U8(domain_i_pd + off_tx_pdo_4);
    uint16_t ERROR_CODE = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
    uint8_t DIG_IN = EC_READ_U8(domain_i_pd + off_tx_pdo_6);
    int32_t ACT_VEL = EC_READ_S32(domain_i_pd + off_tx_pdo_7);
    int16_t ADC_VAL = EC_READ_S16(domain_i_pd + off_tx_pdo_8);

    mode_of_operation_disp = OPMODE_DISP;
    status_word = STATUS_WD;

    if (log_complete == false)
    {
        if ((status_word & 0b1001111) == Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
        {
            current_status = Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON;
            std::cout << slave_ns << ": NOT_READY_TO_SWITCH_ON" << std::endl;
        }
        else if ((status_word & 0b1001111) == Status_word::Bit_flags::SWITCH_ON_DISABLED)
        {
            current_status = Status_word::Bit_flags::SWITCH_ON_DISABLED;
            std::cout <<slave_ns << ": SWITCH_ON_DISABLED" << std::endl;
        }
        else if ((status_word & 0b1101111) == Status_word::Bit_flags::READY_TO_SWITCH_ON)
        {
            current_status = Status_word::Bit_flags::READY_TO_SWITCH_ON;
            std::cout << slave_ns << ": READY_TO_SWITCH_ON" << std::endl;
        }
        else if ((status_word & 0b1101111) == Status_word::Bit_flags::SWITCHED_ON)
        {
            current_status = Status_word::Bit_flags::SWITCHED_ON;
            std::cout << slave_ns << ": SWITCHED_ON" << std::endl;
        }
        else if ((status_word & 0b1101111) == Status_word::Bit_flags::OPERATION_ENABLED)
        {
            current_status = Status_word::Bit_flags::OPERATION_ENABLED;
            std::cout << slave_ns << ": OPERATION_ENABLED" << std::endl;
            log_complete = true;
        }
        else if ((status_word & 0b1101111) == Status_word::Bit_flags::QUICK_STOP_ACTIVE)
        {
            current_status = Status_word::Bit_flags::QUICK_STOP_ACTIVE;
            std::cout << slave_ns << ": QUICK_STOP_ACTIVE" << std::endl;
        }
        else if ((status_word & 0b1001111) == Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
        {
            current_status = Status_word::Bit_flags::FAULT_REACTION_ACTIVE;
            std::cout << slave_ns << ": FAULT_REACTION_ACTIVE" << std::endl;
        }
        else if ((status_word & 0b1001111) == Status_word::Bit_flags::FAULT)
        {
            current_status = Status_word::Bit_flags::FAULT;
            std::cout << slave_ns << ": FAULT" << std::endl;
        }
    }

    // std::cout << "MACT_TXPDO: " << slave_ns << " | " << ACT_POS << ", " << STATUS_WD << ", " << ACT_TOR << ", " << uint16_t(OPMODE_DISP) << ", " << ERROR_CODE << ", " << uint16_t(DIG_IN) << ", " << ACT_VEL << ", " << ADC_VAL << std::endl;
}

void Ec_slave_mact::transfer_rx_pdo()
{
    EC_WRITE_S32(domain_i_pd + off_rx_pdo_1, TARGET_POS);
    EC_WRITE_U16(domain_i_pd + off_rx_pdo_2, desired_control);
    EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, OP_MODE);

    // EC_WRITE_S32(domain_i_pd + off_rx_pdo_1, TARGET_POS);
    // EC_WRITE_U16(domain_i_pd + off_rx_pdo_2, CONTROL_WD);
    // EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, OP_MODE);
}

void Ec_slave_mact::process_tx_pdo()
{
}

void Ec_slave_mact::process_rx_pdo()
{
}

void Ec_slave_mact::config_data_transfer()
{
}

void Ec_slave_mact::publish_data()
{
}

void Ec_slave_mact::subscribe_data()
{
}

void Ec_slave_mact::main_process()
{
    t_stamp += 4;
    if ((2500 <= t_stamp) && (t_stamp <= 8000))
    {
        if (enable_status == false)
        {
            OP_MODE = 10;
            enable();
            TARGET_POS = 0;
        }
    }
    else
    {
        enable();
        OP_MODE = 8;
        double A = 8192.0;
        double T = 2.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 15000.0) * 0.001;
        TARGET_POS = A * std::sin(w * t);
    }

    // if ((2500 <= t_stamp) && (t_stamp <= 5000))
    // {
    //     OP_MODE = 8;
    //     CONTROL_WD = 0;
    // }
    // else if ((5000 <= t_stamp) && (t_stamp <= 7000))
    // {
    //     CONTROL_WD = 6;
    // }
    // else if ((7000 <= t_stamp) && (t_stamp <= 9000))
    // {
    //     CONTROL_WD = 7;
    // }
    // else if ((9000 <= t_stamp) && (t_stamp <= 11000))
    // {
    //     CONTROL_WD = 15;
    // }
    // else if ((11000 <= t_stamp) && (t_stamp <= 15000))
    // {
    //     TARGET_POS = 0;
    // }
    // else
    // {
    //     double A = 8192.0;
    //     double T = 2.0;
    //     double f = 1.0 / T;
    //     double w = 2.0 * 3.1417 * f;
    //     double t = ((double)t_stamp - 15000.0) * 0.001;
    //     TARGET_POS = A * std::sin(w * t);
    // }
}

void Ec_slave_mact::enable()
{
    if (current_status == Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
        // transition 1
    }
    else if (current_status == Status_word::Bit_flags::SWITCH_ON_DISABLED)
    {
        // transition 2
        desired_control = Control_word::Bit_flags::SHUTDOWN;
    }
    else if (current_status == Status_word::Bit_flags::READY_TO_SWITCH_ON)
    {
        // transition 3
        desired_control = Control_word::Bit_flags::SWITCH_ON;
    }
    else if (current_status == Status_word::Bit_flags::SWITCHED_ON)
    {
        // transition 4
        desired_control = Control_word::Bit_flags::ENABLE_OPERATION;
    }
    else if (current_status == Status_word::Bit_flags::OPERATION_ENABLED)
    {
    }
    else if (current_status == Status_word::Bit_flags::QUICK_STOP_ACTIVE)
    {
        // transition 16 or 12
        desired_control = Control_word::Bit_flags::ENABLE_OPERATION;
        // desired_control = Control_word::Bit_flags::DISABLE_VOLTAGE;
    }
    else if (current_status == Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
    {
        // transition 14
    }
    else if (current_status == Status_word::Bit_flags::FAULT)
    {
        // transition 15
        desired_control = Control_word::Bit_flags::FAULT_RESET;
    }
}
