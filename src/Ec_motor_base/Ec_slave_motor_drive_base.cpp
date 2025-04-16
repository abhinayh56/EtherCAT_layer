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

void Ec_slave_motor_drive_base::init()
{
}

void Ec_slave_motor_drive_base::stop()
{
}

void Ec_slave_motor_drive_base::enable()
{
    if (status_word == Pdo_object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
    {
        control_word = Pdo_object::Control_word::Bit_flags::
    }
}

void Ec_slave_motor_drive_base::disable()
{
    control_word = Pdo_object::Control_word::Bit_flags::DISABLE_VOLTAGE;
}

void Ec_slave_motor_drive_base::set_operating_mode(Motor_drive::Mode mode_)
{
    if (mode_ == Motor_drive::Mode::POSITION)
    {
        mode_of_operation = 8;
    }
    else if (mode_ == Motor_drive::Mode::VELOCITY)
    {
        mode_of_operation = 9;
    }
    else if (mode_ == Motor_drive::Mode::TORQUE)
    {
        mode_of_operation = 10;
    }
    else
    {
        mode_of_operation = 0;
    }
}

void Ec_slave_motor_drive_base::check_fault()
{
}

void Ec_slave_motor_drive_base::clear_fault()
{
    mode_of_operation = Pdo_object::Control_word::Bit_flags::FAULT_RESET;
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