//
// Created by vesord on 03.04.2021.
//

#ifndef SPACESNAKE_UTILS_H
#define SPACESNAKE_UTILS_H

#include "spaceSnake.h"

typedef struct	s_listPos {
	struct s_listPos*	next;
	vec3f				pos;
}				t_listPos;

void rotateMatVec(mat3f * mat, vec3f vec, GLfloat angle);
void normalize(vec3f* vec);
void transposeMat(mat3f *mat);

vec3f randVec3fRange(GLfloat min, GLfloat max);

GLfloat distance(vec3f v1, vec3f v2);

#endif //SPACESNAKE_UTILS_H
