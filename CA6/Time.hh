#include <ctime>
#pragma once

class TimePeriod
{
private:
    time_t start;
    time_t end;

public:
    TimePeriod(time_t start, time_t end);
    bool is_in_period(time_t travel_start, time_t travel_end);
    time_t get_mission_start();
    time_t get_mission_end();
};