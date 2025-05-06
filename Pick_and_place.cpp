#ifndef PICK_AND_PLACE_H
#define PICK_AND_PLACE_H

#include <stdint.h>
#include <vector>


struct Way_point
{
    double th_1 = 0;
    double th_2 = 0;
    double th_3 = 0;
    double th_4 = 0;
    double th_5 = 0;
    double th_6 = 0;
    double th_7 = 0;
    double th_8 = 0;
    double th_9 = 0;
    double th_10 = 0;
    double th_11 = 0;
    double th_12 = 0;
    double th_13 = 0;
    double th_14 = 0;
};

class Pick_and_place
{
public:
    Pick_and_place()
    {
    }

    ~Pick_and_place()
    {
    }

    void add_point(Way_point wp_new)
    {
        wp_arr.push_back(wp_new);
        num_wp = wp_arr.size();
    }

    void remove_point(uint16_t n)
    {
    }

    void follow_wp()
    {
        // 1. subscribe index_wp

        // 2. if(index_wp < num_wp)
        //    publish wp_arr[index_wp]
    }

private:
    std::vector<Way_point> wp_arr;
    uint16_t num_wp = 0;

    uint16_t index_wp = 0;
};

#endif // PICK_AND_PLACE_H
