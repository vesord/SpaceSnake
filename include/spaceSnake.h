//
// Created by vesord on 03.04.2021.
//

#ifndef SPACESNAKE_SPACESNAKE_H
#define SPACESNAKE_SPACESNAKE_H

#include <GL/glut.h>
#include "materials.h"

typedef struct	s_vec3f {
	GLfloat x;
	GLfloat y;
	GLfloat z;
}				vec3f;

typedef struct	s_mat3f {
	vec3f row1;
	vec3f row2;
	vec3f row3;
}				mat3f;

typedef struct	s_directionMat {
	vec3f f;	// forward
	vec3f u;	// up
	vec3f l;	// left
}				dirMat;

typedef struct	s_listPos {
	struct s_listPos*	next;
	vec3f				pos;
	t_material_type		material;
}				t_listPos;

typedef struct	s_globalConfiguration {
	t_listPos *snake;			// todo change pos list to (void* data) list
	t_listPos *fruits;
}				t_globalConfiguration;

#endif //SPACESNAKE_SPACESNAKE_H
