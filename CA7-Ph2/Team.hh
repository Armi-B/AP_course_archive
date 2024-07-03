#include <string>
#include <vector>
#include "Player.hh"
using namespace std;

#pragma once

class Team
{
private:
    string name;
    int GA;
    int GF;
    int score;
    vector<Player *> players;

    void update_plyers_with_result(int opponent_goals, int week_ind, int result_default, const vector<string> &present_players);
    void update_players_with_goals(int week_index, const vector<string> &goals, const vector<string> &assists, const vector<string> &own_goals);
    void update_players_with_opponent_goals(int opponent_goals, int week_index, const vector<string> &present_players, const vector<string> &opponent_players, const vector<string> &goals);
    void update_players_point_with_Ax(int week_index, const vector<string> &present_players);

public:
    Team(string name, vector<Player *> players);
    bool is_name_same(string given_name);
    void update_with_a_match(int GF, int GA);
    void update_players_point(int opponent_goals, int week_index, int result_default, const vector<string> &present_players, const vector<string> &opponent_players, const vector<string> &goals, const vector<string> &assists, const vector<string> &own_goals);
    string get_name();
    int get_score();
    int goal_difference();
    int get_gf();
    void print_team();
    vector<Player *> chose_players(int role);
};