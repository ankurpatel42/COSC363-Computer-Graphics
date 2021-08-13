cmake_minimum_required(VERSION 2.8)

project(lab2)

add_executable(MapleLeaf.out MapleLeaf.cpp)
add_executable(Vase.out Vase.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( MapleLeaf.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( Vase.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
