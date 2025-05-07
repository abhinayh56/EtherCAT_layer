#include "Ec_slave_ingenia.h"

Ec_slave_ingenia::Ec_slave_ingenia(uint16_t slave_address_, const std::string &slave_ns_)
{
    slave_address = slave_address_;
    slave_ns = slave_ns_;
}

Ec_slave_ingenia::~Ec_slave_ingenia()
{
}

uint16_t Ec_slave_ingenia::set_info_from_eni()
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
    register_pdo(&m_tx_pdo.Status_Word);
    register_pdo(&m_tx_pdo.Actual_position);
    register_pdo(&m_tx_pdo.Actual_velocity);
    register_pdo(&m_tx_pdo.Operation_mode_display);

    register_pdo(&m_rx_pdo.CONTROL_WD);
    register_pdo(&m_rx_pdo.TARGET_POS);
    register_pdo(&m_rx_pdo.TARGET_VEL);
    register_pdo(&m_rx_pdo.OP_MODE);

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::transfer_tx_pdo()
{
    m_tx_pdo.Status_Word.value = EC_READ_U16(domain_i_pd + m_tx_pdo.Status_Word.offset);
    m_tx_pdo.Actual_position.value = EC_READ_S32(domain_i_pd + m_tx_pdo.Actual_position.offset);
    m_tx_pdo.Actual_velocity.value = EC_READ_S32(domain_i_pd + m_tx_pdo.Actual_velocity.offset);
    m_tx_pdo.Operation_mode_display.value = EC_READ_U8(domain_i_pd + m_tx_pdo.Operation_mode_display.offset);

    b_tx_pdo_value.status_word = m_tx_pdo.Status_Word.value;
    b_tx_pdo_value.position_actual_value = m_tx_pdo.Actual_position.value;
    b_tx_pdo_value.velocity_actual_value = m_tx_pdo.Actual_velocity.value;
    b_tx_pdo_value.mode_of_operation_display = m_tx_pdo.Operation_mode_display.value;

    check_status();

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::transfer_rx_pdo()
{
    EC_WRITE_U16(domain_i_pd + m_rx_pdo.CONTROL_WD.offset, b_rx_pdo_value.control_word);     // UINT16
    EC_WRITE_S32(domain_i_pd + m_rx_pdo.TARGET_POS.offset, b_rx_pdo_value.target_position);  // SINT32
    EC_WRITE_U8(domain_i_pd + m_rx_pdo.OP_MODE.offset, b_rx_pdo_value.mode_of_operation); // UIN8T

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
    t_stamp += 1;

    if (t_stamp <= 3000)
    {
        b_rx_pdo_value.mode_of_operation = 8;
        b_rx_pdo_value.target_position = offset;
    }
    if ((t_stamp > 3000) && (t_stamp <= 10000))
    {
        b_rx_pdo_value.mode_of_operation = 8;
        b_rx_pdo_value.target_position = offset;
        enable();
    }
    else
    {
        // enable();
        double A = 200000.0;
        double T = 3.0;
        double f = 1.0 / T;
        double w = 2.0 * 3.1417 * f;
        double t = ((double)t_stamp - 10000.0) * 0.001;
        b_rx_pdo_value.target_position = A * std::sin(w * t) + offset;
    }

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::reset()
{
    offset = b_tx_pdo_value.position_actual_value;
    t_stamp = 0;

    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_ingenia::init()
{
    // sync_position();
    // sync_velocity();
    // sync_torque();
    offset = b_tx_pdo_value.position_actual_value;
    t_stamp = 0;

    return Ec_callback_status::SUCCESS;
}
