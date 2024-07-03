#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Bonus.hh"
#include "Turtle.hh"
#include "Location.hh"
#include "Enemy.hh"
#include "Portal.hh"
#include "Baby_turtle.hh"
#include "Manual.hh"

using namespace sf;
using namespace std;

void Turtle::check_enemies( vector<Enemy *> enemies, Portal *portal)
{
    for(Enemy *enemy:enemies)
    {
        if(enemy->is_fit_to_hit(pos,moving_direction))
        {
            enemy->hit();
        }
        if(enemy->can_hit_turtle(pos,moving_direction))
        {
            this->hit(portal);
        }
    }
}

Turtle::Turtle(Texture *texture, sf::Vector2u image_count, float switch_time, Portal *portal, RenderWindow *window, Location* pos):
animation(texture,sf::Vector2u(6, 3),0.3f), pos(pos)
{
    picture.setSize(Vector2f(100.0f,100.0f));
    picture.setPosition(portal->give_pos());
    picture.setTexture(texture);
    speed = PLAYER_SPEED;
    life_chance = TURTLE_POWER;
    moving_direction = STATIC;
    portal->teleport(pos);
    score =0;
}

void Turtle::draw()
{
    window->draw(picture);
}

bool Turtle::is_dead()
{
    return life_chance == 0;
}

bool Turtle::move(Portal *portal, vector<Enemy *> enemies, vector<Baby_turtle *> babies, vector<Bonus *> bonuses, int delta_t)
{
    bool is_move_successful = false;
    Vector2f movement(0.0f, 0.0f);
    switch (moving_direction)
    {
    case UP:
    {
        is_move_successful = pos->change(0, 1);
        break;
    }
    case RIGHT:
    {
        is_move_successful = pos->change(speed*delta_t, 0);
        movement.x +=speed*delta_t;
        break;
    }
    case LEFT:
    {
        is_move_successful = pos->change(-1*speed*delta_t, 0);
        movement.x +=speed*delta_t;
        break;
    }
    case DOWN:
    {
        is_move_successful = pos->change(0, -1);
        break;
    }
    }
    this->check_enemies(enemies,portal);
    this->check_Bonuses(bonuses);
    this->check_babies(babies);

    animation.update(0, delta_t, moving_direction);
    picture.setTextureRect(animation.uv_rect);
    picture.move(movement);

    return is_move_successful;
}

void Turtle::hit(Portal *portal)
{
    life_chance--;
    if (!is_dead())
    {
        portal->teleport(pos);
    }
}

void Turtle::increase_score(int sc)
{
    if(sc<=0)
    {
        return;
    }
    score+=sc;
}

void Turtle::check_Bonuses(vector<Bonus*> bonuses)
{
    for(Bonus *bonus:bonuses)
    {
        if(bonus->is_achievable(pos))
        {
            bonus->achieve(this);
        }
    }
}

void Turtle::check_babies(vector<Baby_turtle*> babies)
{
    for(Baby_turtle* baby: babies)
    {
        if(baby->can_get_free(pos))
        {
            baby->unfreeze();
        }
    }
}

void Turtle::change_direction(Direction direction)
{
    moving_direction=direction;
}
