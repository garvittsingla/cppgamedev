# Game dev in cpp using raylib

## All things i learnt from this project

1. There are many and versatile ways to compile your cpp project in a executable depending on platform or tools used. So we use Cmake to build our project

```cmake

# specifying cmake version
cmake_minimum_required(VERSION "3.19.2")

#we mention the cmake project name
project(game)
# setting the default cpp version
set(CMAKE_CXX_STANDARD 17)

# telling external libs that used
set(BUILD_SHARED_LIBS OFF CACHE BOOL "BUILD RAYLIB AS STATIC LIBRARIES" FORCE)

add_subdirectory(thirdParty/raylib-master)
add_subdirectory(thirdParty/imgui-docking)
add_subdirectory(thirdParty/rlimgui)
add_subdirectory(thirdParty/FastNoiseSIMD)

#main executable
add_executable(${PROJECT_NAME} src/platform/main.cpp)
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/platform")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/gameLayer")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC  RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/resources/")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib imgui rlimgui fastNoiseSIMD)
```

2. We are using raylib as it lets us make a window, draw block in it and give us a camera , we use imgui as a library to draw UI elements making our debugging easy, to make a bridge between raylib and imgui
3. To seperate the gamelogic and the main logic we made different folders , and make 3 function `startGame`,`updateGame` and `stopGame`. In raylib the code written inside the update game i.e. `(!WindowShouldClose){}` will be updated every frame