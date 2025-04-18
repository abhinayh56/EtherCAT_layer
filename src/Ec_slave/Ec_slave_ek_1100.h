#ifndef EC_SLAVE_EK_1100_H
#define EC_SLAVE_EK_1100_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_ek_1100 : public Ec_slave_base
{
public:
    Ec_slave_ek_1100(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_ek_1100();

    virtual void set_info();
    virtual void set_pdo();
    virtual void monitor_status();
    virtual void transfer_tx_pdo();
    virtual void transfer_rx_pdo();
    virtual void process_tx_pdo();
    virtual void process_rx_pdo();
    virtual void config_data_transfer();
    virtual void publish_data();
    virtual void subscribe_data();
    virtual void main_process();

private:
    uint16_t alias = 0;
    uint16_t position = 100;
    uint32_t vendor_id = 0x00000002;
    uint32_t product_code = 0x044c2c52;

    ec_sync_info_t slave_2_syncs[1] = {
        {0xff}};

    unsigned int off_1;
    ec_pdo_entry_reg_t domain_regs[1] = {
        {}};
};

#endif // EC_SLAVE_EK_1100_H
