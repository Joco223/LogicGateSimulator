cmake_minimum_required(VERSION 3.8.2)
project(LGS CXX)

find_package(SDL2 REQUIRED)

find_library(SDL2_TTF_LIB "SDL2_ttf")
find_library(SDL2_IMAGE_LIB "SDL2_image")

add_executable(lgs
src/Main.cpp
src/Camera.cpp
src/Sandbox.cpp
src/GUI_Controller.cpp
src/Simple2D/Simple2D_GUI.cpp
src/Simple2D/Simple2D_Text.cpp
src/Simple2D/Simple2D_Sprite.cpp
src/Simple2D/Simple2D.cpp)

target_include_directories(lgs PRIVATE inc inc/Simple2D)
target_compile_features(lgs PRIVATE cxx_std_17)
target_link_libraries(lgs PRIVATE SDL2 ${SDL2_TTF_LIB} ${SDL2_IMAGE_LIB})
