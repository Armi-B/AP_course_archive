#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "FutballFantasy.hh"

using namespace std;

FutballFantasy::FutballFantasy()
{
    this->read_league();
    this->make_accesses(user_access, admin_access);
    this->make_default_num_of_role();
    admins.push_back(new Admin(ADMIN_NAME, ADMIN_PASS, admin_access));
    curr_week_code = 1;
    curr_user = nullptr;
    open_transfer_window = true;
}

void FutballFantasy::start_futball_fantasy()
{
    string command_type, command;
    while (std::cin >> command_type)
    {
        if (command_type == GET)
        {
            cin >> command;
            this->get_command_handle(command);
        }
        else if (command_type == PUT)
        {
        }
        else if (command_type == POST)
        {
            cin >> command;
            this->post_command_handle(command);
        }
        else if (command_type == DELETE)
        {
        }
        else
        {
            string trash;
            getline(std::cin, trash);
            cout << BAD_REQUEST_ERR << endl;
        }
    }
    this->free_memory();
}

void FutballFantasy::post_command_handle(string command)
{
    if (command == SIGNUP_COMM)
    {
        this->sign_up();
    }
    else if (command == LOGIN_COMM)
    {
        this->login();
    }
    else if (command == ADMIN_LOGIN_COMM)
    {
        this->register_admin();
    }
    else if (command == LOGOUT_COMM)
    {
        this->logout();
    }
    else if (command == SELL_PLAYER_COMM)
    {
        this->sell_player();
    }
    else if (command == BUY_PLAYER_COMM)
    {
        this->buy_player();
    }
    else if (command == CLOSE_TW_COMM)
    {
        this->close_transfer_wind();
    }
    else if (command == OPEN_TW_COMM)
    {
        this->open_transfer_wind();
    }
    else if (command == PASS_WEEK_COMM)
    {
        this->pass_week();
    }
    else if (command == SET_CAPTAIN)
    {
        this->set_captain();
    }
    else
    {
        string trash;
        getline(std::cin, trash);
        cout << NOT_FOUND_ERR << endl;
    }
}

void FutballFantasy::get_command_handle(string command)
{
    if (command == TEAM_OF_WEEK_COMM)
    {
        this->team_of_the_week();
    }
    else if (command == TEAM_DATA_COMM)
    {
        this->show_team_players();
    }
    else if (command == LEAGUE_DATA_COMM)
    {
        this->league_standings();
    }
    else if (command == MATCHES_DATA_COMM)
    {
        this->matches_result_league();
    }
    else if (command == FANTASY_TEAM_DATA_COMM)
    {
        this->squad();
    }
    else if (command == SHOW_BUDGET_COMM)
    {
        this->show_budget();
    }
    else
    {
        string trash;
        getline(std::cin, trash);
        cout << NOT_FOUND_ERR << endl;
    }
}

void FutballFantasy::sign_up()
{
    try
    {
        if (curr_user != nullptr)
        {
            throw MyException(PERMISSION_ERR);
        }
        User *user = this->add_user();
        curr_user = user;
        cout << SUCCESSFULLY_DONE << endl;
    }
    catch (MyException &ex)
    {
        string trash;
        getline(std::cin, trash);
        ex.print_message();
    }
}

NormalUser *FutballFantasy::add_user()
{
    string trash, name, pass;
    std::cin >> trash >> trash >> name >> trash >> pass;
    int check = this->find_user_name(users, name);
    if (check != NOT_FOUND)
    {
        throw MyException(BAD_REQUEST_ERR);
    }
    NormalUser *user = new NormalUser(name, pass, user_access);
    users.push_back(user);
    return user;
}

int FutballFantasy::find_user_name(const vector<User *> &goal_user, string name)
{
    for (int i = 0; i < goal_user.size(); i++)
    {
        if (goal_user[i]->is_same_name(name))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

int FutballFantasy::find_team(string team_name)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i]->is_name_same(team_name))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

int FutballFantasy::find_player(string p_name)
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

int FutballFantasy::find_week(int week_code)
{
    for (int i = 0; i < weeks.size(); i++)
    {
        if (weeks[i]->is_same_week(week_code))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

void FutballFantasy::free_memory()
{
    this->free_players();
    this->free_weeks();
    this->free_teams();
    this->free_admins();
    this->free_users();
    this->free_accesses();
    delete league;
}

void FutballFantasy::free_players()
{
    for (Player *p : players)
    {
        delete p;
    }
}

void FutballFantasy::free_weeks()
{
    for (Week *w : weeks)
    {
        delete w;
    }
}

void FutballFantasy::free_teams()
{
    for (Team *t : teams)
    {
        delete t;
    }
}

void FutballFantasy::free_admins()
{
    for (User *a : admins)
    {
        delete a;
    }
}

void FutballFantasy::free_users()
{
    for (User *u : users)
    {
        delete u;
    }
}

void FutballFantasy::free_accesses()
{
    for (Permission *per : user_access)
    {
        delete per;
    }
    for (Permission *per : admin_access)
    {
        delete per;
    }
}

void FutballFantasy::login()
{
    try
    {
        if (curr_user != nullptr)
        {
            throw MyException(PERMISSION_ERR);
        }
        int index = this->check_acc();
        curr_user = users[index];
        cout << SUCCESSFULLY_DONE << endl;
    }
    catch (MyException &ex)
    {
        string trash;
        getline(std::cin, trash);
        ex.print_message();
    }
}

int FutballFantasy::check_acc()
{
    string trash, name, pass;
    std::cin >> trash >> trash >> name >> trash >> pass;
    int index = this->find_user_name(users, name);
    if (index == NOT_FOUND)
    {
        throw MyException(NOT_FOUND_ERR);
    }
    if (!users[index]->is_same_pass(pass))
    {
        throw MyException(PERMISSION_ERR);
    }
    return index;
}

void FutballFantasy::logout()
{
    try
    {
        if (curr_user == nullptr)
        {
            throw MyException(PERMISSION_ERR);
        }
        curr_user = nullptr;
        cout << SUCCESSFULLY_DONE << endl;
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

void FutballFantasy::sell_player()
{
    try
    {
        if (curr_user == nullptr || !open_transfer_window)
        {
            throw MyException(PERMISSION_ERR);
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException(PERMISSION_ERR);
        }
        NormalUser *user = (NormalUser *)curr_user;
        user->sell_a_player();
        cout << SUCCESSFULLY_DONE << endl;
    }
    catch (MyException &ex)
    {
        if (!(ex.message_is_equal(NOT_FOUND_ERR)))
        {
            string trash;
            getline(std::cin, trash);
        }
        ex.print_message();
    }
}

void FutballFantasy::buy_player()
{
    string name, trash;
    std::cin >> trash >> trash;
    getline(std::cin, name);
    name.erase(name.begin() + 0);
    int player_ind = this->find_player(name);
    try
    {
        if (curr_user == nullptr || !open_transfer_window)
        {
            throw MyException(PERMISSION_ERR);
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException(PERMISSION_ERR);
        }
        NormalUser *user = (NormalUser *)curr_user;
        int player_ind = this->find_player(name);
        if (player_ind == NOT_FOUND)
        {
            throw MyException(NOT_FOUND_ERR);
        }
        user->buy_a_player(players[player_ind], default_num_of_role_in_team);
        cout << SUCCESSFULLY_DONE << endl;
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

void FutballFantasy::register_admin()
{
    try
    {
        if (curr_user != nullptr)
        {
            throw MyException(PERMISSION_ERR);
        }
        int index = this->check_admin_acc();
        curr_user = admins[index];
        cout << SUCCESSFULLY_DONE << endl;
    }
    catch (MyException &ex)
    {
        string trash;
        getline(std::cin, trash);
        ex.print_message();
    }
}

void FutballFantasy::open_transfer_wind()
{
    if (!open_transfer_window)
    {
        this->change_transfer_window();
    }
    else
    {
        cout << BAD_REQUEST_ERR << endl;
    }
}

void FutballFantasy::close_transfer_wind()
{
    if (open_transfer_window)
    {
        this->change_transfer_window();
    }
    else
    {
        cout << BAD_REQUEST_ERR << endl;
    }
}

int FutballFantasy::check_admin_acc()
{
    string trash, name, pass;
    std::cin >> trash >> trash >> name >> trash >> pass;
    int index = this->find_user_name(admins, name);
    if (index == NOT_FOUND || !admins[index]->is_same_pass(pass))
    {
        throw MyException(BAD_REQUEST_ERR);
    }
    return index;
}

void FutballFantasy::make_accesses(vector<Permission *> &user, vector<Permission *> &admin)
{
    user.push_back(new Permission(PASS_WEEK, false));
    user.push_back(new Permission(TRANSFER_WINDOW, false));
    user.push_back(new Permission(HAVING_F_TEAM, true));

    admin.push_back(new Permission(PASS_WEEK, true));
    admin.push_back(new Permission(TRANSFER_WINDOW, true));
    admin.push_back(new Permission(HAVING_F_TEAM, false));
}

void FutballFantasy::make_default_num_of_role()
{
    vector<int> temp(NUM_OF_ROLE_TYPE, 0);
    default_num_of_role_in_team = temp;
    for (int i = 0; i < NUM_OF_ROLE_TYPE; i++)
    {
        switch (i)
        {
        case DF:
            default_num_of_role_in_team[i] = NUM_OF_DF_IN_TEAM;
            break;
        case GK:
            default_num_of_role_in_team[i] = NUM_OF_GK_IN_TEAM;
            break;
        case MD:
            default_num_of_role_in_team[i] = NUM_OF_MD_IN_TEAM;
            break;
        case FW:
            default_num_of_role_in_team[i] = NUM_OF_FW_IN_TEAM;
            break;
        default:
            break;
        }
    }
}

void FutballFantasy::change_transfer_window()
{
    if (curr_user == nullptr)
    {
        cout << PERMISSION_ERR << endl;
        return;
    }
    if (curr_user->is_accessible(TRANSFER_WINDOW))
    {
        open_transfer_window = (!open_transfer_window);
        cout << SUCCESSFULLY_DONE << endl;
        return;
    }
    cout << PERMISSION_ERR << endl;
}

void FutballFantasy::pass_week()
{
    if (curr_user == nullptr)
    {
        cout << PERMISSION_ERR << endl;
        return;
    }
    if (curr_user->is_accessible(PASS_WEEK))
    {
        read_a_week(WEEK_FILE + to_string(curr_week_code) + ".csv");
        this->sort_team_by_points();
        curr_week_code++;
        cout << SUCCESSFULLY_DONE << endl;
        return;
    }
    cout << PERMISSION_ERR << endl;
}

void FutballFantasy::set_captain()
{
    string name, trash;
    std::cin >> trash >> trash;
    getline(std::cin, name);
    name.erase(name.begin() + 0);
    try
    {
        if (curr_user == nullptr)
        {
            throw MyException(PERMISSION_ERR);
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException(PERMISSION_ERR);
        }
        NormalUser *curr = (NormalUser *)curr_user;
        curr->set_a_captain(name);
        cout << SUCCESSFULLY_DONE << endl;
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

void FutballFantasy::read_league()
{
    league = new League(LEAGUE_NAME);
    string line, role, player, team_name;
    ifstream league_file;
    league_file.open(LEAGUE_FILE, ios::in);
    if (league_file.is_open())
    {
        getline(league_file, line);
        while (getline(league_file, line))
        {
            vector<Player *> temp_players;
            stringstream line_stream(line);
            getline(line_stream, team_name, ',');
            this->read_players(line_stream, temp_players);
            Team *team_ptr = new Team(team_name, temp_players);
            teams.push_back(team_ptr);
            league->get_new_teams(team_ptr);
            players.insert(players.end(), temp_players.begin(), temp_players.end());
        }
    }
    league_file.close();
}

void FutballFantasy::read_players(stringstream &line_stream, vector<Player *> &temp_players)
{
    string role, player;
    for (int i = 0; i < 4; i++)
    {
        getline(line_stream, role, ',');
        stringstream role_stream(role);
        while (getline(role_stream, player, ';'))
        {
            string p_name, price;
            stringstream player_stream(player);
            getline(player_stream, p_name, ':');
            getline(player_stream, price, ':');
            price.pop_back();
            Player *player_ptr;
            switch (i)
            {
            case GK:
                player_ptr = new GK_Player(PLAYER_ROLE(i), p_name, stoi(price));
                break;
            case DF:
                player_ptr = new DF_Player(PLAYER_ROLE(i), p_name, stoi(price));
                break;
            case MD:
                player_ptr = new MD_Player(PLAYER_ROLE(i), p_name, stoi(price));
                break;
            case FW:
                player_ptr = new FW_Player(PLAYER_ROLE(i), p_name, stoi(price));
                break;
            default:
                break;
            }
            temp_players.push_back(player_ptr);
        }
    }
}

void FutballFantasy::read_a_week(string address)
{
    string line, team_names, result, y_card, red_card, goals, injured, team1_players, team2_players;
    vector<Match *> matches;
    ifstream week_file;
    week_file.open(address);
    if (week_file.is_open())
    {
        getline(week_file, line);
        while (getline(week_file, line))
        {
            stringstream line_stream(line);
            getline(line_stream, team_names, ',');
            getline(line_stream, result, ',');
            getline(line_stream, injured, ',');
            getline(line_stream, y_card, ',');
            getline(line_stream, red_card, ',');
            getline(line_stream, goals, ',');
            getline(line_stream, team1_players, ',');
            getline(line_stream, team2_players, ',');
            stringstream team_name_s(team_names);
            string team1_name, team2_name, point1, point2;
            getline(team_name_s, team1_name, ':');
            getline(team_name_s, team2_name, ':');
            stringstream result_stream(result);
            getline(result_stream, point1, ':');
            getline(result_stream, point2, ':');
            this->update(team1_name, team2_name, point1, point2, injured, y_card, red_card, goals, team1_players, team2_players);
            matches.push_back(new Match(teams[find_team(team1_name)], teams[find_team(team2_name)], stoi(point1), stoi(point2)));
        }
    }
    week_file.close();
    weeks.push_back(new Week(curr_week_code, matches));
}

void FutballFantasy::update(string team1_name, string team2_name, string point1, string point2, string injured, string y_cards, string r_cards, string goals, string team1_players, string team2_players)
{
    int point1_i = stoi(point1);
    int point2_i = stoi(point2);
    Team *team1 = teams[find_team(team1_name)];
    Team *team2 = teams[find_team(team2_name)];
    this->update_team(team1, team2, point1_i, point2_i);
    this->update_players_scores(team1, team2, goals, point1_i, point2_i, team1_players, team2_players);
    this->update_fantasy_team_score();
    this->update_players_cards(r_cards, y_cards);
    this->update_players_health(injured);
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->update_is_ready();
    }
}

void FutballFantasy::update_players_scores(Team *team1, Team *team2, string goals, int point1, int point2, string team1_players, string team2_players)
{
    string temp_player, temp_block, temp_goal, temp_assist;
    vector<string> players_team1, players_team2, goals_vec, assists_vec, own_goals;
    stringstream team_1_p(team1_players);
    stringstream team_2_p(team2_players);
    while (getline(team_1_p, temp_player, ';'))
    {
        players_team1.push_back(temp_player);
    }
    while (getline(team_2_p, temp_player, ';'))
    {
        players_team2.push_back(temp_player);
    }
    stringstream goals_stream(goals);
    while (getline(goals_stream, temp_block, ';'))
    {
        stringstream block_stream(temp_block);
        getline(block_stream, temp_goal, ':');
        getline(block_stream, temp_assist, ':');
        if(temp_assist == OWN_GOAL)
        {
            own_goals.push_back(temp_goal);
        }
        else
        {
            goals_vec.push_back(temp_goal);
            assists_vec.push_back(temp_assist);
        }
    }
    if(point1==point2)
    {
        team1->update_players_point(point2, curr_week_code-1, EQUAL_MATCH_POINT, players_team1, players_team2, goals_vec, assists_vec,own_goals );
        team2->update_players_point(point1, curr_week_code-1, EQUAL_MATCH_POINT, players_team2, players_team1, goals_vec, assists_vec, own_goals);
    }
    else if(point1>point2)
    {
        team1->update_players_point(point2, curr_week_code-1, VICTOR_TEAM_POINT, players_team1, players_team2, goals_vec, assists_vec,own_goals );
        team2->update_players_point(point1, curr_week_code-1, LOSER_TEAM_POINT, players_team2, players_team1, goals_vec, assists_vec, own_goals);
    }
    else
    {
        team1->update_players_point(point2, curr_week_code-1, LOSER_TEAM_POINT, players_team1, players_team2, goals_vec, assists_vec,own_goals );
        team2->update_players_point(point1, curr_week_code-1, VICTOR_TEAM_POINT, players_team2, players_team1, goals_vec, assists_vec, own_goals);
    }
}

void FutballFantasy::update_players_cards(string r_cards, string y_cards)
{
    string a_y_card, a_r_card;
    stringstream y_card_stream(y_cards);
    while (getline(y_card_stream, a_y_card, ';'))
    {
        int player_ind = this->find_player(a_y_card);
        if (player_ind != NOT_FOUND)
        {
            players[player_ind]->update_with_y_card();
        }
    }
    stringstream r_card_stream(r_cards);
    while (getline(r_card_stream, a_r_card, ';'))
    {
        int player_ind = this->find_player(a_r_card);
        if (player_ind != NOT_FOUND)
        {
            players[player_ind]->update_with_r_card();
        }
    }
}

void FutballFantasy::update_players_health(string injuries)
{
    string a_injury;
    stringstream injury_stream(injuries);
    while (getline(injury_stream, a_injury, ';'))
    {
        int player_ind = this->find_player(a_injury);
        if (player_ind != NOT_FOUND)
        {
            players[player_ind]->update_with_injury();
        }
    }
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->update_health();
    }
}

void FutballFantasy::update_team(Team *team1, Team *team2, int point1, int point2)
{
    team1->update_with_a_match(point1, point2);
    team2->update_with_a_match(point2, point1);
}

void FutballFantasy::update_fantasy_team_score()
{
    for (int i=0; i<users.size(); i++)
    {
        NormalUser *user = (NormalUser *)users[i];
        user->update_f_team_score(curr_week_code-1);
    }
}

void FutballFantasy::matches_result_league()
{
    int week_code;
    this->read_optional_week_num(week_code);
    try
    {
        if (week_code > MAX_LEAGUE_WEEKS)
        {
            throw MyException(NOT_FOUND_ERR);
        }
        int week_ind = this->find_week(week_code);
        if (week_ind == NOT_FOUND)
        {
            throw MyException(BAD_REQUEST_ERR);
        }
        weeks[week_ind]->print_matches();
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

void FutballFantasy::league_standings()
{
    cout << "league standings:" << endl;
    for (int i = 0; i < teams.size(); i++)
    {
        cout << i << ". ";
        teams[i]->print_team();
    }
}

void FutballFantasy::squad()
{
    int user_index;
    this->read_squad_parameter(user_index);
    try
    {
        if (curr_user == nullptr)
        {
            throw MyException(PERMISSION_ERR);
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException(PERMISSION_ERR);
        }
        if (user_index == NOT_FOUND)
        {
            throw MyException(NOT_FOUND_ERR);
        }
        NormalUser *user;
        if (user_index == CURR_USER)
        {
            user = (NormalUser *)curr_user;
        }
        else
        {
            user = (NormalUser *)users[user_index];
        }
        user->print_fantasy_team(curr_week_code-1);
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

void FutballFantasy::team_of_the_week()
{
    int week_code;
    this->read_optional_week_num(week_code);
    try
    {
        int week_ind = this->find_week(week_code);
        if (week_ind == NOT_FOUND)
        {
            throw MyException(BAD_REQUEST_ERR);
        }
        this->print_team_of_week(week_code - 1);
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

void FutballFantasy::show_team_players()
{
    int role;
    string team_name;
    bool ranks;
    this->read_players_parameter(team_name, ranks, role);
    try
    {
        if (role == INVALID_ROLE)
        {
            throw MyException(BAD_REQUEST_ERR);
        }
        int team_ind = this->find_team(team_name);
        if (team_ind == NOT_FOUND)
        {
            throw MyException(NOT_FOUND_ERR);
        }
        this->print_team_players(team_ind, ranks, role);
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

void FutballFantasy::read_optional_week_num(int &week_code)
{
    string trash, week, rest_line;
    getline(cin, rest_line);
    if (rest_line == " ?" || rest_line == "" || rest_line == " ? ")
    {
        week_code = curr_week_code-1;
        return;
    }
    rest_line.erase(rest_line.begin(), rest_line.begin() + 2);
    stringstream line_stream(rest_line);
    getline(line_stream, trash, ' ');
    getline(line_stream, week, ' ');
    week_code = stoi(week);
}

void FutballFantasy::read_squad_parameter(int &user_index)
{
    string trash, fantasy_team_name, rest_line;
    getline(cin, rest_line);
    if (rest_line == " ?" || rest_line == "" || rest_line == " ? ")
    {
        user_index = CURR_USER;
        return;
    }
    rest_line.erase(rest_line.begin(), rest_line.begin() + 2);
    stringstream line_stream(rest_line);
    getline(line_stream, trash, ' ');
    getline(line_stream, fantasy_team_name, ' ');
    user_index = this->find_user_name(users, fantasy_team_name);
}

void FutballFantasy::read_players_parameter(string &team_name, bool &ranks, int &role)
{
    string trash, team, rest_line, first_part, second_part;
    cin >> trash >> trash >> team;
    stringstream team_name_stream(team);
    getline(team_name_stream, team_name, '_');
    team_name.append(" ");
    getline(team_name_stream, trash, '_');
    team_name.append(trash);
    getline(cin, rest_line);
    if (rest_line == " " || rest_line == "")
    {
        ranks = false;
        role = ALL_ROLES;
        return;
    }
    rest_line.erase(rest_line.begin());
    stringstream line_stream(rest_line);
    getline(line_stream, first_part, ' ');
    getline(line_stream, second_part, ' ');
    if (first_part == "ranks")
    {
        ranks = true;
        role = ALL_ROLES;
        return;
    }
    else
    {
        ranks = false;
        if (second_part == "ranks")
        {
            ranks = true;
        }
        role = this->specify_role(first_part);
    }
}

void FutballFantasy::sort_team_by_points()
{
    sort(this->teams.begin(), this->teams.end(), [](Team *first_team, Team *second_team)
         {
    if(first_team->get_score()<second_team->get_score())
    {
        return true;
    }
    else if(first_team->get_score()==second_team->get_score())
    {
        if((first_team->goal_difference())<(second_team->goal_difference()))
        {
            return true;
        }
        else if((first_team->goal_difference())<(second_team->goal_difference()))
        {
            if(first_team->get_gf()<second_team->get_gf())
            {
                return true;
            }
        }
    }
    return false; });
}

void FutballFantasy::print_team_of_week(int week_code)
{
    cout << "team of the week:" << endl;
    for (int i = 0; i < NUM_OF_ROLE_TYPE; i++)
    {
        vector<Player *> bests = this->find_two_bests_in_role(week_code, (PLAYER_ROLE)i);
        if (i == 1)
        {
            for (int j = 1; j < 3; j++)
            {
                cout << ROLE_NAMES[i] << " " << j << ": " << bests[j - 1]->get_name() << " | score: " << bests[j - 1]->get_point(week_code) << endl;
            }
        }
        else
        {
            cout << ROLE_NAMES[i] << ": " << bests[0]->get_name() << " | score: " << bests[0]->get_point(week_code) << endl;
        }
    }
}

void FutballFantasy::show_budget()
{
    try
    {
        if (curr_user == nullptr)
        {
            throw MyException(PERMISSION_ERR);
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException(PERMISSION_ERR);
        }
        NormalUser *user = (NormalUser *)curr_user;
        user->print_budget();
    }
    catch (MyException &ex)
    {
        ex.print_message();
    }
}

vector<Player *> FutballFantasy::find_two_bests_in_role(int week_code, PLAYER_ROLE g_role)
{
    vector<Player *> bests(2, nullptr);
    bool first_find = false;
    for (Player *player : players)
    {
        if (!first_find)
        {
            if (player->get_role() == g_role)
            {
                bests[0] = player;
                first_find = true;
            }
        }
        else
        {
            if (player->is_playing_better_than(week_code, bests[0]))
            {
                bests[1] = bests[0];
                bests[0] = player;
            }
            else if (bests[1] != nullptr)
            {
                if (player->is_playing_better_than(week_code, bests[1]))
                {
                    bests[1] = player;
                }
            }
        }
    }
    return bests;
}

int FutballFantasy::specify_role(string second_part)
{
    for (int i = 0; i < NUM_OF_ROLE_TYPE; i++)
    {
        if (second_part == AB_ROLE_NAMES[i])
        {
            return i;
        }
    }
    return INVALID_ROLE;
}

void FutballFantasy::print_team_players(int team_ind, bool ranks, int role)
{
    vector<Player *> chosen_players = teams[team_ind]->chose_players(role);
    if (ranks)
    {
        sort_players_with_points(chosen_players);
    }
    cout << "list of players:" << endl;
    for (int i = 0; i < chosen_players.size(); i++)
    {
        cout << i << ". ";
        chosen_players[i]->print_player_for_its_team(curr_week_code - 2);
    }
}

void FutballFantasy::sort_players_with_points(vector<Player *> &chosen_players)
{
    int temp_ind = 0;
    for (int i = 0; i < chosen_players.size(); i++)
    {
        temp_ind = 0;
        for (int j = 0; j < chosen_players.size() - i; j++)
        {
            if (chosen_players[j]->get_point(curr_week_code - 1) > chosen_players[temp_ind]->get_point(curr_week_code - 1))
            {
                temp_ind = j;
            }
        }
        chosen_players.push_back(chosen_players[temp_ind]);
        chosen_players.erase(chosen_players.begin() + temp_ind);
    }
}
