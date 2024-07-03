#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Location.hh"
#include "Enemy.hh"
#include "Portal.hh"
#include "Turtle.hh"
#include "Baby_turtle.hh"
#include "Manual.hh"
#include "Bonus.hh"

using namespace sf;
using namespace std;

class Turtix_game
{
public:
    Turtix_game(int m);
    void start();

private:
    bool game_finished;
    bool paused;
    void check_babies_portal();
    void read_maps();
    char make_portal(int i, int j, char portal_map_state);
    void create_background_sprite();
    void handle_events(Event *event);
    void exit_game();
    void free_memory();
    void free_characters();
    void free_map();
    void draw();
    void draw_grounds();
    
    Direction direction;
    View *view;
    RenderWindow *window;
    Sprite background_sprite;
    Sprite ground_pic;

    Turtle *turtle;
    Portal *portal;
    vector<Enemy *> enemies;
    vector<Baby_turtle*> babies;
    vector<Bonus*> bonuses;

    vector<Location *> edges;
    vector<Location *> grounds;
};