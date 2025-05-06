#ifndef EC_SLAVE_MACT_H
#define EC_SLAVE_MACT_H

#include "../Ec_slave_base_motor_drive/Ec_slave_base_motor_drive.h"

class Ec_slave_mact : public Ec_slave_base_motor_drive
{
public:
    Ec_slave_mact(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_mact();

    virtual uint16_t set_info_from_eni();
    virtual uint16_t set_pdo();
    virtual uint16_t transfer_tx_pdo();
    virtual uint16_t transfer_rx_pdo();
    virtual uint16_t process_tx_pdo();
    virtual uint16_t process_rx_pdo();
    virtual uint16_t config_data_transfer();
    virtual uint16_t publish_data();
    virtual uint16_t subscribe_data();
    virtual uint16_t main_process();
    virtual uint16_t reset();
    virtual uint16_t init();

private:
    #include "Ec_slave_mact_info.h"

    struct Tx_pdo
    {
        Pdo_variable<int32_t>  ACT_POS     = {0x6064, 0x00};
        Pdo_variable<uint16_t> STATUS_WD   = {0x6041, 0x00};
        Pdo_variable<int16_t>  ACT_TOR     = {0x6077, 0x00};
        Pdo_variable<uint8_t>  OPMODE_DISP = {0x6061, 0x00};
        Pdo_variable<uint16_t> ERROR_CODE  = {0x603f, 0x00};
        Pdo_variable<uint8_t>  DIG_IN      = {0x3002, 0x00};
        Pdo_variable<int32_t>  ACT_VEL     = {0x606c, 0x00};
        Pdo_variable<int16_t>  ADC_VAL     = {0x3007, 0x00};
    } m_tx_pdo;

    struct Rx_pdo
    {
        Pdo_variable<int32_t> TARGET_POS  = {0x607a, 0x00};
        Pdo_variable<uint16_t> CONTROL_WD  = {0x6040, 0x00};
        // Pdo_variable<int> TARGET_TORQ = {0x6071, 0x00};
        Pdo_variable<uint8_t> OP_MODE     = {0x6060, 0x00};
        // Pdo_variable<int> ERROR_CLEAR = {0x3004, 0x00};
        // Pdo_variable<int> DIG_OUT     = {0x3001, 0x00};
        // Pdo_variable<int> TARGET_VEL  = {0x60ff, 0x00};
    } m_rx_pdo;

    // unsigned int off_rx_pdo_1;
    // unsigned int off_rx_pdo_2;
    // unsigned int off_rx_pdo_3;
    // unsigned int off_rx_pdo_4;
    // unsigned int off_rx_pdo_5;
    // unsigned int off_rx_pdo_6;
    // unsigned int off_rx_pdo_7;

    // unsigned int off_tx_pdo_1;
    // unsigned int off_tx_pdo_2;
    // unsigned int off_tx_pdo_3;
    // unsigned int off_tx_pdo_4;
    // unsigned int off_tx_pdo_5;
    // unsigned int off_tx_pdo_6;
    // unsigned int off_tx_pdo_7;
    // unsigned int off_tx_pdo_8;

    // ec_pdo_entry_reg_t domain_regs[16] = {
    //     {0, 11, 0x00113322, 0x00001022, 0x607a, 0x00, &off_rx_pdo_1}, /* TARGET_POS */
    //     {0, 11, 0x00113322, 0x00001022, 0x6040, 0x00, &off_rx_pdo_2}, /* CONTROL_WD */
    //     {0, 11, 0x00113322, 0x00001022, 0x6071, 0x00, &off_rx_pdo_3}, /* TARGET_TORQ */
    //     {0, 11, 0x00113322, 0x00001022, 0x6060, 0x00, &off_rx_pdo_4}, /* OP_MODE */
    //     {0, 11, 0x00113322, 0x00001022, 0x3004, 0x00, &off_rx_pdo_5}, /* ERROR_CLEAR */
    //     {0, 11, 0x00113322, 0x00001022, 0x3001, 0x00, &off_rx_pdo_6}, /* DIG_OUT */
    //     {0, 11, 0x00113322, 0x00001022, 0x60ff, 0x00, &off_rx_pdo_7}, /* TARGET_VEL */
    //     {0, 11, 0x00113322, 0x00001022, 0x6064, 0x00, &off_tx_pdo_1}, /* ACT_POS */
    //     {0, 11, 0x00113322, 0x00001022, 0x6041, 0x00, &off_tx_pdo_2}, /* STATUS_WD */
    //     {0, 11, 0x00113322, 0x00001022, 0x6077, 0x00, &off_tx_pdo_3}, /* ACT_TOR */
    //     {0, 11, 0x00113322, 0x00001022, 0x6061, 0x00, &off_tx_pdo_4}, /* OPMODE_DISP */
    //     {0, 11, 0x00113322, 0x00001022, 0x603f, 0x00, &off_tx_pdo_5}, /* ERROR_CODE */
    //     {0, 11, 0x00113322, 0x00001022, 0x3002, 0x00, &off_tx_pdo_6}, /* DIG_IN */
    //     {0, 11, 0x00113322, 0x00001022, 0x606c, 0x00, &off_tx_pdo_7}, /* ACT_VEL */
    //     {0, 11, 0x00113322, 0x00001022, 0x3007, 0x00, &off_tx_pdo_8}, /* ADC_VAL */
    //     {}};

    unsigned long t_stamp = 0;
    uint32_t offset = 0;
};

#endif // EC_SLAVE_MACT_H
