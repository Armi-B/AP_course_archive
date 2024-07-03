#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>

#include "Manual.hh"
#include "Turtix_game.hh"

char Turtix_game::make_portal(int i, int j, char portal_map_state)
{
    if (portal_map_state == FOUND)
    {
        cerr << "there is more than one portal in this map" << endl;
    }
    Location *pos = new Location(j, i);
    portal = new Portal(ON_PORTAL_ADDRESS, OFF_PORTAL_ADDRESS, pos, window);

    return FOUND;
}

void Turtix_game::create_background_sprite()
{
    Texture texture;
    if (!texture.loadFromFile(BACKGROUND_IMAGE_ADDRESS))
    {
        return;
    }
    texture.setSmooth(true);
    texture.setRepeated(true);
    background_sprite.setScale(sf::Vector2f(0.8, 0.8));
    background_sprite.setTexture(texture);
    background_sprite.setTextureRect(IntRect(-5, -5, 5000, 5000));
}

void Turtix_game::start()
{
    float delta_t = 0.0f;
    sf::Clock clock;
    while (!this->game_finished)
    {
        delta_t = clock.restart().asSeconds();
        sf::Event event;
        while (window->pollEvent(event))
        {
            this->handle_events(&event);
        }
        if (!paused)
        {
            if (direction != STATIC)
            {
                turtle->move(portal, enemies, babies, bonuses, delta_t);
            }
            for (Enemy *enemy : enemies)
            {
                enemy->move(edges);
            }
            for (Baby_turtle *baby : babies)
            {
                baby->move_into_portal();
            }
            if (turtle->is_dead())
            {
                game_finished = true;
            }
        }
        window->clear();
        this->draw();
        window->display();
    }
}

Turtix_game::Turtix_game(int m) : game_finished(false), paused(false)
{
    this->read_maps();
    this->create_background_sprite();
    this->window = new RenderWindow(VideoMode(WINDOWS_SIZE, WINDOWS_SIZE), "turtix");
    this->view = new View(Vector2f(0.0f, 0.0f), Vector2f(540.0f, 540.0f));
    Texture texture;
    if (!texture.loadFromFile(TURTLE_IMAGE_ADDRESS))
    {
        cerr << "turtle.png doesn't found" << endl;
    }
    Location* pos = new Location(0,0);
    turtle = new Turtle(&texture, sf::Vector2u(6, 3), 0.3f, portal, window, pos);
    if (!texture.loadFromFile(GROUND_IMAGE_ADDRESS))
    {
        cerr << "ground.png doesn't found" << endl;
    }
    texture.setSmooth(true);
    ground_pic.setTexture(texture);
}

void Turtix_game::check_babies_portal()
{
    for (Baby_turtle *baby : babies)
    {
        baby->change_portal(portal);
    }
}

void Turtix_game::handle_events(Event *event)
{
    switch ((event->type))
    {
    case sf::Event::Closed:
        this->game_finished = true;
        direction = STATIC;
        break;
    case sf::Event::LostFocus:
        this->paused = true;
        direction = STATIC;
        break;
    case Event::GainedFocus:
        this->paused = false;
        direction = STATIC;
        break;
    case Event::KeyPressed:
    {
        if (event->key.code == sf::Keyboard::Right || event->key.code == sf::Keyboard::D)
        {
            direction = RIGHT;
        }
        else if (event->key.code == sf::Keyboard::Left || event->key.code == sf::Keyboard::A)
        {
            direction = LEFT;
        }
        else if (event->key.code == sf::Keyboard::Up || event->key.code == sf::Keyboard::W)
        {
            direction = UP;
        }
        else if (event->key.code == sf::Keyboard::Down || event->key.code == sf::Keyboard::S)
        {
            direction = DOWN;
        }
        break;
    }
    }
}

void Turtix_game::exit_game()
{
    this->free_memory();
}

void Turtix_game::free_memory()
{
    delete view;
    delete window;
    this->free_characters();
    this->free_map();
}

void Turtix_game::free_characters()
{
    for (Baby_turtle *baby : babies)
    {
        delete baby;
    }
    for (Enemy *enemy : enemies)
    {
        delete enemy;
    }
    for (Bonus *bonus : bonuses)
    {
        delete bonus;
    }
    delete turtle;
}

void Turtix_game::free_map()
{
    for (Location *edge : edges)
    {
        delete edge;
    }
    for (Location *ground : grounds)
    {
        delete ground;
    }
    delete portal;
}

void Turtix_game::draw()
{
    for (Baby_turtle *baby : babies)
    {
        baby->draw();
    }
    for (Enemy *enemy : enemies)
    {
        enemy->draw();
    }
    for (Bonus *bonus : bonuses)
    {
        bonus->draw_bonus();
    }
    this->draw_grounds();
    turtle->draw();
    portal->draw_portal();
}

void Turtix_game::draw_grounds()
{
    for (Location *ground : grounds)
    {
        ground_pic.setPosition(sf::Vector2f(ground->get_x() * TILE_SIZE, ground->get_y() * TILE_SIZE));
        window->draw(ground_pic);
    }
}

void Turtix_game::read_maps()
{
    fstream file;
    string entry;
    char portal_map_state = NOT_FOUND;
    file.open(MAP_FILE_ADDRESS, ios::in);
    if (!file)
    {
        cerr << "file does'nt open" << endl;
        abort();
    }
    for (int i = MAX_TILES_NUMBER - 1; i > -1; i--)
    {
        getline(file, entry);
        if (entry == "")
        {
            continue;
        }
        int last_ground = -2;
        for (int j = 0; j < entry.size(); j++)
        {
            if (entry[j] == '.')
            {
                grounds.push_back(new Location(j, i));
                last_ground = j;
            }
            else if (entry[j] == '$')
            {
                portal_map_state = this->make_portal(i, j, portal_map_state);
            }
            else if (entry[j] == 'E')
            {
                Location *pos = new Location(j, i);
                enemies.push_back(new Enemy_type1(pos, ENEMY1_IMAGE_ADDRESS, window));
            }
            else if (entry[j] == 'M')
            {
                Location *pos = new Location(j, i);
                enemies.push_back(new Enemy_type2(pos, ENEMY2_PERISHABLE_IMAGE_ADDRESS, ENEMY2_IMMORTAL_IMAGE_ADDRESS, window));
            }
            else if (entry[j] == 'O')
            {
                Location *pos = new Location(j, i);
                Baby_turtle* baby = new Baby_turtle(FREE_BABY_TURTLE_IMAGE_ADDRESS, FREEZE_BABY_TURTLE_IMAGE_ADDRESS, portal, pos, window);
                babies.push_back(baby);
            }
            else if (entry[j] == '^')
            {
                Location *pos = new Location(j, i);
                bonuses.push_back(new Diamond(pos, window));
            }
            else if (entry[j] == '*')
            {
                Location *pos = new Location(j, i);
                bonuses.push_back(new Star(pos, window));
            }
            else if (j==last_ground + 1 && entry[j]!= '.' || last_ground + 1 < 11 && last_ground + 1 > entry.size() - 1)
            {
                edges.push_back(new Location(j, i));
            }
            if (file.eof())
            {
                break;
            }
        }
        if (file.eof())
        {
            break;
        }
    }
    file.close();
    if (portal_map_state == NOT_FOUND)
    {
        cerr << "there is no portal in this map" << endl;
        return;
    }
    this->check_babies_portal();
}
