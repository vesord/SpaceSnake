#include "spaceSnake.h"
#include "drawing.h"
#include "moving.h"
#include "keys.h"

extern dirMat g_cam;
extern t_globalConfiguration cnf;

void locateLight() {
	glPushMatrix();
	GLfloat lightPos[] = {0.0, 0.0, 100.0, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(cnf.snake->pos.x - g_cam.f.x * 10 + g_cam.u.x * 4, cnf.snake->pos.y - g_cam.f.y * 10 + g_cam.u.y * 4, cnf.snake->pos.z - g_cam.f.z * 10 + g_cam.u.z * 4,
			  cnf.snake->pos.x, cnf.snake->pos.y, cnf.snake->pos.z,
			  g_cam.u.x, g_cam.u.y, g_cam.u.z);

	drawSkyBox();
	drawScene();
	drawSnake();
	drawFruits();
	locateLight();

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