#ifndef EC_SLAVE_MOTOR_DRIVE_BASE_H
#define EC_SLAVE_MOTOR_DRIVE_BASE_H

#include <cmath>
#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"
#include "../Ec_utils/Ec_objects.h"

namespace Motor_drive
{
    enum Enable_status : uint16_t
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

#ifndef AAAAA
#define AAAAA
namespace Control_word
{
    enum Bit_flags : uint16_t
    {
        SHUTDOWN = (1 << 2) | (1 << 1),
        SWITCH_ON = (1 << 2) | (1 << 1) | (1 << 0),
        SWITCH_ON_AND_ENABLE_OPERATION = (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0),
        DISABLE_VOLTAGE = 0x00,
        QUICK_STOP = 1 << 1,
        DISABLE_OPERATION = (1 << 2) | (1 << 1) | (1 << 0),
        ENABLE_OPERATION = (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0),
        FAULT_RESET = 1 << 7
    };
}

namespace Status_word
{
    enum Bit_flags : uint16_t
    {
        NOT_READY_TO_SWITCH_ON = 0x00,
        SWITCH_ON_DISABLED = 1 << 6,
        READY_TO_SWITCH_ON = (1 << 5) | (1 << 0),
        SWITCHED_ON = (1 << 5) | (1 << 1) | (1 << 0),
        OPERATION_ENABLED = (1 << 5) | (1 << 2) | (1 << 1) | (1 << 0),
        QUICK_STOP_ACTIVE = (1 << 2) | (1 << 1) | (1 << 0),
        FAULT_REACTION_ACTIVE = (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0),
        FAULT = 1 << 3,

        // Values provided beow are operation mode specific
        // CSP: Cyclic Synchronous Position
        // CSV: Cyclic Synchronous Velocity
        // CST: Cyclic Synchronous Torque
        // PPM: Profile Position Mode
        // PVM: Profile Velocity Mode
        // HM: Homing Mode
        CSP_FOLLOWING_ERROR_BIT = 1 << 13,
        CSP_TARGET_POSITION_IGNORED = 1 << 12,
        CSV_TARGET_VELOCITY_IGNORED = 1 << 12,
        CST_TARGET_TORQUE_IGNORED = 1 << 12,
        PPM_FOLLOWING_ERROR_BIT = 1 << 13,
        PPM_SET_PPINT_ACKNOWLEDGE_BIT = 1 << 12,
        PVM_SPEED_BIT = 1 << 12,
        HM_HOMING_ERROR_BIT = 1 << 13,
        HM_HOMING_ATTAINED_BIT = 1 << 12
    };
}
#endif

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

    void init();
    void stop();
    void enable();
    void disable();
    void set_operating_mode(Motor_drive::OP_mode mode_);
    void check_status();
    void clear_fault();
    void set_position(double position_command_);
    void set_velocity(double velocity_comman_);
    void set_torque(double torque_command_);
    double get_position();
    double get_velocity();
    double get_torque();
    void sync_position();
    void sync_velocity();
    void sync_torque();

protected:
    Motor_drive::Enable_status enable_status = Motor_drive::Enable_status::DISABLE;
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
    uint8_t mode_of_operation_display;
    int32_t position_actual_value = 0;
    int32_t velocity_actual_value = 0;
    int16_t torque_actual_value = 0;

    uint16_t control_word;
    uint8_t mode_of_operation = Object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    int32_t target_position = 0;
    int32_t target_velocity = 0;
    int16_t target_torque = 0;

private:
    uint16_t current_status = Object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON;
};

#endif // EC_SLAVE_MOTOR_DRIVE_BASE_H
