cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(MPSnake)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_executable(client WIN32 client/main.cxx)

add_executable(client_tests client/main.cxx)
target_include_directories(client_tests PRIVATE contrib/Catch2/single_include)
target_compile_definitions(client_tests PRIVATE SNAKE_TESTING=1)
add_test(NAME client_tests COMMAND client_tests)
