#ifndef EC_SLAVE_MOTOR_SALVE_H
#define EC_SLAVE_MOTOR_SALVE_H

#include <cmath>
#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"

namespace Motor_drive
{
    enum class OP_status
    {
        ENABLE = 0,
        DISABLE = 1
    };

    enum class Mode
    {
        POSITION = 0,
        VELOCITY = 1,
        TORQUE = 2
    };

    struct Mode_supported
    {
        bool position = false;
        bool velocity = false;
        bool torque = false;
    };

    enum class Fault
    {
        OVER_CURRENT = 0,
        OVER_TEMPERATURE = 1,
        OVER_VOLTAGE = 2,
        UNKOWN = 3,
        NO_FAULT = 4
    };

    struct Pose
    {
        double position = 0;
        double velocity = 0;
        double torque = 0;
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

    virtual void init();
    virtual void e_stop();
    virtual void enable();
    virtual void disable();
    virtual void set_operating_mode(Motor_drive::Mode mode_);
    virtual void check_fault();
    virtual void clear_fault();
    virtual void set_position(double th_0);
    virtual void set_velocity(double v_0);
    virtual void set_torque(double tau_0);

protected:
    Motor_drive::OP_status op_status = Motor_drive::OP_status::DISABLE;
    Motor_drive::Mode mode = Motor_drive::Mode::TORQUE;
    Motor_drive::Mode_supported mode_supported;
    Motor_drive::Fault fault = Motor_drive::Fault::NO_FAULT;
    bool e_stop_flag = false;

    Motor_drive::Pose pose_current;
    Motor_drive::Pose pose_setpoint;
};

#endif // EC_SLAVE_MOTOR_SALVE_H
