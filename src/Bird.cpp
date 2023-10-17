#include "../include/Bird.h"
#define N 800

int refTimer = 10;

int Bird::id_count = 0;
Bird::Bird(glm::vec2 position, glm::vec2 velocity)
{
    this->position = (position); 
    this->velocity = (velocity);
    bird_id = id_count++;
}

std::ostream& operator<<(std::ostream& os, const Bird& bird) {
    os << "Bird "<<bird.getId()<<"\nPos: (" << bird.getPosition().x << ", " << bird.getPosition().y << ")\nVel: "
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

void Bird::limitVelocity()
{
    float speedLim = 40;
    float speed = glm::length(velocity);

    if (speed > speedLim)
    {
        velocity -= velocity/speed * speedLim;
    }
}
void Bird::updatePosition(float deltaTime)
{   
    //glm::vec2 nvelocity = glm::normalize(velocity);
    //std::cout<<"pos ("<<position.x<<", " <<position.y<<")\n";
    position += velocity * deltaTime;
    
    if (position.y >= N || position.y <= 0)
        reflect(0);
    else if(position.x >= N || position.x <=0)
        reflect(1);
    
}

bool inBounds(float x, float y)
{
    if (y >= N || y <= 0 ||  x >= N || x <=0)
        return false;
    return true;

}

float Bird::euclDist(Bird b)
{
    return glm::distance(position, b.getPosition());
}

glm::mat2 Bird::getRotationMatrix(float theta)
{
    return glm::mat2(cos(theta), -sin(theta), sin(theta), cos(theta));

}

void Bird::reflect(int surface)
{
    float A, B;
    switch(surface)
    {
        case 0: //top; y = N OR y = 0
        A = 0.0f; B = 1.0f;
        
        //std::cout<<"-----------------------HIT TOP OR BOTTOM\n----------\n\n";
        break;

        case 1: //left; x = 0 OR x = N
        A = 1.0f; B = 0.0f;
       
        //std::cout<<"-----------------------HIT left or right\n----------\n\n";
       break;

    }
    glm::vec2 normal(A, B);
    float mag_vel = glm::length(velocity);
    float mag_normal = glm::length(normal);
    
    float dot_prod = glm::dot(velocity, normal);

    //std::cout<<"vel: "<<glm::to_string(velocity)<<" with mag" <<mag_vel<<"\n";

    
    //float angle_theta = std::acos(dot_prod / (mag_vel * mag_normal)); //angle of incidence
    //glm::mat2 rotation_matrix = getRotationMatrix(2 * angle_theta);


    //std::cout << glm::to_string(rotation_matrix) << std::endl;
    glm::vec2 reflected_vel = glm::reflect(velocity, normal);
    velocity = reflected_vel;
    
    //std::cout<<"reflected vel: " << glm::to_string(reflected_vel) << std::endl;
    
    //while(1);
}

void Bird::drawBird()
{
//finding the base position of the bird

    if (this->is_leader)
    {
       return;
    }
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
