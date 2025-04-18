#include "Ec_slave_motor_drive_base.h"

Ec_slave_motor_drive_base::Ec_slave_motor_drive_base()
{
}

Ec_slave_motor_drive_base::~Ec_slave_motor_drive_base()
{
}

void Ec_slave_motor_drive_base::set_info()
{
}

void Ec_slave_motor_drive_base::set_pdo()
{
}

void Ec_slave_motor_drive_base::monitor_status()
{
}

void Ec_slave_motor_drive_base::transfer_tx_pdo()
{
}

void Ec_slave_motor_drive_base::transfer_rx_pdo()
{
}

void Ec_slave_motor_drive_base::process_tx_pdo()
{
}

void Ec_slave_motor_drive_base::process_rx_pdo()
{
}

void Ec_slave_motor_drive_base::config_data_transfer()
{
}

void Ec_slave_motor_drive_base::publish_data()
{
}

void Ec_slave_motor_drive_base::subscribe_data()
{
}

void Ec_slave_motor_drive_base::main_process()
{
}

void Ec_slave_motor_drive_base::init()
{
}

void Ec_slave_motor_drive_base::stop()
{
    disable();
}

void Ec_slave_motor_drive_base::enable()
{
    // std::cout << "enable called " ;
    if (current_status == Object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
        // std::cout << ",  NOT_READY_TO_SWITCH_ON " << std::endl;
        // transition 1
    }
    else if (current_status == Object::Status_word::Bit_flags::SWITCH_ON_DISABLED)
    {
        // std::cout << ",  SWITCH_ON_DISABLED " << std::endl;
        // transition 2
        control_word = Object::Control_word::Bit_flags::SHUTDOWN;
    }
    else if (current_status == Object::Status_word::Bit_flags::READY_TO_SWITCH_ON)
    {
        // std::cout << ",  READY_TO_SWITCH_ON " << std::endl;
        // transition 3
        control_word = Object::Control_word::Bit_flags::SWITCH_ON;
    }
    else if (current_status == Object::Status_word::Bit_flags::SWITCHED_ON)
    {
        // std::cout << ",  SWITCHED_ON " << std::endl;
        // transition 4
        control_word = Object::Control_word::Bit_flags::ENABLE_OPERATION;
    }
    else if (current_status == Object::Status_word::Bit_flags::OPERATION_ENABLED)
    {
        // std::cout << ",  OPERATION_ENABLED " << std::endl;
        enable_status = Motor_drive::Enable_status::ENABLE;
    }
    else if (current_status == Object::Status_word::Bit_flags::QUICK_STOP_ACTIVE)
    {
        // std::cout << ",  QUICK_STOP_ACTIVE " << std::endl;
        // transition 16 or 12
        // control_word = Object::Control_word::Bit_flags::ENABLE_OPERATION;
        control_word = Object::Control_word::Bit_flags::DISABLE_VOLTAGE;
    }
    else if (current_status == Object::Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
    {
        // std::cout << ",  FAULT_REACTION_ACTIVE " << std::endl;
        // transition 14
    }
    else if (current_status == Object::Status_word::Bit_flags::FAULT)
    {
        // std::cout << ",  FAULT " << std::endl;
        // transition 15
        control_word = Object::Control_word::Bit_flags::FAULT_RESET;
    }
}

void Ec_slave_motor_drive_base::disable()
{
    control_word = Object::Control_word::Bit_flags::DISABLE_VOLTAGE;
}

void Ec_slave_motor_drive_base::set_operating_mode(Motor_drive::OP_mode mode_)
{
    if (mode_ == Motor_drive::OP_mode::POSITION)
    {
        mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_POSITION_MODE;
    }
    else if (mode_ == Motor_drive::OP_mode::VELOCITY)
    {
        mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_VELOCITY_MODE;
    }
    else if (mode_ == Motor_drive::OP_mode::TORQUE)
    {
        mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    }
    else
    {
        mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    }
}

void Ec_slave_motor_drive_base::check_status()
{
    uint16_t previoius_status = current_status;
    if ((status_word & 0b1001111) == Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
        current_status = Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON;
        if(previoius_status != current_status) {std::cout << slave_ns << ": NOT_READY_TO_SWITCH_ON" << std::endl;}
    }
    else if ((status_word & 0b1001111) == Status_word::Bit_flags::SWITCH_ON_DISABLED)
    {
        current_status = Status_word::Bit_flags::SWITCH_ON_DISABLED;
        if(previoius_status != current_status) {std::cout <<slave_ns << ": SWITCH_ON_DISABLED" << std::endl;}
    }
    else if ((status_word & 0b1101111) == Status_word::Bit_flags::READY_TO_SWITCH_ON)
    {
        current_status = Status_word::Bit_flags::READY_TO_SWITCH_ON;
        if(previoius_status != current_status) {std::cout << slave_ns << ": READY_TO_SWITCH_ON" << std::endl;}
    }
    else if ((status_word & 0b1101111) == Status_word::Bit_flags::SWITCHED_ON)
    {
        current_status = Status_word::Bit_flags::SWITCHED_ON;
        if(previoius_status != current_status) {std::cout << slave_ns << ": SWITCHED_ON" << std::endl;}
    }
    else if ((status_word & 0b1101111) == Status_word::Bit_flags::OPERATION_ENABLED)
    {
        current_status = Status_word::Bit_flags::OPERATION_ENABLED;
        if(previoius_status != current_status) {std::cout << slave_ns << ": OPERATION_ENABLED" << std::endl;}
    }
    else if ((status_word & 0b1101111) == Status_word::Bit_flags::QUICK_STOP_ACTIVE)
    {
        current_status = Status_word::Bit_flags::QUICK_STOP_ACTIVE;
        if(previoius_status != current_status) {std::cout << slave_ns << ": QUICK_STOP_ACTIVE" << std::endl;}
    }
    else if ((status_word & 0b1001111) == Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
    {
        current_status = Status_word::Bit_flags::FAULT_REACTION_ACTIVE;
        if(previoius_status != current_status) {std::cout << slave_ns << ": FAULT_REACTION_ACTIVE" << std::endl;}
    }
    else if ((status_word & 0b1001111) == Status_word::Bit_flags::FAULT)
    {
        current_status = Status_word::Bit_flags::FAULT;
        if(previoius_status != current_status) {std::cout << slave_ns << ": FAULT" << std::endl;}
    }
    else if ((status_word & (1<<13)) == Status_word::Bit_flags::CSP_FOLLOWING_ERROR_BIT)
    {
        current_status = Status_word::Bit_flags::CSP_FOLLOWING_ERROR_BIT;
        if(previoius_status != current_status) {std::cout << slave_ns << ": CSP_FOLLOWING_ERROR_BIT" << std::endl;}
    }
    else if ((status_word & (1<<12)) == Status_word::Bit_flags::CSP_TARGET_POSITION_IGNORED)
    {
        current_status = Status_word::Bit_flags::CSP_TARGET_POSITION_IGNORED;
        if(previoius_status != current_status) {std::cout << slave_ns << ": CSP_TARGET_POSITION_IGNORED" << std::endl;}
    }
    else
    {
        std::cout << "none\n";
    }
}

void Ec_slave_motor_drive_base::clear_fault()
{
    mode_of_operation = Object::Control_word::Bit_flags::FAULT_RESET;
}

void Ec_slave_motor_drive_base::set_position(double position_command_)
{
    position_command = position_command_;
}

void Ec_slave_motor_drive_base::set_velocity(double velocity_comman_)
{
    velocity_command = velocity_comman_;
}

void Ec_slave_motor_drive_base::set_torque(double torque_command_)
{
    torque_command = torque_command_;
}

double Ec_slave_motor_drive_base::get_position()
{
    return position_actual;
}

double Ec_slave_motor_drive_base::get_velocity()
{
    return velocity_actual;
}

double Ec_slave_motor_drive_base::get_torque()
{
    return torque_actual;
}

void Ec_slave_motor_drive_base::sync_position()
{
    position_command = position_actual;
}

void Ec_slave_motor_drive_base::sync_velocity()
{
    velocity_command = velocity_actual;
}

void Ec_slave_motor_drive_base::sync_torque()
{
    torque_command = torque_actual;
}
