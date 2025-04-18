#include "Ec_objects.h"

namespace Object
{
    namespace Control_word
    {
        uint16_t index = 0x1600;
        uint8_t sub_index = 0x01;
        uint16_t pdo_index = 0x6040;
        uint8_t pdo_sub_index = 0x00;
    }

    namespace Status_word
    {
        uint16_t index = 0x1A00;
        uint8_t sub_index = 0x01;
        uint16_t pdo_index = 0x6041;
        uint8_t pdo_sub_index = 0x00;
    }

    namespace Modes_of_operation
    {
        uint16_t index = 0x1600;
        uint8_t sub_index = 0x02;
        uint16_t pdo_index = 0x6060;
        uint8_t pdo_sub_index = 0x00;
    }

    namespace Modes_of_operation_display
    {
        uint16_t index = 0x1A00;
        uint8_t sub_index = 0x02;
        uint16_t pdo_index = 0x6061;
        uint8_t pdo_sub_index = 0x00;
    }
}
