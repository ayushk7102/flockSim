#include "../include/Bird.h"
#include "../include/Flock.h"
#define N 800
//#include <iostream>
//#include <GLFW/glfw3.h>
//#include <cstdlib>

void drawBird(float x, float y)
{   x = (x)/(N/2) - 1.0;
    y = (y)/(N/2) - 1.0;
    float size = 0.05f;
    glBegin(GL_POLYGON);
    
    glVertex2f(x, y);
    //glVertex2f(x-size, y+size);
    glVertex2f(x+size/2, y+size);
    glVertex2f(x+size, y);

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
        drawBird(randomVector.x, randomVector.y); 
        
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
            drawBird(x, y);
            
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
