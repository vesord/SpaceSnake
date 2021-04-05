#include "spaceSnake.h"
#include "display.h"
#include "keys.h"
#include "moving.h"
#include "bmp.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

t_globalConfiguration cnf;

void initGlut(int *argc, char ** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(cnf.window.width, cnf.window.height);
	glutInitWindowPosition(cnf.window.initPosX, cnf.window.initPosY);
	glutCreateWindow("Space Snake");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
}

void initGL() {
	glClearColor(.3f, .3f, .3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, cnf.window.width, cnf.window.height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(cnf.window.fovy, cnf.window.aspect, cnf.window.zNear, cnf.window.zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void deleteSnake() {
	lstFreeSimple(cnf.snake);
}

static void initSnake() {
	cnf.snake = malloc(sizeof *cnf.snake);
	cnf.snake->next = NULL;
	cnf.snake->pos.x = 0.f;
	cnf.snake->pos.y = 0.f;
	cnf.snake->pos.z = 20.f;
	cnf.snake->material = cnf.game.snakeDefault.material;

	cnf.snake->next = malloc(sizeof *cnf.snake);
	cnf.snake->next->next = NULL;
	cnf.snake->next->pos.x = cnf.snake->pos.x;
	cnf.snake->next->pos.y = cnf.snake->pos.y;
	cnf.snake->next->pos.z = cnf.snake->pos.z + 1.5;
	cnf.snake->next->material = cnf.game.snakeDefault.material;

	cnf.tail = cnf.snake->next;
}

static void setDefaultConfiguration() {
	cnf.game = g_configDefault.game;
	cnf.head = g_configDefault.head;
	cnf.cam = g_configDefault.cam;
	cnf.score = 0;
}

void restart() {
	deleteSnake();
	setDefaultConfiguration();
	initSnake();
}

void initLight() {
	glEnable(GL_LIGHTING);
	GLfloat myAmbient[] = {0.3, 0.3, 0.3, 1.};
	GLfloat myDiffuse[] = {1., 1., 1., 1.};
	GLfloat mySpecular[] = {1., 1., 1., 1.};
	glLightfv(GL_LIGHT0, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mySpecular);
	glEnable(GL_LIGHT0);
}

void initTexture(const char *filename, GLuint *texture) {
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP_SGIS,GL_TRUE);

	int width, height, channels;
	unsigned char* image = myBMPLoader(filename, &width, &height, &channels);
	if (!image)
		exit(1);

	GLenum colorStore = channels == 4 ? GL_RGBA : GL_RGB;

	fixImage(image, width, height, channels);
	glTexImage2D(GL_TEXTURE_2D, 0, colorStore, width, height, 0, colorStore, GL_UNSIGNED_BYTE, image);
	gluBuild2DMipmaps(GL_TEXTURE_2D, channels, width, height, colorStore, GL_UNSIGNED_BYTE, image);
	free(image);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void initTextures() {
	glEnable(GL_TEXTURE_2D);

	initTexture("./textures/skyboxSpace/left.bmp", &cnf.tex.skybox.left);
	initTexture("./textures/skyboxSpace/right.bmp", &cnf.tex.skybox.right);
	initTexture("./textures/skyboxSpace/front.bmp", &cnf.tex.skybox.front);
	initTexture("./textures/skyboxSpace/back.bmp", &cnf.tex.skybox.back);
	initTexture("./textures/skyboxSpace/down.bmp", &cnf.tex.skybox.down);
	initTexture("./textures/skyboxSpace/up.bmp", &cnf.tex.skybox.up);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void printIntro() {
	printf("You're abandoned immortal super duper ultra mega dangerous destroyer annihilator SNAKE.\n");
	printf("You've been jailed forever by your enemies. And you only joy now is infinite donat eating.\n\n");
	printf("CONTROLS: WASDQE, mouse left, mouse wheel, ESC\n");
	printf("Checkout spaceSnake.h for configuration (key/mouse inversion included)\n\n");
	printf("Type something to start.\n");

	char dummy;
	read(0, &dummy, 1);
}

int main(int argc, char ** argv) {
	printIntro();
	cnf = g_configDefault;
	initGlut(&argc, argv);
	initGL();
	initTextures();
	initLight();
	restart();
	addFruits(cnf.game.fruitDefault.initCount);

	glutMainLoop();
	return 0;
}
