#include "../include/Bird.h"
#include "../include/Flock.h"
#define N 800
//#include <iostream>
//#include <GLFW/glfw3.h>
//#include <cstdlib>


void drawBird(Bird bird)
{   //finding the base position of the bird
    float x = bird.getPosition().x;
    float y = bird.getPosition().y; 
    x = (x)/(N/2) - 1.0;
    y = (y)/(N/2) - 1.0;
    float size = 0.05f;
    float s = size;
    glBegin(GL_POLYGON);
    
    std::vector<glm::vec2> points, shifted_points;
    points.push_back(glm::vec2(x, y));
    points.push_back(glm::vec2(x+size/2, y+size));
    points.push_back(glm::vec2(x+size, y));
    shifted_points = points;
    //finding the angle theta from the velocity vector
    float theta = atan2(bird.getVelocity().y, bird.getVelocity().x);
    
    float beta = M_PI/2 - atan2(2, 1);

    float x1, y1, x2, y2, s_hyp;
    s_hyp = s * sqrt(5)/2; 
    
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


void drawRandomDots() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5.0f);

    glBegin(GL_POINTS);
    for(int i = 0; i < 100; i++) {
        float x = (float) (rand() % 800) / 400 - 1.0;
        float y = (float) (rand() % 600) / 300 - 1.0;
        glColor3f((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX);
       
       glVertex2f(x, y);
    }
    glEnd();
}

int main()
{  
    srand(time(0));
    glm::vec2 pos;

    glm::vec2 randomVector(float(rand()%N), float(rand()%N));
    Bird b;
    b.setPositionVec(randomVector);
    std::cout << "Random 2D Vector: (" << randomVector.x << ", " << randomVector.y << ")" << std::endl;

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(N, N, "Birds", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        //drawRandomDots();
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        //glColor3f((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX);
        glColor3f(1.0f, 0.0f, 0.0f);
        
        float dt = 1.0f;
        glm::vec2 vel(2.0f,-0.8f);
        b.setVelocityVec(vel);
            drawBird(b);
            b.updatePosition(dt);
            
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
 
}
int main2() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Random Dots", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        //drawRandomDots();
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (int i = 0; i < 100; i++) {
            float x = (float) (rand() % 800) / 400 - 1.0;
            float y = (float) (rand() % 600) / 300 - 1.0;
            glColor3f((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX);
            //drawBird(x, y);
            
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
