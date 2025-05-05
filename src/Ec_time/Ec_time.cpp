#include "Ec_time.h"

Ec_time::Ec_time(uint64_t cycle_time_, Ec_time_var::Time_unit cycle_time_unit)
{
    switch (cycle_time_unit)
    {
    case Ec_time_var::Time_unit::N_SECOND:
        cycle_time_ns = cycle_time_;
        break;
    case Ec_time_var::Time_unit::U_SECOND:
        cycle_time_ns = cycle_time_ * 1000;
        break;
    case Ec_time_var::Time_unit::M_SECOND:
        cycle_time_ns = cycle_time_ * 1000000;
        break;
    case Ec_time_var::Time_unit::SECOND:
        cycle_time_ns = cycle_time_ * 1000000000;
        break;
    case Ec_time_var::Time_unit::MINUTE:
        cycle_time_ns = cycle_time_ * 60000000000;
        break;
    case Ec_time_var::Time_unit::HOUR:
        cycle_time_ns = cycle_time_ * 3600000000000;
        break;
    case Ec_time_var::Time_unit::DAY:
        cycle_time_ns = cycle_time_ * 3600000000000 * 24;
        break;
    default:
        cycle_time_ns = cycle_time_;
        break;
    };
}

Ec_time::~Ec_time()
{
}

void Ec_time::init()
{
    t_now_us = 0;
    t_now_ms = 0;
    t_now_s = 0;
    t_now_m = 0;
    t_now_h = 0;
    t_now_d = 0;
}

void Ec_time::reset()
{
    init();
}

void Ec_time::update()
{
    t_now_ns = cycle_time_ns;
    t_now_us = t_now_ns / 1000;
    t_now_ms = t_now_ns / 1000000;
    t_now_s = t_now_ns / 1000000000;
    t_now_m = t_now_ns / 60000000000;
    t_now_h = t_now_ns / 3600000000000;
    t_now_d = t_now_ns / (3600000000000 * 24);
}

uint64_t Ec_time::current_time_ns()
{
    return t_now_ns;
}

uint64_t Ec_time::current_time_us()
{
    return t_now_us;
}

uint64_t Ec_time::current_time_ms()
{
    return t_now_ms;
}

uint64_t Ec_time::current_time_s()
{
    return t_now_s;
}

uint64_t Ec_time::current_time_m()
{
    return t_now_m;
}

uint64_t Ec_time::current_time_h()
{
    return t_now_h;
}

uint64_t Ec_time::current_time_d()
{
    return t_now_d;
}
