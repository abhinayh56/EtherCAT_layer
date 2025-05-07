#include "Ec_slave_base_motor_drive.h"

Ec_slave_base_motor_drive::Ec_slave_base_motor_drive()
{
}

Ec_slave_base_motor_drive::~Ec_slave_base_motor_drive()
{
}

uint16_t Ec_slave_base_motor_drive::set_info()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::set_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::transfer_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::transfer_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::process_tx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::process_rx_pdo()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::config_data_transfer()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::publish_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::subscribe_data()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::main_process()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::reset()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::init()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::init_motor_drive()
{
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::stop()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    ret_val |= disable();

    return ret_val;
}

uint16_t Ec_slave_base_motor_drive::enable()
{
    uint16_t ret_val = Ec_callback_status::IN_PROGRESS;

    // std::cout << "enable called " ;
    if (current_status == Object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
        ret_val = Ec_callback_status::IN_PROGRESS;
        // std::cout << ",  NOT_READY_TO_SWITCH_ON " << std::endl;
        // transition 1
    }
    else if (current_status == Object::Status_word::Bit_flags::SWITCH_ON_DISABLED)
    {
        // std::cout << ",  SWITCH_ON_DISABLED " << std::endl;
        // transition 2
        b_rx_pdo_value.control_word = Object::Control_word::Bit_flags::SHUTDOWN;
        ret_val = Ec_callback_status::IN_PROGRESS;
    }
    else if (current_status == Object::Status_word::Bit_flags::READY_TO_SWITCH_ON)
    {
        // std::cout << ",  READY_TO_SWITCH_ON " << std::endl;
        // transition 3
        b_rx_pdo_value.control_word = Object::Control_word::Bit_flags::SWITCH_ON;
        ret_val = Ec_callback_status::IN_PROGRESS;
    }
    else if (current_status == Object::Status_word::Bit_flags::SWITCHED_ON)
    {
        // std::cout << ",  SWITCHED_ON " << std::endl;
        // transition 4
        b_rx_pdo_value.control_word = Object::Control_word::Bit_flags::ENABLE_OPERATION;
        ret_val = Ec_callback_status::IN_PROGRESS;
    }
    else if (current_status == Object::Status_word::Bit_flags::OPERATION_ENABLED)
    {
        // std::cout << ",  OPERATION_ENABLED " << std::endl;
        enable_status = Motor_drive::Enable_status::ENABLE;
        ret_val = Ec_callback_status::SUCCESS;
    }
    else if (current_status == Object::Status_word::Bit_flags::QUICK_STOP_ACTIVE)
    {
        // std::cout << ",  QUICK_STOP_ACTIVE " << std::endl;
        // transition 16 or 12
        // control_word = Object::Control_word::Bit_flags::ENABLE_OPERATION;
        b_rx_pdo_value.control_word = Object::Control_word::Bit_flags::DISABLE_VOLTAGE;
        ret_val = Ec_callback_status::IN_PROGRESS;
    }
    else if (current_status == Object::Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
    {
        // std::cout << ",  FAULT_REACTION_ACTIVE " << std::endl;
        // transition 14
        ret_val = Ec_callback_status::IN_PROGRESS;
    }
    else if (current_status == Object::Status_word::Bit_flags::FAULT)
    {
        // std::cout << ",  FAULT " << std::endl;
        // transition 15
        b_rx_pdo_value.control_word = Object::Control_word::Bit_flags::FAULT_RESET;
        ret_val = Ec_callback_status::FAILURE;
    }

    return ret_val;
}

uint16_t Ec_slave_base_motor_drive::disable()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    b_rx_pdo_value.control_word = Object::Control_word::Bit_flags::DISABLE_VOLTAGE;
    
    return Ec_callback_status::SUCCESS;
}

uint16_t Ec_slave_base_motor_drive::set_operating_mode(Motor_drive::OP_mode mode_)
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    if (mode_ == Motor_drive::OP_mode::POSITION)
    {
        b_rx_pdo_value.mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_POSITION_MODE;
    }
    else if (mode_ == Motor_drive::OP_mode::VELOCITY)
    {
        b_rx_pdo_value.mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_VELOCITY_MODE;
    }
    else if (mode_ == Motor_drive::OP_mode::TORQUE)
    {
        b_rx_pdo_value.mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    }
    else
    {
        b_rx_pdo_value.mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    }

    return ret_val;
}

uint16_t Ec_slave_base_motor_drive::check_status()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;

    uint16_t previoius_status = current_status;
    if ((b_tx_pdo_value.status_word & 0b1001111) == Object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
        current_status = Object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": NOT_READY_TO_SWITCH_ON" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & 0b1001111) == Object::Status_word::Bit_flags::SWITCH_ON_DISABLED)
    {
        current_status = Object::Status_word::Bit_flags::SWITCH_ON_DISABLED;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": SWITCH_ON_DISABLED" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & 0b1101111) == Object::Status_word::Bit_flags::READY_TO_SWITCH_ON)
    {
        current_status = Object::Status_word::Bit_flags::READY_TO_SWITCH_ON;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": READY_TO_SWITCH_ON" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & 0b1101111) == Object::Status_word::Bit_flags::SWITCHED_ON)
    {
        current_status = Object::Status_word::Bit_flags::SWITCHED_ON;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": SWITCHED_ON" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & 0b1101111) == Object::Status_word::Bit_flags::OPERATION_ENABLED)
    {
        current_status = Object::Status_word::Bit_flags::OPERATION_ENABLED;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": OPERATION_ENABLED" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & 0b1101111) == Object::Status_word::Bit_flags::QUICK_STOP_ACTIVE)
    {
        current_status = Object::Status_word::Bit_flags::QUICK_STOP_ACTIVE;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": QUICK_STOP_ACTIVE" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & 0b1001111) == Object::Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
    {
        current_status = Object::Status_word::Bit_flags::FAULT_REACTION_ACTIVE;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": FAULT_REACTION_ACTIVE" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & 0b1001111) == Object::Status_word::Bit_flags::FAULT)
    {
        current_status = Object::Status_word::Bit_flags::FAULT;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": FAULT" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & (1 << 13)) == Object::Status_word::Bit_flags::CSP_FOLLOWING_ERROR_BIT)
    {
        current_status = Object::Status_word::Bit_flags::CSP_FOLLOWING_ERROR_BIT;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": CSP_FOLLOWING_ERROR_BIT" << std::endl;
        }
    }
    else if ((b_tx_pdo_value.status_word & (1 << 12)) == Object::Status_word::Bit_flags::CSP_TARGET_POSITION_IGNORED)
    {
        current_status = Object::Status_word::Bit_flags::CSP_TARGET_POSITION_IGNORED;
        if (previoius_status != current_status)
        {
            std::cout << "INFO   : " << slave_ns << ": CSP_TARGET_POSITION_IGNORED" << std::endl;
        }
    }
    else
    {
        std::cout << "INFO   : " << slave_ns << ": UNKNOWN_STATE" << std::endl;
    }

    return ret_val;
}

uint16_t Ec_slave_base_motor_drive::clear_fault()
{
    uint16_t ret_val = Ec_callback_status::SUCCESS;
    
    b_rx_pdo_value.mode_of_operation = Object::Control_word::Bit_flags::FAULT_RESET;

    return ret_val;
}

void Ec_slave_base_motor_drive::set_position(double position_command_)
{
    position_command = position_command_;
}

void Ec_slave_base_motor_drive::set_velocity(double velocity_comman_)
{
    velocity_command = velocity_comman_;
}

void Ec_slave_base_motor_drive::set_torque(double torque_command_)
{
    torque_command = torque_command_;
}

double Ec_slave_base_motor_drive::get_position()
{
    return position_actual;
}

double Ec_slave_base_motor_drive::get_velocity()
{
    return velocity_actual;
}

double Ec_slave_base_motor_drive::get_torque()
{
    return torque_actual;
}

void Ec_slave_base_motor_drive::sync_position()
{
    position_command = position_actual;
}

void Ec_slave_base_motor_drive::sync_velocity()
{
    velocity_command = velocity_actual;
}

void Ec_slave_base_motor_drive::sync_torque()
{
    torque_command = torque_actual;
}
