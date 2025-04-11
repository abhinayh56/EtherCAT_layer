#ifndef EC_SLAVE_5_H
#define EC_SLAVE_5_H

#include <cmath>
#include <stdint.h>
#include "Ec_slave_base.h"

class Ec_slave_5 : public Ec_slave_base
{
public:
    Ec_slave_5(uint16_t slave_address_, const std::string &slave_name_)
    {
        slave_address = slave_address_;
        slave_name = slave_name_;
    }

    ~Ec_slave_5() {}

    virtual void set_info()
    {
        slave_info.alias = alias;
        slave_info.position = position;
        slave_info.vendor_id = vendor_id;
        slave_info.product_code = product_code;

        slave_info.slave_pdo_entries = slave_4_pdo_entries;
        slave_info.slave_pdos = slave_4_pdos;
        slave_info.slave_syncs = slave_4_syncs;
    }

    virtual void set_pdo()
    {
        domain_i_regs = domain_regs;
    }

    virtual void monitor_status() {}

    virtual void transfer_tx_pdo()
    {
        int32_t  ACT_POS     = EC_READ_S32(domain_i_pd + off_tx_pdo_1);
        uint16_t STATUS_WD   = EC_READ_U16(domain_i_pd + off_tx_pdo_2);
        int16_t  ACT_TOR     = EC_READ_S16(domain_i_pd + off_tx_pdo_3);
        uint8_t  OPMODE_DISP = EC_READ_U8(domain_i_pd + off_tx_pdo_4);
        uint16_t ERROR_CODE  = EC_READ_U16(domain_i_pd + off_tx_pdo_5);
        uint8_t  DIG_IN      = EC_READ_U8(domain_i_pd + off_tx_pdo_6);
        int32_t  ACT_VEL     = EC_READ_S32(domain_i_pd + off_tx_pdo_7);
        int16_t  ADC_VAL     = EC_READ_S16(domain_i_pd + off_tx_pdo_8);

        // std::cout << "MACT_TXPDO: " << ACT_POS << ", " << STATUS_WD << ", " << ACT_TOR << ", " << uint16_t(OPMODE_DISP) << ", " << ERROR_CODE << ", " << uint16_t(DIG_IN) << ", " << ACT_VEL << ", " << ADC_VAL << std::endl;
    }

    virtual void transfer_rx_pdo()
    {
        t_stamp += 4;

        if ((2500<= t_stamp) && (t_stamp <= 5000))
        {
            OP_MODE = 8;
            CONTROL_WD = 0;
        }
        else if ((5000 <= t_stamp) && (t_stamp <= 7000))
        {
            CONTROL_WD = 6;
        }
        else if ((7000 <= t_stamp) && (t_stamp <= 9000))
        {
            CONTROL_WD = 7;
        }
        else if ((9000 <= t_stamp) && (t_stamp <= 11000))
        {
            CONTROL_WD = 15;
        }
        else if ((11000 <= t_stamp) && (t_stamp <= 15000))
        {
            TARGET_POS = 0;
        }
        else
        {
            double A = 8192.0;
            double T = 2.0;
            double f = 1.0/T;
            double w = 2.0 * 3.1417 * f;
            double t = ((double)t_stamp - 15000.0) * 0.001;
            TARGET_POS = A * std::sin(w*t);
        }

        EC_WRITE_S32(domain_i_pd + off_rx_pdo_1, TARGET_POS);
        EC_WRITE_U16(domain_i_pd + off_rx_pdo_2, CONTROL_WD);
        EC_WRITE_U8(domain_i_pd + off_rx_pdo_4, OP_MODE);
    }

    virtual void process_tx_pdo() {}
    virtual void process_rx_pdo() {}
    virtual void config_data_transfer() {}
    virtual void publish_data() {}
    virtual void subscribe_data() {}

private:
    uint16_t alias = 0;
    uint16_t position = 9;
    uint32_t vendor_id = 0x00113322;
    uint32_t product_code = 0x00001022;

    ec_pdo_entry_info_t slave_4_pdo_entries[15] = {
        {0x607a, 0x00, 32}, /* TARGET_POS */
        {0x6040, 0x00, 16}, /* CONTROL_WD */
        {0x6071, 0x00, 16}, /* TARGET_TORQ */
        {0x6060, 0x00, 8},  /* OP_MODE */
        {0x3004, 0x00, 16}, /* ERROR_CLEAR */
        {0x3001, 0x00, 8},  /* DIG_OUT */
        {0x60ff, 0x00, 32}, /* TARGET_VEL */
        {0x6064, 0x00, 32}, /* ACT_POS */
        {0x6041, 0x00, 16}, /* STATUS_WD */
        {0x6077, 0x00, 16}, /* ACT_TOR */
        {0x6061, 0x00, 8},  /* OPMODE_DISP */
        {0x603f, 0x00, 16}, /* ERROR_CODE */
        {0x3002, 0x00, 8},  /* DIG_IN */
        {0x606c, 0x00, 32}, /* ACT_VEL */
        {0x3007, 0x00, 16}, /* ADC_VAL */
    };

    ec_pdo_info_t slave_4_pdos[2] = {
        {0x1600, 7, slave_4_pdo_entries + 0}, /* Outputs */
        {0x1a00, 8, slave_4_pdo_entries + 7}, /* Inputs */
    };

    ec_sync_info_t slave_4_syncs[3] = {
        {0, EC_DIR_OUTPUT, 1, slave_4_pdos + 0, EC_WD_ENABLE},
        {1, EC_DIR_INPUT, 1, slave_4_pdos + 1, EC_WD_DISABLE},
        {0xff}};

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

    ec_pdo_entry_reg_t domain_regs[41] = {
        {0, 9, 0x00113322, 0x00001022, 0x607a, 0x00, &off_rx_pdo_1}, /* TARGET_POS */
        {0, 9, 0x00113322, 0x00001022, 0x6040, 0x00, &off_rx_pdo_2}, /* CONTROL_WD */
        {0, 9, 0x00113322, 0x00001022, 0x6071, 0x00, &off_rx_pdo_3}, /* TARGET_TORQ */
        {0, 9, 0x00113322, 0x00001022, 0x6060, 0x00, &off_rx_pdo_4}, /* OP_MODE */
        {0, 9, 0x00113322, 0x00001022, 0x3004, 0x00, &off_rx_pdo_5}, /* ERROR_CLEAR */
        {0, 9, 0x00113322, 0x00001022, 0x3001, 0x00, &off_rx_pdo_6}, /* DIG_OUT */
        {0, 9, 0x00113322, 0x00001022, 0x60ff, 0x00, &off_rx_pdo_7}, /* TARGET_VEL */
        {0, 9, 0x00113322, 0x00001022, 0x6064, 0x00, &off_tx_pdo_1}, /* ACT_POS */
        {0, 9, 0x00113322, 0x00001022, 0x6041, 0x00, &off_tx_pdo_2}, /* STATUS_WD */
        {0, 9, 0x00113322, 0x00001022, 0x6077, 0x00, &off_tx_pdo_3}, /* ACT_TOR */
        {0, 9, 0x00113322, 0x00001022, 0x6061, 0x00, &off_tx_pdo_4}, /* OPMODE_DISP */
        {0, 9, 0x00113322, 0x00001022, 0x603f, 0x00, &off_tx_pdo_5}, /* ERROR_CODE */
        {0, 9, 0x00113322, 0x00001022, 0x3002, 0x00, &off_tx_pdo_6}, /* DIG_IN */
        {0, 9, 0x00113322, 0x00001022, 0x606c, 0x00, &off_tx_pdo_7}, /* ACT_VEL */
        {0, 9, 0x00113322, 0x00001022, 0x3007, 0x00, &off_tx_pdo_8}, /* ADC_VAL */
        {}};

    unsigned long t_stamp = 0;

    int32_t TARGET_POS = 0; // off_rx_pdo_1
    uint16_t CONTROL_WD = 0; // off_rx_pdo_2
    uint8_t OP_MODE = 0;     // off_rx_pdo_4
};

#endif // EC_SLAVE_5_H
