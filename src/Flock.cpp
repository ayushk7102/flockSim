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
    float dt = 1.0f;
    for(auto &bird: birds)
    {
        bird.updatePosition(dt);
    }
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
