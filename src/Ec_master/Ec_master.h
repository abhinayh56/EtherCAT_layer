#ifndef EC_MASTER_H
#define EC_MASTER_H

#include <ecrt.h>
#include <vector>
#include <iostream>
#include "../Ec_slave_base/Ec_slave_base.h"
#include "../Ec_logger/Ec_logger_console/Ec_logger_console.h"

#define CYCLIC_SLAVE_CALL_PARALLEL
// #define CYCLIC_SLAVE_CALL_SEQUENTIAL

class Ec_master
{
public:
    Ec_master();
    ~Ec_master();

    void add_slave(Ec_slave_base *new_slave);
    bool start();
    bool stop();
    void config();
    void cyclic_task();
    bool is_running();
    uint16_t get_num_slaves();

private:
    ec_master_t *master = nullptr;
    ec_master_state_t master_state = {};

    ec_domain_t *domain_i = nullptr;
    ec_domain_state_t domain_i_state = {};

    uint8_t *domain_i_pd = nullptr;
    bool run = false;

    uint16_t num_slaves = 0;
    std::vector<Ec_slave_base *> slave_base_arr;

    void config_slaves_data_transfer();
    bool create_domain();
    void set_slave_info();
    void config_slaves();
    void register_slaves_pdo_to_domain();
    bool activate();
    bool get_domain_process_data();
    void set_domain_process_data();

    void monitor_status();
    void transfer_tx_pdo();
    void process_tx_pdo();
    void publish_data();
    void subscribe_data();
    void main_process();
    void process_rx_pdo();
    void transfer_rx_pdo();
};

#endif // EC_MASTER_H