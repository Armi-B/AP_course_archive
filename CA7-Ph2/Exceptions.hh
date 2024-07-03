#include <string>
using namespace std;
#pragma once

class MyException
{
private:
    string message;

public:
    MyException(string message);
    void print_message();
    bool message_is_equal(string s);
};