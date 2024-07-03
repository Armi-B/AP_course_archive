#include <iostream>
#include <string>
#include "Exceptions.hh"

using namespace std;

MyException::MyException(string message) :message(message)
{

}

void MyException::print_message()
{
    cout<<message<<endl;
}
