#include <vector>
#include <string>
#include <iostream>
#include "Player.hh"

using namespace std;

Player::Player(PLAYER_ROLE role, string name) : name(name), role(role), is_ready(true)
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
    return second_p->is_same_role(role)&&((point[week_code]>second_p->get_point(week_code))||(point[week_code]==second_p->get_point(week_code)&&name<second_p->get_name()));
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

void Player::update_point(float score, int week_index)
{
    point[week_index] = score;
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

void Player::print_player_for_its_team(int week_code)
{
    cout<<"name: "<<name<<" | role: "<<AB_ROLE_NAMES[role]<<" | score: ";
    if(get_point(week_code) == NO_MATCH_PLAY)
    {
        cout<<0<<endl;
    }
    else
    {
        cout<<this->get_point(week_code)<<endl;
    }
}

