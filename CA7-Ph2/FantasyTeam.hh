#include <vector>
#include <iostream>
#include "Player.hh"
#include "Manual.hh"
#include "Exceptions.hh"
using namespace std;

class FantasyTeam
{
private:
    unsigned team_size;
    vector<float> weeks_point;
    vector<int> num_of_role_player;
    vector<Player *> players;
    int captain_index;

public:
    FantasyTeam();
    int find_player_by_name(string p_name);
    int find_player_by_role(PLAYER_ROLE role, int n_th);
    void delete_a_player(int player_index);
    int sell_player();
    void buy_player(Player *player, const vector<int> &role_num);
    void sort_players_by_name(vector<Player *> &g_players);
    bool update_team_score(int curr_week_code);
    void print(string team_name, int week_code);
    void set_captain(string name);
    int get_total_point(int curr_week_code);
    int get_total_price();
};
