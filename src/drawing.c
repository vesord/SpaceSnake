#include "spaceSnake.h"
#include "utils.h"

extern vec3f g_pos;
extern dirMat g_cam;
extern t_listPos *g_snake;
extern t_listPos *g_fruits;

void drawScene() {
	GLdouble ofs = 50.; // todo config
	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(.9f, 0.2f, 2.f); // -x plane
	glVertex3d( ofs,  ofs,  ofs);
	glVertex3d( ofs,  ofs, -ofs);
	glVertex3d( ofs, -ofs, -ofs);
	glVertex3d( ofs, -ofs,  ofs);
	glColor3f(.4f, 0.f, 0.7f); // +x plane
	glVertex3d(-ofs,  ofs, -ofs);
	glVertex3d(-ofs,  ofs,  ofs);
	glVertex3d(-ofs, -ofs,  ofs);
	glVertex3d(-ofs, -ofs, -ofs);
	glColor3f(0.1f, 0.5f, 0.8f); // -z plane
	glVertex3d( ofs,  ofs, -ofs);
	glVertex3d(-ofs,  ofs, -ofs);
	glVertex3d(-ofs, -ofs, -ofs);
	glVertex3d( ofs, -ofs, -ofs);
	glColor3f(0.7f, 0.1f, 0.3f); // +z plane
	glVertex3d( ofs,  ofs,  ofs);
	glVertex3d( ofs, -ofs,  ofs);
	glVertex3d(-ofs, -ofs,  ofs);
	glVertex3d(-ofs,  ofs,  ofs);
	glColor3f(0.5f, 0.9f, 0.3f); // +y plane
	glVertex3d( ofs,  ofs,  ofs);
	glVertex3d(-ofs,  ofs,  ofs);
	glVertex3d(-ofs,  ofs, -ofs);
	glVertex3d( ofs,  ofs, -ofs);
	glColor3f(0.2f, 0.9f, 0.9f); // -y plane
	glVertex3d( ofs, -ofs,  ofs);
	glVertex3d( ofs, -ofs, -ofs);
	glVertex3d(-ofs, -ofs, -ofs);
	glVertex3d(-ofs, -ofs,  ofs);
	glEnd();
	glPopMatrix();
}

void drawSnake() {
	glPushMatrix();
	glColor3f(0.04f, 0.08f, 0.3f);

	t_listPos *body = g_snake;
	for (; body; body = body->next) {
		glPushMatrix();
		glTranslatef(body->pos.x, body->pos.y, body->pos.z);
//		glutWireSphere(1, 10, 10);		// todo configure snake size
		glutSolidSphere(1, 50, 50);		// todo configure snake size
		glPopMatrix();
	}
	glPopMatrix();
}

void drawFruits() {
	t_listPos *fruit = g_fruits;

	glColor3f(0.6f, 0.1f, 0.3f);
	for (; fruit; fruit = fruit->next) {
		glPushMatrix();
		glTranslatef(fruit->pos.x, fruit->pos.y, fruit->pos.z);
//		glutWireTorus(0.3, 0.6, 10, 10); // todo config fruit size
		glutSolidTorus(0.3, 0.6, 10, 10); // todo config fruit size
		glPopMatrix();
	}
}
