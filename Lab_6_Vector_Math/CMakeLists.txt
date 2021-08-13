cmake_minimum_required(VERSION 2.8)

project(lab5)

add_executable(FlightPath.out I_FlightPath/FlightPath.cpp)
add_executable(Model3Dvn.out II_Model3Dvn/Model3Dvn.cpp)
add_executable(GLM.out III_GLM/GLM_Examples.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( FlightPath.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( Model3Dvn.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( GLM.out ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
