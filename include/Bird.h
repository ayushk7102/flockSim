#ifndef BIRD_HPP
#define BIRD_HPP

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cmath>
#include "Flock.h"
#include <ctime>
class Flock;
class Bird
{
    private:

    glm::vec2 position;
    glm::vec2 velocity;
    
    public:

    Bird() : position(0.0f, 0.0f), velocity(0.0f, 0.0f){} ;
    Bird(float x, float y);
    Bird(glm::vec2 position, glm::vec2 velocity);

    glm::vec2 getPosition();
    glm::vec2 getVelocity();
    
    void setPositionVec(glm::vec2 position);
    void setVelocityVec(glm::vec2 velocity);

    void setPosition(float x, float y);
    void setVelocity(float x, float y);
    
    void updatePosition(float deltaTime);
    //void updatePosition(const std::vector<Bird>& flock);
    //void updatePosition(const Flock flock);
    


};
#endif
