#include <iostream>
#include "Ec_master/Ec_master.h"


Ec_master ec_master;

int main()
{
    ec_master.start();
    ec_master.stop();
    ec_master.config();

    std::cout << "Hi code" << std::endl;

    return 0;
}
