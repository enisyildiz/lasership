#include "player.h"
#include "raymath.h"

void Player::input()
{
    this->direction.x = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    this->direction.y = (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);
    this->direction = Vector2Normalize(this->direction);

    if (IsKeyPressed(KEY_SPACE))
    {
        Player::laserVector->push_back(Laser(laserTexture, { this->position.x + this->size.x / 2, this->position.y - 60 }));
        PlaySound(this->laserSound);
    }
}

void Player::checkLimit()
{
    this->direction.x = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    this->direction.y = (int)IsKeyDown(KEY_DOWN) - (int)IsKeyDown(KEY_UP);
    this->direction = Vector2Normalize(this->direction);

    this->position.x = std::max((float)0, std::min(this->position.x, GetScreenWidth() - this->size.x));
    this->position.y = std::max((float)0, std::min(this->position.y, GetScreenHeight() - this->size.y));
}

void Player::update(float dt)
{
    Player::input();

    this->position.x += this->direction.x * this->speed * dt;
    this->position.y += this->direction.y * this->speed * dt;

    Player::checkLimit();
}