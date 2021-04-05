#include "spaceSnake.h"
#include "drawing.h"
#include "moving.h"
#include "keys.h"

extern t_globalConfiguration cnf;

void locateLight() {
	glPushMatrix();
	GLfloat lightPos[] = {-30.0f, -30.0f, 100.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glPopMatrix();
}

static void genCamEyePosition(vec3f *camEye) {
	static vec3f dir;

	dir = cnf.cam.camDir;
	dir.x *= cnf.cam.zoom;
	dir.y *= cnf.cam.zoom;
	dir.z *= cnf.cam.zoom;

	camEye->x = cnf.snake->pos.x + cnf.head.r1.x * dir.x + cnf.head.r2.x * dir.y + cnf.head.r3.x * dir.z;
	camEye->y = cnf.snake->pos.y + cnf.head.r1.y * dir.x + cnf.head.r2.y * dir.y + cnf.head.r3.y * dir.z;
	camEye->z = cnf.snake->pos.z + cnf.head.r1.z * dir.x + cnf.head.r2.z * dir.y + cnf.head.r3.z * dir.z;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	vec3f camEye;
	genCamEyePosition(&camEye);

	gluLookAt(camEye.x, camEye.y, camEye.z,
			  cnf.snake->pos.x, cnf.snake->pos.y, cnf.snake->pos.z,
			  cnf.head.r2.x, cnf.head.r2.y, cnf.head.r2.z);

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