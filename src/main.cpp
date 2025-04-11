#include <unistd.h>
#include <iostream>
#include "Ec_master/Ec_master.h"
#include  "Ec_slave/Ec_slave_1.h"
#include  "Ec_slave/Ec_slave_2.h"

Ec_master ec_master;

Ec_slave_1 el_2008(1, "SLAVE_1_ADDR");
Ec_slave_2 el_1008(2, "SLAVE_2_ADDR");

int main()
{
    ec_master.add_slave(&el_2008);
    ec_master.add_slave(&el_1008);

    ec_master.start();

    ec_master.config();

    // while (ec_master.is_running())
    // {
    //     ec_master.cyclic_task();
    //     usleep(4000);
    // }

    return 0;
}
