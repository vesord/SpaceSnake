#include "spaceSnake.h"
#include "keys.h"
#include "utils.h"
#include <math.h>

t_pressedKeys g_pressedKeys;
extern t_globalConfiguration cnf;

void doKeysActions() {
	if (g_pressedKeys.a)
		rotateMatVec((mat3f*)&cnf.cam, cnf.cam.r2, M_PI / 180. * cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.d)
		rotateMatVec((mat3f*)&cnf.cam, cnf.cam.r2, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.w)
		rotateMatVec((mat3f*)&cnf.cam, cnf.cam.r3, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.s)
		rotateMatVec((mat3f*)&cnf.cam, cnf.cam.r3, M_PI / 180. * cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.q)
		rotateMatVec((mat3f*)&cnf.cam, cnf.cam.r1, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.e)
		rotateMatVec((mat3f*)&cnf.cam, cnf.cam.r1, M_PI / 180. * cnf.game.snakeDefault.rotSpeed);

	normalize(&cnf.cam.r1);
	normalize(&cnf.cam.r2);
	normalize(&cnf.cam.r3);
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
