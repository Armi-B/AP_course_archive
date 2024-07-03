#include <string>
#include <vector>
#include "Manual.hh"
using namespace std;

#pragma once

class Player
{
private:
    string name;
    vector<float> point;
    PLAYER_ROLE role;
    int num_y_cards;
    int remaining_injury_time;
    bool red_card;
    bool is_ready;
public:
    Player(PLAYER_ROLE role, string name);
    bool is_name_same(string p_name);
    bool is_same_role(PLAYER_ROLE g_role);
    bool is_playing_better_than(int week_code, Player *second_p);
    void update_with_y_card();
    void update_with_r_card();
    void update_with_injury();
    void update_health();
    void update_point(float score, int week_index);
    void update_is_ready();
    bool ready();
    PLAYER_ROLE get_role();
    string get_name();
    float get_point(int curr_week_code);
    void print_player_for_its_team(int week_code);
};
