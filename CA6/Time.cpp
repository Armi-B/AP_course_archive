#include "Time.hh"
#include <iostream>

using namespace std;

TimePeriod::TimePeriod(time_t given_start, time_t given_end)
{
    if(given_start>given_end)
    {
        throw runtime_error("INVALID_ARGUMENTS");
    }
    start=given_start;
    end = given_end;
}

bool TimePeriod::is_in_period(time_t travel_start, time_t travel_end)
{
    return travel_start-start>=0&&end-travel_end>=0;
}

time_t TimePeriod::get_mission_start()
{
    return start;
}

time_t TimePeriod::get_mission_end()
{
    return end;
}