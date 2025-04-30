#ifndef EC_MASTER_H
#define EC_MASTER_H

#include <string>
#include <cstdlib>
#include "../Ec_logger/Ec_logger_console/Ec_logger_console.h"

class Ec_master
{
public:
    Ec_master(const std::string &master_ns_)
    {
        master_ns = master_ns_;
    }

    ~Ec_master()
    {
    }

    bool start()
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Starting master ...", 1);

        int result = system("sudo /etc/init.d/ethercat start");
        if (result == 0)
        {
            running_status = true;
            LOG_CONSOLE_SOURCE_INFO(master_ns, "Master started", 1);
        }
        else
        {
            running_status = false;
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to start master", 1);
        }

        return true;
    }

    bool stop()
    {
        LOG_CONSOLE_SOURCE_INFO(master_ns, "Stopping master...", 1);
        int result = system("sudo /etc/init.d/ethercat stop");
        if (result == 0)
        {
            running_status = false;
            LOG_CONSOLE_SOURCE_INFO(master_ns, "Master stopped", 1);
        }
        else
        {
            running_status = true;
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to stop master", 1);
        }

        return true;
    }

    bool restart()
    {
        int result = system("sudo /etc/init.d/ethercat restart");
        if (result == 0)
        {
            running_status = true;
            LOG_CONSOLE_SOURCE_INFO(master_ns, "Master restarting...", 1);
        }
        else
        {
            running_status = false;
            LOG_CONSOLE_SOURCE_ERROR(master_ns, "Failed to restart master", 1);
        }

        return true;
    }

    bool is_running()
    {
        return running_status;
    }

private:
    std::string master_ns;
    bool running_status = false;
};

#endif // EC_MASTER_H
