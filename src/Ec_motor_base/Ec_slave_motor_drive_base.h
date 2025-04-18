#ifndef EC_SLAVE_MOTOR_SALVE_H
#define EC_SLAVE_MOTOR_SALVE_H

#include <cmath>
#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"
#include "../Ec_utils/Ec_objects.h"

namespace Motor_drive
{
    enum OP_status : uint16_t
    {
        ENABLE = 0,
        DISABLE = 1
    };

    enum OP_mode : uint16_t
    {
        POSITION = 0,
        VELOCITY = 1,
        TORQUE = 2
    };

    enum Fault : uint16_t
    {
        OVER_CURRENT = 0,
        OVER_TEMPERATURE = 1,
        OVER_VOLTAGE = 2,
        UNKOWN = 3,
        NO_FAULT = 4
    };

    struct OP_mode_supported
    {
        bool position = false;
        bool velocity = false;
        bool torque = false;
    };
}

class Ec_slave_motor_drive_base : public Ec_slave_base
{
public:
    Ec_slave_motor_drive_base();
    ~Ec_slave_motor_drive_base();

    virtual void set_info();
    virtual void set_pdo();
    virtual void monitor_status();
    virtual void transfer_tx_pdo();
    virtual void transfer_rx_pdo();
    virtual void process_tx_pdo();
    virtual void process_rx_pdo();
    virtual void config_data_transfer();
    virtual void publish_data();
    virtual void subscribe_data();
    virtual void main_process();

    virtual void init();
    virtual void stop();
    virtual void enable();
    virtual void disable();
    virtual void set_operating_mode(Motor_drive::OP_mode mode_);
    virtual void check_status();
    virtual void clear_fault();
    virtual void set_position(double position_command_);
    virtual void set_velocity(double velocity_comman_);
    virtual void set_torque(double torque_command_);
    virtual double get_position();
    virtual double get_velocity();
    virtual double get_torque();
    virtual void sync_position();
    virtual void sync_velocity();
    virtual void sync_torque();

protected:
    Motor_drive::OP_status op_status = Motor_drive::OP_status::DISABLE;
    Motor_drive::OP_mode op_mode = Motor_drive::OP_mode::TORQUE;
    Motor_drive::OP_mode_supported mode_supported;

    Motor_drive::Fault fault = Motor_drive::Fault::NO_FAULT;

    double position_actual = 0;
    double velocity_actual = 0;
    double torque_actual = 0;

    double position_command = 0;
    double velocity_command = 0;
    double torque_command = 0;

    uint16_t status_word;
    int8_t mode_of_operation_display;
    int32_t position_actual_value = 0;
    int32_t velocity_actual_value = 0;
    int16_t torque_actual_value = 0;

    uint16_t control_word;
    int8_t mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    int32_t target_position = 0;
    int32_t target_velocity = 0;
    int16_t target_torque = 0;

private:
    uint16_t current_status = Object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON;
};

#endif // EC_SLAVE_MOTOR_SALVE_H
