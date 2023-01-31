cmake_minimum_required(VERSION 3.16.3)

project(Planner)

include_directories(./include)
include_directories(./imgui/)
include_directories(./imgui/backends/)
include_directories(./imgui/misc/)
add_executable(output ./src/main.cpp ./imgui/imgui.cpp ./imgui/imgui_demo.cpp ./imgui/imgui_draw.cpp ./imgui/imgui_tables.cpp ./imgui/imgui_widgets.cpp ./imgui/backends/imgui_impl_glut.cpp ./imgui/backends/imgui_impl_opengl2.cpp)
target_link_libraries(output -lGL -lglut)