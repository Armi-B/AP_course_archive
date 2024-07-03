#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Manual.hh"
#include "Location.hh"

using namespace sf;
using namespace std;

class Portal
{
private:
    RenderWindow *window;
    Sprite on_picture;
    Sprite off_picture;
    Location *pos;
    Portal_state state;

public:
    Portal(string on_address ,string off_address, Location *pos, RenderWindow *window);
    void draw_portal();
    void teleport(Location *another_place);
    void turn_off_portal();
    bool is_contains(Location * second_obj);
    bool is_in_left(Location * second_obj);
    Vector2f give_pos();
};
