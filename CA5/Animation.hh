#pragma once

#include <SFML/Graphics.hpp>
#include "Manual.hh"

class Animation
{
private:
sf:: Vector2u image_count;
sf:: Vector2u curr_image;
float total_time;
float switch_time;
public:
sf::IntRect uv_rect;
Animation(sf::Texture *texture, sf::Vector2u image_count, float switch_time);
void update(int row, float delta_t, Direction direction);

};