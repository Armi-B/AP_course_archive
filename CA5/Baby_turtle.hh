#pragma once

#include "Location.hh"
#include "Portal.hh"

using namespace std;
using namespace sf;

class Baby_turtle
{
private:
    int state;
    Sprite free_sprite;
    Sprite frozen_sprite;
    Direction moving_direct;
    Portal *portal;
    Location *pos;
    RenderWindow *window;
    
public:
    Baby_turtle(string free_pic, string frozen_pic, Portal *portal, Location *pos, RenderWindow *window);
    void change_portal(Portal *port);
    void move_into_portal();
    bool can_get_free(Location *second_obj);
    Direction calculate_direction();
    void unfreeze();
    bool draw();
};