#include <string>
#include <vector>
#include <iostream>
#include "Team.hh"

Team::Team(string name, vector<Player *> players) : players(players), name(name)
{
    GA = 0;
    GF = 0;
    score = 0;
}

bool Team::is_name_same(string given_name)
{
    return name == given_name;
}

void Team::update_with_a_match(int gf, int ga)
{
    if (gf > ga)
    {
        score += 3;
    }
    else if (gf == ga)
    {
        score++;
    }
    GA += ga;
    GF += gf;
}

string Team::get_name()
{
    return name;
}

int Team::get_score()
{
    return score;
}

int Team::goal_difference()
{
    return GF - GA;
}

int Team::get_gf()
{
    return GF;
}

void Team::print_team()
{
    cout << name << ": score: " << score << " | GF: " << GF << " | GA: " << GA << endl;
}

vector<Player *> Team::chose_players(int role)
{
    vector<Player *> chosen_players;
    if (role == ALL_ROLES)
    {
        chosen_players = players;
    }
    else
    {
        for (Player *p : players)
        {
            if (p->is_same_role((PLAYER_ROLE)role))
            {
                chosen_players.push_back(p);
            }
        }
    }
    return chosen_players;
}

void Team::update_players_point(int opponent_goals, int week_index, int result_default, const vector<string> &present_players, const vector<string> &opponent_players, const vector<string> &goals, const vector<string> &assists, const vector<string> &own_goals)
{
    this->update_plyers_with_result(opponent_goals, week_index, result_default, present_players);
    this->update_players_with_goals(week_index, goals, assists, own_goals);
    this->update_players_with_opponent_goals(opponent_goals, week_index, present_players, opponent_players, goals);
    this->update_players_point_with_Ax( week_index, present_players);
}

void Team::update_plyers_with_result(int opponent_goals, int week_ind, int result_default, const vector<string> &present_players)
{
    for (int i = 0; i < present_players.size(); i++)
    {
        for (Player *p : players)
        {
            if (p->is_name_same(present_players[i]))
            {
                p->update_point_with_default_points(result_default, week_ind);
                if (opponent_goals == 0)
                {
                    p->update_point_with_clean_sheet(week_ind);
                }
            }
        }
    }
}

void Team::update_players_with_goals(int week_index, const vector<string> &goals, const vector<string> &assists, const vector<string> &own_goals)
{
    for (int i = 0; i < goals.size(); i++)
    {
        for (Player *p : players)
        {
            if (p->is_name_same(goals[i]))
            {
                p->update_point_with_goals(week_index);
            }
        }
    }
    for (int i = 0; i < assists.size(); i++)
    {
        for (Player *p : players)
        {
            if (p->is_name_same(assists[i]))
            {
                p->update_point_with_assists(week_index);
            }
        }
    }
    for (int i = 0; i < own_goals.size(); i++)
    {
        for (Player *p : players)
        {
            if (p->is_name_same(own_goals[i]))
            {
                p->update_point_with_own_goal(week_index);
            }
        }
    }
}

void Team::update_players_with_opponent_goals(int opponent_goals, int week_index, const vector<string> &present_players, const vector<string> &opponent_players, const vector<string> &goals)
{
    for (int i = 0; i < present_players.size(); i++)
    {
        for (Player *p : players)
        {
            if (p->is_name_same(present_players[i]))
            {
                p->update_point_with_opponent_goal(week_index, opponent_goals, i, opponent_players, goals);
            }
        }
    }
}

void Team::update_players_point_with_Ax(int week_index, const vector<string> &present_players)
{
    for (int i = 0; i < present_players.size(); i++)
    {
        for (Player *p : players)
        {
            if (p->is_name_same(present_players[i]))
            {
                p->update_point_with_Ax(week_index);
            }
        }
    }
}
