cmake_minimum_required(VERSION 3.17)
project(Fractal_Map_Discovery)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML REQUIRED system window graphics network audio)

file(GLOB SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries( ${PROJECT_NAME}
        ${SFML_LIBRARIES} sfml-graphics sfml-system sfml-window
)