#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Location.hh"
#include "Manual.hh"

using namespace sf;
using namespace std;

class Enemy
{
protected:
    bool dead;
    int moving_direction;
    Sprite sprite;
    Location *pos;
    RenderWindow *window;
    bool is_direction_fit_to_hit(Location *turtle_pos, Direction direction);
    void turn_back();
    void check_position(vector<Location *> edges);

public:
    Enemy(Location *position, string pic_address, RenderWindow *window);
    void move(vector<Location *> edges);
    bool is_dead();
    virtual bool can_hit_turtle(Location *turtle_pos, Direction direction) = 0;
    virtual void draw() = 0;
    virtual bool is_fit_to_hit(Location *turtle_pos, Direction direction) = 0;
    virtual void hit() = 0;
};

class Enemy_type1 : public Enemy
{
private:
    int life_chance;

public:
    Enemy_type1(Location *position, string pic_address, RenderWindow *window);
    void draw();
    bool is_fit_to_hit(Location *turtle_pos, Direction direction);
    bool can_hit_turtle(Location *turtle_pos, Direction direction);
    void hit();
};

class Enemy_type2 : public Enemy
{
private:
    Sprite immortal_sprite;
    int period_of_state;
    bool is_perishable;

public:
    Enemy_type2(Location *position, string pic_perishable_address, string pic_immortal_address, RenderWindow *window);
    void draw();
    bool is_fit_to_hit(Location *turtle_pos, Direction direction);
    bool can_hit_turtle(Location *turtle_pos, Direction direction);
    void change_perishability();
    void hit();
};