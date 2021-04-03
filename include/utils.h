//
// Created by vesord on 03.04.2021.
//

#ifndef SPACESNAKE_UTILS_H
#define SPACESNAKE_UTILS_H

#include "spaceSnake.h"

void rotateMatVec(mat3f * mat, vec3f vec, GLfloat angle);
void normalize(vec3f* vec);
void transposeMat(mat3f *mat);

#endif //SPACESNAKE_UTILS_H
