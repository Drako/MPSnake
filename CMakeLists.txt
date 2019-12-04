cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(MPSnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

enable_testing()

set(client_SOURCES
        client/main.cxx
        client/application.cxx client/application.hxx
        client/sdl.hxx client/sdl_helpers.hxx
        client/actual_sdl.hxx client/actual_sdl.cxx
        client/window.hxx client/window.cxx
        client/surface.hxx client/surface.cxx
        client/default_colors.hxx
        client/native.cxx client/native.hxx
        client/game_object.hxx client/game_objects.cxx
        client/goal.hxx client/goal.cxx)
set(client_test_SOURCES
        client/mock_sdl.hxx client/mock_sdl.cxx
        client/application_tests.cxx
        client/window_tests.cxx
        client/surface_tests.cxx
        client/goal_tests.cxx)

add_executable(client WIN32 ${client_SOURCES})
target_include_directories(client PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(client PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES})

add_executable(client_tests ${client_SOURCES} ${client_test_SOURCES})
target_include_directories(client_tests PRIVATE
        contrib/Catch2/single_include
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(client_tests PRIVATE
        ${SDL2_LIBRARY}
        ${SDL2_TTF_LIBRARIES})
target_compile_definitions(client_tests PRIVATE SNAKE_TESTING=1)
add_test(NAME client_tests COMMAND client_tests)
