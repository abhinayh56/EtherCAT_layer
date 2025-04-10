#include <ecrt.h>
#include <vector>
#include <iostream>

class Ec_master
{
public:
    Ec_master();
    ~Ec_master();

    // void add_slave(Ec_slave_base *new_slave);
    int start();
    // void config();
    // void cyclic_task();
    // bool is_running();

private:
    ec_master_t *master = nullptr;
    ec_master_state_t master_state = {};

    ec_domain_t *domain_i = nullptr;
    ec_domain_state_t domain_i_state = {};

    uint8_t *domain_i_pd = nullptr;
    bool run = false;

    unsigned int num_slaves = 0;
    // std::vector<Ec_slave_base *> slave_base_arr;
};
