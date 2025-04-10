#include <iostream>
#include "ecrt.h"

static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};
static ec_domain_t *domain1 = NULL;
static ec_domain_state_t domain1_state = {};

int main()
{
    master = ecrt_request_master(0);
    if (!master)
    {
        return -1;
    }
    else
    {
        std::cout << "Master handle: " << master << std::endl;
    }

    std::cout << "Hi code" << std::endl;

    return 0;
}