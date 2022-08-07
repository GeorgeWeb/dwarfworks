cmake_minimum_required(VERSION 3.16)
project(glad LANGUAGES C)

set(Glad_Dir "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${PROJECT_NAME} STATIC "${Glad_Dir}/src/glad.c")
target_include_directories(${PROJECT_NAME} PUBLIC "${Glad_Dir}/include")

# add_library(glad::glad ALIAS glad)
