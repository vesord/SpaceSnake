#include "spaceSnake.h"
#include "keys.h"
#include "utils.h"
#include <math.h>

extern dirMat g_cam;
extern t_pressedKeys g_pressedKeys;

void doKeysActions() { // todo refactor
	if (g_pressedKeys.a)
		rotateMatVec((mat3f*)&g_cam, g_cam.u, M_PI / 180. * 7);
	if (g_pressedKeys.d)
		rotateMatVec((mat3f*)&g_cam, g_cam.u, M_PI / 180. * -7);
	if (g_pressedKeys.w)
		rotateMatVec((mat3f*)&g_cam, g_cam.l, M_PI / 180. * -7);
	if (g_pressedKeys.s)
		rotateMatVec((mat3f*)&g_cam, g_cam.l, M_PI / 180. * 7);
	if (g_pressedKeys.q)
		rotateMatVec((mat3f*)&g_cam, g_cam.f, M_PI / 180. * -7);
	if (g_pressedKeys.e)
		rotateMatVec((mat3f*)&g_cam, g_cam.f, M_PI / 180. * 7);
};