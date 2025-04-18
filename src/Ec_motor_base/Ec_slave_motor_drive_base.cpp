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
    uint16_t current_status = status_word & 0b1101111;

    if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::SWITCH_ON_DISABLED)
    {
        control_word = CiA_402::Pdo_object::Control_word::Bit_flags::SHUTDOWN;
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::READY_TO_SWITCH_ON)
    {
        control_word = CiA_402::Pdo_object::Control_word::Bit_flags::SWITCH_ON;
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::SWITCHED_ON)
    {
        control_word = CiA_402::Pdo_object::Control_word::Bit_flags::ENABLE_OPERATION;
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::OPERATION_ENABLED)
    {
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::QUICK_STOP_ACTIVE)
    {
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
    {
    }
    else if (current_status == CiA_402::Pdo_object::Status_word::Bit_flags::FAULT)
    {
    }
}

void Ec_slave_motor_drive_base::disable()
{
    control_word = CiA_402::Pdo_object::Control_word::Bit_flags::DISABLE_VOLTAGE;
}

void Ec_slave_motor_drive_base::set_operating_mode(Motor_drive::Mode mode_)
{
    if (mode_ == Motor_drive::Mode::POSITION)
    {
        mode_of_operation = CiA_402::Pdo_object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_POSITION_MODE;
    }
    else if (mode_ == Motor_drive::Mode::VELOCITY)
    {
        mode_of_operation = CiA_402::Pdo_object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_VELOCITY_MODE;
    }
    else if (mode_ == Motor_drive::Mode::TORQUE)
    {
        mode_of_operation = CiA_402::Pdo_object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    }
    else
    {
        mode_of_operation = CiA_402::Pdo_object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    }
}

void Ec_slave_motor_drive_base::check_status()
{
}

void Ec_slave_motor_drive_base::clear_fault()
{
    mode_of_operation = CiA_402::Pdo_object::Control_word::Bit_flags::FAULT_RESET;
}

void Ec_slave_motor_drive_base::set_position(double th_0)
{
    position_command = th_0;
}

void Ec_slave_motor_drive_base::set_velocity(double v_0)
{
    velocity_command = v_0;
}

void Ec_slave_motor_drive_base::set_torque(double tau_0)
{
    torque_command = tau_0;
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
