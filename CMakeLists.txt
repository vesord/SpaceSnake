cmake_minimum_required(VERSION 3.16)
project(SpaceSnake C)

set(CMAKE_C_STANDARD 99)

IF (APPLE)
	set(CMAKE_C_FLAGS "-framework Cocoa -framework OpenGL -framework GLUT")
ENDIF()

include_directories(include)

SET(SRC src/main.c
    src/drawing.c
    src/moving.c
    src/utils.c
    src/keys.c
    src/materials.c
    src/display.c
    src/bmp.c
    )

add_executable(SpaceSnake ${SRC})

IF(UNIX AND NOT APPLE)
    target_link_libraries(SpaceSnake glut GL GLU m)
ENDIF()
