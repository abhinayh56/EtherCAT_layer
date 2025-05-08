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
    register_pdo(&m_rx_pdo.TARGET_POS);
    register_pdo(&m_rx_pdo.CONTROL_WD);
    register_pdo(&m_rx_pdo.TARGET_TORQ);
    register_pdo(&m_rx_pdo.OP_MODE);
    register_pdo(&m_rx_pdo.ERROR_CLEAR);
    register_pdo(&m_rx_pdo.DIG_OUT);
    register_pdo(&m_rx_pdo.TARGET_VEL);

    register_pdo(&m_tx_pdo.ACT_POS);
    register_pdo(&m_tx_pdo.STATUS_WD);
    register_pdo(&m_tx_pdo.ACT_TOR);
    register_pdo(&m_tx_pdo.OPMODE_DISP);
    register_pdo(&m_tx_pdo.ERROR_CODE);
    register_pdo(&m_tx_pdo.DIG_IN);
    register_pdo(&m_tx_pdo.ACT_VEL);
    register_pdo(&m_tx_pdo.ADC_VAL);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::transfer_tx_pdo()
{
    transfer_tx_pdo_S32(&m_tx_pdo.ACT_POS);
    transfer_tx_pdo_U16(&m_tx_pdo.STATUS_WD);
    transfer_tx_pdo_S16(&m_tx_pdo.ACT_TOR);
    transfer_tx_pdo_U8(&m_tx_pdo.OPMODE_DISP);
    transfer_tx_pdo_U16(&m_tx_pdo.ERROR_CODE);
    transfer_tx_pdo_U8(&m_tx_pdo.DIG_IN);
    transfer_tx_pdo_S32(&m_tx_pdo.ACT_VEL);
    transfer_tx_pdo_S16(&m_tx_pdo.ADC_VAL);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::transfer_rx_pdo()
{
    transfer_rx_pdo_S32(&m_rx_pdo.TARGET_POS);
    transfer_rx_pdo_U16(&m_rx_pdo.CONTROL_WD);
    transfer_rx_pdo_S16(&m_rx_pdo.TARGET_TORQ);
    transfer_rx_pdo_U8(&m_rx_pdo.OP_MODE);
    transfer_rx_pdo_U16(&m_rx_pdo.ERROR_CLEAR);
    transfer_rx_pdo_U8(&m_rx_pdo.DIG_OUT);
    transfer_rx_pdo_S32(&m_rx_pdo.TARGET_VEL);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::process_tx_pdo()
{
    b_tx_pdo_value.status_word = m_tx_pdo.STATUS_WD.value;
    b_tx_pdo_value.mode_of_operation_display = m_tx_pdo.OPMODE_DISP.value;
    b_tx_pdo_value.position_actual_value = m_tx_pdo.ACT_POS.value;
    b_tx_pdo_value.velocity_actual_value = m_tx_pdo.ACT_VEL.value;
    b_tx_pdo_value.torque_actual_value = m_tx_pdo.ACT_TOR.value;

    check_status();

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::process_rx_pdo()
{
    m_rx_pdo.TARGET_POS.value = b_rx_pdo_value.target_position;
    m_rx_pdo.CONTROL_WD.value = b_rx_pdo_value.control_word;
    m_rx_pdo.OP_MODE.value = b_rx_pdo_value.mode_of_operation;

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

    if (enable_status == Motor_drive::Enable_status::DISABLE)
    {
        offset = b_tx_pdo_value.position_actual_value;
    }

    t_stamp += 1;

    Motor_drive::Enable_status enable_status = Motor_drive::Enable_status::DISABLE;
    // std::cout << ": " << t_stamp << " | " << enable_status;
    if (t_stamp <= 10000)
    {
        if (enable_status == Motor_drive::Enable_status::DISABLE)
        {
            b_rx_pdo_value.mode_of_operation = 8;
            enable();
            b_rx_pdo_value.target_position = offset;
            // std::cout << ", " << "inside enable" << std::endl;
        }
    }
    else
    {
        enable();
        // std::cout << ", " << "outside enable" << std::endl;
        b_rx_pdo_value.mode_of_operation = 8;
        double A = 8191.0 * 0.5;
        double T = 3.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 10000.0) * 0.001;
        b_rx_pdo_value.target_position = A * std::sin(w * t) + offset;
    }

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::reset()
{
    offset = b_tx_pdo_value.position_actual_value;
    t_stamp = 0;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_mact::init()
{
    // sync_position();
    // sync_velocity();
    // sync_torque();
    offset = b_tx_pdo_value.position_actual_value;
    t_stamp = 0;

    return Ec_callback_status::SUCCESS;
}
