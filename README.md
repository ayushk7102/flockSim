# FlockSim: Modelling Bird Flocking Behaviour

FlockSim is an interactive flocking simulator that implements the Boids model, a classic algorithm to model the collective behavior of a group of autonomous agents, such as a flock of birds or a school of fish.

![cut](https://github.com/ayushk7102/flockSim/assets/65803868/48580f3a-dd2d-408c-ad67-1a828f75e02a)

## The Model
Each agent (a boid) in the model is represented by a position, velocity, and state. The state of a boid defines its visual radius, protective radius, and leadership (whether or not it is a flock leader). Velocity remains constant for flock leaders. 


Three rules govern the movement of the non-leader boids: 
### 1. Cohesion
Each boid flies towards the center of mass of the other boids in its visual radius.
### 2. Separation
Each boid tries to avoid running into the other boids within a distance equal to its protective radius. 
### 3. Alignment
Each boid tries to match the velocity (heading and speed) of the other boids around it. 



## Getting Started
Clone the repository locally and follow the below instructions to get the project running on your machine:

### Prerequisites
To build the repository, the following need to be installed:
* CMake 
* OpenGL (4.6+)
* GLMath (header-only library [GLM](https://github.com/g-truc/glm) 0.9.9+)
* ImGUI (1.89.9+)
  
### Installation and Build

Navigate to the repository and generate the Makefile in the ```build``` directory using CMake.
   ```sh
cmake build
   ```
Build the project using ```make```
```
cd build
make
```
In order to write the output map to image (.png) files, create a directory called ```images``` in ```/build/bin/```  and set the variable ```writeImg = true```in ```/include/Flock.h```  (line 20).

To run the executable: 
```
cd bin && ./flockSim
```





