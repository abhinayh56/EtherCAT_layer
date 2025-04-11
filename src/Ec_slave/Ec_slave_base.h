#ifndef EC_SLAVE_BASE_H
#define EC_SLAVE_BASE_H

#include <stdint.h>
#include "../Ec_logger/Ec_logger_console/Ec_logger_console.h"

class Ec_slave_base
{
public:
    Ec_slave_base();
    ~Ec_slave_base();

    void set_slave_name(const std::string &slave_name_);
    const std::string &get_slave_name() const;
    void set_slave_address(uint16_t slave_address_);
    uint16_t get_slave_address();

protected:
    std::string slave_name;
    uint16_t slave_address;
};

#endif // EC_SLAVE_BASE_H
