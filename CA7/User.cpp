#include <string>
#include "User.hh"

Permission::Permission(PERMISSION_TYPE type, bool accessible) : type(type), accessible(accessible)
{
}

bool User::is_same_name(string given_name)
{
    return given_name == name;
}

bool User::is_same_pass(string given_pass)
{
    return given_pass == password;
}

User::User(string name, string pass, vector<Permission *> accesses) : name(name), password(pass), accesses(accesses)
{
}

User::~User()
{
}

NormalUser::NormalUser(string name, string pass, vector<Permission *> accesses) : User(name, pass, accesses)
{
    did_ever_complete_a_team = false;
    fantasy_team = new FantasyTeam();
    remaining_buy = DEFAULT_BUY_COUNT;
    remaining_sell = DEFAULT_SELL_COUNT;
}

NormalUser::~NormalUser()
{
    delete fantasy_team;
}

void NormalUser::sell_a_player()
{
    if(remaining_sell=0 && did_ever_complete_a_team)
    {
        throw MyException("Permission Denied");
    }
    fantasy_team->sell_player();
    if(did_ever_complete_a_team)
    {
        remaining_sell--;
    }
}

void NormalUser::buy_a_player(Player *player, const vector<int> &role_num)
{
    if(remaining_buy=0 && did_ever_complete_a_team)
    {
        throw MyException("Permission Denied");
    }
    fantasy_team->buy_player(player,role_num);
    if(did_ever_complete_a_team)
    {
        remaining_sell--;
    }
}

void NormalUser::update_f_team_score(int curr_week_code)
{
    did_ever_complete_a_team = did_ever_complete_a_team | fantasy_team->update_team_score(curr_week_code);
    remaining_buy = DEFAULT_BUY_COUNT;
    remaining_sell = DEFAULT_SELL_COUNT;
}

void NormalUser::print_fantasy_team()
{
    fantasy_team->print(name);
}

Admin::Admin(string name, string pass, vector<Permission *> accesses) : User(name, pass, accesses)
{
}

bool User::is_accessible(PERMISSION_TYPE given_type)
{
    for (int i = 0; i < accesses.size(); i++)
    {
        if (accesses[i]->is_type_same(given_type) && accesses[i]->can_do())
        {
            return true;
        }
    }
    return false;
}

bool Permission::is_type_same(PERMISSION_TYPE given_type)
{
    return given_type == type;
}

bool Permission::can_do()
{
    return accessible;
}

