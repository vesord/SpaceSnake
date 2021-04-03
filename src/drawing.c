#include "spaceSnake.h"
#include <math.h>

extern vec3f g_pos;
extern dirMat g_cam;

void drawScene() {
	GLdouble ofs = 15.; // todo config
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
	glTranslatef(g_pos.x, g_pos.y, g_pos.z);

	GLfloat angle = acosf(-g_cam.f.z) / M_PI * 180.f;
	glRotatef(angle, g_cam.f.y, -g_cam.f.x, 0);

	glutWireSphere(5.f, 10, 10);
	glPopMatrix();
}
