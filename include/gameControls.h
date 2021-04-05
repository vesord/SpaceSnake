#ifndef SPACESNAKE_GAMECONTROLS_H
#define SPACESNAKE_GAMECONTROLS_H

#ifdef __APPLE__
# define GL_SILENCE_DEPRECATION
# include "GLUT/glut.h"
#else
# include "GL/glut.h"
#endif

typedef struct	s_gameContols {
	GLfloat mouseSense;
	GLfloat mouseInverse;
	GLfloat keyInverse;
}				gameControls;

#endif //SPACESNAKE_GAMECONTROLS_H
