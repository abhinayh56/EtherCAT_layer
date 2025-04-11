#include <unistd.h>
#include <iostream>
#include "Ec_master/Ec_master.h"
#include  "Ec_slave/Ec_slave_1.h"
#include  "Ec_slave/Ec_slave_2.h"
#include  "Ec_slave/Ec_slave_3.h"

Ec_master ec_master;

Ec_slave_1 el_2008(1, "EL_2008");
Ec_slave_2 el_1008(2, "EL_1008");
Ec_slave_3 rfid(3, "RFID");

int main()
{
    ec_master.add_slave(&el_2008);
    ec_master.add_slave(&el_1008);
    ec_master.add_slave(&rfid);

    ec_master.start();

    ec_master.config();

    while (ec_master.is_running())
    {
        ec_master.cyclic_task();
        usleep(4000);
    }

    return 0;
}
