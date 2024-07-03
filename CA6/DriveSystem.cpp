#include "Manual.hh"
#include "DriveSystem.hh"

int DriveSystem::find_mission_ind(int id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->is_id_same(id))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

int DriveSystem::find_driver_ind(int id)
{
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->is_id_same(id))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

bool DriveSystem::is_mission_duplicated(int mission_id)
{
    if (this->find_mission_ind(mission_id) != NOT_FOUND)
    {
        cout << "DUPLICATE_MISSION_ID" << endl;
        return true;
    }
    return false;
}

void DriveSystem::creat_time_mission()
{
    int mission_id, reward_amount;
    time_t start, end, target;
    int status = scanf("%d %ld %ld %ld %d",&mission_id,&start,&end,&target, &reward_amount);
    if(status!= 5)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    //cin >> mission_id >> start >> end >> target >> reward_amount;
    if (this->is_mission_duplicated(mission_id))
    {
        return;
    }
    try
    {
        missions.push_back(new TimeMission(mission_id, start, end, reward_amount, target));
        cout << "OK" << endl;
    }
    catch (runtime_error &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}

void DriveSystem::creat_distance_mission()
{
    int mission_id, reward_amount, target;
    time_t start, end;
    int status = scanf("%d %ld %ld %d %d",&mission_id,&start,&end,&target, &reward_amount);
    if(status!= 5)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    //cin >> mission_id >> start >> end >> target >> reward_amount;
    if (this->is_mission_duplicated(mission_id))
    {
        return;
    }
    try
    {
        missions.push_back(new DistanceMission(mission_id, start, end, reward_amount, target));
        cout << "OK" << endl;
    }
    catch (runtime_error &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}

void DriveSystem::creat_count_mission()
{
    int mission_id, reward_amount, target;
    time_t start, end;
    int status = scanf("%d %ld %ld %d %d",&mission_id,&start,&end,&target, &reward_amount);
    if(status!= 5)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    //cin >> mission_id >> start >> end >> target >> reward_amount;
    if (this->is_mission_duplicated(mission_id))
    {
        return;
    }
    try
    {
        missions.push_back(new CountMission(mission_id, start, end, reward_amount, target));
        cout << "OK" << endl;
    }
    catch (runtime_error &ex)
    {
        cout << "INVALID_ARGUMENTS" << endl;
    }
}

void DriveSystem::assign_mission()
{
    int driver_id, mission_id, driver_ind, mission_ind;
    int status = scanf("%d %d",&mission_id,&driver_id);
    if(status!= 2)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    //cin >> mission_id >> driver_id;
    mission_ind = this->find_mission_ind(mission_id);
    if (mission_ind == NOT_FOUND)
    {
        cout << "MISSION_NOT_FOUND" << endl;
        return;
    }
    driver_ind = this->find_driver_ind(driver_id);
    if (driver_ind == NOT_FOUND)
    {
        drivers.push_back(new Driver(driver_id));
        driver_ind = drivers.size() - 1;
    }
    else if (drivers[driver_ind]->find_mission_ind(mission_id) != NOT_FOUND)
    {
        cout << "DUPLICATE_DRIVER_MISSION" << endl;
        return;
    }
    drivers[driver_ind]->assign_new_mission(missions[mission_ind]);
    drivers[driver_ind]->sort_driver_missions();
    cout << "OK" << endl;
}

void DriveSystem::record_ride()
{
    int distance, id;
    time_t start, end;
    int status = scanf("%ld %ld %d %d",&start,&end,&id, &distance);
    if(status!= 4)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    //cin >> start >> end >> id >> distance;
    if (start > end)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    int driver_index = find_driver_ind(id);
    drivers[driver_index]->new_travel(start, end, id, distance);
    drivers[driver_index]->print_completed_missions(end);
}

void DriveSystem::show_missions_status()
{
    int id;
    int status = scanf("%d",&id);
    if(status!= 1)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    //cin>>id;
    int driver_index = find_driver_ind(id);
    if(driver_index==NOT_FOUND)
    {
        return;
    }
    drivers[driver_index]->print_missions();
}

void DriveSystem::start_system()
{
    string command;
    while (cin >> command)
    {
        if (command == "add_time_mission")
        {
            this->creat_time_mission();
        }
        else if (command == "add_distance_mission")
        {
            this->creat_distance_mission();
        }
        else if (command == "add_count_mission")
        {
            this->creat_count_mission();
        }
        else if (command == "assign_mission")
        {
            this->assign_mission();
        }
        else if (command == "record_ride")
        {
            this->record_ride();
        }
        else if(command == "show_missions_status")
        {
            this->show_missions_status();
        }
    }
    for (int i = 0; i < drivers.size(); i++)
    {
        delete drivers[i];
    }
    for (int i = 0; i < missions.size(); i++)
    {
        delete missions[i];
    }
}
