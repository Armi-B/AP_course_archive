#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "Location.hh"
#include "Turtle.hh"
#include "Manual.hh"
#include "Bonus.hh"

using namespace sf;
using namespace std;

Bonus::Bonus(int sc, Location *position, string texture_address, RenderWindow *window) : window(window)
{
    Texture texture;
    if(!texture.loadFromFile(texture_address))
    {
        return;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    score = sc;
    pos = position;
    state = UN_ACHIEVED;
}

Diamond::Diamond(Location *pos, RenderWindow *window) : Bonus(10, pos, DIAMOND_IMAGE_ADDRESS, window)
{
    return;
}

Star::Star(Location *pos, RenderWindow *window) : Bonus(5, pos, STAR_IMAGE_ADDRESS, window)
{
    return;
}

bool Bonus::is_achievable(Location* character_pos)
{
    if(pos->contains(character_pos)&&state==UN_ACHIEVED)
    {
        return true;
    }
    return false;
}

void Bonus::achieve(Turtle *turtle)
{
    turtle->increase_score(score);
    state=ACHIEVED;
}

void Bonus::draw_bonus()
{
    sprite.setPosition(sf::Vector2f(pos->get_x()* TILE_SIZE, pos->get_y()* TILE_SIZE));
    sprite.setScale(sf::Vector2f(BONUS_SIZE_SCALE, BONUS_SIZE_SCALE));
    window->draw(sprite);
}
