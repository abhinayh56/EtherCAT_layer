#ifndef EC_MASTER_H
#define EC_MASTER_H

#include <cstdlib>
#include "../Ec_logger/Ec_logger_console/Ec_logger_console.h"

class Ec_master
{
public:
    Ec_master()
    {
    }

    ~Ec_master()
    {
    }

    bool start()
    {
        LOG_CONSOLE_SOURCE_INFO("EC_MASTER", "Starting master ...", 1);

        int result = system("sudo /etc/init.d/ethercat start");
        if (result == 0)
        {
            LOG_CONSOLE_SOURCE_INFO("EC_MASTER", "Master started", 1);
        }
        else
        {
            LOG_CONSOLE_SOURCE_ERROR("EC_MASTER", "Failed to start master", 1);
        }

        return true;
    }

    bool stop()
    {
        int result = system("sudo /etc/init.d/ethercat stop");
        if (result == 0)
        {
            LOG_CONSOLE_SOURCE_INFO("EC_MASTER", "Master stopped", 1);
        }
        else
        {
            LOG_CONSOLE_SOURCE_ERROR("EC_MASTER", "Failed to stop master", 1);
        }

        return true;
    }
};

#endif // EC_MASTER_H
