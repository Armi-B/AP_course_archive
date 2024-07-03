#include <string>
#include "Team.hh"
#include "Week.hh"
using namespace std;

#pragma once
class League
{
private:
    string name;
    vector<Team *> teams;
    vector<Week *> weeks;

public:
    League(string name);
    void get_new_teams(Team *team);
    void get_new_week(Week *week);
};