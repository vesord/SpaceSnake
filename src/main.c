#include "spaceSnake.h"
#include "display.h"
#include "keys.h"
#include "moving.h"
#include "bmp.h"
#include "utils.h"

t_globalConfiguration cnf;

void initGlut(int *argc, char ** argv) {
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 640);		// todo add to config
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Space Snake");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutIgnoreKeyRepeat(GL_TRUE);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyReleased);
}

void initGL() {
	glClearColor(.3f, .3f, .3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);

	glViewport(0, 0, 640, 640); // todo add config window size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1., 2., 2000.); // todo add config fov aspect
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void deleteSnake() {
	lstFreeSimple(cnf.snake);
}

static void initSnake() {
	cnf.snake = malloc(sizeof *cnf.snake);
	cnf.snake->pos.x = 0.f;
	cnf.snake->pos.y = 0.f;
	cnf.snake->pos.z = 20.f;
	cnf.snake->next = NULL;

	// todo: delete
	t_listPos *tmp;
	t_listPos *prev;
	prev = cnf.snake;

	tmp = malloc(sizeof *cnf.snake);
	tmp->next = NULL;
	tmp->pos.x = prev->pos.x;
	tmp->pos.y = prev->pos.y;
	tmp->pos.z = prev->pos.z + 1.5;
	cnf.snake->next = tmp;
	prev = tmp;

	tmp = malloc(sizeof *cnf.snake);
	tmp->next = NULL;
	tmp->pos.x = prev->pos.x;
	tmp->pos.y = prev->pos.y;
	tmp->pos.z = prev->pos.z + 1.5;
	cnf.snake->next->next = tmp;
	prev = tmp;

	tmp = malloc(sizeof *cnf.snake);
	tmp->next = NULL;
	tmp->pos.x = prev->pos.x;
	tmp->pos.y = prev->pos.y;
	tmp->pos.z = prev->pos.z + 1.5;
	cnf.snake->next->next->next = tmp;

	// todo end delete
}

static void setDefaultConfiguration() {
	cnf.game = configDefault.game;
	cnf.cam = configDefault.cam;
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

int main(int argc, char ** argv) {
	initGlut(&argc, argv);
	initGL();
	initTextures();
	initLight();
	restart();
	addFruits(cnf.game.fruitDefault.initCount);

	glutMainLoop();
	return 0;
}
