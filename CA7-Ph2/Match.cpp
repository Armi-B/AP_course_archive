#include <string>
#include <vector>
#include <iostream>
#include "Match.hh"

Match::Match(Team *team1, Team *team2, int point_team1, int point_team2)
{
    match_teams.push_back(team1);
    match_teams.push_back(team2);
    result.push_back(point_team1);
    result.push_back(point_team2);
}

void Match::print_match()
{
    cout << match_teams[0]->get_name() << " " << result[0] << " | " << match_teams[1]->get_name() << " " << result[1] << endl;
}
