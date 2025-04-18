#include <unistd.h>
#include <iostream>
#include "Ec_master/Ec_master.h"
#include "Ec_slave/Ec_slave_ek_1100.h"
#include "Ec_slave/Ec_slave_ek_1122.h"
#include "Ec_slave/Ec_slave_el_2008.h"
#include "Ec_slave/Ec_slave_el_1008.h"
#include "Ec_slave/Ec_slave_rfid.h"
#include "Ec_slave/Ec_slave_mact.h"
#include "Ec_slave/Ec_slave_ingenia.h"
#include <chrono>

int main()
{
    using namespace std::chrono;

    Ec_master ec_master;

    Ec_slave_ek_1100 ek_1100(0, "EK_1100");
    Ec_slave_ek_1122 ek_1122_1(3, "EK_1122_1");
    Ec_slave_ek_1122 ek_1122_2(4, "EK_1122_2");
    Ec_slave_ek_1122 ek_1122_3(5, "EK_1122_3");
    Ec_slave_ek_1122 ek_1122_4(6, "EK_1122_4");
    Ec_slave_el_2008 el_2008(1, "EL_2008");
    Ec_slave_el_1008 el_1008(2, "EL_1008");
    Ec_slave_rfid rfid(7, "RFID");
    Ec_slave_mact mact_1(8, "MACT_1");
    Ec_slave_mact mact_2(9, "MACT_2");
    Ec_slave_mact mact_3(10, "MACT_3");
    Ec_slave_mact mact_4(11, "MACT_4");
    Ec_slave_ingenia ingenia(12, "INGENIA");

    ec_master.add_slave(&ek_1100);
    ec_master.add_slave(&ek_1122_1);
    ec_master.add_slave(&ek_1122_2);
    ec_master.add_slave(&ek_1122_3);
    ec_master.add_slave(&ek_1122_4);
    ec_master.add_slave(&el_2008);
    ec_master.add_slave(&el_1008);
    ec_master.add_slave(&rfid);
    ec_master.add_slave(&mact_1);
    ec_master.add_slave(&mact_2);
    ec_master.add_slave(&mact_3);
    ec_master.add_slave(&mact_4);
    ec_master.add_slave(&ingenia);

    ec_master.start();

    ec_master.config();

    while (ec_master.is_running())
    {
        auto start = high_resolution_clock::now();

        ec_master.cyclic_task();
        

        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);

        std::cout <<"took " << duration.count() << " µs" << std::endl;

        usleep(1000000/500);
    }

    return 0;
}
