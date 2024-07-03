#include <SFML/Graphics.hpp>

#include "Manual.hh"
#include "Location.hh"

using namespace sf;
using namespace std;

Location::Location(float given_x, float given_y)
{
    if (x < MIN_TILES_NUMBER || y < MIN_TILES_NUMBER || y > MAX_TILES_NUMBER || x > MAX_TILES_NUMBER)
    {
        return;
    }
    x = given_x;
    y = given_y;
}

bool Location::change(float delta_x, float delta_y)
{
    if (x < MIN_TILES_NUMBER || y < MIN_TILES_NUMBER || y > MAX_TILES_NUMBER || x > MAX_TILES_NUMBER)
    {
        return false;
    }
    x = x + delta_x;
    y = y + delta_y;
    return true;
}

int Location::get_x()
{
    return x;
}

int Location::get_y()
{
    return y;
}

bool Location::crash_from_right(Location *second_object)
{
    int obj_x=second_object->get_x(), obj_y=second_object->get_y();

    if(x>=obj_x&&x<obj_x+0.5&&y<obj_y+0.1&&y>obj_y-0.1)
    {
        return true;
    }
    return false;
}

bool Location::crash_from_left(Location *second_object)
{
    int obj_x=second_object->get_x(), obj_y=second_object->get_y();

    if(x<=obj_x&&x>obj_x-0.5&&y<obj_y+0.1&&y>obj_y-0.1)
    {
        return true;
    }
    return false;
}

bool Location::contains(Location *second_object)
{
    int obj_x=second_object->get_x(), obj_y=second_object->get_y();

    if(x<obj_x+0.5&&x>obj_x-0.5&&y<obj_y+0.5&&y>obj_y-0.5)
    {
        return true;
    }
    return false;
}
