//
// Created by vesord on 03.04.2021.
//

#ifndef SPACESNAKE_SPACESNAKE_H
#define SPACESNAKE_SPACESNAKE_H

#include <GL/glut.h>
#include "materials.h"
#include "gameConfiguration.h"
#include "gameTextures.h"

typedef struct	s_vec3f {
	GLfloat x;
	GLfloat y;
	GLfloat z;
}				vec3f;

typedef struct	s_mat3f {
	vec3f r1;
	vec3f r2;
	vec3f r3;
}				mat3f;

typedef struct	s_listPos {
	struct s_listPos*	next;
	vec3f				pos;
	t_material_type		material;
}				t_listPos;

typedef struct	s_cameraParams {
	vec3f camDir;
	GLfloat zoom;
	GLfloat zoomMax;
	GLfloat zoomMin;
}				gameCamera;

typedef struct	s_globalConfiguration {
	t_listPos		*snake;			// todo change pos list to (void* data) list
	t_listPos		*fruits;
	mat3f 			head;
	gameParams		game;
	gameTextures	tex;
	gameCamera		cam;
}				t_globalConfiguration;

static t_globalConfiguration configDefault = {.snake = NULL, .fruits = NULL,
	.head = {
		.r1.x = 0.f, .r1.y = 0.f, .r1.z = -1.f,		// forward
		.r2.x = 0.f, .r2.y = 1.f, .r2.z = 0.f,		// up
		.r3.x =1.f, .r3.y =0.f, .r3.z = 0.f			// right
	},
	.game = {
		.snakeDefault.size = 1.f,
		.snakeDefault.bodyDistance = 1.7f,
		.snakeDefault.material = MATERIAL_CHROME,
		.snakeDefault.movSpeed = 0.1f,
		.snakeDefault.movSpeedIncrease = 0.002,
		.snakeDefault.rotSpeed = 4.5f,
		.snakeDefault.rotSpeedIncrease = 0.045f,
		.snakeDefault.growCount = 2,
		.fruitDefault.size = 0.9f,
		.fruitDefault.initCount = 10,
		.cell.radius = 50.f},
	.cam = {
		.camDir = {.x = -0.92847669088f, .y = 0.3713906763f, .z = 0.f},
		.zoom = 11,
		.zoomMax = 50,
		.zoomMin = 5
		}
};

void restart();

#endif //SPACESNAKE_SPACESNAKE_H
