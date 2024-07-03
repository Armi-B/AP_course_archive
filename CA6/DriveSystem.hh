#include <vector>
#include <iostream>
#include "Driver.hh"
#include "Time.hh"
#include "Mission.hh"
#pragma once

class DriveSystem
{
private:
    vector<Mission *> missions;
    vector<Driver *> drivers;
    int find_mission_ind(int id);
    int find_driver_ind(int id);
    void creat_time_mission();
    void creat_distance_mission();
    void creat_count_mission();
    bool is_mission_duplicated(int mission_id);
    void assign_mission();
    void record_ride();
    void show_missions_status();
public:
    void start_system();
};