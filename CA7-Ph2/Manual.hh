#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

#pragma once

#define A(x) 10.0/(exp(-1*x/6.0)+1)

#define GET "GET"
#define POST "POST"
#define PUT "PUT"
#define DELETE "DELETE"

#define SUCCESSFULLY_DONE "OK"
#define NOT_FOUND_ERR "Not Found"
#define BAD_REQUEST_ERR "Bad Request"
#define PERMISSION_ERR "Permission Denied"
#define UNAVAILABLE_PLAYER_ERR "This player is not available for next week"

#define SIGNUP_COMM "signup"
#define LOGIN_COMM "login"
#define ADMIN_LOGIN_COMM "register_admin"
#define LOGOUT_COMM "logout"
#define SELL_PLAYER_COMM "sell_player"
#define BUY_PLAYER_COMM "buy_player"
#define CLOSE_TW_COMM "close_transfer_window"
#define OPEN_TW_COMM "open_transfer_window"
#define PASS_WEEK_COMM "pass_week"
#define SET_CAPTAIN "set_captain"

#define TEAM_OF_WEEK_COMM "team_of_the_week"
#define TEAM_DATA_COMM "players"
#define LEAGUE_DATA_COMM "league_standings"
#define MATCHES_DATA_COMM "matches_result_league"
#define FANTASY_TEAM_DATA_COMM "squad"
#define SHOW_BUDGET_COMM "show_budget"

#define ADMIN_NAME "admin"
#define ADMIN_PASS "123456"

#define LEAGUE_NAME "premier_league"

#define OWN_GOAL "OWN_GOAL"

#define DEFAULT_GK_POINT 3
#define DEFAULT_DF_POINT 1
#define DEFAULT_MD_POINT 0
#define DEFAULT_FW_POINT 0
#define VICTOR_TEAM_POINT 5
#define LOSER_TEAM_POINT -1
#define EQUAL_MATCH_POINT 1
#define GK_CLEAN_SHEET_POINT 5
#define GK_CANT_KEEP_GOAL_POINT -1
#define DF_CLEAN_SHEET_POINT 2
#define DF_GOAL_POINT 4
#define DF_ASSIST_POINT 3
#define MD_CLEAN_SHEET_POINT 1
#define MD_GOAL_POINT 3
#define MD_ASSIST_POINT 2
#define FW_GOAL_POINT 3
#define FW_ASSIST_POINT 1
#define FW_NO_GOAL_POINT -1
#define GOAL_INTO_OWN_GATE_POINT -3

#define DEFAULT_BUDGET 2500
#define DEFAULT_BUY_COUNT 2
#define DEFAULT_SELL_COUNT 2
#define INJURY_PERIOD 3
#define CAPTAIN_FACTOR 2
#define TARGET_PLAYER_GOAL_POINT -1

#define NOT_FOUND -1
#define CURR_USER -2
#define NO_MATCH_PLAY -900
#define NOT_COMPLETE -900
#define ALL_ROLES -1
#define INVALID_ROLE -2

#define LEAGUE_FILE "data/premier_league.csv"
#define WEEK_FILE "data/weeks_stats/week_"

#define MAX_LEAGUE_WEEKS 19
#define MAX_SIZE_OF_TEAM 5
#define NUM_OF_ROLE_TYPE 4
#define NUM_OF_DF_IN_TEAM 2
#define NUM_OF_GK_IN_TEAM 1
#define NUM_OF_MD_IN_TEAM 1
#define NUM_OF_FW_IN_TEAM 1

#define GK_INDEX 0
#define LEFT_DF_INDEX 1
#define MIDDLE_LEFT_DF_INDEX 2
#define MIDDLE_RIGHT_DF_INDEX 3
#define RIGHT_DF_INDEX 4
#define LEFT_MD_INDEX 5
#define MIDDLE_MD_INDEX 6
#define RIGHT_MD_INDEX 7
#define LEFT_FW_INDEX 8
#define MIDDLE_FW_INDEX 9
#define RIGHT_FW_INDEX 10

enum PLAYER_ROLE
{
    GK = 0,
    DF = 1,
    MD = 2,
    FW = 3
};

enum PERMISSION_TYPE
{
    PASS_WEEK,
    TRANSFER_WINDOW,
    HAVING_F_TEAM
};

const vector<string> ROLE_NAMES = {"Goalkeeper", "Defender", "Midfielder", "Striker"};
const vector<string> AB_ROLE_NAMES = {"gk", "df", "md", "fw"};