cmake_minimum_required(VERSION 3.28)
project(learner_quest)

set(CMAKE_CXX_STANDARD 17)

# Include SDL2 and SDL2_ttf headers
include_directories(${CMAKE_SOURCE_DIR}/includes/SDL2/include)
include_directories(${CMAKE_SOURCE_DIR}/includes/SDL2_ttf/include)

# Link SDL2 and SDL2_ttf libraries
link_directories(${CMAKE_SOURCE_DIR}/includes/SDL2/lib)
link_directories(${CMAKE_SOURCE_DIR}/includes/SDL2_ttf/lib)

# Add the executable
add_executable(learner_quest
    src/main.cpp
    src/Game.cpp
    src/Game.h
    src/Events.cpp
    src/Events.h
    src/UI.cpp
    src/UI.h
    src/Utilities/Logger.cpp
    src/Utilities/Logger.h
    src/Scene.h
    src/SceneManager.cpp
    src/SceneManager.h
    src/Scenes/Main.h
    src/Scenes/Second.h
    src/Scenes/Third.h
)

# Link the libraries to the executable
target_link_libraries(learner_quest SDL2 SDL2_ttf)
