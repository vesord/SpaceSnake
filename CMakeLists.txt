cmake_minimum_required(VERSION 3.17)
project(SpaceSnake C)

set(CMAKE_C_STANDARD 99)

IF (APPLE)
    SET(GCC_COVERAGE_COMPILE_FLAGS "")
    SET(GCC_COVERAGE_LINK_FLAGS    "-framework OpenGL -framework GLUT")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINK_FLAGS}")
ENDIF()

include_directories(include)

add_executable(SpaceSnake src/main.c src/drawing.c include/drawing.h src/moving.c include/moving.h include/spaceSnake.h src/utils.c include/utils.h src/keys.c include/keys.h src/materials.c include/materials.h src/display.c include/display.h include/bmp.h src/bmp.c)

IF(UNIX AND NOT APPLE)
    target_link_libraries(SpaceSnake glut GL GLU m)
ENDIF()