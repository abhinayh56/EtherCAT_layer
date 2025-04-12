#ifndef EC_SLAVE_BASE_H
#define EC_SLAVE_BASE_H

#include <ecrt.h>
#include <stdint.h>
#include "../Ec_utils/Ec_utils.h"
#include "../Common/Data_transfer.h"
#include "../Ec_logger/Ec_logger_console/Ec_logger_console.h"

class Ec_slave_base : public Data_transfer
{
public:
    Ec_slave_base();
    ~Ec_slave_base();

    void set_slave_name(const std::string &slave_name_);
    const std::string &get_slave_name();
    void set_slave_address(uint16_t slave_address_);
    uint16_t get_slave_address();

    virtual void set_info();
    void config_slave(ec_master_t *master);
    
    virtual void set_pdo();
    void register_pdo_to_domain(ec_domain_t *domain_i);
    
    void set_domain(uint8_t *domain_i_pd_);

    virtual void monitor_status();
    virtual void transfer_tx_pdo();
    virtual void transfer_rx_pdo();
    virtual void process_tx_pdo();
    virtual void process_rx_pdo();

    virtual void config_data_transfer();
    virtual void publish_data();
    virtual void subscribe_data();

protected:
    std::string slave_name;
    uint16_t slave_address;
    Slave_info slave_info;

    ec_slave_config_t *sc;
    ec_slave_config_state_t sc_state;
    uint8_t *domain_i_pd = NULL;

    ec_pdo_entry_reg_t *domain_i_regs;
};

#endif // EC_SLAVE_BASE_H
