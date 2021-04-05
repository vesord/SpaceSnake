#include "spaceSnake.h"
#include "drawing.h"
#include "moving.h"
#include "keys.h"
#include "utils.h"

extern t_globalConfiguration cnf;

void locateLight() {
	glPushMatrix();
	GLfloat lightPos[] = {-30.0f, -30.0f, 100.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();
}


static void genCamEyePosition(vec3f *camEye) {
	GLfloat dst = 11;
	vec3f dir = {.x = -10, .y = 4, .z = 0};
	normalize(&dir);

	dir.x *= dst;
	dir.y *= dst;
	dir.z *= dst;

//	camEye->x = cnf.snake->pos.x - cnf.cam.r1.x * 10 + cnf.cam.r2.x * 4;
//	camEye->y = cnf.snake->pos.y - cnf.cam.r1.y * 10 + cnf.cam.r2.y * 4;
//	camEye->z = cnf.snake->pos.z - cnf.cam.r1.z * 10 + cnf.cam.r2.z * 4;

	camEye->x = cnf.snake->pos.x + cnf.cam.r1.x * dir.x + cnf.cam.r2.x * dir.y + cnf.cam.r3.x * dir.z;
	camEye->y = cnf.snake->pos.y + cnf.cam.r1.y * dir.x + cnf.cam.r2.y * dir.y + cnf.cam.r3.y * dir.z;
	camEye->z = cnf.snake->pos.z + cnf.cam.r1.z * dir.x + cnf.cam.r2.z * dir.y + cnf.cam.r3.z * dir.z;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	vec3f camEye;
	genCamEyePosition(&camEye);

	gluLookAt(camEye.x, camEye.y, camEye.z,
			  cnf.snake->pos.x, cnf.snake->pos.y, cnf.snake->pos.z,
			  cnf.cam.r2.x, cnf.cam.r2.y, cnf.cam.r2.z);

	drawSkyBox();
	drawScene();
	drawSnake();
	drawFruits();
	locateLight();

	move();
	checkEvents();
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