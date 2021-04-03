//
// Created by vesord on 03.04.2021.
//

#include "spaceSnake.h"
#include "math.h"

void swapGLfloat(GLfloat* first, GLfloat* second) {
	GLfloat tmp;

	tmp = *first;
	*first = *second;
	*second = tmp;
}

static GLfloat mulMatVectors(GLfloat m1x, GLfloat m1y, GLfloat m1z, 
							 GLfloat m2x, GLfloat m2y, GLfloat m2z) {
	return m1x * m2x + m1y * m2y + m1z * m2z;
}

mat3f mulMat(mat3f *mat1, mat3f *mat2) { // todo think about optimization
	mat3f res;
	res.row1.x = mulMatVectors(mat1->row1.x, mat1->row1.y, mat1->row1.z,
							   mat2->row1.x, mat2->row2.x, mat2->row3.x);
	res.row1.y = mulMatVectors(mat1->row1.x, mat1->row1.y, mat1->row1.z,
							   mat2->row1.y, mat2->row2.y, mat2->row3.y);
	res.row1.z = mulMatVectors(mat1->row1.x, mat1->row1.y, mat1->row1.z,
							   mat2->row1.z, mat2->row2.z, mat2->row3.z);

	res.row2.x = mulMatVectors(mat1->row2.x, mat1->row2.y, mat1->row2.z,
							   mat2->row1.x, mat2->row2.x, mat2->row3.x);
	res.row2.y = mulMatVectors(mat1->row2.x, mat1->row2.y, mat1->row2.z,
							   mat2->row1.y, mat2->row2.y, mat2->row3.y);
	res.row2.z = mulMatVectors(mat1->row2.x, mat1->row2.y, mat1->row2.z,
							   mat2->row1.z, mat2->row2.z, mat2->row3.z);

	res.row3.x = mulMatVectors(mat1->row3.x, mat1->row3.y, mat1->row3.z,
							   mat2->row1.x, mat2->row2.x, mat2->row3.x);
	res.row3.y = mulMatVectors(mat1->row3.x, mat1->row3.y, mat1->row3.z,
							   mat2->row1.y, mat2->row2.y, mat2->row3.y);
	res.row3.z = mulMatVectors(mat1->row3.x, mat1->row3.y, mat1->row3.z,
							   mat2->row1.z, mat2->row2.z, mat2->row3.z);
	return res;
}

void transposeMat(mat3f *mat) {
	swapGLfloat(&mat->row1.y, &mat->row2.x);
	swapGLfloat(&mat->row1.z, &mat->row3.x);
	swapGLfloat(&mat->row2.z, &mat->row3.y);
}

/**
 * rotation is performed by rotation 3x3 matrix
 * \param mat is pointer to 3x3 matrix which would be rotated
 * \param vec normalized 3x1 vector around which rotate
 * \param angle angle
*/
void rotateMatVec(mat3f * mat, vec3f vec, GLfloat angle) { // todo think about moving getting rot matrix in another f()
	GLfloat angCos = cosf(angle);
	GLfloat angSin = sinf(angle);
	mat3f rotMat;
	rotMat.row1.x = angCos + (1 - angCos) * vec.x * vec.x;
	rotMat.row1.y = (1 - angCos) * vec.x * vec.y - angSin * vec.z;
	rotMat.row1.z = (1 - angCos) * vec.x * vec.z + angSin * vec.y;
	rotMat.row2.x = (1 - angCos) * vec.y * vec.x + angSin * vec.z;
	rotMat.row2.y = angCos + (1 - angCos) * vec.y * vec.y;
	rotMat.row2.z = (1 - angCos) * vec.y * vec.z - angSin * vec.x;
	rotMat.row3.x = (1 - angCos) * vec.z * vec.x - angSin * vec.y;
	rotMat.row3.y	= (1 - angCos) * vec.z * vec.y + angSin * vec.x;
	rotMat.row3.z = angCos + (1 - angCos) * vec.z * vec.z;
	transposeMat(mat);
	*mat = mulMat(&rotMat, mat);
	transposeMat(mat);
}

void normalize(vec3f* vec) {
	GLfloat size = sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x /= size;
	vec->y /= size;
	vec->z /= size;
}