cmake_minimum_required(VERSION "3.19.2")


project(game)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "BUILD RAYLIB AS STATIC LIBRARIES" FORCE)

add_subdirectory(thirdParty/raylib-master)
add_subdirectory(thirdParty/imgui-docking)
add_subdirectory(thirdParty/rlimgui)
add_subdirectory(thirdParty/FastNoiseSIMD)

add_executable(${PROJECT_NAME} src/platform/main.cpp
        src/gameLayer/gameMain.cpp
        src/gameLayer/gameMain.h
        src/platform/asserts.h
        src/platform/asserts.cpp
        src/gameLayer/assetManager.h
        src/gameLayer/assetManager.cpp
        src/gameLayer/assetManager.cpp
        src/gameLayer/blocks.h
        src/gameLayer/gameMap.h
        src/gameLayer/gameMap.cpp
        src/gameLayer/helpers.h
        src/gameLayer/helpers.cpp
        src/gameLayer/randomStuff.h
        src/gameLayer/randomStuff.cpp
        src/gameLayer/worldGenerator.h
        src/gameLayer/worldGenerator.cpp
)
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/platform")
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/gameLayer")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC  RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src/resources/")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib imgui rlimgui fastNoiseSIMD)