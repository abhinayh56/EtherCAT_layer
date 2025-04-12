#ifndef EC_SLAVE_2_H
#define EC_SLAVE_2_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_2 : public Ec_slave_base
{
public:
    Ec_slave_2(uint16_t slave_address_, const std::string &slave_name_)
    {
        slave_address = slave_address_;
        slave_name = slave_name_;
    }

    ~Ec_slave_2() {}

    virtual void set_info()
    {
        slave_info.alias = alias;
        slave_info.position = position;
        slave_info.vendor_id = vendor_id;
        slave_info.product_code = product_code;

        slave_info.slave_pdo_entries = slave_2_pdo_entries;
        slave_info.slave_pdos = slave_2_pdos;
        slave_info.slave_syncs = slave_2_syncs;
    }

    virtual void set_pdo()
    {
        domain_i_regs = domain_regs;
    }

    virtual void monitor_status() {}
    
    virtual void transfer_tx_pdo()
    {
        uint16_t dig_input = EC_READ_U8(domain_i_pd + off_1);
        // std::cout << "dig_input: " << dig_input <<  ",     |               ";
    }

    virtual void transfer_rx_pdo() {}
    virtual void process_tx_pdo() {}
    virtual void process_rx_pdo() {}
    virtual void config_data_transfer() {}
    virtual void publish_data() {}
    virtual void subscribe_data() {}

private:
    uint16_t alias = 0;
    uint16_t position = 2;
    uint32_t vendor_id = 0x00000002;
    uint32_t product_code = 0x03f03052;

    ec_pdo_entry_info_t slave_2_pdo_entries[8] = {
        {0x6000, 0x01, 1}, /* Input */
        {0x6010, 0x01, 1}, /* Input */
        {0x6020, 0x01, 1}, /* Input */
        {0x6030, 0x01, 1}, /* Input */
        {0x6040, 0x01, 1}, /* Input */
        {0x6050, 0x01, 1}, /* Input */
        {0x6060, 0x01, 1}, /* Input */
        {0x6070, 0x01, 1}, /* Input */
    };

    ec_pdo_info_t slave_2_pdos[8] = {
        {0x1a00, 1, slave_2_pdo_entries + 0}, /* Channel 1 */
        {0x1a01, 1, slave_2_pdo_entries + 1}, /* Channel 2 */
        {0x1a02, 1, slave_2_pdo_entries + 2}, /* Channel 3 */
        {0x1a03, 1, slave_2_pdo_entries + 3}, /* Channel 4 */
        {0x1a04, 1, slave_2_pdo_entries + 4}, /* Channel 5 */
        {0x1a05, 1, slave_2_pdo_entries + 5}, /* Channel 6 */
        {0x1a06, 1, slave_2_pdo_entries + 6}, /* Channel 7 */
        {0x1a07, 1, slave_2_pdo_entries + 7}, /* Channel 8 */
    };
    
    ec_sync_info_t slave_2_syncs[2] = {
        {0, EC_DIR_INPUT, 8, slave_2_pdos + 0, EC_WD_DISABLE},
        {0xff}
    };

    unsigned int off_1;
    ec_pdo_entry_reg_t domain_regs[2] = {
        {0, 2, 0x00000002, 0x03f03052, 0x6000, 0x01, &off_1},
        {}};
};

#endif // EC_SLAVE_2_H
