#include <algorithm>
#include <iostream>
#include "FantasyTeam.hh"

using namespace std;

FantasyTeam::FantasyTeam() : team_size(0)
{
    vector<int> num_role_in_team(NUM_OF_ROLE_TYPE, 0);
    num_of_role_player = num_role_in_team;
    vector<float> team_point(19, NOT_COMPLETE);
    weeks_point = team_point;
    captain_index = NOT_COMPLETE;
}

int FantasyTeam::find_player_by_name(string p_name)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->is_name_same(p_name))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

int FantasyTeam::find_player_by_role(PLAYER_ROLE role, int n_th)
{
    vector<Player *> role_players;
    for (Player *player : players)
    {
        if (player->is_same_role(role))
        {
            role_players.push_back(player);
        }
    }
    if (role_players.size() == 0)
    {
        return NOT_FOUND;
    }
    this->sort_players_by_name(role_players);
    return find_player_by_name(role_players[n_th - 1]->get_name());
}

void FantasyTeam::delete_a_player(int player_index)
{
    if (player_index == NOT_FOUND)
    {
        throw MyException(NOT_FOUND_ERR);
    }
    num_of_role_player[players[player_index]->get_role()]--;
    players.erase(players.begin() + player_index);
    team_size--;
}

int FantasyTeam::sell_player()
{
    if (team_size == 0)
    {
        throw MyException(BAD_REQUEST_ERR);
    }
    string name, trash;
    cin >> trash >> trash;
    getline(cin, name);
    name.erase(name.begin());
    int ind = this->find_player_by_name(name);
    this->delete_a_player(ind);
    return players[ind]->get_price();
}

void FantasyTeam::buy_player(Player *player, const vector<int> &role_num)
{
    if (team_size >= MAX_SIZE_OF_TEAM || role_num[player->get_role()] <= num_of_role_player[player->get_role()] || this->find_player_by_name(player->get_name()) != NOT_FOUND)
    {
        throw MyException(BAD_REQUEST_ERR);
    }
    if (!player->ready())
    {
        throw MyException(UNAVAILABLE_PLAYER_ERR);
    }
    players.push_back(player);
    num_of_role_player[player->get_role()]++;
    team_size++;
}

void FantasyTeam::sort_players_by_name(vector<Player *> &g_players)
{
    sort(g_players.begin(), g_players.end(), [](Player *first, Player *second)
         { return first->get_name() < second->get_name(); });
}

bool FantasyTeam::update_team_score(int curr_week_code)
{
    bool result = false;
    int new_point = 0;
    if (team_size == MAX_SIZE_OF_TEAM)
    {
        result = true;
        for (int i = 0; i < MAX_SIZE_OF_TEAM; i++)
        {
            if (players[i]->ready())
            {
                int player_point = (players[i]->get_point(curr_week_code));
                if(player_point == NO_MATCH_PLAY)
                {
                    player_point = 0;
                }
                if (i == captain_index)
                {
                    new_point += CAPTAIN_FACTOR * player_point;
                }
                else
                {
                    new_point += player_point;
                }
            }
            else
            {
                result = false;
                new_point = 0;
                break;
            }
        }
    }
    weeks_point[curr_week_code] = new_point;
    return result;
}

void FantasyTeam::print(string team_name, int week_code)
{
    if (!(team_size == MAX_SIZE_OF_TEAM))
    {
        throw MyException("Empty");
    }
    cout << "fantasy_team: " << team_name << endl;
    for (int i = 0; i < NUM_OF_ROLE_TYPE; i++)
    {
        if (i == 1)
        {
            for (int j = 1; j < 3; j++)
            {
                cout << ROLE_NAMES[i] << j << ": " << players[find_player_by_role((PLAYER_ROLE)i, j)]->get_name();
                if (i == captain_index)
                {
                    cout << " (CAPTAIN)";
                }
                cout << endl;
            }
        }
        else
        {
            cout << ROLE_NAMES[i] << ": " << players[find_player_by_role((PLAYER_ROLE)i, 1)]->get_name();
            if (i == captain_index)
            {
                cout << " (CAPTAIN)";
            }
            cout << endl;
        }
    }
    cout << "Total Points: " << this->get_total_point(week_code) << endl;
    cout << "Total Cost: " << this->get_total_price() << endl;
}

void FantasyTeam::set_captain(string name)
{
    int index = this->find_player_by_name(name);
    if (index == NOT_FOUND)
    {
        throw MyException(NOT_FOUND_ERR);
    }
    captain_index = index;
}

int FantasyTeam::get_total_point(int curr_week_code)
{
    int total_point = 0;
    for (int w = 0; w < curr_week_code; w++)
    {
        if (weeks_point[w] == NOT_COMPLETE)
        {
            continue;
        }
        total_point += weeks_point[w];
    }
    return total_point;
}

int FantasyTeam::get_total_price()
{
    int total_price = 0;
    for (int w = 0; w < MAX_SIZE_OF_TEAM; w++)
    {
        total_price += players[w]->get_price();
    }
    return total_price;
}
