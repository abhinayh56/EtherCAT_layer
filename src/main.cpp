#include <iostream>
#include "Ec_master/Ec_master.h"
#include "Ec_slave/Ec_slave_base.h"

Ec_master ec_master;

Ec_slave_base ec_slave_base;

int main()
{
    ec_master.start();
    ec_master.stop();
    ec_master.config();

    std::cout << "Hi code" << std::endl;

    ec_slave_base.set_slave_address(12345);
    std::cout << "slave_addr: " << ec_slave_base.get_slave_address();

    return 0;
}
