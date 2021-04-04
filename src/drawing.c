#include "spaceSnake.h"
#include "materials.h"

extern dirMat g_cam;
extern GLuint g_texSun;
extern GLuint g_texSpace;
extern t_globalConfiguration cnf;

void drawScene() {
	applyMaterial(GL_BACK, MATERIAL_EMPTY_END);
	applyMaterial(GL_FRONT, MATERIAL_EMPTY_END);

	GLdouble ofs = 50.; // todo config
	glPushMatrix();
	glutWireSphere(ofs, 25, 25);
	glPopMatrix();
}

void drawSnake() {
	glPushMatrix();
	applyMaterial(GL_FRONT, MATERIAL_EMERALD);

	t_listPos *body = cnf.snake;
	for (; body; body = body->next) {
		glPushMatrix();
		glTranslatef(body->pos.x, body->pos.y, body->pos.z);
		glutSolidSphere(1, 50, 50);		// todo configure snake size
		glPopMatrix();
	}
	glPopMatrix();
}

void drawFruits() {
	t_listPos *fruit = cnf.fruits;

	applyMaterial(GL_FRONT, MATERIAL_GOLD);
	for (; fruit; fruit = fruit->next) {
		glPushMatrix();
		glTranslatef(fruit->pos.x, fruit->pos.y, fruit->pos.z);
//		glutWireTorus(0.3, 0.6, 10, 10); // todo config fruit size
		glutSolidTorus(0.3, 0.6, 10, 10); // todo config fruit size
		glPopMatrix();
	}
}

void drawSkyBox() {
	GLfloat ofs = 500.f;

	glBindTexture(GL_TEXTURE_2D, g_texSpace);
	applyMaterial(GL_FRONT, MATERIAL_EMPTY_END);
	glBegin(GL_QUADS);
	glColor3f(.9f, 0.2f, 2.f); // -x plane
	glTexCoord2f(0.0f, 0.0f); glVertex3f( ofs,  ofs,  ofs);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( ofs,  ofs, -ofs);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( ofs, -ofs, -ofs);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( ofs, -ofs,  ofs);

	glColor3f(.4f, 0.f, 0.7f); // +x plane
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-ofs,  ofs, -ofs);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-ofs,  ofs,  ofs);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-ofs, -ofs,  ofs);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-ofs, -ofs, -ofs);

	glColor3f(0.1f, 0.5f, 0.8f); // -z plane
	glTexCoord2f(0.0f, 0.0f); glVertex3f( ofs,  ofs, -ofs);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-ofs,  ofs, -ofs);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-ofs, -ofs, -ofs);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( ofs, -ofs, -ofs);

	glColor3f(0.7f, 0.1f, 0.3f); // +z plane
	glTexCoord2f(0.0f, 0.0f); glVertex3f( ofs,  ofs,  ofs);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( ofs, -ofs,  ofs);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-ofs, -ofs,  ofs);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-ofs,  ofs,  ofs);

	glColor3f(0.2f, 0.9f, 0.9f); // -y plane
	glTexCoord2f(0.0f, 0.0f); glVertex3f( ofs, -ofs,  ofs);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( ofs, -ofs, -ofs);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-ofs, -ofs, -ofs);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-ofs, -ofs,  ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, g_texSun);
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.9f, 0.3f); // +y plane
	glTexCoord2f(0.0f, 0.0f); glVertex3f( ofs,  ofs,  ofs);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-ofs,  ofs,  ofs);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-ofs,  ofs, -ofs);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( ofs,  ofs, -ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}
