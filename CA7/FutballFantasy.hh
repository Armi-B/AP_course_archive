#include <vector>
#include "League.hh"
#include "Player.hh"
#include "Team.hh"
#include "User.hh"
#include "Exceptions.hh"

using namespace std;
#pragma once

class FutballFantasy
{
private:
    vector<User *> users;
    vector<User *> admins;
    vector<Player *> players;
    vector<Team *> teams;
    vector<Week *> weeks;
    League *league;

    User *curr_user;
    int curr_week_code;
    bool open_transfer_window;

    vector<Permission *> user_access;
    vector<Permission *> admin_access;
    vector<int> default_num_of_role_in_team;

    void read_league();
    void read_a_week(string address);

    void post_command_handle(string command);
    void get_command_handle(string command);

    void make_accesses(vector<Permission *> &user, vector<Permission *> &admin);
    void make_default_num_of_role();

    void sign_up();
    void login();
    void logout();
    void sell_player();
    void buy_player();
    void register_admin();
    void change_transfer_window();
    void pass_week();

    NormalUser *add_user();
    void update(string injured, string y_cards, string r_cards, string scores);
    void update_players_scores(string scores);
    void update_players_cards(string r_card, string y_card);
    void update_players_health(string injuries);
    void update_team(string team1, string team2, string point1, string point2);
    void update_fantasy_team_score();

    void matches_result_league();
    void league_standings();
    void squad();
    void team_of_the_week();
    void show_team_players();

    void read_optional_week_num(int &week_code);
    void read_squad_parameter(int &user_index);
    void read_players_parameter(string &team_name, bool &ranks, int &role);

    void sort_team_by_points();
    void print_team_of_week(int week_code);
    vector<Player*> find_two_bests_in_role(int week_code, PLAYER_ROLE g_role);
    int specify_role(string second_part);
    void print_team_players(int team_ind, bool ranks, int role);
    void sort_players_with_points(vector<Player *> &chosen_players);

    int find_team(string name);
    int find_user_name(const vector<User *> &goal_user, string name);
    int find_player(string p_name);
    int find_week(int week_code);
    int check_acc();
    int check_admin_acc();

    void free_memory();
    void free_players();
    void free_weeks();
    void free_teams();
    void free_admins();
    void free_users();
    void free_accesses();
public:
    FutballFantasy();
    void start_futball_fantasy();
};
