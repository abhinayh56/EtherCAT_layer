#ifndef EC_SLAVE_1_H
#define EC_SLAVE_1_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_1 : public Ec_slave_base
{
public:
    Ec_slave_1(uint16_t slave_address_, const std::string &slave_name_)
    {
        slave_address = slave_address_;
        slave_name = slave_name_;
    }

    ~Ec_slave_1() {}
};

#endif // EC_SLAVE_1_H