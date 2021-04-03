#include "spaceSnake.h"
#include "drawing.h"
#include "moving.h"
#include "utils.h"
#include "keys.h"

#include <math.h>

vec3f g_pos = {.x = 0.f, .y = 0.f, .z = 20.f};
//vec3f g_vel = {.x = 0.f, .y = 0.f, .z = -1.f};

dirMat g_cam = {
	.f.x = 0.f, .f.y = 0.f, .f.z = -1.f,
	.u.x = 0.f, .u.y = 1.f, .u.z = 0.f,
	.l.x =1.f, .l.y =0.f, .l.z = 0.f
};

t_pressedKeys g_pressedKeys;

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


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(g_pos.x, g_pos.y, g_pos.z, g_cam.f.x * 100, g_cam.f.y * 100, g_cam.f.z * 100, g_cam.u.x, g_cam.u.y, g_cam.u.z);


	glColor3f(1.f, 0., 0.);
	glutWireTeapot(1);


	drawScene();

	calculateStep();
	doKeysActions();

	glFlush();
	glutSwapBuffers();
}

void idle() {
	display();
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	// todo probably set gluPerspective
}

void initGlut(int *argc, char ** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 640);		// todo add to config
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Space Snake");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutIgnoreKeyRepeat(GL_TRUE);
//	glutKeyboardUpFunc()
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
}

void initGL() {
	glClearColor(.3f, .3f, .3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // todo probably true

	glViewport(0, 0, 640, 640); // todo add config
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1., 2., 200.); // todo add config
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char ** argv) {
	initGlut(&argc, argv);
	initGL();

	glutMainLoop();
	return 0;
}
