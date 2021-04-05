#ifndef SPACESNAKE_GAMETEXTURES_H
#define SPACESNAKE_GAMETEXTURES_H

#include "GL/glut.h"

typedef struct	s_skybox {
	GLuint up;
	GLuint down;
	GLuint left;
	GLuint right;
	GLuint front;
	GLuint back;
}				t_skybox;

typedef struct	s_gameTextures {
	t_skybox skybox;
}				gameTextures;

#endif //SPACESNAKE_GAMETEXTURES_H
