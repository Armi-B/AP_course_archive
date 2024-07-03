#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "dec_classes.hh"
#include "Animation.hh"
#include "Manual.hh"

using namespace sf;
using namespace std;

#pragma once

class Turtle
{
private:
    int score;
    int speed;
    int life_chance;
    Direction moving_direction;
    RectangleShape picture;
    Animation animation;
    Location *pos;
    RenderWindow *window;
    Portal *portal;

    void check_enemies(vector<Enemy *> enemies, Portal *portal);
    void check_Bonuses(vector<Bonus *> bonuses);
    void check_babies(vector<Baby_turtle *> babies);
    void hit(Portal *portal);

public:
    Turtle(Texture *texture, sf::Vector2u image_count, float switch_time, Portal *portal, RenderWindow *window, Location* pos);
    void draw();
    bool move(Portal *portal, vector<Enemy *> enemies, vector<Baby_turtle *> babies, vector<Bonus *> bonuses, int delta_t);
    bool is_dead();
    void increase_score(int sc);
    void change_direction(Direction direction);
};
