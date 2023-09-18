#ifndef FLOCK_HPP
#define FLOCK_HPP
#include <vector>
#include <iostream>
#include <cstdlib>
#include "Bird.h"
class Bird;
class Flock
{
    private:
    std::vector<Bird> birds;

    glm::vec2 minVelocity;
    glm::vec2 maxVelocity;

    public:

    Flock();
    Flock(std::vector<Bird> birds);
    
    void setBirds(std::vector<Bird> birds);

    void setMinVelocity(glm::vec2 minVel);
    void setMaxVelocity(glm::vec2 maxVel);
    
    std::vector<Bird> getBirds();
    void initRandomFlock(int n);
    void drawFlock();
    
    void updateFlock();
    int render();
    glm::vec2 getCenterOfMass();


    
};
#endif
