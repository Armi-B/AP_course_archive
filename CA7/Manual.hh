#include <vector>

using namespace std;

#pragma once
#define DEFAULT_BUY_COUNT 2
#define DEFAULT_SELL_COUNT 2
#define INJURY_PERIOD 3
#define GET "GET"
#define POST "POST"
#define PUT "PUT"
#define DELETE "DELETE"
#define NOT_FOUND -1
#define CURR_USER -2
#define NO_MATCH_PLAY -1
#define NOT_COMPLETE -1
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

enum PLAYER_ROLE
{
    GK=0,
    DF=1,
    MD=2,
    FW=3
};

enum PERMISSION_TYPE
{
    PASS_WEEK,
    TRANSFER_WINDOW,
    HAVING_F_TEAM
};

const vector<string> ROLE_NAMES = {"Goalkeeper", "Defender", "Midfielder", "Striker"};
const vector<string> AB_ROLE_NAMES = {"gk","df","md","fw"};