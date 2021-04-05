#ifndef SPACESNAKE_GAMEWINDOW_H
#define SPACESNAKE_GAMEWINDOW_H

#include "types.h"

typedef struct	s_windowParams {
	int width;
	int height;
	int initPosX;
	int initPosY;
	int fullscreen;
	GLdouble fovy;
	GLdouble aspect;
	GLdouble zNear;
	GLdouble zFar;
}				gameWindow;

#endif //SPACESNAKE_GAMEWINDOW_H
