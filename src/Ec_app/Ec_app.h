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

    uint16_t add_slave(Ec_slave_base *new_slave);
    uint16_t start();
    uint16_t stop();
    uint16_t config();
    uint16_t cyclic_task();
    uint16_t get_num_slaves();

private:
    std::string master_ns;
    ec_master_t *master = nullptr;
    ec_master_state_t master_state = {};

    ec_domain_t *domain_i = nullptr;
    ec_domain_state_t domain_i_state = {};

    uint8_t *domain_i_pd = nullptr;

    uint16_t num_slaves = 0;
    std::vector<Ec_slave_base *> slave_base_arr;

    bool all_slaves_operational = false;
    bool process_data_exchange_complete = false;
    uint32_t num_process_data_exchange_error = 0;

    uint16_t config_slaves_data_transfer();
    uint16_t create_domain();
    uint16_t set_slaves_info_from_eni();
    uint16_t config_slaves();
    uint16_t register_slaves_pdo_to_domain();
    uint16_t activate();
    uint16_t get_domain_process_data();
    uint16_t set_domain_process_data();

    uint16_t monitor_master_status();
    uint16_t monitor_domain_i_status();
    uint16_t monitor_slave_status();
    uint16_t is_process_data_exchange_complete();
    uint16_t is_all_slaves_operational();
    uint16_t get_num_process_data_exchange_error();

    uint16_t transfer_tx_pdo();
    uint16_t process_tx_pdo();
    uint16_t publish_data();
    uint16_t subscribe_data();
    uint16_t main_process();
    uint16_t process_rx_pdo();
    uint16_t transfer_rx_pdo();

    uint16_t reset();
    uint16_t init();
};

#endif // EC_APP_H
