#include "Time.hh"
#pragma once

class Mission
{
protected:
    TimePeriod period;
private:
    int mission_id;
    int reward_amount;

public:
    Mission(int mission_id, time_t start, time_t end, int reward_amount);
    virtual ~Mission() = default;
    bool is_id_same(int id);
    int get_end();
    void print(time_t end);
    void print2(time_t end);
    virtual long check_travel(long score, int distance, time_t start, time_t end) = 0;
    virtual bool is_mission_complete(long cached_score) = 0;
};

class TimeMission : public Mission
{
private:
    time_t target_time_in_second;

public:
    TimeMission(int mission_id, time_t start, time_t end, int reward_amount, time_t target_time_in_minute);
    long check_travel(long score, int distance, time_t start, time_t end);
    bool is_mission_complete(long cached_score);
};

class DistanceMission : public Mission
{
private:
    int target_distance_in_meter;

public:
    DistanceMission(int mission_id, time_t start, time_t end, int reward_amount, int target_distance_in_meter);
    long check_travel(long score, int distance, time_t start, time_t end);
    bool is_mission_complete(long cached_score);
};

class CountMission : public Mission
{
private:
    int target_number;

public:
    CountMission(int mission_id, time_t start, time_t end, int reward_amount, int target_number);
    long check_travel(long score, int distance, time_t start, time_t end);
    bool is_mission_complete(long cached_score);
};
