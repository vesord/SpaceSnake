//
// Created by vesord on 03.04.2021.
//

#include "spaceSnake.h"
#include "keys.h"
#include "utils.h"
#include <math.h>

extern dirMat g_cam;
extern t_pressedKeys g_pressedKeys;

void doKeysActions() {
	if (g_pressedKeys.a)
		rotateMatVec((mat3f*)&g_cam, g_cam.u, M_PI / 180. * -7);
	if (g_pressedKeys.d)
		rotateMatVec((mat3f*)&g_cam, g_cam.u, M_PI / 180. * 7);
};