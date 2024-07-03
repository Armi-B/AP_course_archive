#include <string>
#include <vector>
#include <iostream>
#include "Manual.hh"
#include "Player.hh"
#include "Exceptions.hh"
#include "FantasyTeam.hh"
using namespace std;

#pragma once

class Permission
{
private:
    PERMISSION_TYPE type;
    bool accessible;

public:
    Permission(PERMISSION_TYPE type, bool accessible);
    bool is_type_same(PERMISSION_TYPE type);
    bool can_do();
};

class User
{
protected:
    string name;
    string password;
    vector<Permission *> accesses;

public:
    User(string name, string pass, vector<Permission *> accesses);
    virtual ~User();
    bool is_same_name(string given_name);
    bool is_same_pass(string given_pass);
    bool is_accessible(PERMISSION_TYPE type);
};

class NormalUser : public User
{
private:
    FantasyTeam *fantasy_team;
    unsigned remaining_buy;
    unsigned remaining_sell;
    bool did_ever_complete_a_team;
    int budget;

public:
    NormalUser(string name, string pass, vector<Permission *> accesses);
    ~NormalUser();
    void sell_a_player();
    void buy_a_player(Player *player, const vector<int> &role_num);
    void update_f_team_score(int curr_week_code);
    void print_fantasy_team(int curr_week_code);
    void set_a_captain(string c_name);
    void print_budget();
};

class Admin : public User
{
public:
    Admin(string name, string pass, vector<Permission *> accesses);
};
