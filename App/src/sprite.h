#pragma once

#include <raylib.h>

class Sprite {
public:
	Texture2D texture;
	Vector2 position;
	float speed;
	Vector2 direction;
	Vector2 size;
	bool discard = false;
	float collisionRadius;

	Sprite(Texture2D texture, Vector2 position, float speed, Vector2 direction);

	void checkDiscard();
	Vector2 getCenter();
	virtual void update(float dt);
	void draw();
};