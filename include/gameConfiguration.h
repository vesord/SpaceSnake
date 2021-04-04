#ifndef SPACESNAKE_GAMECONFIGURATION_H
#define SPACESNAKE_GAMECONFIGURATION_H

#include "materials.h"

typedef struct	s_snakeParams {
	GLfloat size;
	GLfloat maxSize;
	GLfloat minSize;
	GLfloat	bodyDistance;
	GLfloat movSpeed;
	GLfloat rotSpeed;
	t_material_type material;
}				t_snakeParams;

typedef struct	s_fruitParams {
	GLfloat size;
	GLuint	initCount;
	GLfloat maxSize;
	GLfloat minSize;
	t_material_type material;
}				t_fruitParams;

typedef struct	s_cellParams {
	GLfloat radius;
	GLfloat maxRadius;
	GLfloat minRadius;
	t_material_type material;
}				t_cellParams;

typedef struct	s_gameParams {
	t_snakeParams snakeDefault;
	t_fruitParams fruitDefault;
	t_cellParams  cell;
}				gameParams;

#endif //SPACESNAKE_GAMECONFIGURATION_H
