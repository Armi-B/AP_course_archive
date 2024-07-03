#pragma once
using namespace sf;
using namespace std;

#define NOT_FOUND 'n'
#define FOUND 'f'
#define UN_ACHIEVED 1
#define ACHIEVED 0
#define FREEZE 0
#define FREE 1

const float PORTAL_SIZE_SCALE = 0.5;
const float TURTLE_SIZE_SCALE = 0.2;
const float BONUS_SIZE_SCALE =0.1;
const float PLAYER_SPEED = 100.0;
const int TURTLE_POWER = 3;
const int ENEMY1_POWER = 2;
const int PERIOD_OF_ENEMY2 = 10;
const int MAX_TILES_NUMBER = 12;
const int MIN_TILES_NUMBER = 0;
const int WINDOWS_SIZE = 540;
const int TILE_SIZE = WINDOWS_SIZE / MAX_TILES_NUMBER;

const string BACKGROUND_IMAGE_ADDRESS = "images/background.png";
const string ENEMY1_IMAGE_ADDRESS = "images/enemy1.png";
const string ENEMY2_PERISHABLE_IMAGE_ADDRESS = "images/enemy2_perish.png";
const string ENEMY2_IMMORTAL_IMAGE_ADDRESS = "images/enemy2_immortal.png";
const string DIAMOND_IMAGE_ADDRESS = "images/diamond.png";
const string STAR_IMAGE_ADDRESS = "images/star.png";
const string FREEZE_BABY_TURTLE_IMAGE_ADDRESS = "images/freeze_turtle.png";
const string FREE_BABY_TURTLE_IMAGE_ADDRESS = "images/free_turtle.png";
const string TURTLE_IMAGE_ADDRESS = "images/turtle.png";
const string MAP_FILE_ADDRESS = "map.txt";
const string OFF_PORTAL_ADDRESS = "images/off_portal.png";
const string ON_PORTAL_ADDRESS = "images/on_portal.png";
const string GROUND_IMAGE_ADDRESS = "images/ground.png";

enum Direction
{
    LEFT,
    UP,
    RIGHT,
    DOWN,
    STATIC
};

enum Portal_state
{
    OFF,
    ON
};
