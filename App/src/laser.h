#include "sprite.h"

class Laser : public Sprite {
public:

	Laser(Texture2D texture, Vector2 position)
		: Sprite(texture, position, (float)600, {0,-1}) {
	}

	Rectangle getRect();
};