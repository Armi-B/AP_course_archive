#include <iostream>
#include <vector>
#include <string>
#define ASCII 32

using namespace std;

string to_upper(string &line, int index = 0);
char captalize(char character);

int main()
{
    //به ازای هر خط ورودی حروف بزرگ شده ی آن را چاپ میکند.
    string line;
    while (getline(cin, line))
    {
        cout << to_upper(line) << endl;
    }
    return 0;
}

string to_upper(string &line, int index)
{
    string result;
    result.push_back(captalize(line[index]));
    if (index >= (line.length() - 1))
    {
        return result;
    }
    //رشته ورودی را با حروف بزرگ بازنویسی میکند.
    result.append(to_upper(line, index + 1));
    return result;
}

char captalize(char character)
{
    if ((int)character > 96 && (int)character < 123)
    {
        //اگر کاراکتر ما از حروف کوچک بود حرف بزرگ متناظرش را برمیگردانیم.
        char cap = (char)((int)character - ASCII);
        return cap;
    }
    return character;
}