cmake_minimum_required(VERSION 3.31)
project(hephaestus VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CACHE{JSON_BuildTests} TYPE BOOL FORCE VALUE OFF)

add_subdirectory(external/SDL EXCLUDE_FROM_ALL)
add_subdirectory(external/nlohmann_json)

add_executable(hph src/main.cpp external/glad/glad.c)

include_directories(include external)

find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(hph SDL3::SDL3 OpenGL::GL nlohmann_json::nlohmann_json glm::glm)
