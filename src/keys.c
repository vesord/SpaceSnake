#include "spaceSnake.h"
#include "keys.h"
#include "utils.h"
#include <math.h>

t_pressedKeys g_pressedKeys;
t_pressedMouse g_pressedMouse;
extern t_globalConfiguration cnf;

void doKeysActions() {
	if (g_pressedKeys.a)
		rotateMatVec((mat3f*)&cnf.head, cnf.head.r2, M_PI / 180. * cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.d)
		rotateMatVec((mat3f*)&cnf.head, cnf.head.r2, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.w)
		rotateMatVec((mat3f*)&cnf.head, cnf.head.r3, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.s)
		rotateMatVec((mat3f*)&cnf.head, cnf.head.r3, M_PI / 180. * cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.q)
		rotateMatVec((mat3f*)&cnf.head, cnf.head.r1, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed);
	if (g_pressedKeys.e)
		rotateMatVec((mat3f*)&cnf.head, cnf.head.r1, M_PI / 180. * cnf.game.snakeDefault.rotSpeed);

	normalize(&cnf.head.r1);
	normalize(&cnf.head.r2);
	normalize(&cnf.head.r3);
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

static void wheelUpAction() {
	cnf.cam.zoom = cnf.cam.zoom == cnf.cam.zoomMax ? cnf.cam.zoom : cnf.cam.zoom + 1.f;
}

static void wheelDownAction() {
	cnf.cam.zoom = cnf.cam.zoom == cnf.cam.zoomMin ? cnf.cam.zoom : cnf.cam.zoom - 1.f;
}

void mouseButton(int button, int state, int x, int y) {
	switch (button) {
		case 1: g_pressedMouse.left = state == GLUT_UP ? 0 : 1; break;
		case 2: g_pressedMouse.right = state == GLUT_UP ? 0 : 1; break;
		case 3: if (state == GLUT_UP) wheelUpAction(); break;
		case 4: if (state == GLUT_UP) wheelDownAction(); break;
		default: break;
	}
}

static void moveCam(int x, int y) {
	static int prevx;
	static int prevy;

}

void mouseMove(int x, int y) {
	if (g_pressedMouse.right)
		moveCam(x, y);
}
