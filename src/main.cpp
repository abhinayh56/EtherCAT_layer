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

    Ec_master ec_master("Master");

    Ec_slave_ek_1100 ek_1100(0, "EK_1100");
    Ec_slave_el_2008 el_2008(1, "EL_2008");
    Ec_slave_el_1008 el_1008(2, "EL_1008");
    Ec_slave_ek_1122 ek_1122_1(3, "EK_1122_1");
    Ec_slave_ek_1122 ek_1122_2(4, "EK_1122_2");
    Ec_slave_ek_1122 ek_1122_3(5, "EK_1122_3");
    Ec_slave_ingenia ingenia(6, "INGENIA");
    Ec_slave_ek_1122 ek_1122_4(7, "EK_1122_4");
    Ec_slave_rfid rfid(8, "RFID");
    Ec_slave_mact mact_1(9, "MACT_1");
    Ec_slave_mact mact_2(10, "MACT_2");
    Ec_slave_mact mact_3(11, "MACT_3");
    Ec_slave_mact mact_4(12, "MACT_4");
    Ec_slave_rfid rfid_2(13, "RFID");
    Ec_slave_mact mact_5(14, "MACT_4");
    Ec_slave_mact mact_6(15, "MACT_4");
    Ec_slave_mact mact_7(16, "MACT_4");
    Ec_slave_mact mact_8(17, "MACT_4");

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
    ec_master.add_slave(&rfid_2);
    ec_master.add_slave(&mact_5);
    ec_master.add_slave(&mact_6);
    ec_master.add_slave(&mact_7);
    ec_master.add_slave(&mact_8);

    ec_master.start();

    ec_master.config();

    while (ec_master.is_running())
    {
        auto start = high_resolution_clock::now();

        ec_master.cyclic_task();
        

        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);
        
        // std::cout << "Num_slaves: " << ec_master.get_num_slaves() << std::endl;
        // std::cout <<"took " << duration.count() << " µs" << std::endl;

        usleep(1000000/1000);
    }

    return 0;
}
