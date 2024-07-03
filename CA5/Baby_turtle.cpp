#include <SFML/Graphics.hpp>
#include "Location.hh"
#include "Baby_turtle.hh"
#include "Portal.hh"
#include "Manual.hh"

using namespace sf;
using namespace std;

Baby_turtle::Baby_turtle(string free_pic, string frozen_pic, Portal *portal, Location *pos, RenderWindow *window) : portal(portal), pos(pos), window(window)
{
    Texture texture;
    vector<Sprite *> sprites = {&free_sprite, &frozen_sprite};
    vector<string> addresses = {free_pic, frozen_pic};
    for (int i = 0; i < 2; i++)
    {
        if (!texture.loadFromFile(addresses[i]))
        {
            return;
        }
        texture.setSmooth(true);
        sprites[i]->setTexture(texture);
    }
    state = FREEZE;
    moving_direct = LEFT;
}

bool Baby_turtle::can_get_free(Location *second_obj)
{
    if (state == FREEZE && pos->contains(second_obj))
    {
        return true;
    }
    return false;
}
//
void Baby_turtle::move_into_portal()
{
}

void Baby_turtle::unfreeze()
{
    state = FREE;
    this->move_into_portal();
}

bool Baby_turtle::draw()
{
    if (portal->is_contains(pos))
    {
        return false;
    }
    if (state == FREEZE)
    {
        frozen_sprite.setPosition(sf::Vector2f(pos->get_x() * TILE_SIZE, pos->get_y() * TILE_SIZE));
        frozen_sprite.setScale(sf::Vector2f(BONUS_SIZE_SCALE, BONUS_SIZE_SCALE));
        window->draw(frozen_sprite);
    }
    else
    {
        int x = pos->get_x();
        int y = pos->get_y();
        switch (moving_direct)
        {
        case RIGHT:
        {
            x++;
            free_sprite.setRotation(180);
            break;
        }
        case DOWN:
        {
            y--;
            break;
        }
        case LEFT:
        {
            x--;
            break;
        }
        }
        free_sprite.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
        free_sprite.setScale(sf::Vector2f(TURTLE_SIZE_SCALE, TURTLE_SIZE_SCALE));
        window->draw(free_sprite);
    }
    return true;
}

Direction Baby_turtle::calculate_direction()
{
    if(portal->is_in_left(pos))
    {
        return LEFT;
    }    
    return RIGHT;
}

void Baby_turtle::change_portal(Portal *port)
{
    portal = port;
}
