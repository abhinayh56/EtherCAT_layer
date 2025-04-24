#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

class Data_transfer
{
public:
    virtual uint16_t config_data_transfer() = 0;

    virtual uint16_t publish_data() = 0;

    virtual uint16_t subscribe_data() = 0;
};

#endif // DATA_TRANSFER_H
