#include "spaceSnake.h"
#include "keys.h"
#include "utils.h"
#include <math.h>

t_pressedKeys g_pressedKeys;
t_pressedMouse g_pressedMouse;
extern t_globalConfiguration cnf;

void doKeysActions() {	// todo optimization multiplication
	GLfloat keyInvert = cnf.control.keyInverse;

	if (g_pressedKeys.a)
		rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r2, M_PI / 180. * cnf.game.snakeDefault.rotSpeed * keyInvert);	// r2 - up direction (rot around up)
	if (g_pressedKeys.d)
		rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r2, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed * keyInvert);
	if (g_pressedKeys.w)
		rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r3, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed * keyInvert);	// r3 - left direction (rot around left)
	if (g_pressedKeys.s)
		rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r3, M_PI / 180. * cnf.game.snakeDefault.rotSpeed * keyInvert);
	if (g_pressedKeys.q)
		rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r1, M_PI / 180. * -cnf.game.snakeDefault.rotSpeed * keyInvert);	// r1 - front direction (rot around front)
	if (g_pressedKeys.e)
		rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r1, M_PI / 180. * cnf.game.snakeDefault.rotSpeed * keyInvert);

	normalize(&cnf.head.r1);
	normalize(&cnf.head.r2);
	normalize(&cnf.head.r3);
}

void keyPressed(unsigned char key, int x, int y) {
	if (cnf.game.pause && key != 27)
		return;

	switch (key) {
		case 'a': g_pressedKeys.a = 1; break;
		case 'd': g_pressedKeys.d = 1; break;
		case 'w': g_pressedKeys.w = 1; break;
		case 's': g_pressedKeys.s = 1; break;
		case 'q': g_pressedKeys.q = 1; break;
		case 'e': g_pressedKeys.e = 1; break;
		case 27 : cnf.game.pause = !cnf.game.pause; /* ESC code */
		default: break;
	}
}

void keyReleased(unsigned char key, int x, int y) {
	if (cnf.game.pause)
		return;

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
	if (cnf.game.pause)
		return;

	switch (button) {
		case GLUT_LEFT_BUTTON: {
			g_pressedMouse.left = state == GLUT_UP ? 0 : 1;
			g_pressedMouse.pushedlx = x;
			g_pressedMouse.pushedly = y;
			break;
		}
		case GLUT_RIGHT_BUTTON: {
			g_pressedMouse.right = state == GLUT_UP ? 0 : 1;
			g_pressedMouse.pushedrx = x;
			g_pressedMouse.pushedry = y;
			break;
		}
		case 3: if (state == GLUT_UP) wheelUpAction(); break;
		case 4: if (state == GLUT_UP) wheelDownAction(); break;
		default: break;
	}
}

static GLfloat getIntense(GLfloat effect) {
	GLfloat intense = effect * cnf.control.mouseSense;
	return (intense > 1.) * 1. + (intense <= 1.) * intense;
}

static void moveSnake(int x, int y, int *prevx, int *prevy) { // todo optimization multiplication
	GLfloat intense;

	intense = getIntense(x - *prevx);
	rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r2,
					M_PI / 180. * cnf.game.snakeDefault.rotSpeed * intense * cnf.control.mouseInverse);	// r2 - up direction (rot around up)
	intense = getIntense(y - * prevy);
	rotMatAroundVec((mat3f *) &cnf.head, cnf.head.r3,
					M_PI / 180. * cnf.game.snakeDefault.rotSpeed * intense * cnf.control.mouseInverse);	// r3 - left direction (rot around left)
	*prevx = x;
	*prevy = y;
}

static void moveCam(int x, int y, int *prevx, int *prevy) {
	GLfloat intense;
	mat3f rotMat;

	intense = getIntense(x - *prevx);
	genRotMat(&rotMat, normalVecZ, M_PI / 180. * 5.f * intense * cnf.control.mouseInverse);
	rotVec(&cnf.cam.camDir, &rotMat);

	intense = getIntense(y - *prevy);
	genRotMat(&rotMat, normalVecY, M_PI / 180. * 5.f * intense * cnf.control.mouseInverse);
	rotVec(&cnf.cam.camDir, &rotMat);

	*prevx = x;
	*prevy = y;
}

// cam rotation by mouse is not working properly...
void mouseMove(int x, int y) {
	if (cnf.game.pause)
		return;

	if (g_pressedMouse.left)
		moveSnake(x, y, &g_pressedMouse.pushedlx, &g_pressedMouse.pushedly);
//	if (g_pressedMouse.right)
//		moveCam(x, y, &g_pressedMouse.pushedrx, &g_pressedMouse.pushedry);
}
