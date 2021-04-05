//
// Created by vesord on 03.04.2021.
//

#ifndef SPACESNAKE_UTILS_H
#define SPACESNAKE_UTILS_H

#include "spaceSnake.h"

void genRotMat(mat3f *rotMat, vec3f vec, GLfloat angle);
void rotVec(vec3f *vec, mat3f *rotMat);
void rotMatAroundVec(mat3f * mat, vec3f vec, GLfloat angle);
void normalize(vec3f* vec);
void transposeMat(mat3f *mat);

vec3f randVec3fRange(GLfloat min, GLfloat max);

GLfloat distance(vec3f v1, vec3f v2);

void lstFreeSimple(t_listPos *lst);

#endif //SPACESNAKE_UTILS_H
