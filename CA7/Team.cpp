#include <string>
#include <vector>
#include <iostream>
#include "Team.hh"

Team::Team(string name, vector<Player *> players): players(players), name(name)
{
    GA =0;
    GF =0;
    score =0;
}

bool Team::is_name_same(string given_name)
{
    return name==given_name;
}

void Team::update_with_a_match(int gf, int ga)
{
    if(gf>ga)
    {
        score += 3;
    }
    else if(gf==ga)
    {
        score++;
    }
    GA+=ga;
    GF+=gf;
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
    return GF-GA;
}

int Team::get_gf()
{
    return GF;
}

void Team::print_team()
{
    cout<<name<<": score: "<<score<<" | GF: "<<GF<<" | GA: "<<GA<<endl;
}

vector<Player *> Team::chose_players(int role)
{
    vector<Player *> chosen_players;
    if(role==ALL_ROLES)
    {
        chosen_players = players;
    }
    else
    {
        for(Player *p : players)
        {
            if(p->is_same_role((PLAYER_ROLE) role))
            {
                chosen_players.push_back(p);
            }
        }
    }
    return chosen_players;
}
