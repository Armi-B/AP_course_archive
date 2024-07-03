#include <string>
#include <vector>
#include "Manual.hh"
using namespace std;

#pragma once

class Player
{
protected:
    vector<float> point;
    string name;
    PLAYER_ROLE role;
    int num_y_cards;
    int remaining_injury_time;
    int price;
    bool red_card;
    bool is_ready;

public:
    Player(PLAYER_ROLE role, string name, int price);
    bool is_name_same(string p_name);
    bool is_same_role(PLAYER_ROLE g_role);
    bool is_playing_better_than(int week_code, Player *second_p);
    bool can_bought(int budget);
    void update_with_y_card();
    void update_with_r_card();
    void update_with_injury();
    void update_health();
    virtual void update_point_with_default_points(int result, int week_code)=0;
    virtual void update_point_with_clean_sheet(int week_ind) = 0;
    virtual void update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals) = 0;
    virtual void update_point_with_assists(int week_index) = 0;
    virtual void update_point_with_goals(int week_index) = 0;
    void update_point_with_own_goal(int week_ind);
    void update_point_with_Ax(int week_ind);
    void update_is_ready();
    bool ready();
    PLAYER_ROLE get_role();
    string get_name();
    float get_point(int curr_week_code);
    int get_price();
    virtual void print_player_for_its_team(int week_code) = 0;
};

class GK_Player : public Player
{
private:
    int clean_sheet;
public:
    GK_Player(PLAYER_ROLE role, string name, int price);
    void update_point_with_default_points(int result, int week_code);
    void update_point_with_clean_sheet(int week_ind);
    void update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals);
    void update_point_with_goals(int week_index);
    void update_point_with_assists(int week_index);
    void print_player_for_its_team(int week_index);
};

class DF_Player : public Player
{
private:
    int clean_sheet;
    int goals;
    int assist_goal;
public:
    DF_Player(PLAYER_ROLE role, string name, int price);
    void update_point_with_default_points(int result, int week_code);
    void update_point_with_clean_sheet(int week_ind);
    void update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals);
    void update_point_with_goals(int week_index);
    void update_point_with_assists(int week_index);
    void print_player_for_its_team(int week_code);
};

class MD_Player : public Player
{
private:
    int clean_sheet;
    int goals;
    int assist_goal;
public:
    MD_Player(PLAYER_ROLE role, string name, int price);
    void update_point_with_default_points(int result, int week_code);
    void update_point_with_clean_sheet(int week_ind);
    void update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals);
    void update_point_with_goals(int week_index);
    void update_point_with_assists(int week_index);
    void print_player_for_its_team(int week_code);
};

class FW_Player : public Player
{
private:
    int goals;
    int assist_goal;
public:
    FW_Player(PLAYER_ROLE role, string name, int price);
    void update_point_with_default_points(int result, int week_code);
    void update_point_with_clean_sheet(int week_ind);
    void update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals);
    void update_point_with_goals(int week_index);
    void update_point_with_assists(int week_index);
    void print_player_for_its_team(int week_code);
};
