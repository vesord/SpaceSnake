#include "spaceSnake.h"
#include "utils.h"
#include <string.h>

extern vec3f g_pos;
extern dirMat g_cam;
extern t_listSnake *g_snake;

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

static void magicallyRotateCam() {
	mat3f trCam = *((mat3f*)&g_cam);
	transposeMat(&trCam);
	mat4f m;
	memset(&m, 0, sizeof(m));
	memcpy(&m.row1, &g_cam.f, sizeof(g_cam.f));
	memcpy(&m.row2, &g_cam.u, sizeof(g_cam.u));
	memcpy(&m.row3, &g_cam.l, sizeof(g_cam.l));
	m.row4.w = 1;
	glMultMatrixf((GLfloat*)&m);
	glRotatef(90.f, 0.f, -1.f, 0.f);
}

void drawSnake() {
	glPushMatrix();
	glColor3f(0.f, 0.f, 0.f);

//	glTranslatef(g_pos.x, g_pos.y, g_pos.z); // go to camera
//	magicallyRotateCam();
//	glTranslatef(-g_pos.x, -g_pos.y, -g_pos.z);
//	glTranslatef(0.f, -3.f, -10.f); // point from camera where start drawing snake

	t_listSnake *body = g_snake;

	for (; body; body = body->next) {
		glPushMatrix();
		glTranslatef(body->pos.x, body->pos.y, body->pos.z);
//		glTranslatef(0.f, -3.f, -10.f); // point from camera where start drawing snake
		glutWireSphere(1, 10, 10);
		glPopMatrix();
	}

	glPopMatrix();
}
