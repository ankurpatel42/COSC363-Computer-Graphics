cmake_minimum_required(VERSION 2.8)

project(lab1)

add_executable(Teapot.out Teapot.cpp)
add_executable(Model3d.out Model3D.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( Teapot.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( Model3d.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
