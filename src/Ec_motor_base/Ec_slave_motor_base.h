#ifndef EC_SLAVE_MOTOR_SALVE_H
#define EC_SLAVE_MOTOR_SALVE_H

#include <cmath>
#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"

namespace Motor
{
    enum class State
    {
        ENABLE = 0,
        DISABLE = 1
    };

    enum class Mode
    {
        POSITION = 0,
        VELOCITY = 1,
        TORQUE = 0
    };

    enum class Fault
    {
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
    Motor::State state = Motor::State::DISABLE;
    Motor::Mode mode = Motor::Mode::TORQUE;
    bool e_stop_flag = false;
    uint16_t fault_type;
};

#endif // EC_SLAVE_MOTOR_SALVE_H
