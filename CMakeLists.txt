cmake_minimum_required(VERSION 3.3)

project(pomotime)

add_subdirectory(extern/wxWidgets)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} pomotime.cpp cycle.cpp)

target_link_libraries(${PROJECT_NAME} wx::net wx::core wx::base)
