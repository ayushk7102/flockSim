cmake_minimum_required(VERSION 3.12)
project(flockSim)

# Set C++ standard (e.g., C++11)
set(CMAKE_CXX_STANDARD 11)


# Include directories for header files
include_directories(include)

# Find OpenGL package
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


# Source files for your project
set(SOURCES
    src/main.cpp
    src/Bird.cpp
    src/Flock.cpp
    # Add more source files as needed
)

# Create an executable from your source files
add_executable(flockSim ${SOURCES})


# Link OpenGL libraries
target_link_libraries(flockSim ${OPENGL_LIBRARIES} glfw) 


# Set the output directory for the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Specify any additional include directories if needed
# include_directories(${SOME_LIBRARY_INCLUDE_DIRS})

# Specify any additional linker directories if needed
# link_directories(${SOME_LIBRARY_LINK_DIRS})

