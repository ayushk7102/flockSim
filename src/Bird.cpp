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

void Bird::setVelocityVec(glm::vec2 velocity)
{
    this->velocity = velocity;
}
void Bird::setPositionVec(glm::vec2 position)
{
    this->position = position;
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
    //glm::vec2 nvelocity = glm::normalize(velocity);
    std::cout<<"pos ("<<position.x<<", " <<position.y<<")\n";
    position += velocity * deltaTime;
}
