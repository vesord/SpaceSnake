#ifndef SPACESNAKE_SPACESNAKE_H
#define SPACESNAKE_SPACESNAKE_H

#include <GL/glut.h>
#include "types.h"
#include "materials.h"
#include "gameConfiguration.h"
#include "gameTextures.h"
#include "gameCamera.h"
#include "gameWindow.h"

typedef struct	s_globalConfiguration {
	t_listPos		*snake;			// todo change pos list to (void* data) list
	t_listPos		*fruits;
	mat3f 			head;
	gameParams		game;
	gameTextures	tex;
	gameCamera		cam;
	gameWindow		window;
}				t_globalConfiguration;

static const t_globalConfiguration g_configDefault = {.snake = NULL, .fruits = NULL,
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
		.cell.radius = 50.f,
		.pause = 0},
	.cam = {
		.camDir = {.x = -0.92847669088f, .y = 0.3713906763f, .z = 0.f},
		.zoom = 25,
		.zoomMax = 50,
		.zoomMin = 5
		},
	.window = {
		.width = 640,
		.height = 640,
		.initPosX = 20,
		.initPosY = 20,
		.aspect = 1.,
		.fovy = 60.,
		.zFar = 2000.,
		.zNear = 2,
		.fullscreen = 0
	}
};

void restart();

#endif //SPACESNAKE_SPACESNAKE_H
