#include <vector>
#include "Match.hh"
using namespace std;
#pragma once

class Week
{
private:
    int week_code;
    vector<Match *> matches;

public:
    Week(int code, vector<Match *> matches);
    bool is_same_week(int given_code);
    void print_matches();
};
