#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#define RIGHT -1
#define DOWN 1
using namespace std;
// decleartions
void symons_ways(int &ways, int n, int num_of_move = 1);
// global variables
vector<int> moves;

int main()
{
    int ways = 0, n;
    cin >> n;
    symons_ways(ways, n);
    cout << ways;
    return 0;
}

void symons_ways(int &ways, int n, int num_of_move)
{
    if (num_of_move == (2 * n) + 1)
    {
        ways++;
        return;
    }
    if (accumulate(moves.begin(), moves.end(), 0) > 0)
    {
        moves.push_back(RIGHT);
        symons_ways(ways, n, num_of_move + 1);
        moves.pop_back();
    }
    if ((accumulate(moves.begin(), moves.end(), 0) < (n - (num_of_move - n))) || num_of_move <= n)
    {
        moves.push_back(DOWN);
        symons_ways(ways, n, num_of_move + 1);
        moves.pop_back();
    }
}