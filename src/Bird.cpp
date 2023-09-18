#include "../include/Bird.h"
#define N 800

int Bird::id_count = 0;
Bird::Bird(glm::vec2 position, glm::vec2 velocity) : position(position), velocity(velocity) {}


std::ostream& operator<<(std::ostream& os, const Bird& bird) {
    os << "Bird\nPos: (" << bird.getPosition().x << ", " << bird.getPosition().y << ")\nVel: "
       << bird.getVelocity().x << " x  " << bird.getVelocity().y << " y\n\n";
    return os;
}
glm::vec2 Bird::getPosition() const
{   
    return position;
}

int Bird::getId() const
{
    return bird_id;
}
glm::vec2 Bird::getVelocity() const
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
    //std::cout<<"pos ("<<position.x<<", " <<position.y<<")\n";
    position += velocity * deltaTime;
}
void Bird::drawBird()
{
//finding the base position of the bird
    float x = position.x;
    float y = position.y; 
    x = (x)/(N/2) - 1.0;
    y = (y)/(N/2) - 1.0;
    //float size = 0.05f;
    float s = bird_size;
    glBegin(GL_POLYGON);
    
    //finding the angle theta from the velocity vector
    float theta = atan2(velocity.y, velocity.x);
    
    float beta = M_PI/2 - atan2(3, 1);

    float x1, y1, x2, y2, s_hyp;
    s_hyp = s * sqrt(10)/3; 
    
    float gamma = theta - beta;
    float gamma_dash = theta + beta;
    

    x1 = x - s_hyp * cos(gamma);
    y1 = y - s_hyp * sin(gamma);
    
    x2 = x - s_hyp * cos(gamma_dash);
    y2 = y - s_hyp * sin(gamma_dash);    
    
    
   glVertex2f(x1, y1);
   glVertex2f(x, y);
   glVertex2f(x2, y2);
   //glVertex2f(x-size/2, y-size);
   //glVertex2f(x, y);
   //glVertex2f(x+size/2, y-size);

    
    glEnd();
}
