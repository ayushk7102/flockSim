#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/Flock.h"
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

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

    glm::vec2 leading_vel = glm::linearRand(minVelocity-5.0f, maxVelocity+5.0f);
    int numLeaders = 20;
    float x, y;
    
    std::cout<<"Randomising leader birds...\n";
    x= rand() % N/4;
    y = rand() % N/4;
    std::cout<<x<<" ,"<<y<<"\n";
    for(int i=0; i<numLeaders; i++)
    {
        
        
        int dx, dy;
        do {
        dx= rand()%N/4; + x;
        dy = rand()%N/4 + y;
        std::cout<<x+dx<<"  ;;;"<<y+dy<<"\n";
        } while(!inBounds(x+dx, y+dy));
        Bird bird(glm::vec2(x + dx, y + dy), leading_vel);
        bird.is_leader = true;
        birds.push_back(bird);
    }
}

void Flock::drawFlock()
{
    for(auto &bird : birds)
    {	//std::cout<<bird;
        bird.drawBird();
    }	
}
int dtime = 0;
void Flock::updateFlock()
{
    float dt =0.5f; // time delta
    
    float w_c = 1.0f;
    float w_s = 1.0f;
    float w_a = 1.0f;
    
    float damp_factor = 0.00;

    glm::vec2 cohesion, separation, alignment;
    for(auto &bird: birds)
    {   
        int id = bird.getId();
        bird.updatePosition(dt);
        
        if (bird.is_leader)
            continue;

        if(dtime % 30!=0)
            {dtime++;
            //continue;
            }
        
        cohesion = getFlockCenterOfMass(id);
        separation = diffuse(bird);
        alignment = getFlockHeading(id);
        
        //std::cout<<"----------------\nCohesion: "<<cohesion.x<<", "<<cohesion.y<<"\n";
        //std::cout<<"Separation: "<<separation.x<<", "<<separation.y<<"\n";
        //std::cout<<"Alignment: "<<alignment.x<<","<<alignment.y<<"\n--------------------\n";
        
        //bird.setVelocityVec(bird.getVelocity() + (w_c * cohesion + w_s * separation + w_a * alignment));
        bird.setVelocityVec(bird.getVelocity() + glm::normalize((w_c * cohesion + w_s *separation + w_a * alignment + glm::vec2(0.001f, 0.001f))));
    
   //bird.limitVelocity();
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
    float epsilon =b1.prot_radius;//40;// 50.0f; // diffusion distance
    glm::vec2 perturbation(0.0f, 0.0f);
    for(auto &b2: birds)
    {
        if (b2.getId() == b1.bird_id)
            continue;
        
        float dist = b1.euclDist(b2);
        if (dist < epsilon)
            perturbation -= (b2.getPosition() - b1.getPosition());
            
    }

    return perturbation/100.0f;
}
glm::vec2 Flock::getFlockCenterOfMass(int id)
{
    glm::vec2 com(0.0f, 0.0f);
    int n_birds_in_vis = 0;
    for(auto &bird : birds)
    {
       // if (bird.bird_id == id)
         //   continue;
        
        Bird b = getBirdById(id);
        if (b.euclDist(bird) < b.vis_radius )
        
            {n_birds_in_vis++;
            com += bird.getPosition();}
    }
    com = com /((float)(n_birds_in_vis ? n_birds_in_vis:1));
    glm::vec2 orig_pos = getBirdById(id).getPosition();
    
    return (com - orig_pos) / 1000.0f;
}

glm::vec2 Flock::getFlockHeading(int id) // get the average velocity of flock
{
    glm::vec2 avg_vel(0.0f, 0.0f);
    Bird b = getBirdById(id);
    int n_birds_in_vis = 0;
    for(auto &bird : birds)
    {
         
         //   continue;
        if (bird.euclDist(b) < bird.vis_radius)
        {
            avg_vel += bird.getVelocity();
            n_birds_in_vis +=1 ;
        }
    }

    //avg_vel /= ((float)(n_birds_in_radius));
    avg_vel  = avg_vel /((float)(n_birds_in_vis ? n_birds_in_vis:1));
    glm::vec2 orig_vel = getBirdById(id).getVelocity();
    
    return (avg_vel - orig_vel) / 100.0f;
} 

void saveImage(const char* filepath, GLFWwindow* w) {
 int width, height;
 glfwGetFramebufferSize(w, &width, &height);
 GLsizei nrChannels = 3;
 GLsizei stride = nrChannels * width;
 stride += (stride % 4) ? (4 - stride % 4) : 0;
 GLsizei bufferSize = stride * height;
 std::vector<char> buffer(bufferSize);
 glPixelStorei(GL_PACK_ALIGNMENT, 4);
 glReadBuffer(GL_FRONT);
 glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
 stbi_flip_vertically_on_write(true);
 stbi_write_png(filepath, width, height, nrChannels, buffer.data(), stride);
 std::cout<<"Saved png "<<filepath<<"\n";
}

int Flock::render()
{
    int frameNo = 1;
    if (!glfwInit()) return -1;
    
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    // Setup Dear ImGui context
//IMGUI_CHECKVERSION();
//std::cout<<"checked version\n";




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
// saveImage(("images/image"+std::to_string(frameNo++)+".png").c_str(), window);
}     
	glfwTerminate();
 return 0;
}


