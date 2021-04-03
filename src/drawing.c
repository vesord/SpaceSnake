#include "spaceSnake.h"
#include <math.h>

#include "utils.h"
#include <stdlib.h>
#include <string.h>

extern vec3f g_pos;
extern dirMat g_cam;

typedef struct s_vec4f {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
}				vec4f;

typedef struct s_mat4f {
	vec4f row1;
	vec4f row2;
	vec4f row3;
	vec4f row4;
}				mat4f;

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


	mat3f trCam = *((mat3f*)&g_cam);
	transposeMat(&trCam);
	trCam.row1.x *= -1;
	trCam.row1.y *= -1;
	trCam.row1.z *= -1;

	mat4f m;
	memset(&m, 0, sizeof(m));
	memcpy(&m.row1, &g_cam.f, sizeof(g_cam.f));
	memcpy(&m.row2, &g_cam.u, sizeof(g_cam.f));
	memcpy(&m.row3, &g_cam.l, sizeof(g_cam.f));
	m.row4.w = 1;

	glMultMatrixf((GLfloat*)&m);

//	GLfloat angle = acosf(-g_cam.f.z) / M_PI * 180.f;
//	glRotatef(angle, 0, 1.f, 0);

//	glutWireSphere(5.f, 10, 10);
	glutWireTeapot(4);
	glPopMatrix();
}
