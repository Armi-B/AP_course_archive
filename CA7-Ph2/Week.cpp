#include <vector>
#include "Week.hh"

Week::Week(int code, vector<Match *> matches) : week_code(code), matches(matches)
{
}

bool Week::is_same_week(int given_code)
{
    return given_code == week_code;
}

void Week::print_matches()
{
    for (Match *match : matches)
    {
        match->print_match();
    }
}
