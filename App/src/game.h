
#include <iostream>
#include <raylib.h>
#include <print>
#include <vector>

#include "player.h"
#include "meteor.h"
#include "timer.h"

#define BG_COLOR   CLITERAL(Color){ 15,10,25,255 }

struct star_t
{
    Vector2 pos;
    float scale;
};

class Game {
public:
    const int windowWidth = 1280;
    const int windowHeight = 900;

    Player* player;
    Timer* meteorTimer;
    star_t starData[30];
    std::vector<Laser> lasers;
    std::vector<Meteor> meteors;

    Texture2D playerTexture;
    Texture2D laserTexture;
    Texture2D meteorTexture;
    Texture2D starTexture;
    Font scoreFont;

    Sound laserSound;
    Sound explosionSound;
    Music gameMusic;

    Game();
    ~Game();

    void discardSprites();
    void createMeteor();
    void checkCollisions();
    void drawScore();
    void drawStars();
    void update();
    void draw();
    void run();
};