#ifndef EC_SLAVE_1_H
#define EC_SLAVE_1_H

#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_1 : public Ec_slave_base
{
private:
    ec_pdo_entry_info_t slave_1_pdo_entries[8] = {
        {0x7000, 0x01, 1}, /* Output */
        {0x7010, 0x01, 1}, /* Output */
        {0x7020, 0x01, 1}, /* Output */
        {0x7030, 0x01, 1}, /* Output */
        {0x7040, 0x01, 1}, /* Output */
        {0x7050, 0x01, 1}, /* Output */
        {0x7060, 0x01, 1}, /* Output */
        {0x7070, 0x01, 1}, /* Output */
    };

    ec_pdo_info_t slave_1_pdos[8] = {
        {0x1600, 1, slave_1_pdo_entries + 0}, /* Channel 1 */
        {0x1601, 1, slave_1_pdo_entries + 1}, /* Channel 2 */
        {0x1602, 1, slave_1_pdo_entries + 2}, /* Channel 3 */
        {0x1603, 1, slave_1_pdo_entries + 3}, /* Channel 4 */
        {0x1604, 1, slave_1_pdo_entries + 4}, /* Channel 5 */
        {0x1605, 1, slave_1_pdo_entries + 5}, /* Channel 6 */
        {0x1606, 1, slave_1_pdo_entries + 6}, /* Channel 7 */
        {0x1607, 1, slave_1_pdo_entries + 7}, /* Channel 8 */
    };

    ec_sync_info_t slave_1_syncs[2] = {
        {0, EC_DIR_OUTPUT, 8, slave_1_pdos + 0, EC_WD_ENABLE},
        {0xff}
    };
    
    unsigned int off_1;
    unsigned int off_2;
    unsigned int off_3;
    unsigned int off_4;
    unsigned int off_5;
    unsigned int off_6;
    unsigned int off_7;
    unsigned int off_8;

    ec_pdo_entry_reg_t domain_regs[9] = {
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7000, 0x01, &off_1},
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7010, 0x01, &off_2},
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7020, 0x01, &off_3},
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7030, 0x01, &off_4},
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7040, 0x01, &off_5},
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7050, 0x01, &off_6},
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7060, 0x01, &off_7},
        {slave_info.alias, slave_info.position, slave_info.vendor_id, slave_info.product_code, 0x7070, 0x01, &off_8},
        {}};

public:
    Ec_slave_1(uint16_t slave_address_, const std::string &slave_name_)
    {
        slave_address = slave_address_;
        slave_name = slave_name_;
    }

    ~Ec_slave_1() {}

    virtual void set_info()
    {
        slave_info.alias = 0;
        slave_info.position = 1;
        slave_info.vendor_id = 0x00000002;
        slave_info.product_code = 0x07d83052;

        slave_info.slave_pdo_entries = slave_1_pdo_entries;
        slave_info.slave_pdos = slave_1_pdos;
        slave_info.slave_syncs = slave_1_syncs;
    }

    virtual void set_pdo()
    {
        domain_i_regs = domain_regs;
    }

    virtual void monitor_status() {}
    virtual void transfer_tx_pdo() {}
    virtual void transfer_rx_pdo() {}
    virtual void process_tx_pdo() {}
    virtual void process_rx_pdo() {}
    virtual void config_data_transfer() {}
    virtual void publish_data() {}
    virtual void subscribe_data() {}
};

#endif // EC_SLAVE_1_H
