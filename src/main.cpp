#include <unistd.h>
#include <iostream>
#include "Ec_app/Ec_master.h"
#include "Ec_app/Ec_app.h"
#include "Ec_slave/Ec_slave_ek_1100.h"
#include "Ec_slave/Ec_slave_ek_1122.h"
#include "Ec_slave/Ec_slave_el_2008.h"
#include "Ec_slave/Ec_slave_el_1008.h"
#include "Ec_slave/Ec_slave_rfid.h"
#include "Ec_slave/Ec_slave_mact.h"
#include "Ec_slave/Ec_slave_ingenia.h"

int main()
{
    Ec_master ec_master("EC_MASTER");

    Ec_app ec_app("EC_APP");

    Ec_slave_ek_1100 ek_1100(0, "EK_1100");
    Ec_slave_el_2008 el_2008(1, "EL_2008");
    Ec_slave_el_1008 el_1008(2, "EL_1008");
    Ec_slave_ek_1122 ek_1122_1(3, "EK_1122_1");
    Ec_slave_ek_1122 ek_1122_2(4, "EK_1122_2");
    Ec_slave_ek_1122 ek_1122_3(5, "EK_1122_3");
    Ec_slave_ingenia ingenia(6, "INGENIA");
    Ec_slave_ek_1122 ek_1122_4(7, "EK_1122_4");
    Ec_slave_rfid rfid(8, "RFID_1");
    Ec_slave_mact mact_1(9, "MACT_1");
    Ec_slave_mact mact_2(10, "MACT_2");
    Ec_slave_mact mact_3(11, "MACT_3");
    Ec_slave_mact mact_4(12, "MACT_4");
    Ec_slave_rfid rfid_2(13, "RFID_2");
    Ec_slave_mact mact_5(14, "MACT_5");
    Ec_slave_mact mact_6(15, "MACT_6");
    Ec_slave_mact mact_7(16, "MACT_7");
    Ec_slave_mact mact_8(17, "MACT_8");

    ec_app.add_slave(&ek_1100);
    ec_app.add_slave(&el_2008);
    ec_app.add_slave(&el_1008);
    ec_app.add_slave(&ek_1122_1);
    ec_app.add_slave(&ek_1122_2);
    ec_app.add_slave(&ek_1122_3);
    ec_app.add_slave(&ingenia);
    ec_app.add_slave(&ek_1122_4);
    ec_app.add_slave(&rfid);
    ec_app.add_slave(&mact_1);
    ec_app.add_slave(&mact_2);
    ec_app.add_slave(&mact_3);
    ec_app.add_slave(&mact_4);
    ec_app.add_slave(&rfid_2);
    ec_app.add_slave(&mact_5);
    ec_app.add_slave(&mact_6);
    ec_app.add_slave(&mact_7);
    ec_app.add_slave(&mact_8);

    usleep(2000000);

    uint64_t max_retries = 100000;
    uint64_t num_retries = 0;
    bool run_ethercat_layer = true;

    while (run_ethercat_layer && (num_retries < max_retries))
    {
        LOG_CONSOLE("\n\n-----------------------\nSTARTING ETHERCAT LAYER\n-----------------------\n\n", 1);
        uint16_t ret_val = Ec_callback_status::SUCCESS;

        if (!ec_master.is_running())
        {
            ec_master.start();
            usleep(5000000);

            ret_val |= ec_app.start();
            if (ret_val == Ec_callback_status::FAILURE)
            {
                LOG_CONSOLE_SOURCE_ERROR("MAIN", "Failed to start EC_APP", 1);
            }
            else
            {
                ret_val |= ec_app.config();
                if (ret_val == Ec_callback_status::FAILURE)
                {
                    LOG_CONSOLE_SOURCE_ERROR("MAIN", "Failed to perform configuration of EC_APP", 1);
                }
                else
                {
                    num_retries = 0;
                    LOG_CONSOLE_SOURCE_INFO("MAIN", "Cyclic task started", 1);
                    while (ret_val == Ec_callback_status::SUCCESS)
                    {
                        ret_val |= ec_app.cyclic_task();
                        if (ret_val == Ec_callback_status::FAILURE)
                        {
                            LOG_CONSOLE_SOURCE_ERROR("MAIN", "Failed to perform cyclic task of EC_APP", 1);
                            LOG_CONSOLE_SOURCE_ERROR("MAIN", "Cyclic task stopped", 1);
                            break;
                        }

                        usleep(1000000 / 1250);
                    }
                }

                ret_val = ec_app.stop();
                if (ret_val == Ec_callback_status::FAILURE)
                {
                    LOG_CONSOLE_SOURCE_ERROR("MAIN", "Failed to stop EC_APP", 1);
                }
            }

            ec_master.stop();
        }

        num_retries++;
        run_ethercat_layer = ec_app.get_run_status();
        std::cout << "num_retries: " << num_retries << std::endl;
        if ((run_ethercat_layer == false) || (num_retries >= max_retries))
        {
            break;
        }
        else
        {
            LOG_CONSOLE_SOURCE_INFO("MAIN", "Retrying to initiate the main program...", 1);
            usleep(500000);
        }
    }

    return 0;
}
