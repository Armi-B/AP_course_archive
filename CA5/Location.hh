#pragma once

class Location
{
private:
    float x;
    float y;

public:
    Location(float given_x, float given_y);
    bool change(float delta_x = 1, float delta_y = 1);
    int get_x();
    int get_y();
    bool crash_from_right(Location *second_object);
    bool crash_from_left(Location *second_object);
    bool contains(Location *second_object);
};