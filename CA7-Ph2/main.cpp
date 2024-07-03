#include "FutballFantasy.hh"

using namespace std;

int main()
{
    FutballFantasy *futball_fantasy = new FutballFantasy;
    futball_fantasy->start_futball_fantasy();
    delete futball_fantasy;

    return 0;
}