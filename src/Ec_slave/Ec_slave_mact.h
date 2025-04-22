#ifndef EC_SLAVE_MACT_H
#define EC_SLAVE_MACT_H

#include <stdint.h>
#include "../Ec_slave_base_motor_drive/Ec_slave_base_motor_drive.h"

class Ec_slave_mact : public Ec_slave_base_motor_drive
{
public:
    Ec_slave_mact(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_mact();

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
    #include "Ec_slave_mact_info.h"

    unsigned int off_rx_pdo_1;
    unsigned int off_rx_pdo_2;
    unsigned int off_rx_pdo_3;
    unsigned int off_rx_pdo_4;
    unsigned int off_rx_pdo_5;
    unsigned int off_rx_pdo_6;
    unsigned int off_rx_pdo_7;

    unsigned int off_tx_pdo_1;
    unsigned int off_tx_pdo_2;
    unsigned int off_tx_pdo_3;
    unsigned int off_tx_pdo_4;
    unsigned int off_tx_pdo_5;
    unsigned int off_tx_pdo_6;
    unsigned int off_tx_pdo_7;
    unsigned int off_tx_pdo_8;

    ec_pdo_entry_reg_t domain_regs[16] = {
        {0, 11, 0x00113322, 0x00001022, 0x607a, 0x00, &off_rx_pdo_1}, /* TARGET_POS */
        {0, 11, 0x00113322, 0x00001022, 0x6040, 0x00, &off_rx_pdo_2}, /* CONTROL_WD */
        {0, 11, 0x00113322, 0x00001022, 0x6071, 0x00, &off_rx_pdo_3}, /* TARGET_TORQ */
        {0, 11, 0x00113322, 0x00001022, 0x6060, 0x00, &off_rx_pdo_4}, /* OP_MODE */
        {0, 11, 0x00113322, 0x00001022, 0x3004, 0x00, &off_rx_pdo_5}, /* ERROR_CLEAR */
        {0, 11, 0x00113322, 0x00001022, 0x3001, 0x00, &off_rx_pdo_6}, /* DIG_OUT */
        {0, 11, 0x00113322, 0x00001022, 0x60ff, 0x00, &off_rx_pdo_7}, /* TARGET_VEL */
        {0, 11, 0x00113322, 0x00001022, 0x6064, 0x00, &off_tx_pdo_1}, /* ACT_POS */
        {0, 11, 0x00113322, 0x00001022, 0x6041, 0x00, &off_tx_pdo_2}, /* STATUS_WD */
        {0, 11, 0x00113322, 0x00001022, 0x6077, 0x00, &off_tx_pdo_3}, /* ACT_TOR */
        {0, 11, 0x00113322, 0x00001022, 0x6061, 0x00, &off_tx_pdo_4}, /* OPMODE_DISP */
        {0, 11, 0x00113322, 0x00001022, 0x603f, 0x00, &off_tx_pdo_5}, /* ERROR_CODE */
        {0, 11, 0x00113322, 0x00001022, 0x3002, 0x00, &off_tx_pdo_6}, /* DIG_IN */
        {0, 11, 0x00113322, 0x00001022, 0x606c, 0x00, &off_tx_pdo_7}, /* ACT_VEL */
        {0, 11, 0x00113322, 0x00001022, 0x3007, 0x00, &off_tx_pdo_8}, /* ADC_VAL */
        {}};

    unsigned long t_stamp = 0;
    uint32_t offset = 0;
};

#endif // EC_SLAVE_MACT_H
