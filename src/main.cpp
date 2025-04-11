#include <unistd.h>
#include <iostream>
#include "Ec_master/Ec_master.h"
#include  "Ec_slave/Ec_slave_1.h"

Ec_master ec_master;

Ec_slave_1 ec_slave_1(1001, "SLAVE_1_ADDR");

int main()
{
    ec_master.add_slave(&ec_slave_1);

    ec_master.start();

    // ec_master.config();

    // while (ec_master.is_running())
    // {
    //     ec_master.cyclic_task();
    //     usleep(4000);
    // }

    return 0;
}
