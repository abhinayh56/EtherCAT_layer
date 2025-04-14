#ifndef EC_SLAVE_INGENIA_H
#define EC_SLAVE_INGENIA_H

#include <cmath>
#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_ingenia : public Ec_slave_base
{
public:
    Ec_slave_ingenia(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_ingenia();

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

private:
    uint16_t alias = 0;
    uint16_t position = 12;
    uint32_t vendor_id = 0x0000029c;
    uint32_t product_code = 0x03811002;

    ec_pdo_entry_info_t slave_12_pdo_entries[8] = {
        {0x6040, 0x00, 16},
        {0x607a, 0x00, 32},
        {0x60ff, 0x00, 32},
        {0x6060, 0x00, 8},
        {0x6041, 0x00, 16}, /* Status Word */
        {0x6064, 0x00, 32}, /* Actual position */
        {0x606c, 0x00, 32}, /* Actual velocity */
        {0x6061, 0x00, 8},  /* Operation mode display */
    };

    ec_pdo_info_t slave_12_pdos[2] = {
        {0x1600, 4, slave_12_pdo_entries + 0},
        {0x1a00, 4, slave_12_pdo_entries + 4}, /* TPDO 1 mapping parameter */
    };

    ec_sync_info_t slave_12_syncs[5] = {
        {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
        {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
        {2, EC_DIR_OUTPUT, 1, slave_12_pdos + 0, EC_WD_ENABLE},
        {3, EC_DIR_INPUT, 1, slave_12_pdos + 1, EC_WD_DISABLE},
        {0xff}};

    unsigned int off_rx_pdo_1;
    unsigned int off_rx_pdo_2;
    unsigned int off_rx_pdo_3;
    unsigned int off_rx_pdo_4;

    unsigned int off_tx_pdo_1;
    unsigned int off_tx_pdo_2;
    unsigned int off_tx_pdo_3;
    unsigned int off_tx_pdo_4;

    ec_pdo_entry_reg_t domain_regs[41] = {
        {0, 12, 0x0000029c, 0x03811002, 0x6040, 0x00, &off_rx_pdo_1}, // UINT16
        {0, 12, 0x0000029c, 0x03811002, 0x607a, 0x00, &off_rx_pdo_2}, // UINT32
        {0, 12, 0x0000029c, 0x03811002, 0x60ff, 0x00, &off_rx_pdo_3}, // UINT32
        {0, 12, 0x0000029c, 0x03811002, 0x6060, 0x00, &off_rx_pdo_4}, // UINT8
        {0, 12, 0x0000029c, 0x03811002, 0x6041, 0x00, &off_tx_pdo_1}, /* Status Word */ // UINT16
        {0, 12, 0x0000029c, 0x03811002, 0x6064, 0x00, &off_tx_pdo_2}, /* Actual position */ // UINT32
        {0, 12, 0x0000029c, 0x03811002, 0x606c, 0x00, &off_tx_pdo_3}, /* Actual velocity */ // UINT32
        {0, 12, 0x0000029c, 0x03811002, 0x6061, 0x00, &off_tx_pdo_4}, /* Operation mode display */ // UINT8
        {}};

    unsigned long t_stamp = 0;

    // int32_t TARGET_POS = 0;  // off_rx_pdo_1
    uint16_t CONTROL_WD = 0; // off_rx_pdo_2
    uint8_t OP_MODE = 0;     // off_rx_pdo_4
};

#endif // EC_SLAVE_INGENIA_H
