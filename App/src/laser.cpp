#include "laser.h"

Rectangle Laser::getRect()
{
    return Rectangle(this->position.x, this->position.y, this->size.x, this->size.y);
}