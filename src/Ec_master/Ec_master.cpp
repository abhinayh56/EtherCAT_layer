#include "Ec_master.h"

Ec_master::Ec_master()
{
}

Ec_master::~Ec_master()
{
}

int Ec_master::start()
{
    master = ecrt_request_master(0);
    if (!master)
    {
        return -1;
    }
    else
    {
        std::cout << "Master handle: " << master << std::endl;
        return 0;
    }
}