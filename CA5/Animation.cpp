#include "Animation.hh"

Animation::Animation(Texture *texture, Vector2u image_count, float switch_time) : image_count(image_count), switch_time(switch_time)
{
    total_time = 0.0f;
    curr_image.x = 0;
    uv_rect.width = texture->getSize().x / float(image_count.x);
    uv_rect.height = texture->getSize().y / float(image_count.y);
}

void Animation::update(int row, float delta_t, Direction direction)
{
    curr_image.y = row;
    total_time += delta_t;

    if (total_time >= switch_time)
    {
        total_time -= switch_time;
        curr_image.x++;
        if (curr_image.x >= image_count.x)
        {
            curr_image.x = 0;
        }
    }
    uv_rect.top = curr_image.y * uv_rect.height;
    if (direction == LEFT)
    {
        uv_rect.left = curr_image.x * uv_rect.width;
        uv_rect.width = abs(uv_rect.width);
    }
    else
    {
        uv_rect.left = (curr_image.x + 1) * abs(uv_rect.width);
        uv_rect.width = abs(uv_rect.width);
    }
}