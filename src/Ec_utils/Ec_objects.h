#ifndef EC_OBJECTS_H
#define EC_OBJECTS_H

#include <stdint.h>

namespace Object
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

#endif // EC_OBJECTS_H
