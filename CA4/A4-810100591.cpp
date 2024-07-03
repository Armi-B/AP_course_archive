#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#define NO_CHANGE -1
#define NOT_EXIST -1
#define NUM_CONFIG_CONST 5
#define TEAM_DATA_ADDRESS "assets/teams.csv"
#define SALARY_DATA_ADDRESS "assets/salary_configs.csv"
#define EMPLOYEE_DATA_ADDRESS "assets/employees.csv"
#define WORKING_DATA_ADDRESS "assets/salary_configs.csv"
enum COLUMNS
{
    first,
    second,
    third,
    fourth,
    fifth,
    sixth
};

using namespace std;


struct Time_interval
{
    int start_interval;
    int end_interval;
};

struct working_day
{
    int day;
    vector<Time_interval> intervals;
};

class Employee
{
private:
    string id;
    string name;
    int age;
    string level;

public:
    Employee(string given_id, string given_name, string given_level, int given_age);
    string get_name() { return name; }
    int get_age() { return age; }
    string get_level() { return level; }
    bool is_id_equal(string emp_id) { return id == emp_id; }
};

class Working_hours
{
private:
    string employee_id;
    vector<working_day> working_days;

public:
    Working_hours(string id, int day, int start_period, int end_period);
    Working_hours(string id, vector<working_day> working_days);
    void delete_working_interval(int given_day);
    void add_working_interval(int given_day, int start_period, int end_period);
    bool is_interval_exist(int given_day, int start_time, int end_time);
    void add_new_day(int given_day, int start_time, int end_time);
    bool is_id_equal(string given_id) { return employee_id == given_id; }
    bool is_day_equal(int given_day, int index) { return working_days[index].day == given_day; }
    vector<working_day> get_working_days() { return working_days; }
};

class Team
{
private:
    string team_id;
    string team_head_id;
    vector<string> member_ids;
    int bonus_percentage = 0;
    int bonus_min_working_hours;
    float bonus_working_hours_max_var;

public:
    Team(int bonus_min, float bonus_var, string id, string team_head, vector<string> members);
    void update_bonus(int new_bonus_percentage);
    string get_team_id() { return team_id; }
    bool is_team_id_equal(string given_id) { return given_id == team_id; }
};

class Level_salary_config
{
private:
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;

public:
    Level_salary_config(string lev, int base_sal, int sal_per_h, int sal_per_extra, int office_h, int tax_persc);
    void update_level_salary_config(int new_base_salary, int new_salary_per_hour, int new_salary_per_extra_hour, int new_official_working_hours, int new_tax_percentage);
    void print_salary_config();
    bool is_level_equal(string given_level);
};


void take_action(vector<Employee> &employees, vector<Working_hours> &working_report, vector<Team> &teams, vector<Level_salary_config> &salary_configs);
void input_data(vector<Employee> &employees, vector<Working_hours> &working_report, vector<Team> &teams, vector<Level_salary_config> &salary_configs);
void delete_working_hours(vector<Working_hours> &working_report);
void update_salary_config(vector<Level_salary_config> &salary_configs);
void show_salary_config(vector<Level_salary_config> &salary_configs);
void add_working_hours(vector<Working_hours> &working_report);
void get_new_config(vector<int> &parameters, int size);
bool is_day_valid(int given_day);
bool is_interval_valid(int start_period, int end_period);
void update_team_bonus(vector<Team> &teams);
bool sort_by_id(Team first_team, Team second_team);
int index_of_id_repo(vector<Working_hours> &report, string given_id);
int index_of_day_days(Working_hours employee_repo, int day);
vector<working_day> creat_working_days(int given_day, int start_time, int end_time);
vector<string> seperate_words(const string line, string delimiter = ",");
vector<Team> input_teams();
vector<Level_salary_config> input_salary_config();
vector<Working_hours> input_working_report();
vector<Employee> input_employees();


int main()
{
    vector<Employee> employees;
    vector<Working_hours> working_report;
    vector<Team> teams;
    vector<Level_salary_config> salary_configs;
    input_data(employees, working_report, teams, salary_configs);
    cout << teams.size() << ',' << salary_configs.size() << employees.size() << ',' << working_report.size() << endl;
    take_action(employees, working_report, teams, salary_configs);
    return 0;
}

Employee::Employee(string given_id, string given_name, string given_level, int given_age)
{
    id = given_id;
    name = given_name;
    level = given_level;
    age = given_age;
}

void Team::update_bonus(int new_bonus_percentage)
{
    bonus_percentage = new_bonus_percentage;
}

Team::Team(int bonus_min, float bonus_var, string id, string team_head, vector<string> members)
{
    bonus_min_working_hours = bonus_min;
    bonus_working_hours_max_var = bonus_var;
    team_id = id;
    team_head_id = team_head;
    member_ids = members;
    bonus_percentage = 0;
}

Level_salary_config::Level_salary_config(string lev, int base_sal, int sal_per_h, int sal_per_extra, int office_h, int tax_persc)
{
    level = lev;
    base_salary = base_sal;
    salary_per_hour = sal_per_h;
    salary_per_extra_hour = sal_per_extra;
    official_working_hours = office_h;
    tax_percentage = tax_persc;
}

bool Level_salary_config::is_level_equal(string given_level)
{
    return given_level == level;
}

void Level_salary_config::print_salary_config()
{
    cout << "Base Salary: " << base_salary << endl;
    cout << "Salary Per Hour: " << salary_per_hour << endl;
    cout << "Salary Per Extra Hour: " << salary_per_extra_hour << endl;
    cout << "Official Working Hours: " << official_working_hours << endl;
    cout << "Tax: " << tax_percentage << "%" << endl;
}

void Level_salary_config::update_level_salary_config(int new_base_salary, int new_salary_per_hour, int new_salary_per_extra_hour, int new_official_working_hours, int new_tax_percentage)
{
    if (new_base_salary != NO_CHANGE)
    {
        base_salary = new_base_salary;
    }
    if (new_salary_per_hour != NO_CHANGE)
    {
        salary_per_hour = new_salary_per_hour;
    }
    if (new_salary_per_extra_hour != NO_CHANGE)
    {
        salary_per_extra_hour = new_salary_per_extra_hour;
    }
    if (new_official_working_hours != NO_CHANGE)
    {
        official_working_hours = new_official_working_hours;
    }
    if (new_tax_percentage != NO_CHANGE)
    {
        tax_percentage = new_tax_percentage;
    }
}

Working_hours::Working_hours(string id, vector<working_day> given_working_days)
{
    employee_id = id;
    working_days = given_working_days;
}

Working_hours::Working_hours(string id, int day, int start_period, int end_period)
{
    Time_interval new_interval = {start_period, end_period};
    vector<Time_interval> new_interval_vec = {new_interval};
    working_day new_day = {day, new_interval_vec};
    working_days = {new_day};
    employee_id=id;
}

bool Working_hours::is_interval_exist(int given_day_index, int start_time, int end_time)
{
    for (int i = 0; i < working_days[given_day_index].intervals.size(); i++)
    {
        if (working_days[given_day_index].intervals[i].start_interval < end_time &&
                working_days[given_day_index].intervals[i].start_interval >= start_time ||
            working_days[given_day_index].intervals[i].end_interval <= end_time &&
                working_days[given_day_index].intervals[i].end_interval > start_time)
        {
            return true;
        }
    }
    return false;
}

void Working_hours::add_working_interval(int given_day_index, int start_period, int end_period)
{
    Time_interval new_interval = {start_period, end_period};
    working_days[given_day_index].intervals.push_back(new_interval);
}

void Working_hours::add_new_day(int given_day, int start_time, int end_time)
{
    working_day new_day = {given_day};
    Time_interval new_interval = {start_time, end_time};
    new_day.intervals.push_back(new_interval);
    working_days.push_back(new_day);
}

void Working_hours::delete_working_interval(int given_day)
{
    for (int i = 0; i < working_days.size(); i++)
    {
        if (working_days[i].day == given_day)
        {
            working_days.erase(working_days.begin() + i);
            break;
        }
    }
}

void show_salary_config(vector<Level_salary_config> &salary_configs)
{
    string given_level;
    cin >> given_level;
    for (int i = 0; i < salary_configs.size(); i++)
    {
        if (salary_configs[i].Level_salary_config::is_level_equal(given_level))
        {
            salary_configs[i].Level_salary_config::print_salary_config();
            break;
        }
        if (i == salary_configs.size() - 1)
        {
            cout << "INVALID_LEVEL" << endl;
        }
    }
}

void get_new_config(vector<int> &parameters, int size)
{
    string check_var;
    for (int i = 0; i < size; i++)
    {
        cin >> check_var;
        if (check_var == "-")
        {
            parameters[i] = -1;
            continue;
        }
        else
        {
            parameters[i] = stoi(check_var);
        }
    }
}

void update_salary_config(vector<Level_salary_config> &salary_configs)
{
    string given_level;
    vector<int> parameters(NUM_CONFIG_CONST);
    cin >> given_level;
    for (int i = 0; i < salary_configs.size(); i++)
    {
        if (salary_configs[i].Level_salary_config::is_level_equal(given_level))
        {
            get_new_config(parameters, NUM_CONFIG_CONST);
            salary_configs[i].Level_salary_config::update_level_salary_config(parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]);
            cout << "OK" << endl;
            break;
        }
        if (i == salary_configs.size() - 1)
        {
            cout << "INVALID_LEVEL" << endl;
        }
    }
}

bool is_day_valid(int given_day)
{
    if (given_day > 30 || given_day < 1)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    return true;
}

bool is_interval_valid(int start_period, int end_period)
{
    if (start_period < 1 || start_period > 24 || end_period < 1 || end_period > 24 || end_period < start_period)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    return true;
}

void add_working_hours(vector<Working_hours> &working_report)
{
    string given_id;
    int given_day, start_period, end_period;
    cin >> given_id >> given_day >> start_period >> end_period;
    for (int i = 0; i < working_report.size(); i++)
    {
        if (working_report[i].Working_hours::is_id_equal(given_id))
        {
            if (is_day_valid(given_day) && is_interval_valid(start_period, end_period))
            {
                for (int j = 0; j < (working_report[i].get_working_days()).size(); j++)
                {
                    if (working_report[i].Working_hours::is_day_equal(given_day, j))
                    {
                        if (working_report[i].Working_hours::is_interval_exist(j, start_period, end_period))
                        {
                            cout << "INVALID_INTERVAL" << endl;
                            return;
                        }
                        else
                        {
                            working_report[i].Working_hours::add_working_interval(j, start_period, end_period);
                            cout << "OK" << endl;
                            return;
                        }
                    }
                    else if (j == (working_report[i].get_working_days()).size() - 1)
                    {
                        working_report[i].Working_hours::add_new_day(given_day, start_period, end_period);
                        cout << "OK" << endl;
                        return;
                    }
                }
            }
            else
            {
                cout << "INVALID_ARGUMENTS" << endl;
                return;
            }
        }
        if (i == working_report.size() - 1)
        {
            cout << "EMPLOYEE_NOT_FOUND" << endl;
            return;
        }
    }
}

void delete_working_hours(vector<Working_hours> &working_report)
{
    string given_id;
    int given_day;
    cin >> given_id >> given_day;
    if (given_day > 30 || given_day < 1)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    for (int i = 0; i < working_report.size(); i++)
    {
        if (working_report[i].Working_hours::is_id_equal(given_id))
        {
            working_report[i].Working_hours::delete_working_interval(given_day);
            cout << "OK" << endl;
            break;
        }
        if (i == working_report.size() - 1)
        {
            cout << "EMPLOYEE_NOT_FOUND" << endl;
            return;
        }
    }
}

void update_team_bonus(vector<Team> &teams)
{
    string given_id;
    int given_perc;
    cin >> given_id >> given_perc;
    if (given_perc > 100 || given_perc < 0)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].Team::is_team_id_equal(given_id))
        {
            teams[i].update_bonus(given_perc);
            cout << "OK" << endl;
            return;
        }
    }
    cout << "TEAM_NOT_FOUND" << endl;
}

bool sort_by_id(Team first_team, Team second_team)
{
    return first_team.get_team_id() < second_team.get_team_id();
}

vector<string> seperate_words(const string line, string delimiter)
{
    vector<string> words;
    string temp_line = line;
    size_t delimiter_ind = 0;
    while ((delimiter_ind = temp_line.find(delimiter)) != string::npos)
    {
        words.push_back(temp_line.substr(0, delimiter_ind));
        temp_line.erase(0, delimiter_ind + delimiter.length());
    }
    words.push_back(temp_line);
    return words;
}

void take_action(vector<Employee> &employees, vector<Working_hours> &working_report, vector<Team> &teams, vector<Level_salary_config> &salary_configs)
{
    string command;
    while ((cin >> command))
    {
        if (command == "report_salaries")
        {
        }
        else if (command == "report_employee_salary")
        {
        }
        else if (command == "report_team_salary")
        {
        }
        else if (command == "report_total_hours_per_day")
        {
        }
        else if (command == "report_employee_per_hour")
        {
        }
        else if (command == "show_salary_config")
        {
            show_salary_config(salary_configs);
        }
        else if (command == "update_salary_config")
        {
            update_salary_config(salary_configs);
        }
        else if (command == "add_working_hours")
        {
            add_working_hours(working_report);
        }
        else if (command == "delete_working_hours")
        {
            delete_working_hours(working_report);
        }
        else if (command == "update_team_bonus")
        {
            update_team_bonus(teams);
        }
        else if (command == "find_teams_for_bonus")
        {
        }
    }
}

void input_data(vector<Employee> &employees, vector<Working_hours> &working_report, vector<Team> &teams, vector<Level_salary_config> &salary_configs)
{
    teams = input_teams();
    salary_configs = input_salary_config();
    employees = input_employees();
    //working_report = input_working_report();
}

vector<Team> input_teams()
{
    ifstream fin(TEAM_DATA_ADDRESS);
    vector<string> lines;
    string temp_line;
    while (getline(fin, temp_line))
    {
        lines.push_back(temp_line);
    }
    fin.close();
    vector<Team> teams;
    for (int i = 1; i < lines.size(); i++)
    {
        vector<string> words_in_line = seperate_words(lines[i]);
        vector<string> members = seperate_words(words_in_line[third], "$");
        Team temp_team(stoi(words_in_line[fourth]), stof(words_in_line[fifth]),
                       words_in_line[first], words_in_line[second], members);
        teams.push_back(temp_team);
    }
    sort(teams.begin(), teams.end(), sort_by_id);
    return teams;
}

vector<Level_salary_config> input_salary_config()
{
    ifstream file;
    file.open(SALARY_DATA_ADDRESS);
    vector<string> lines;
    string temp_line;
    while (getline(file, temp_line))
    {
        lines.push_back(temp_line);
    }
    file.close();
    vector<Level_salary_config> salary_configs;
    for (int i = 1; i < lines.size(); i++)
    {
        vector<string> words_in_line = seperate_words(lines[i]);
        Level_salary_config temp_salary_config(words_in_line[first], stoi(words_in_line[second]),
                                               stoi(words_in_line[third]), stoi(words_in_line[fourth]),
                                               stoi(words_in_line[fifth]), stoi(words_in_line[sixth]));
        salary_configs.push_back(temp_salary_config);
    }
    return salary_configs;
}

vector<Working_hours> input_working_report()
{
    ifstream fin(WORKING_DATA_ADDRESS);
    vector<string> lines;
    string temp_line;
    //خطوط جدید را میگیرد.
    while (getline(fin, temp_line))
    {
        //در برداری از خط ها ذخیره میکند.
        lines.push_back(temp_line);
    }
    fin.close();
    vector<Working_hours> report;
    for (int i = 1; i < lines.size(); i++)
    {
        vector<string> words_in_line = seperate_words(lines[i]);
        vector<string> working_period = seperate_words(words_in_line[third], "-");
        int employee_index = index_of_id_repo(report, words_in_line[first]);
        if (employee_index != NOT_EXIST)
        {
            int day_index = index_of_day_days(report[employee_index], stoi(words_in_line[second]));
            if (day_index != NOT_EXIST)
            {
                report[employee_index].add_working_interval(day_index, stoi(working_period[first]), stoi(working_period[second]));
            }
            else
            {
                report[employee_index].add_new_day(stoi(words_in_line[second]), stoi(working_period[first]), stoi(working_period[second]));
            }
        }
        // peroblem
        else
        {
            int day = stoi(words_in_line[second]);
            int start_period = stoi(working_period[first]);
            int end_period = stoi(working_period[second]);
            Working_hours temp_employee_repo(words_in_line[first], day, start_period, end_period);
            report.push_back(temp_employee_repo);
        }
    }
    return report;
}

vector<Employee> input_employees()
{
    ifstream file;
    file.open(EMPLOYEE_DATA_ADDRESS);
    vector<string> lines;
    string temp_line;
    while (getline(file, temp_line))
    {
        lines.push_back(temp_line);
    }
    file.close();
    vector<Employee> employees;
    for (int i = 1; i < lines.size(); i++)
    {
        vector<string> words_in_line = seperate_words(lines[i]);
        Employee temp_employee(words_in_line[first], words_in_line[second], words_in_line[fourth], stoi(words_in_line[third]));
        employees.push_back(temp_employee);
    }
    return employees;
}

int index_of_id_repo(vector<Working_hours> &report, string given_id)
{
    //اگر گزارش مورد نظر را بیابد ایندکس آن را برمی‌گرداند
    for (int i = 0; i < report.size(); i++)
    {
        if (report[i].is_id_equal(given_id))
        {
            return i;
        }
    }
    return NOT_EXIST;
}

int index_of_day_days(Working_hours employee_repo, int day)
{
    for (int i = 0; i < employee_repo.get_working_days().size(); i++)
    {
        if (employee_repo.is_day_equal(day, i))
        {
            return i;
        }
    }
    return NOT_EXIST;
}

vector<working_day> creat_working_days(int given_day, int start_time, int end_time)
{
    working_day new_day;
    Time_interval new_interval = {start_time, end_time};
    new_day.day = given_day;
    new_day.intervals.push_back(new_interval);
    vector<working_day> working_days;
    working_days.push_back(new_day);
    return working_days;
}
