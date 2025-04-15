#ifndef EC_OBJECTS_H
#define EC_OBJECTS_H

#include <stdint.h>

namespace Object
{
    namespace Control_word
    {
        uint16_t index = 0x1600;
        uint8_t sub_index = 0x01;

        enum Bit_flags : uint16_t
        {
            
        };
    }
}

#endif // EC_OBJECTS_H