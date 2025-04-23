#ifndef EC_SLAVE_INGENIA_H
#define EC_SLAVE_INGENIA_H

#include <cmath>
#include <stdint.h>
#include "../Ec_slave_base_motor_drive/Ec_slave_base_motor_drive.h"

class Ec_slave_ingenia : public Ec_slave_base_motor_drive
{
public:
    Ec_slave_ingenia(uint16_t slave_address_, const std::string &slave_ns_);
    ~Ec_slave_ingenia();

    virtual void set_info();
    virtual void set_pdo();
    // virtual void monitor_status();
    virtual void transfer_tx_pdo();
    virtual void transfer_rx_pdo();
    virtual void process_tx_pdo();
    virtual void process_rx_pdo();
    virtual void config_data_transfer();
    virtual void publish_data();
    virtual void subscribe_data();
    virtual void main_process();

private:
    #include "Ec_slave_ingenia_info.h"
    
    unsigned int off_rx_pdo_1;
    unsigned int off_rx_pdo_2;
    unsigned int off_rx_pdo_3;
    unsigned int off_rx_pdo_4;

    unsigned int off_tx_pdo_1;
    unsigned int off_tx_pdo_2;
    unsigned int off_tx_pdo_3;
    unsigned int off_tx_pdo_4;

    ec_pdo_entry_reg_t domain_regs[9] = {
        {0, 12, 0x0000029c, 0x03811002, 0x6040, 0x00, &off_rx_pdo_1}, /* CONTROL_WD */  // UINT16
        {0, 12, 0x0000029c, 0x03811002, 0x607a, 0x00, &off_rx_pdo_2}, /* TARGET_POS */  // SINT32
        {0, 12, 0x0000029c, 0x03811002, 0x60ff, 0x00, &off_rx_pdo_3}, /* TARGET_VEL */  // SINT32
        {0, 12, 0x0000029c, 0x03811002, 0x6060, 0x00, &off_rx_pdo_4}, /* OP_MODE */     // UIN8T
        {0, 12, 0x0000029c, 0x03811002, 0x6041, 0x00, &off_tx_pdo_1}, /* Status Word */ // UINT16
        {0, 12, 0x0000029c, 0x03811002, 0x6064, 0x00, &off_tx_pdo_2}, /* Actual position */ // SINT32
        {0, 12, 0x0000029c, 0x03811002, 0x606c, 0x00, &off_tx_pdo_3}, /* Actual velocity */ // SINT32
        {0, 12, 0x0000029c, 0x03811002, 0x6061, 0x00, &off_tx_pdo_4}, /* Operation mode display */ // UINT8
        {}};

    unsigned long t_stamp = 0;
};

#endif // EC_SLAVE_INGENIA_H
