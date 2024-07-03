#include <vector>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include "Player.hh"

using namespace std;

Player::Player(PLAYER_ROLE role, string name, int price) : name(name), role(role), is_ready(true), price(price)
{
    vector<float> point_vector(19, NO_MATCH_PLAY);
    point = point_vector;
    remaining_injury_time = 0;
    num_y_cards = 0;
    red_card = false;
}

bool Player::is_name_same(string p_name)
{
    return p_name == name;
}

bool Player::is_same_role(PLAYER_ROLE g_role)
{
    return g_role == role;
}

bool Player::is_playing_better_than(int week_code, Player *second_p)
{
    return second_p->is_same_role(role) && ((point[week_code] > second_p->get_point(week_code)) || (point[week_code] == second_p->get_point(week_code) && name < second_p->get_name()));
}

bool Player::can_bought(int budget)
{
    return budget - price > 0;
}

void Player::update_with_y_card()
{
    num_y_cards++;
}

void Player::update_with_r_card()
{
    num_y_cards = 0;
    red_card = true;
}

void Player::update_with_injury()
{
    remaining_injury_time = INJURY_PERIOD;
}

void Player::update_health()
{
    if (remaining_injury_time > 0)
    {
        remaining_injury_time--;
    }
}

void Player::update_point_with_own_goal(int week_ind)
{
    point[week_ind] += GOAL_INTO_OWN_GATE_POINT;
}

void Player::update_point_with_Ax(int week_ind)
{
    point[week_ind] = A(point[week_ind]);
}

void Player::update_is_ready()
{
    is_ready = true;
    if (red_card)
    {
        num_y_cards = 0;
        is_ready = false;
    }
    if (remaining_injury_time > 0)
    {
        is_ready = false;
    }
    if (num_y_cards >= 3)
    {
        num_y_cards = 0;
        is_ready = false;
    }
}

bool Player::ready()
{
    return is_ready;
}

PLAYER_ROLE Player::get_role()
{
    return role;
}

string Player::get_name()
{
    return name;
}

float Player::get_point(int curr_week_code)
{
    return point[curr_week_code];
}

int Player::get_price()
{
    return price;
}

GK_Player::GK_Player(PLAYER_ROLE role, string name, int price) : Player(role, name, price)
{
    clean_sheet = 0;
}

void GK_Player::update_point_with_default_points(int match_result, int week_ind)
{
    point[week_ind] = match_result + DEFAULT_GK_POINT;
}

void GK_Player::update_point_with_clean_sheet(int week_ind)
{
    clean_sheet ++;
    point[week_ind] += GK_CLEAN_SHEET_POINT;
}

void GK_Player::update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals)
{
    point[week_ind] += GK_CANT_KEEP_GOAL_POINT* num_goals;
}

void GK_Player::update_point_with_goals(int week_index)
{
    point[week_index] += 0;
}

void GK_Player::update_point_with_assists(int week_index)
{
    point[week_index] += 0;
}

void GK_Player::print_player_for_its_team(int week_code)
{
    cout << "name: " << name << " | role: " << AB_ROLE_NAMES[role] << " | score: ";
    if (get_point(week_code) == NO_MATCH_PLAY)
    {
        cout << 0;
    }
    else
    {
        cout << this->get_point(week_code);
    }
    cout<<" | cost: "<<price<<" | clean sheets: "<<clean_sheet<<endl;
}

DF_Player::DF_Player(PLAYER_ROLE role, string name, int price) : Player(role, name, price)
{
    clean_sheet = 0;
    goals = 0;
    assist_goal = 0;
}

void DF_Player::update_point_with_default_points(int result, int week_code)
{
    point[week_code] = result + DEFAULT_DF_POINT;
}

void DF_Player::update_point_with_clean_sheet(int week_ind)
{
    clean_sheet++;
    point[week_ind] += DF_CLEAN_SHEET_POINT;
}

void DF_Player::update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals)
{
    for (int i = 0; i < goals.size(); i++)
    {
        if(player_ind == LEFT_DF_INDEX && (goals[i] == opponent_players[RIGHT_DF_INDEX] || goals[i] == opponent_players[RIGHT_FW_INDEX])
        || player_ind == RIGHT_DF_INDEX && (goals[i] == opponent_players[LEFT_DF_INDEX] || goals[i] == opponent_players[LEFT_FW_INDEX])
        || (player_ind == MIDDLE_RIGHT_DF_INDEX||player_ind == MIDDLE_LEFT_DF_INDEX) && (goals[i] == opponent_players[MIDDLE_FW_INDEX] || goals[i] == opponent_players[MIDDLE_LEFT_DF_INDEX] || goals[i] == opponent_players[MIDDLE_RIGHT_DF_INDEX]))
        {
            point[week_ind] += TARGET_PLAYER_GOAL_POINT;
        }
    }
}

void DF_Player::update_point_with_goals(int week_index)
{
    goals++;
    point[week_index] += DF_GOAL_POINT;
}

void DF_Player::update_point_with_assists(int week_index)
{
    assist_goal++;
    point[week_index] += DF_ASSIST_POINT;
}

void DF_Player::print_player_for_its_team(int week_code)
{
    cout << "name: " << name << " | role: " << AB_ROLE_NAMES[role] << " | score: ";
    if (get_point(week_code) == NO_MATCH_PLAY)
    {
        cout << 0;
    }
    else
    {
        cout << this->get_point(week_code);
    }
    cout<<" | cost: "<<price<<" | clean sheets: "<<clean_sheet<<" | goals: "<< goals<<" | assists: "<<assist_goal<<endl;
}

MD_Player::MD_Player(PLAYER_ROLE role, string name, int price) : Player(role, name, price)
{
    clean_sheet = 0;
    goals = 0;
    assist_goal = 0;
}

void MD_Player::update_point_with_default_points(int result, int week_code)
{
    point[week_code] = result + DEFAULT_MD_POINT;
}

void MD_Player::update_point_with_clean_sheet(int week_ind)
{
    clean_sheet++;
    point[week_ind] += MD_CLEAN_SHEET_POINT;
}

void MD_Player::update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals)
{
    for (int i = 0; i < goals.size(); i++)
    {
        if(goals[i]== opponent_players[LEFT_MD_INDEX]||goals[i]== opponent_players[RIGHT_MD_INDEX]||goals[i]== opponent_players[MIDDLE_MD_INDEX])
        {
            point[week_ind] += TARGET_PLAYER_GOAL_POINT;
        }
    }
}

void MD_Player::update_point_with_goals(int week_index)
{
    goals++;
    point[week_index] += MD_GOAL_POINT;
}

void MD_Player::update_point_with_assists(int week_index)
{
    assist_goal++;
    point[week_index] += MD_ASSIST_POINT;
}

void MD_Player::print_player_for_its_team(int week_code)
{
    cout << "name: " << name << " | role: " << AB_ROLE_NAMES[role] << " | score: ";
    if (get_point(week_code) == NO_MATCH_PLAY)
    {
        cout << 0;
    }
    else
    {
        cout << this->get_point(week_code);
    }
    cout<<" | cost: "<<price<<" | clean sheets: "<<clean_sheet<<" | goals: "<< goals<<" | assists: "<<assist_goal<<endl;
}

FW_Player::FW_Player(PLAYER_ROLE role, string name, int price) : Player(role, name, price)
{
    goals = 0;
    assist_goal = 0;
}

void FW_Player::update_point_with_default_points(int result, int week_code)
{
    point[week_code] = result + DEFAULT_FW_POINT;
}

void FW_Player::update_point_with_clean_sheet(int week_ind)
{
    point[week_ind] += 0;
}

void FW_Player::update_point_with_opponent_goal(int week_ind, int num_goals, int player_ind, const vector<string> &opponent_players, const vector<string> &goals)
{
}

void FW_Player::update_point_with_goals(int week_index)
{
    goals++;
    point[week_index] += FW_GOAL_POINT;
}

void FW_Player::update_point_with_assists(int week_index)
{
    assist_goal++;
    point[week_index] += FW_ASSIST_POINT;
}

void FW_Player::print_player_for_its_team(int week_code)
{
    cout << "name: " << name << " | role: " << AB_ROLE_NAMES[role] << " | score: ";
    if (get_point(week_code) == NO_MATCH_PLAY)
    {
        cout << 0;
    }
    else
    {
        cout << this->get_point(week_code);
    }
    cout<<" | cost: "<<price<<" | goals: "<< goals<<" | assists: "<<assist_goal<<endl;
}
