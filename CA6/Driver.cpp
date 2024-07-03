#include "Driver.hh"
#include "Manual.hh"
#include <iostream>
#include <algorithm>
using namespace std;

Driver::Driver(int id) : driver_id(id)
{
    rewards = 0;
}

void Driver::sort_driver_missions()
{
    sort(this->missions.begin(), this->missions.end(), [](const DriverMission e1, DriverMission e2){return e1.mission->get_end()<e2.mission->get_end();});
}

void Driver::assign_new_mission(Mission *mission)
{
    DriverMission new_driver_mission = {mission, 0, NOT_COMPLETE};
    missions.push_back(new_driver_mission);
}

bool Driver::is_id_same(int id)
{
    return id == driver_id;
}

int Driver::find_mission_ind(int id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i].mission->is_id_same(id))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

void Driver::change_DiverMission_end(time_t the_end, int index)
{
    missions[index].end_travel = the_end;
}

void Driver::new_travel(time_t start, time_t end, int driver_id, int distance)
{
    if (missions.size() == 0)
    {
        return;
    }
    for (int i=0; i<missions.size();i++)
    {
        missions[i].cached_score = missions[i].mission->check_travel(missions[i].cached_score, distance, start, end);
        if ( missions[i].mission->is_mission_complete(missions[i].cached_score) && missions[i].end_travel == NOT_COMPLETE)
        {
            this->change_DiverMission_end(end,i);
        }
    }
}

void Driver::print_completed_missions(time_t end)
{
    cout << "completed missions for driver " << driver_id << ":" << endl;
    int item_number = 0;
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i].end_travel == end)
        {
            item_number++;
            if (item_number != 1)
            {
                cout << endl;
            }
            missions[i].mission->print2(end);
        }
    }
}

void Driver::print_missions()
{
    if(missions.size()==0)
    {
        cout<<"DRIVER_MISSION_NOT_FOUND"<<endl;
    }
    cout << "missions status for driver " << driver_id << ":" << endl;
    for (int i = 0; i < missions.size(); i++)
    {
        if (i != 0)
        {
            cout << endl;
        }
        missions[i].mission->print(missions[i].end_travel);
        cout << "status: ";
        if (missions[i].end_travel == NOT_COMPLETE)
        {
            cout << "ongoing" << endl;
        }
        else
        {
            cout << "completed" << endl;
        }
    }
}
