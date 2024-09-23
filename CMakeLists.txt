cmake_minimum_required(VERSION 3.28)
project(learner_quest)

set(CMAKE_CXX_STANDARD 17)

# Include SDL2 and SDL2_ttf headers
include_directories(${CMAKE_SOURCE_DIR}/includes/SDL2/include)
include_directories(${CMAKE_SOURCE_DIR}/includes/SDL2_ttf/include)
include_directories(${CMAKE_SOURCE_DIR}/includes/SDL2_image/include)

# Link SDL2 and SDL2_ttf libraries
link_directories(${CMAKE_SOURCE_DIR}/includes/SDL2/lib)
link_directories(${CMAKE_SOURCE_DIR}/includes/SDL2_ttf/lib)
link_directories(${CMAKE_SOURCE_DIR}/includes/SDL2_image/lib)

# Add the executable
add_executable(learner_quest
    src/main.cpp
    src/Game.cpp
    src/Game.h
    src/Events.cpp
    src/Events.h
    src/Interface.cpp
    src/Interface.h
    src/Utilities/Logger.cpp
    src/Utilities/Logger.h
    src/Scene.h
    src/SceneManager.cpp
    src/SceneManager.h
    src/UI/Element.h
    src/UI/Elements/Box.h
    src/UI/Elements/Text.h
    src/UI/Elements/Image.h
    src/UI/Elements/RepeatableImage.h
    src/UI/Elements.h
    src/UI/Elements/InteractiveText.h
    src/UI/Forward/Element.h
    src/Options.h
    src/Scenes/MainMenu.h
    src/Scenes/TestScene.h
    src/Scenes/Additive/Settings.h
)

# Link the libraries to the executable
target_link_libraries(learner_quest SDL2 SDL2_ttf SDL2_image)

#if (WIN32)
#    set(SDL2_DLL ${CMAKE_SOURCE_DIR}/includes/SDL2/lib/SDL2.dll)
#    set(SDL2_TTF_DLL ${CMAKE_SOURCE_DIR}/includes/SDL2_ttf/lib/SDL2_ttf.dll)
#    set(SDL2_IMAGE_DLL ${CMAKE_SOURCE_DIR}/includes/SDL2_image/lib/SDL2_image.dll)
#
#    add_custom_command(TARGET learner_quest POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${SDL2_DLL} $<TARGET_FILE_DIR:learner_quest>
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${SDL2_TTF_DLL} $<TARGET_FILE_DIR:learner_quest>
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${SDL2_IMAGE_DLL} $<TARGET_FILE_DIR:learner_quest>
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:learner_quest>/assets
#    )
#
#    set_target_properties(learner_quest PROPERTIES
#        WIN32_EXECUTABLE TRUE
#        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
#    )
#endif()

add_custom_command(TARGET learner_quest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:learner_quest>/assets
)
