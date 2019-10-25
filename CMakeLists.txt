cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(MPSnake)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

enable_testing()

set(client_SOURCES client/main.cxx client/application.cxx client/application.hxx client/SDL.hxx)
set(client_test_SOURCES client/application_tests.cxx)

add_executable(client WIN32 ${client_SOURCES})
target_include_directories(client PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(client PRIVATE ${SDL2_LIBRARIES})

add_executable(client_tests ${client_SOURCES} ${client_test_SOURCES})
target_include_directories(client_tests PRIVATE contrib/Catch2/single_include ${SDL2_INCLUDE_DIRS})
target_link_libraries(client_tests PRIVATE ${SDL2_LIBRARIES})
target_compile_definitions(client_tests PRIVATE SNAKE_TESTING=1)
add_test(NAME client_tests COMMAND client_tests)
