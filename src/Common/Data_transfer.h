#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

class Data_transfer
{
public:
    virtual void config_data_transfer() = 0;

    virtual void publish_data() = 0;

    virtual void subscribe_data() = 0;
};

#endif // DATA_TRANSFER_H
