#include "game.h"
#include <random>
#include <string>

Game::Game()
{
    InitWindow(windowWidth, windowHeight, "Laser Ship");
    InitAudioDevice();

    Game::playerTexture = LoadTexture("../../../App/images/spaceship.png");
    Game::laserTexture = LoadTexture("../../../App/images/laser.png");
    Game::meteorTexture = LoadTexture("../../../App/images/meteor.png");
    Game::starTexture = LoadTexture("../../../App/images/star.png");
    Game::scoreFont = LoadFontEx("../../../App/font/Stormfaze.otf", (float)120, NULL, 0);

    Game::laserSound = LoadSound("../../../App/audio/laser.wav");
    Game::explosionSound = LoadSound("../../../App/audio/explosion.wav");
    Game::gameMusic = LoadMusicStream("../../../App/audio/music.wav");

    player = new Player(Game::playerTexture, { (float)windowWidth / (float)2, (float)windowHeight / (float)2 }, &lasers, laserTexture, laserSound);
    meteorTimer = new Timer(400, true, true, std::bind(&Game::createMeteor, this));

    for (int loop=0; loop<30; loop++ )
    {
        Game::starData[loop].pos.x = (float)(rand() % windowWidth);
        Game::starData[loop].pos.y = (float)(rand() % windowHeight);
        Game::starData[loop].scale = (float)1.0;
    }

    PlayMusicStream(Game::gameMusic);
}

Game::~Game()
{
    std::println("Destructor called!");

    UnloadTexture(Game::playerTexture);
    UnloadTexture(Game::laserTexture);
    UnloadTexture(Game::meteorTexture);
    UnloadTexture(Game::starTexture);

    UnloadSound(Game::laserSound);
    UnloadSound(Game::explosionSound);

    UnloadMusicStream(Game::gameMusic);
    CloseAudioDevice();

    CloseWindow();
}

void Game::discardSprites()
{
    auto itLaser = lasers.begin();

    while (itLaser != lasers.end()) {
        if ((*itLaser).discard == true) {
            itLaser = lasers.erase(itLaser);
            continue;
        }
        itLaser++;
    }

    auto itMeteor = meteors.begin();

    while (itMeteor != meteors.end()) {
        if ((*itMeteor).discard == true) {
            itMeteor = meteors.erase(itMeteor);
            continue;
        }
        itMeteor++;
    }
}

void Game::createMeteor()
{
    Vector2 direction = {(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), 1};
    float speed = (float)(300 + (rand() % 100));
    Vector2 position = { (rand() % GetScreenWidth()), (float)((-50) - (rand() % 100))};
    meteors.push_back(Meteor(meteorTexture, position, speed, direction));
}

void Game::checkCollisions()
{
    for (int laserCounter = 0; laserCounter < lasers.size(); laserCounter++)
    {
        for (int meteorCounter = 0; meteorCounter < meteors.size(); meteorCounter++)
        {
            if (CheckCollisionCircleRec(meteors[meteorCounter].getCenter(), meteors[meteorCounter].collisionRadius, lasers[laserCounter].getRect()))
            {
                lasers[laserCounter].discard = true;
                meteors[meteorCounter].discard = true;
                PlaySound(Game::explosionSound);
            }
        }
    }

    for (int meteorCounter = 0; meteorCounter < meteors.size(); meteorCounter++)
    {
        if (CheckCollisionCircles(player->getCenter(), player->collisionRadius, meteors[meteorCounter].getCenter(), meteors[meteorCounter].collisionRadius))
        {
            CloseWindow();
        }
    }
}

void Game::drawScore()
{
    std::string score = std::to_string((int)GetTime());
    Vector2 text_size = MeasureTextEx(Game::scoreFont, score.c_str(), (float)120, (float)0);
    DrawTextEx(Game::scoreFont, score.c_str(), Vector2(GetScreenWidth() / 2 - text_size.x / 2, 50), (float)120, 0, WHITE);
}

void Game::drawStars()
{
    for (auto star : Game::starData)
    {
        DrawTextureEx(Game::starTexture, star.pos, 0, star.scale, WHITE);
    }    
}

void Game::update()
{
    float dt = GetFrameTime();
    Game::meteorTimer->update();
    Game::player->update(dt);
    Game::discardSprites();
    for (int laserCounter = 0; laserCounter < lasers.size(); laserCounter++)
    {
        lasers[laserCounter].update(dt);
    }
    for (int meteorCounter = 0; meteorCounter < meteors.size(); meteorCounter++)
    {
        meteors[meteorCounter].update(dt);
    }
    Game::checkCollisions();
    UpdateMusicStream(Game::gameMusic);
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(BG_COLOR);

    DrawFPS(0, 0);
    Game::drawStars();
    Game::drawScore();
    Game::player->draw();
    for (Laser laser : Game::lasers)
    {
        laser.draw();
    }
    for (Meteor meteor : Game::meteors)
    {
        meteor.draw();
    }

    EndDrawing();
}

void Game::run()
{
    while (!WindowShouldClose())
    {
        this->update();
        this->draw();
    }
}