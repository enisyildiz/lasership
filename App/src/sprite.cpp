#include "sprite.h"

Sprite::Sprite(Texture2D texture, Vector2 position, float speed, Vector2 direction)
{
	this->texture = texture;
	this->position = position;
	this->speed = speed;
	this->direction = direction;
	this->size.x = texture.width;
	this->size.y = texture.height;
	this->collisionRadius = texture.height / 2;
}

void Sprite::checkDiscard()
{
	int max = GetScreenHeight() + 300;
	int min = -300;
	int pos = this->position.y;

	if ((pos > max) || (pos < min))
	{
		this->discard = true;
	}
	else
	{
		this->discard = false;
	}
}

Vector2 Sprite::getCenter()
{
	Vector2 temp = { this->position.x + this->size.x / 2, this->position.y + this->size.y / 2, };
	return temp;
}

void Sprite::update(float dt)
{
	this->position.x += this->direction.x * this->speed * dt;
	this->position.y += this->direction.y * this->speed * dt;

	Sprite::checkDiscard();
}

void Sprite::draw()
{
	DrawTextureV(this->texture, this->position, WHITE);
}