#include <unistd.h>
#include <iostream>
#include "Ec_master/Ec_master.h"

Ec_master ec_master;

// int main()
// {
//     ec_master.start();

//     ec_master.config();

//     while (ec_master.is_running())
//     {
//         ec_master.cyclic_task();
//         usleep(4000);
//     }

//     ec_master.stop();

//     return 0;
// }


int main()
{
    ec_master.start();
    ec_master.config();

    ec_master.stop();

    return 0;
}
