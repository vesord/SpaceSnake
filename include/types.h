#ifndef SPACESNAKE_TYPES_H
#define SPACESNAKE_TYPES_H

#include "GL/glut.h"
#include "materials.h"

typedef struct	s_vec3f {
	GLfloat x;
	GLfloat y;
	GLfloat z;
}				vec3f;

typedef struct	s_mat3f {
	vec3f r1;
	vec3f r2;
	vec3f r3;
}				mat3f;

typedef struct	s_listPos {
	struct s_listPos*	next;
	vec3f				pos;
	t_material_type		material;
}				t_listPos;

static const vec3f normalVecZ = {.x = 0.f, .y = 0.f, .z = 1.f};
static const vec3f normalVecY = {.x = 0.f, .y = 1.f, .z = 0.f};
static const vec3f normalVecX = {.x = 1.f, .y = 0.f, .z = 0.f};

#endif //SPACESNAKE_TYPES_H
