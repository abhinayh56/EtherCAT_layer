#include <unistd.h>
#include <iostream>
#include "Ec_master/Ec_master.h"
#include  "Ec_slave/Ec_slave_el_2008.h"
#include  "Ec_slave/Ec_slave_el_1008.h"
#include  "Ec_slave/Ec_slave_rfid.h"
#include  "Ec_slave/Ec_slave_mact.h"
#include  "Ec_slave/Ec_slave_5.h"
#include  "Ec_slave/Ec_slave_6.h"
#include  "Ec_slave/Ec_slave_7.h"

Ec_master ec_master;

Ec_slave_el_2008 el_2008(1, "EL_2008");
Ec_slave_el_1008 el_1008(2, "EL_1008");
Ec_slave_rfid rfid(7, "RFID");
// Ec_slave_mact mact_1(4, "MACT_1");
// Ec_slave_5 mact_2(5, "MACT_2");
// Ec_slave_6 mact_3(6, "MACT_3");
// Ec_slave_7 mact_4(7, "MACT_4");

int main()
{
    ec_master.add_slave(&el_2008);
    ec_master.add_slave(&el_1008);
    ec_master.add_slave(&rfid);
    // ec_master.add_slave(&mact_1);
    // ec_master.add_slave(&mact_2);
    // ec_master.add_slave(&mact_3);
    // ec_master.add_slave(&mact_4);

    ec_master.start();

    ec_master.config();

    while (ec_master.is_running())
    {
        ec_master.cyclic_task();
        usleep(4000);
    }

    return 0;
}
