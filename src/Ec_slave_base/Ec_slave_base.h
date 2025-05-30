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

    void set_slave_ns(const std::string &slave_name_);
    const std::string &get_slave_ns();
    void set_slave_address(uint16_t slave_address_);
    uint16_t get_slave_address();

    virtual uint16_t set_info_from_eni();
    uint16_t config_slave(ec_master_t *master);

    virtual uint16_t set_pdo();
    uint16_t register_pdo_to_domain(ec_domain_t *domain_i);

    uint16_t set_domain_ptr(uint8_t *domain_i_pd_);
    uint16_t set_domain(ec_domain_t *domain_i_);

    uint16_t monitor_status();
    bool is_operational();
    bool is_online();
    uint16_t get_current_state();

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

protected:
    std::string slave_ns;
    uint16_t slave_address;
    Slave_info slave_info;

    ec_slave_config_t *sc;
    ec_slave_config_state_t sc_state;
    uint8_t *domain_i_pd = NULL;

    ec_pdo_entry_reg_t *domain_i_regs;
    ec_domain_t *domain_i = NULL;

    template <typename T>
    bool register_pdo(Pdo_variable<T> *pdo_variable)
    {
        pdo_variable->offset = ecrt_slave_config_reg_pdo_entry(sc, pdo_variable->index, pdo_variable->subindex, domain_i, NULL);

        std::cout << "---------------------------> " << pdo_variable->index << ", " << (uint16_t)pdo_variable->subindex << ", " << pdo_variable->offset << ", ";
        if (pdo_variable->offset >= 0)
        {
            pdo_variable->is_supported = true;
            std::cout << "SUCCESS\n";
        }
        else
        {
            pdo_variable->is_supported = false;
            std::cout << "FAILURE\n";
        }

        return pdo_variable->is_supported;
    }

    inline void transfer_tx_pdo_U8(Pdo_variable<uint8_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_U8(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_tx_pdo_U16(Pdo_variable<uint16_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_U16(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_tx_pdo_U32(Pdo_variable<uint32_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_U32(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_tx_pdo_U64(Pdo_variable<uint64_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_U64(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_tx_pdo_S8(Pdo_variable<int8_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_S8(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_tx_pdo_S16(Pdo_variable<int16_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_S16(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_tx_pdo_S32(Pdo_variable<int32_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_S32(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_tx_pdo_S64(Pdo_variable<int64_t> *pdo_variable)
    {
        pdo_variable->value = EC_READ_S64(domain_i_pd + pdo_variable->offset);
    }

    inline void transfer_rx_pdo_U8(Pdo_variable<uint8_t> *pdo_variable)
    {
        EC_WRITE_U8(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }

    inline void transfer_rx_pdo_U16(Pdo_variable<uint16_t> *pdo_variable)
    {
        EC_WRITE_U16(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }

    inline void transfer_rx_pdo_U32(Pdo_variable<uint32_t> *pdo_variable)
    {
        EC_WRITE_U32(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }

    inline void transfer_rx_pdo_U64(Pdo_variable<uint64_t> *pdo_variable)
    {
        EC_WRITE_U64(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }

    inline void transfer_rx_pdo_S8(Pdo_variable<int8_t> *pdo_variable)
    {
        EC_WRITE_S8(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }

    inline void transfer_rx_pdo_S16(Pdo_variable<int16_t> *pdo_variable)
    {
        EC_WRITE_S16(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }

    inline void transfer_rx_pdo_S32(Pdo_variable<int32_t> *pdo_variable)
    {
        EC_WRITE_S32(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }

    inline void transfer_rx_pdo_S64(Pdo_variable<int64_t> *pdo_variable)
    {
        EC_WRITE_S64(domain_i_pd + pdo_variable->offset, pdo_variable->value);
    }
};

#endif // EC_SLAVE_BASE_H
