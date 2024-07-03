#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "dec_classes.hh"
#include "Manual.hh"

using namespace sf;
using namespace std;

#pragma once

class Bonus
{
private:
    int score;
    Location *pos;
    Texture texture;
    Sprite sprite;
    RenderWindow *window;
    int state;

public:
    Bonus(int sc, Location *position, string texture_address, RenderWindow *window);
    void achieve(Turtle *turtle);
    bool is_achievable(Location* character_pos);
    void draw_bonus();
};

class Diamond : public Bonus
{
public:
    Diamond(Location *pos,RenderWindow *window);
};

class Star : public Bonus
{
public:
    Star(Location *pos,RenderWindow *window);
};
