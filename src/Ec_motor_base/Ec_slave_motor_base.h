#ifndef EC_SLAVE_MOTOR_SALVE_H
#define EC_SLAVE_MOTOR_SALVE_H

#include <cmath>
#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"

namespace Motor
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

class Ec_slave_motor_base : public Ec_slave_base
{
public:
    Ec_slave_motor_base();
    ~Ec_slave_motor_base();

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

    void init();
    void e_stop();
    void enable();
    void disable();
    void set_operating_mode(Motor::Mode mode_);
    void check_fault();
    void clear_fault();
    void set_position(double th_0);
    void set_velocity(double v_0);
    void set_torque(double tau_0);

protected:
    Motor::OP_status state = Motor::OP_status::DISABLE;
    Motor::Mode mode = Motor::Mode::TORQUE;
    Motor::Mode_supported mode_supported;
    Motor::Fault fault = Motor::Fault::NO_FAULT;
    bool e_stop_flag = false;

    Motor::Pose pose_current;
    Motor::Pose pose_setpoint;
};

#endif // EC_SLAVE_MOTOR_SALVE_H
