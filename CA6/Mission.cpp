#include "Manual.hh"
#include "Mission.hh"
#include <iostream>

using namespace std;

Mission::Mission(int mission_id, time_t start, time_t end, int reward_amount) : period(start, end)
{
    if (reward_amount < 0)
    {
        throw runtime_error("INVALID_ARGUMENTS");
    }
    this->reward_amount = reward_amount;
    this->mission_id = mission_id;
}

bool Mission::is_id_same(int id)
{
    return id == mission_id;
}

TimeMission::TimeMission(int mission_id, time_t start, time_t end, int reward_amount, time_t target_time_in_minute) : Mission(mission_id, start, end, reward_amount)
{
    if (target_time_in_minute < 0)
    {
        throw runtime_error("INVALID_ARGUMENTS");
    }
    target_time_in_second = target_time_in_minute * SC_IN_A_MIN;
}

DistanceMission::DistanceMission(int mission_id, time_t start, time_t end, int reward_amount, int target_distance) : Mission(mission_id, start, end, reward_amount)
{
    if (target_distance < 0)
    {
        throw runtime_error("INVALID_ARGUMENTS");
    }
    target_distance_in_meter = target_distance;
}

CountMission::CountMission(int mission_id, time_t start, time_t end, int reward_amount, int target_number): Mission(mission_id,start,end,reward_amount)
{
    if (target_number < 0)
    {
        throw runtime_error("INVALID_ARGUMENTS");
    }
    this->target_number=target_number;

}

long TimeMission::check_travel(long score,int distance, time_t start, time_t end)
{
    if(period.is_in_period(start,end))
    {
        return score+(end-start);
    }
    return score;
}

long DistanceMission::check_travel(long score,int distance, time_t start, time_t end)
{
    if(period.is_in_period(start,end))
    {
        return score+distance;
    }
    return score;
}

long CountMission::check_travel(long score,int distance, time_t start, time_t end)
{
    if(period.is_in_period(start,end))
    {
        return score+1;
    }
    return score;
}

bool TimeMission::is_mission_complete(long cached_score)
{
    return cached_score-target_time_in_second>=0;
}

bool DistanceMission::is_mission_complete(long cached_score)
{
    return cached_score-target_distance_in_meter>=0;
}

bool CountMission::is_mission_complete(long cached_score)
{
    return cached_score-target_number>=0;
}

void Mission::print(time_t end)
{
    cout<<"mission "<<mission_id<<":"<<endl;
    cout<<"start timestamp: "<<period.get_mission_start()<<endl;
    cout<<"end timestamp: ";
    if(end==NOT_COMPLETE)
    {
        cout<<-1<<endl;
    }
    else
    {
        cout<<end<<endl;
    }
    cout<<"reward: "<<reward_amount<<endl;
}

void Mission::print2(time_t end)
{
    cout<<"mission: "<<mission_id<<endl;
    cout<<"start timestamp: "<<period.get_mission_start()<<endl;
    cout<<"end timestamp: ";
    cout<<end<<endl;
    cout<<"reward: "<<reward_amount<<endl;
}

int Mission::get_end()
{
    return period.get_mission_end();
}
