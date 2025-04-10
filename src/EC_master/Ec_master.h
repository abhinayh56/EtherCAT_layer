#include "ecrt.h"
#include <iostream>

class Ec_master
{
public:
    Ec_master();
    ~Ec_master();

    int start();

private:
    ec_master_t *master = nullptr;
    ec_master_state_t master_state = {};
    ec_domain_t *domain1 = nullptr;
    ec_domain_state_t domain1_state = {};
};
