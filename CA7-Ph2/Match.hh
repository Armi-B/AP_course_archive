#include <string>
#include <vector>
#include "Team.hh"
using namespace std;
#pragma once

class Match
{
private:
    vector<Team *> match_teams;
    vector<int> result;

public:
    Match(Team *team1, Team *team2, int point_team1, int point_team2);
    void print_match();
};
