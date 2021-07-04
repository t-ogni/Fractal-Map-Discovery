cmake_minimum_required(VERSION 3.17)
project(Fractal_Map_Discovery)

# some settings
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/)

# build project
find_package(SFML REQUIRED system window graphics network audio)

file(GLOB SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries( ${PROJECT_NAME}
        ${SFML_LIBRARIES} sfml-graphics sfml-system sfml-window
)

# copy res files
file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/resources/)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${PROJECT_SOURCE_DIR}/resources/*
        ${EXECUTABLE_OUTPUT_PATH}/resources/)