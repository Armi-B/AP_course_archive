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
public:
    Team(string name, vector<Player *> players);
    bool is_name_same(string given_name);
    void update_with_a_match(int GF, int GA);
    string get_name();
    int get_score();
    int goal_difference();
    int get_gf();
    void print_team();
    vector<Player *> chose_players(int role);
};