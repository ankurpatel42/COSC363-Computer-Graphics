cmake_minimum_required(VERSION 2.8)

project(akp41_assignment_1)

add_executable(akp41_assignment_1.out akp41_assignment_1.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( akp41_assignment_1.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
