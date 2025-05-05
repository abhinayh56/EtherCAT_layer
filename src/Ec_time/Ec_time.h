#ifndef EC_TIME_H
#define EC_TIME_H

#include <stdint.h>

namespace Ec_time_var
{
    enum Time_unit : uint16_t
    {
        N_SECOND = 0,
        U_SECOND = 1,
        M_SECOND = 2,
        SECOND = 3,
        MINUTE = 4,
        HOUR = 5,
        DAY = 6
    };
}

class Ec_time
{
public:
    Ec_time(uint64_t cycle_time_, Ec_time_var::Time_unit cycle_time_unit = Ec_time_var::Time_unit::N_SECOND);
    ~Ec_time();
    void init();
    void reset();
    void update();
    uint64_t current_time_ns();
    uint64_t current_time_us();
    uint64_t current_time_ms();
    uint64_t current_time_s();
    uint64_t current_time_m();
    uint64_t current_time_h();
    uint64_t current_time_d();

private:
    uint64_t cycle_time_ns = 0;
    uint64_t t_now_ns = 0;
    uint64_t t_now_us = 0;
    uint64_t t_now_ms = 0;
    uint64_t t_now_s = 0;
    uint64_t t_now_m = 0;
    uint64_t t_now_h = 0;
    uint64_t t_now_d = 0;
};

#endif // EC_TIME_H
