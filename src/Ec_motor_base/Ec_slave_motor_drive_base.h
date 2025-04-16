#ifndef EC_SLAVE_MOTOR_SALVE_H
#define EC_SLAVE_MOTOR_SALVE_H

#include <cmath>
#include <stdint.h>
#include "../Ec_slave_base/Ec_slave_base.h"
#include "../Ec_utils/Ec_objects.h"

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
}

namespace Pdo_object
{
    namespace Control_word
    {
        uint16_t index = 0x1600;
        uint8_t sub_index = 0x01;
        uint16_t pdo_index = 0x6040;
        uint8_t pdo_sub_index = 0x00;

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
        uint16_t index = 0x1A00;
        uint8_t sub_index = 0x01;
        uint16_t pdo_index = 0x6041;
        uint8_t pdo_sub_index = 0x00;

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

    namespace Modes_of_operation
    {
        uint16_t index = 0x1600;
        uint8_t sub_index = 0x02;
        uint16_t pdo_index = 0x6060;
        uint8_t pdo_sub_index = 0x00;

        enum Bit_flags : int8_t
        {
            OPEN_LOOP_FIELD_MODE = -3,
            DIAGNOSTICS_MODE = -2,
            COGGING_COMPENSATION_RECORDING_MODE = -1,
            PROFILE_POSITION_MODE = 1,
            PROFILE_VELOCITY_MODE = 3,
            TORQUE_PROFILE_MODE = 4,
            HOMING_MODE = 6,
            CYCLIC_SYNC_POSITION_MODE = 8,
            CYCLIC_SYNC_VELOCITY_MODE = 9,
            CYCLIC_SYNC_TORQUE_MODE = 10
        };
    }

    namespace Modes_of_operation_display
    {
        uint16_t index = 0x1A00;
        uint8_t sub_index = 0x02;
        uint16_t pdo_index = 0x6061;
        uint8_t pdo_sub_index = 0x00;

        enum Bit_flags : int8_t
        {
            OPEN_LOOP_FIELD_MODE = -3,
            DIAGNOSTICS_MODE = -2,
            COGGING_COMPENSATION_RECORDING_MODE = -1,
            NO_MODE_SELECTED = 0,
            PROFILE_POSITION_MODE = 1,
            PROFILE_VELOCITY_MODE = 3,
            TORQUE_PROFILE_MODE = 4,
            HOMING_MODE = 6,
            CYCLIC_SYNC_POSITION_MODE = 8,
            CYCLIC_SYNC_VELOCITY_MODE = 9,
            CYCLIC_SYNC_TORQUE_MODE = 10
        };
    }
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
    virtual void stop();
    virtual void enable();
    virtual void disable();
    virtual void set_operating_mode(Motor_drive::Mode mode_);
    virtual void check_fault();
    virtual void clear_fault();
    virtual void set_position(double th_0);
    virtual void set_velocity(double v_0);
    virtual void set_torque(double tau_0);
    virtual void sync_position();
    virtual void sync_velocity();
    virtual void sync_torque();

protected:
    Motor_drive::OP_status op_status = Motor_drive::OP_status::DISABLE;
    Motor_drive::Mode mode = Motor_drive::Mode::TORQUE;
    Motor_drive::Mode_supported mode_supported;
    Motor_drive::Fault fault = Motor_drive::Fault::NO_FAULT;
    bool e_stop_flag = false;

    uint16_t status_word;
    int8_t mode_of_operation_display;
    int32_t position_actual_value = 0;
    int32_t velocity_actual_value = 0;
    int16_t torque_actual_value = 0;

    uint16_t control_word;
    int8_t mode_of_operation;
    int32_t target_position = 0;
    int32_t target_velocity = 0;
    int16_t target_torque = 0;

    double position_actual = 0;
    double velocity_actual = 0;
    double torque_actual = 0;

    double position_command = 0;
    double velocity_command = 0;
    double torque_command = 0;
};

#endif // EC_SLAVE_MOTOR_SALVE_H
