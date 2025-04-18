#ifndef EC_CIA_402_H
#define EC_CIA_402_H

#include <stdint.h>

namespace CiA_402
{
    enum Drive_fsm : uint16_t
    {
        NOT_READY_TO_SWITCH_ON = 0,
        SWITCHED_ON_DISABLED = 1,
        READY_TO_SWITCH_ON = 2,
        SWITCHED_ON = 3,
        OPERATION_ENABLED = 4,
        QUICK_STOP_ACTIVE = 5,
        FAULT_REACTION_ACTIVE = 6,
        FAULT = 7
    };

    namespace Pdo_object
    {
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

        namespace Modes_of_operation
        {
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
}

class Ec_cia_402
{
public:
    Ec_cia_402()
    {
    }
    ~Ec_cia_402()
    {
    }

    uint16_t check_status(uint16_t status_word)
    {
        if ((status_word & 0b1001111) == CiA_402::Pdo_object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON;
        }
        else if ((status_word & 0b1001111) == CiA_402::Pdo_object::Status_word::Bit_flags::SWITCH_ON_DISABLED)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::SWITCH_ON_DISABLED;
        }
        else if ((status_word & 0b1101111) == CiA_402::Pdo_object::Status_word::Bit_flags::READY_TO_SWITCH_ON)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::READY_TO_SWITCH_ON;
        }
        else if ((status_word & 0b1101111) == CiA_402::Pdo_object::Status_word::Bit_flags::SWITCHED_ON)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::SWITCHED_ON;
        }
        else if ((status_word & 0b1101111) == CiA_402::Pdo_object::Status_word::Bit_flags::OPERATION_ENABLED)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::OPERATION_ENABLED;
        }
        else if ((status_word & 0b1101111) == CiA_402::Pdo_object::Status_word::Bit_flags::QUICK_STOP_ACTIVE)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::QUICK_STOP_ACTIVE;
        }
        else if ((status_word & 0b1001111) == CiA_402::Pdo_object::Status_word::Bit_flags::FAULT_REACTION_ACTIVE)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::FAULT_REACTION_ACTIVE;
        }
        else if ((status_word & 0b1001111) == CiA_402::Pdo_object::Status_word::Bit_flags::FAULT)
        {
            current_status = CiA_402::Pdo_object::Status_word::Bit_flags::FAULT;
        }
    }

    void clear_fault()
    {
    }

private:
    uint16_t status_word;
    int8_t mode_of_operation_display;
    int32_t position_actual_value = 0;
    int32_t velocity_actual_value = 0;
    int16_t torque_actual_value = 0;

    uint16_t control_word;
    int8_t mode_of_operation = CiA_402::Pdo_object::Modes_of_operation::Bit_flags::CYCLIC_SYNC_TORQUE_MODE;
    int32_t target_position = 0;
    int32_t target_velocity = 0;
    int16_t target_torque = 0;

    uint16_t current_status = CiA_402::Pdo_object::Status_word::Bit_flags::NOT_READY_TO_SWITCH_ON;
};

#endif // EC_CIA_402_H
