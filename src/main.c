#include "spaceSnake.h"
#include "drawing.h"
#include "moving.h"
#include "keys.h"
#include "utils.h"

vec3f g_pos = {.x = 0.f, .y = 0.f, .z = 20.f};

dirMat g_cam = {
	.f.x = 0.f, .f.y = 0.f, .f.z = -1.f,
	.u.x = 0.f, .u.y = 1.f, .u.z = 0.f,
	.l.x =1.f, .l.y =0.f, .l.z = 0.f
};

t_listSnake* g_snake = NULL;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(g_pos.x, g_pos.y, g_pos.z, g_cam.f.x * 1000000, g_cam.f.y * 1000000, g_cam.f.z * 1000000, g_cam.u.x, g_cam.u.y, g_cam.u.z);

	glColor3f(1.f, 0., 0.);
	glutWireTeapot(1);

	drawScene();
	drawSnake();

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

void initSnake() {
	g_snake = malloc(sizeof *g_snake);
	g_snake->pos.x = 0.f;
	g_snake->pos.y = -3.f;
	g_snake->pos.z = 5.f;
	g_snake->next = NULL;

	// todo: delete
	t_listSnake *tmp;
	t_listSnake *prev;
	prev = g_snake;

	tmp = malloc(sizeof *g_snake);
	tmp->next = NULL;
	tmp->pos.x = prev->pos.x;
	tmp->pos.y = prev->pos.y;
	tmp->pos.z = prev->pos.z + 1.5;
	g_snake->next = tmp;
	prev = tmp;

//	tmp = malloc(sizeof *g_snake);
//	tmp->next = NULL;
//	tmp->pos.x = prev->pos.x;
//	tmp->pos.y = prev->pos.y;
//	tmp->pos.z = prev->pos.z + 1.5;
//	g_snake->next->next = tmp;
//	prev = tmp;
//
//	tmp = malloc(sizeof *g_snake);
//	tmp->next = NULL;
//	tmp->pos.x = prev->pos.x;
//	tmp->pos.y = prev->pos.y;
//	tmp->pos.z = prev->pos.z + 1.5;
//	g_snake->next->next->next = tmp;

	// todo end delete
}

int main(int argc, char ** argv) {
	initGlut(&argc, argv);
	initGL();
	initSnake();

	glutMainLoop();
	return 0;
}
