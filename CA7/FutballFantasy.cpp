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
    admins.push_back(new Admin("admin", "123456", admin_access));
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
            cout << "Bad Request" << endl;
        }
    }
    this->free_memory();
}

void FutballFantasy::post_command_handle(string command)
{
    if (command == "signup")
    {
        this->sign_up();
    }
    else if (command == "login")
    {
        this->login();
    }
    else if (command == "register_admin")
    {
        this->register_admin();
    }
    else if (command == "logout")
    {
        this->logout();
    }
    else if (command == "sell_player")
    {
        this->sell_player();
    }
    else if (command == "buy_player")
    {
        this->buy_player();
    }
    else if (command == "close_transfer_window")
    {
        this->change_transfer_window();
    }
    else if (command == "open_transfer_window")
    {
        this->change_transfer_window();
    }
    else if (command == "pass_week")
    {
        this->pass_week();
    }
    else
    {
        string trash;
        getline(std::cin, trash);
        cout << "Not Found" << endl;
    }
}

void FutballFantasy::get_command_handle(string command)
{
    if (command == "team_of_the_week")
    {
        this->team_of_the_week();
    }
    else if (command == "players")
    {
        this->show_team_players();
    }
    else if (command == "league_standings")
    {
        this->league_standings();
    }
    else if (command == "matches_result_league")
    {
        this->matches_result_league();
    }
    else if (command == "squad")
    {
        this->squad();
    }
    else
    {
        string trash;
        getline(std::cin, trash);
        cout << "Not Found" << endl;
    }
}

void FutballFantasy::sign_up()
{
    try
    {
        if (curr_user != nullptr)
        {
            throw MyException("Permission Denied");
        }
        User *user = this->add_user();
        curr_user = user;
        cout << "OK" << endl;
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
        throw MyException("Bad Request");
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
            throw MyException("Permission Denied");
        }
        int index = this->check_acc();
        curr_user = users[index];
        cout << "OK" << endl;
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
        throw MyException("Not Found");
    }
    if (!users[index]->is_same_pass(pass))
    {
        throw MyException("Permission Denied");
    }
    return index;
}

void FutballFantasy::logout()
{
    try
    {
        if (curr_user == nullptr)
        {
            throw MyException("Permission Denied");
        }
        curr_user = nullptr;
        cout << "OK" << endl;
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
            throw MyException("Permission Denied");
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException("Permission Denied");
        }
        NormalUser *user = (NormalUser *)curr_user;
        user->sell_a_player();
        cout << "OK" << endl;
    }
    catch (MyException &ex)
    {
        string trash;
        getline(std::cin, trash);
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
            throw MyException("Permission Denied");
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException("Permission Denied");
        }
        NormalUser *user = (NormalUser *)curr_user;
        int player_ind = this->find_player(name);
        if (player_ind == NOT_FOUND)
        {
            throw MyException("Not Found");
        }
        user->buy_a_player(players[player_ind], default_num_of_role_in_team);
        cout << "OK" << endl;
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
            throw MyException("Permission Denied");
        }
        int index = this->check_admin_acc();
        curr_user = admins[index];
        cout << "OK" << endl;
    }
    catch (MyException &ex)
    {
        string trash;
        getline(std::cin, trash);
        ex.print_message();
    }
}

int FutballFantasy::check_admin_acc()
{
    string trash, name, pass;
    std::cin >> trash >> trash >> name >> trash >> pass;
    int index = this->find_user_name(admins, name);
    if (index == NOT_FOUND || !admins[index]->is_same_pass(pass))
    {
        throw MyException("Bad Request");
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
        cout << "Permission Denied" << endl;
        return;
    }
    if (curr_user->is_accessible(TRANSFER_WINDOW))
    {
        open_transfer_window = (!open_transfer_window);
        cout << "OK" << endl;
        return;
    }
    cout << "Permission Denied" << endl;
}

void FutballFantasy::pass_week()
{
    if (curr_user == nullptr)
    {
        cout << "Permission Denied" << endl;
        return;
    }
    if (curr_user->is_accessible(PASS_WEEK))
    {
        read_a_week(WEEK_FILE + to_string(curr_week_code) + ".csv");
        this->sort_team_by_points();
        curr_week_code++;
        cout << "OK" << endl;
        return;
    }
    cout << "Permission Denied" << endl;
}

void FutballFantasy::read_league()
{
    league = new League("premier_league");
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
            for (int i = 0; i < 4; i++)
            {
                getline(line_stream, role, ',');
                stringstream role_stream(role);
                while (getline(role_stream, player, ';'))
                {
                    Player *player_ptr = new Player(PLAYER_ROLE(i), player);
                    temp_players.push_back(player_ptr);
                }
            }
            Team *team_ptr = new Team(team_name, temp_players);
            teams.push_back(team_ptr);
            league->get_new_teams(team_ptr);
            players.insert(players.end(), temp_players.begin(), temp_players.end());
        }
    }
    league_file.close();
}

void FutballFantasy::read_a_week(string address)
{
    string line, team_names, result, y_card, red_card, scores, injured;
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
            getline(line_stream, scores, ',');
            stringstream team_name_s(team_names);
            string team1, team2, point1, point2;
            getline(team_name_s, team1, ':');
            getline(team_name_s, team2, ':');
            stringstream result_stream(result);
            getline(result_stream, point1, ':');
            getline(result_stream, point2, ':');
            this->update_team(team1, team2, point1, point2);
            matches.push_back(new Match(teams[find_team(team1)], teams[find_team(team2)], stoi(point1), stoi(point2)));
        }
    }
    week_file.close();
    weeks.push_back(new Week(curr_week_code + 1, matches));
    this->update(injured, y_card, red_card, scores);
}

void FutballFantasy::update(string injured, string y_cards, string r_cards, string scores)
{
    this->update_players_scores(scores);
    this->update_fantasy_team_score();
    this->update_players_cards(r_cards, y_cards);
    this->update_players_health(injured);
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->update_is_ready();
    }
}

void FutballFantasy::update_players_scores(string scores)
{
    string a_score, p_name, point;
    stringstream score_stream(scores);
    while (getline(score_stream, a_score, ';'))
    {
        stringstream one_person_score_stream(a_score);
        getline(one_person_score_stream, p_name, ':');
        getline(one_person_score_stream, point, ':');
        int player_ind = this->find_player(p_name);
        if (player_ind != NOT_FOUND)
        {
            players[player_ind]->update_point(stof(point), curr_week_code);
        }
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

void FutballFantasy::update_team(string team1, string team2, string point1, string point2)
{
    int team1_ind, team2_ind, g1, g2;
    team1_ind = find_team(team1);
    team2_ind = find_team(team2);
    g1 = stoi(point1);
    g2 = stoi(point2);
    teams[team1_ind]->update_with_a_match(g1, g2);
    teams[team2_ind]->update_with_a_match(g2, g1);
}

void FutballFantasy::update_fantasy_team_score()
{
    for (User *u : users)
    {
        NormalUser *user = (NormalUser *)u;
        user->update_f_team_score(curr_week_code);
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
            throw MyException("Not Found");
        }
        int week_ind = this->find_week(week_code);
        if (week_ind == NOT_FOUND)
        {
            throw MyException("Bad Request");
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
            throw MyException("Permission Denied");
        }
        if (!curr_user->is_accessible(HAVING_F_TEAM))
        {
            throw MyException("Permission Denied");
        }
        if (user_index == NOT_FOUND)
        {
            throw MyException("Not Found");
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
        user->print_fantasy_team();
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
            throw MyException("Bad Request");
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
            throw MyException("Bad Request");
        }
        int team_ind = this->find_team(team_name);
        if (team_ind == NOT_FOUND)
        {
            throw MyException("Not Found");
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
        week_code = curr_week_code;
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
        chosen_players[i]->print_player_for_its_team(curr_week_code - 1);
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