cmake_minimum_required(VERSION 3.23)
project(untitled7)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled7 ${PROJECT_SOURCE_DIR}/ main.cpp Aqua.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:\\SFML-2.5.1\\lib\\cmake\\SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(untitled7 sfml-system sfml-window sfml-graphics sfml-audio)
set(Headers Aqua.h)

