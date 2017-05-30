set(SOURCE_FILES main.cpp)
add_executable(subdivision ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_library(PointLib Point.cpp)
add_library(ColorLib Color.cpp)


target_link_libraries(subdivision ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} PointLib ColorLib)
