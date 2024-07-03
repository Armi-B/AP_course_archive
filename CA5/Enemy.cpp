#include <SFML/Graphics.hpp>

#include "Location.hh"
#include "Enemy.hh"

using namespace sf;
using namespace std;

Enemy::Enemy(Location *pos, string pic_address, RenderWindow *window) : window(window), pos(pos)
{
    Texture texture;
    if (!texture.loadFromFile(pic_address))
    {
        return;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    moving_direction = RIGHT;
    dead = false;
}

Enemy_type1::Enemy_type1(Location *pos, string pic_address, RenderWindow *window) : Enemy(pos, pic_address, window)
{
    life_chance = ENEMY1_POWER;
}

Enemy_type2::Enemy_type2(Location *position, string pic_perishable_address, string pic_immortal_address, RenderWindow *window) : Enemy(pos, pic_perishable_address, window)
{
    Texture texture;
    if (!texture.loadFromFile(pic_immortal_address))
    {
        return;
    }
    sprite.setTexture(texture);
    period_of_state=PERIOD_OF_ENEMY2;
    is_perishable = true;
}

bool Enemy::is_dead()
{
    return dead;
}

void Enemy_type1::hit()
{
    life_chance--;
    if (life_chance <= 0)
    {
        dead = true;
    }
}

void Enemy_type2::hit()
{
    dead = true;
}

bool Enemy::is_direction_fit_to_hit(Location *turtle_pos, Direction direction)
{
    if (moving_direction != RIGHT && direction == RIGHT && pos->crash_from_right(turtle_pos))
    {
        return true;
    }
    else if (moving_direction != LEFT && direction == LEFT && pos->crash_from_right(turtle_pos))
    {
        return true;
    }
    return false;
}

bool Enemy_type1::is_fit_to_hit(Location *turtle_pos, Direction direction)
{
    if ((!dead) && life_chance != 0)
    {
        if (is_direction_fit_to_hit(turtle_pos, direction))
        {
            return true;
        }
    }
    return false;
}

bool Enemy_type2::is_fit_to_hit(Location *turtle_pos, Direction direction)
{
    if ((!dead) && is_perishable)
    {
        if (is_direction_fit_to_hit(turtle_pos, direction))
        {
            return true;
        }
    }
    return false;
}

bool Enemy_type1::can_hit_turtle(Location *turtle_pos, Direction direction)
{
    switch (direction)
    {
    case RIGHT:
    {
        return is_direction_fit_to_hit(turtle_pos, LEFT);
    }
    case LEFT:
    {
        return is_direction_fit_to_hit(turtle_pos, RIGHT);
    }
    default:
    {
        return !is_direction_fit_to_hit(turtle_pos, direction);
    }
    }
}

bool Enemy_type2::can_hit_turtle(Location *turtle_pos, Direction direction)
{
    if (is_perishable)
    {
        switch (direction)
        {
        case RIGHT:
        {
            return is_direction_fit_to_hit(turtle_pos, LEFT);
        }
        case LEFT:
        {
            return is_direction_fit_to_hit(turtle_pos, RIGHT);
        }
        default:
        {
            return is_direction_fit_to_hit(turtle_pos, direction);
        }
        }
    }
    else
    {
        if (pos->contains(turtle_pos))
        {
            return true;
        }
    }
    return false;
}

void Enemy::move(vector<Location *> edges)
{
    bool is_move_successful = false;
    switch (moving_direction)
    {
    case RIGHT:
    {
        cout<<0;
        is_move_successful = pos->change(1.0, 0.0);
        break;
    }
    case LEFT:
    {
        is_move_successful = pos->change(-1.0, 0.0);
        break;
    }
    }
    if(!is_move_successful)
    {
        this->turn_back();
    }
    this->check_position(edges);
}

void Enemy::turn_back()
{
    if (moving_direction == RIGHT)
    {
        moving_direction = LEFT;
    }
    else if (moving_direction == LEFT)
    {
        moving_direction = RIGHT;
    }
    else
    {
        cerr << "invalid enemy direction" << endl;
    }
}

void Enemy::check_position(vector<Location *> edges)
{
    for (Location *edge : edges)
    {
        if (pos->contains(edge))
        {
            turn_back();
            break;
        }
    }
}

void Enemy_type1::draw()
{
    int x = pos->get_x();
    int y = pos->get_y();
    switch (moving_direction)
    {
    case RIGHT:
    {
        x++;
        sprite.setRotation(180);
        break;
    }
    case LEFT:
    {
        x--;
        break;
    }
    }
    sprite.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
    sprite.setScale(sf::Vector2f(TURTLE_SIZE_SCALE, TURTLE_SIZE_SCALE));
    window->draw(sprite);
}

void Enemy_type2::draw()
{
    int x = pos->get_x();
    int y = pos->get_y();
    switch (moving_direction)
    {
    case RIGHT:
    {
        x++;
        sprite.setRotation(180);
        break;
    }
    case LEFT:
    {
        x--;
        break;
    }
    }
    Sprite *chosen_pic = &immortal_sprite;
    if (is_perishable)
    {
        chosen_pic = &sprite;
    }
    chosen_pic->setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
    chosen_pic->setScale(sf::Vector2f(TURTLE_SIZE_SCALE, TURTLE_SIZE_SCALE));
    window->draw(*chosen_pic);
}
