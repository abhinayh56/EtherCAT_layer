#ifndef EC_APP_H
#define EC_APP_H

#include <ecrt.h>
#include <string>
#include <vector>
#include <iostream>
#include "../Ec_slave_base/Ec_slave_base.h"

#define CYCLIC_SLAVE_CALL_PARALLEL
// #define CYCLIC_SLAVE_CALL_SEQUENTIAL

class Ec_app
{
public:
    Ec_app(const std::string &master_ns_);
    ~Ec_app();

    void add_slave(Ec_slave_base *new_slave);
    bool start();
    bool restart();
    bool stop();
    void config();
    void cyclic_task();
    bool is_running();
    uint16_t get_num_slaves();
    void monitor();
    
private:
    std::string master_ns;
    ec_master_t *master = nullptr;
    ec_master_state_t master_state = {};

    ec_domain_t *domain_i = nullptr;
    ec_domain_state_t domain_i_state = {};

    uint8_t *domain_i_pd = nullptr;
    bool run = false;

    uint16_t num_slaves = 0;
    std::vector<Ec_slave_base *> slave_base_arr;

    bool create_instance();
    bool deactivate();
    void config_slaves_data_transfer();
    bool create_domain();
    void set_slaves_info_from_eni();
    void config_slaves();
    void register_slaves_pdo_to_domain();
    bool activate();
    bool get_domain_process_data();
    void set_domain_process_data();

    void monitor_domain_i_state();
    void monitor_master_state();
    void monitor_slave_state();

    void monitor_status();
    void transfer_tx_pdo();
    void process_tx_pdo();
    void publish_data();
    void subscribe_data();
    void main_process();
    void process_rx_pdo();
    void transfer_rx_pdo();
};

#endif // EC_APP_H
