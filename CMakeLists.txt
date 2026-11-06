cmake_minimum_required(VERSION 3.20)
project(PhysicsSandbox CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

include(FetchContent)
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG 5.5 GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(raylib)

add_executable(sandbox src/main.cpp)
target_link_libraries(sandbox raylib)
