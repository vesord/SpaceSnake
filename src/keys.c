#include "spaceSnake.h"
#include "keys.h"
#include "utils.h"
#include <math.h>

extern dirMat g_cam;

t_pressedKeys g_pressedKeys;

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

	normalize(&g_cam.f);
	normalize(&g_cam.u);
	normalize(&g_cam.l);
}

void keyPressed(unsigned char key, int x, int y) {
	switch (key) {
		case 'a': g_pressedKeys.a = 1; break;
		case 'd': g_pressedKeys.d = 1; break;
		case 'w': g_pressedKeys.w = 1; break;
		case 's': g_pressedKeys.s = 1; break;
		case 'q': g_pressedKeys.q = 1; break;
		case 'e': g_pressedKeys.e = 1; break;
		default: break;
	}
}

void keyReleased(unsigned char key, int x, int y) {
	switch (key) {
		case 'a': g_pressedKeys.a = 0; break;
		case 'd': g_pressedKeys.d = 0; break;
		case 'w': g_pressedKeys.w = 0; break;
		case 's': g_pressedKeys.s = 0; break;
		case 'q': g_pressedKeys.q = 0; break;
		case 'e': g_pressedKeys.e = 0; break;
		default: break;
	}
}
