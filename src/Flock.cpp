#include "../include/Flock.h"
#define N 800
Flock::Flock(){}
Flock::Flock(std::vector<Bird> birds)
{
    this->birds = birds;
}

void Flock::setBirds(std::vector<Bird> birds)
{
    this->birds = birds;
}

std::vector<Bird> Flock::getBirds()
{
    return birds;
}


void Flock::initRandomFlock(int n)
{
    n_birds = n;
    srand(time(0));
    minVelocity = glm::vec2(-2.0f, -2.0f);
    maxVelocity = glm::vec2(2.0f, 2.0f);
    
    for(int i=0; i<n; i++)
    {
        int x = rand() % N;
        int y = rand() % N;
        
        glm::vec2 pos(x, y);
        glm::vec2 vel = glm::linearRand(minVelocity, maxVelocity);

        Bird bird(pos, vel);

        birds.push_back(bird);

    }
}

void Flock::drawFlock()
{
    for(auto &bird : birds)
    {	std::cout<<bird;
        bird.drawBird();
    }	
}
void Flock::updateFlock()
{
    float dt =0.5f; // time delta
    
    float w_c = 1.0f;
    float w_s = 1.0f-1;
    float w_a = 1.0f-1;

    glm::vec2 cohesion, separation, alignment;
    for(auto &bird: birds)
    {   
        int id = bird.getId();
        bird.updatePosition(dt);
        
        cohesion = getFlockCenterOfMass(id);
        separation = diffuse(bird);
        alignment = getFlockHeading(id);
        
        std::cout<<"----------------\nCohesion: "<<cohesion.x<<", "<<cohesion.y<<"\n";
        std::cout<<"Separation: "<<separation.x<<", "<<separation.y<<"\n";
        std::cout<<"Alignment: "<<alignment.x<<","<<alignment.y<<"\n--------------------\n";
        
        bird.setVelocityVec(bird.getVelocity() + w_c * cohesion + w_c *
        separation + w_a * alignment);
    }
}

Bird Flock::getBirdById(int id)
{
    Bird b;
    for (auto &bird: birds)
    {
        if (bird.bird_id == id)
            return bird;
    }
    return b;
}

float Flock::getSeparation(Bird b1, Bird b2)
{
    return glm::distance(b1.getPosition(), b2.getPosition());
}

glm::vec2 Flock::diffuse(Bird b1) // diffuse Bird b among the others in flock
{
    float epsilon = 50.0f; // diffusion distance
    glm::vec2 perturbation(0.0f, 0.0f);

    for(auto &b2: birds)
    {
        if (b2.getId() == b1.bird_id)
            continue;
        
        float dist = b1.euclDist(b2);
        if (dist < epsilon)
            perturbation -= (b1.getPosition() - b2.getPosition());
            
    }

    return perturbation;
}
glm::vec2 Flock::getFlockCenterOfMass(int id)
{
    glm::vec2 com(0.0f, 0.0f);

    for(auto &bird : birds)
    {
       // if (bird.bird_id == id)
         //   continue;
       
        Bird b = getBirdById(id);
        if (b.euclDist(bird) < 75.0f)
        
            com += bird.getPosition();
    }
    com = com /((float)(n_birds));
    glm::vec2 orig_pos = getBirdById(id).getPosition();
    
    return (com - orig_pos) / 100.0f;
}

glm::vec2 Flock::getFlockHeading(int id) // get the average velocity of flock
{
    glm::vec2 avg_vel(0.0f, 0.0f);
    Bird b = getBirdById(id);
    for(auto &bird : birds)
    {
         
         //   continue;
        if (bird.euclDist(b) < 20)
        avg_vel += bird.getVelocity();
    }

    avg_vel /= ((float)(n_birds));
    
    glm::vec2 orig_vel = getBirdById(id).getVelocity();
    
    return (avg_vel - orig_vel) / 8.0f;
}   
int Flock::render()
{
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(N, N, "flockSim", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

	int i=0;
    while (!glfwWindowShouldClose(window)) {
        //drawRandomDots();
        
        glClear(GL_COLOR_BUFFER_BIT);
        

        glColor3f(1.0f, 0.0f, 0.0f);
        std::cout<<"Epoch : "<<i++<<"\n";
        drawFlock();
        updateFlock();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
}    
	glfwTerminate();
 return 0;
}
