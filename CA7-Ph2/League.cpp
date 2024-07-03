#include <vector>
#include <string>
#include "League.hh"

League::League(string name) : name(name)
{
}

void League::get_new_teams(Team * team)
{
    teams.push_back(team);
}

void League::get_new_week(Week * week)
{
    weeks.push_back(week);
}
