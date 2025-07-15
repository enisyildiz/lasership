#include "laser.h"
#include <vector>

class Player : public Sprite {
public:

	std::vector<Laser>* laserVector;
	Texture2D laserTexture;
	Sound laserSound;

	Player(Texture2D texture, Vector2 position, std::vector<Laser>* vectorPtr, Texture2D laserText, Sound sound)
		: Sprite(texture, position, (float)500.00, { 0.0, 0.0 }) 
	{
		laserVector = vectorPtr;
		laserTexture = laserText;
		laserSound = sound;
	}

	void input();
	void checkLimit();
	void update(float dt);
};