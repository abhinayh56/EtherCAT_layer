#include <iostream>
#include "EC_master/Ec_master.h"


Ec_master ec_master;

int main()
{
    ec_master.start();

    std::cout << "Hi code" << std::endl;

    return 0;
}
