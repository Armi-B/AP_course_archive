#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Location.hh"
#include "Manual.hh"
#include "Portal.hh"

using namespace sf;
using namespace std;

Portal::Portal(string on_address, string off_address, Location *pos, RenderWindow *window) : pos(pos), window(window)
{
    Texture texture;
    vector<Sprite *> pics = {&off_picture, &on_picture};
    vector<string> addresses = {off_address, on_address};
    for (int i = 0; i < 2; i++)
    {
        if (!texture.loadFromFile(addresses[i]))
        {
            return;
        }
        texture.setSmooth(true);
        pics[i]->setTexture(texture);
    }
    state = ON;
}

void Portal::teleport(Location *another_place)
{
    another_place->change(pos->get_x() - another_place->get_x(), pos->get_y() - another_place->get_y());
}

void Portal::turn_off_portal()
{
    state = OFF;
}

void Portal::draw_portal()
{
    vector<Sprite *> pics = {&on_picture, &off_picture};
    for (int i = 0; i < 2; i++)
    {
        if (state == ON && i == 0 || state == OFF && i == 1)
        {
            pics[i]->setPosition(sf::Vector2f(pos->get_x() * TILE_SIZE, pos->get_y() * TILE_SIZE));
            window->draw(*(pics[i]));
        }
    }
}

bool Portal::is_contains(Location * second_obj)
{
    if(pos->contains(second_obj))
    {
        return true;
    }
    return false;
}

bool Portal::is_in_left(Location * second_obj)
{
    return pos->get_x()<second_obj->get_x();
}

Vector2f Portal::give_pos()
{
    return Vector2f(pos->get_x(), pos->get_y());
}
