#ifndef EC_OBJECTS_H
#define EC_OBJECTS_H

#include <stdint.h>

namespace Object
{
    namespace Control_word
    {
        uint16_t index = 0x1600;
        uint8_t sub_index = 0x00;
        uint16_t pdo_index = 0x6040;
        uint8_t pdo_sub_index = 0x00;

        enum Bit_flags : uint16_t
        {
            SHUTDOWN = (1<<2) | (1<<1),
            SWITCH_ON = (1<<2) | (1<<1) | (1<<0),
            SWITCH_ON_ENABLE_OPERATION = (1<<3) | (1<<2) | (1<<1) | (1<<0),
            DISABLE_VOLTAGE = 0,
            QUICK_STOP = 0,
            DISABLE_OPERATION = 0,
            ENABLE_OPERATION = 0,
            FAULT_RESET = 0
        };
    }
}

#endif // EC_OBJECTS_H