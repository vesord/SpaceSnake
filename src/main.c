#include "spaceSnake.h"
#include "display.h"
#include "keys.h"
#include "utils.h"
#include "moving.h"
#include "bmp.h"

vec3f g_pos = {.x = 0.f, .y = 0.f, .z = 20.f};

dirMat g_cam = {
	.f.x = 0.f, .f.y = 0.f, .f.z = -1.f,
	.u.x = 0.f, .u.y = 1.f, .u.z = 0.f,
	.l.x =1.f, .l.y =0.f, .l.z = 0.f
};

GLuint g_texSun;
GLuint g_texSpace;

t_listPos* g_snake = NULL;	// todo change pos list to (void* data) list
t_listPos* g_fruits = NULL;

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

void initSnake() {
	g_snake = malloc(sizeof *g_snake);
	g_snake->pos.x = 0.f;
	g_snake->pos.y = 0.f;
	g_snake->pos.z = 20.f;
	g_snake->next = NULL;

	// todo: delete
	t_listPos *tmp;
	t_listPos *prev;
	prev = g_snake;

	tmp = malloc(sizeof *g_snake);
	tmp->next = NULL;
	tmp->pos.x = prev->pos.x;
	tmp->pos.y = prev->pos.y;
	tmp->pos.z = prev->pos.z + 1.5;
	g_snake->next = tmp;
	prev = tmp;

	tmp = malloc(sizeof *g_snake);
	tmp->next = NULL;
	tmp->pos.x = prev->pos.x;
	tmp->pos.y = prev->pos.y;
	tmp->pos.z = prev->pos.z + 1.5;
	g_snake->next->next = tmp;
	prev = tmp;

	tmp = malloc(sizeof *g_snake);
	tmp->next = NULL;
	tmp->pos.x = prev->pos.x;
	tmp->pos.y = prev->pos.y;
	tmp->pos.z = prev->pos.z + 1.5;
	g_snake->next->next->next = tmp;

	// todo end delete
}

void initLight() {
//	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	GLfloat myAmbient[] = {.1, .1, .1, 1.};
	GLfloat myDiffuse[] = {1., 1., 1., 1.};
	GLfloat mySpecular[] = {1., 1., 1., 1.};

	glLightfv(GL_LIGHT0, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, mySpecular);
	glEnable(GL_LIGHT0);

/*	glLightfv(GL_LIGHT1, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, mySpecular);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, mySpecular);
	glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT3, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, mySpecular);
	glEnable(GL_LIGHT3);

	glLightfv(GL_LIGHT4, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, mySpecular);
	glEnable(GL_LIGHT4);

	glLightfv(GL_LIGHT5, GL_AMBIENT, myAmbient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, myDiffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, mySpecular);
	glEnable(GL_LIGHT5);*/

	glEnable(GL_LIGHTING);
}

void initTexture(const char *filename, GLuint *texture) {
	glGenTextures(1, texture);
	glBindTexture (GL_TEXTURE_2D, *texture);

	int width, height;
	unsigned char* image = myBMPLoader(filename, &width, &height);
	if (!image)
		exit(1);

	fixImage(image, width, height, 4);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);
	free(image);

//	glBindTexture (GL_TEXTURE_2D, 0);
}

void initTextures() {
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	initTexture("./textures/Star.bmp", &g_texSpace);
//	initTexture("./textures/Moon.bmp", &g_texSun);
}

int main(int argc, char ** argv) {
	initGlut(&argc, argv);
	initGL();
	initTextures();
	initLight();
	initSnake();
	addFruits(10); // todo config initial fruit count

	glutMainLoop();
	return 0;
}
