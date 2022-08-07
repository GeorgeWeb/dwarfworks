cmake_minimum_required(VERSION 3.16)
project(stb_image LANGUAGES C CXX)

set(Stb_Image_Dir "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(stb_image STATIC "${Stb_Image_Dir}/stb_image.cpp")
target_include_directories(stb_image PUBLIC ${Stb_Image_Dir})

# add_library(stb_image::stb_image ALIAS stb_image)
