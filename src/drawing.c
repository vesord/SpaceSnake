#include <GL/glut.h>

void drawScene() {
	GLdouble ofs = 7.; // todo config
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
	glColor3f(0.1f, 0.5f, 0.8f); // +z plane
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
