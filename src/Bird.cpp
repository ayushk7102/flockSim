#include "../include/Bird.h"

Bird::Bird(glm::vec2 position, glm::vec2 velocity) : position(position), velocity(velocity) {}

glm::vec2 Bird::getPosition()
{   
    return position;
}

glm::vec2 Bird::getVelocity()
{   
    return velocity;
}

void Bird::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

void Bird::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}
void Bird::updatePosition(float deltaTime)
{
    position += velocity * deltaTime;
}
