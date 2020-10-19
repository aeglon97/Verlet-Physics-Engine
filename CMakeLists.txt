cmake_minimum_required(VERSION 3.10)

project(verlet_simulator)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/sdl2-cmake-modules/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(verlet_simulator ${SOURCES})

# set_property(TARGET verlet_simulator PROPERTY CXX_STANDARD 17)
target_link_libraries(verlet_simulator ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
# target_link_libraries(${PROJECT_NAME} stdc++fs)
# target_compile_options(verlet_simulator PRIVATE -Wall -Wextra)