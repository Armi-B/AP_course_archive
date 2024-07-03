#include <vector>
#include "Mission.hh"
#include "Manual.hh"
using namespace std;

struct DriverMission
{
    Mission * mission;
    long cached_score;
    time_t end_travel;
};

class Driver
{
private:
    int driver_id;
    int rewards;
    vector<DriverMission> missions;
public:
    Driver(int id);
    void assign_new_mission(Mission * Mission);
    bool is_id_same(int id);
    int find_mission_ind(int id);
    void new_travel(time_t start, time_t end, int driver_id, int distance);
    void print_completed_missions(time_t end);
    void print_missions();
    void sort_driver_missions();
    void change_DiverMission_end(time_t end, int index);
};
