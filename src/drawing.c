#include "spaceSnake.h"
#include "materials.h"

extern GLuint g_texSun;
extern GLuint g_texSpace;
extern t_globalConfiguration cnf;

void drawScene() {
	applyMaterial(GL_BACK, MATERIAL_EMPTY_END);
	applyMaterial(GL_FRONT, MATERIAL_EMPTY_END);

	GLdouble ofs = cnf.game.cell.radius;
	glPushMatrix();
	glutWireSphere(ofs, 20, 20);
	glPopMatrix();
}

void drawSnake() {
	glPushMatrix();
	applyMaterial(GL_FRONT, MATERIAL_EMERALD);

	t_listPos *body = cnf.snake;
	for (; body; body = body->next) {
		glPushMatrix();
		glTranslatef(body->pos.x, body->pos.y, body->pos.z);
		glutSolidSphere(cnf.game.snakeDefault.size, 50, 50);
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
		glutSolidTorus(cnf.game.fruitDefault.size / 2, cnf.game.fruitDefault.size, 25, 25);
		glPopMatrix();
	}
}

void drawSkyBox() {
	GLfloat ofs = 300.f;

	applyMaterial(GL_FRONT, MATERIAL_EMPTY_END);

	glBindTexture(GL_TEXTURE_2D, cnf.tex.skybox.right);
	glBegin(GL_QUADS);
	glColor3f(.9f, 0.2f, 2.f); // +x plane
	glTexCoord2f(1, 1); glVertex3f( ofs,  ofs,  ofs);
	glTexCoord2f(0, 1); glVertex3f( ofs,  ofs, -ofs);
	glTexCoord2f(0, 0); glVertex3f( ofs, -ofs, -ofs);
	glTexCoord2f(1, 0); glVertex3f( ofs, -ofs,  ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, cnf.tex.skybox.left);
	glBegin(GL_QUADS);
	glColor3f(.4f, 0.f, 0.7f); // -x plane
	glTexCoord2f(1, 1); glVertex3f(-ofs,  ofs, -ofs);
	glTexCoord2f(0, 1); glVertex3f(-ofs,  ofs,  ofs);
	glTexCoord2f(0, 0); glVertex3f(-ofs, -ofs,  ofs);
	glTexCoord2f(1, 0); glVertex3f(-ofs, -ofs, -ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, cnf.tex.skybox.front);
	glBegin(GL_QUADS);
	glColor3f(0.1f, 0.5f, 0.8f); // -z plane
	glTexCoord2f(1, 1); glVertex3f( ofs,  ofs, -ofs);
	glTexCoord2f(0, 1); glVertex3f(-ofs,  ofs, -ofs);
	glTexCoord2f(0, 0); glVertex3f(-ofs, -ofs, -ofs);
	glTexCoord2f(1, 0); glVertex3f( ofs, -ofs, -ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, cnf.tex.skybox.back);
	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.1f, 0.3f); // +z plane
	glTexCoord2f(1, 1); glVertex3f(-ofs,  ofs,  ofs);
	glTexCoord2f(0, 1); glVertex3f( ofs,  ofs,  ofs);
	glTexCoord2f(0, 0); glVertex3f( ofs, -ofs,  ofs);
	glTexCoord2f(1, 0); glVertex3f(-ofs, -ofs,  ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, cnf.tex.skybox.down);
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.9f, 0.9f); // -y plane
	glTexCoord2f(1, 1); glVertex3f(-ofs, -ofs, -ofs);
	glTexCoord2f(0, 1); glVertex3f(-ofs, -ofs,  ofs);
	glTexCoord2f(0, 0); glVertex3f( ofs, -ofs,  ofs);
	glTexCoord2f(1, 0); glVertex3f( ofs, -ofs, -ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, cnf.tex.skybox.up);
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.9f, 0.3f); // +y plane
	glTexCoord2f(1, 1); glVertex3f( ofs,  ofs, -ofs);
	glTexCoord2f(0, 1); glVertex3f( ofs,  ofs,  ofs);
	glTexCoord2f(0, 0); glVertex3f(-ofs,  ofs,  ofs);
	glTexCoord2f(1, 0); glVertex3f(-ofs,  ofs, -ofs);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}
