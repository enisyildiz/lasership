#include "sprite.h"

class Meteor : public Sprite {
public:

	Meteor(Texture2D texture, Vector2 position, float speed, Vector2 direction) : Sprite(texture, position, speed, direction) {}
};