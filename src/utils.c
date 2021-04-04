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
	res.r1.x = mulMatVectors(mat1->r1.x, mat1->r1.y, mat1->r1.z,
							 mat2->r1.x, mat2->r2.x, mat2->r3.x);
	res.r1.y = mulMatVectors(mat1->r1.x, mat1->r1.y, mat1->r1.z,
							 mat2->r1.y, mat2->r2.y, mat2->r3.y);
	res.r1.z = mulMatVectors(mat1->r1.x, mat1->r1.y, mat1->r1.z,
							 mat2->r1.z, mat2->r2.z, mat2->r3.z);

	res.r2.x = mulMatVectors(mat1->r2.x, mat1->r2.y, mat1->r2.z,
							 mat2->r1.x, mat2->r2.x, mat2->r3.x);
	res.r2.y = mulMatVectors(mat1->r2.x, mat1->r2.y, mat1->r2.z,
							 mat2->r1.y, mat2->r2.y, mat2->r3.y);
	res.r2.z = mulMatVectors(mat1->r2.x, mat1->r2.y, mat1->r2.z,
							 mat2->r1.z, mat2->r2.z, mat2->r3.z);

	res.r3.x = mulMatVectors(mat1->r3.x, mat1->r3.y, mat1->r3.z,
							 mat2->r1.x, mat2->r2.x, mat2->r3.x);
	res.r3.y = mulMatVectors(mat1->r3.x, mat1->r3.y, mat1->r3.z,
							 mat2->r1.y, mat2->r2.y, mat2->r3.y);
	res.r3.z = mulMatVectors(mat1->r3.x, mat1->r3.y, mat1->r3.z,
							 mat2->r1.z, mat2->r2.z, mat2->r3.z);
	return res;
}

void transposeMat(mat3f *mat) {
	swapGLfloat(&mat->r1.y, &mat->r2.x);
	swapGLfloat(&mat->r1.z, &mat->r3.x);
	swapGLfloat(&mat->r2.z, &mat->r3.y);
}

/**
 * rotation is performed by rotation 3x3 matrix
 * \param mat is pointer to 3x3 matrix which would be rotated
 * \param vec normalized 3x1 vector around which rotate
 * \param angle angle
*/
void rotateMatVec(mat3f * mat, vec3f vec, GLfloat angle) { // todo think about moving getting rot matrix in another r1()
	GLfloat angCos = cosf(angle);
	GLfloat angSin = sinf(angle);
	mat3f rotMat;
	rotMat.r1.x = angCos + (1 - angCos) * vec.x * vec.x;
	rotMat.r1.y = (1 - angCos) * vec.x * vec.y - angSin * vec.z;
	rotMat.r1.z = (1 - angCos) * vec.x * vec.z + angSin * vec.y;
	rotMat.r2.x = (1 - angCos) * vec.y * vec.x + angSin * vec.z;
	rotMat.r2.y = angCos + (1 - angCos) * vec.y * vec.y;
	rotMat.r2.z = (1 - angCos) * vec.y * vec.z - angSin * vec.x;
	rotMat.r3.x = (1 - angCos) * vec.z * vec.x - angSin * vec.y;
	rotMat.r3.y	= (1 - angCos) * vec.z * vec.y + angSin * vec.x;
	rotMat.r3.z = angCos + (1 - angCos) * vec.z * vec.z;
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

float randFloat() {
	return (float)(rand()) / (float)(RAND_MAX);
}

vec3f randVec3fRange(GLfloat min, GLfloat max) {
	vec3f res;
	GLfloat rng = max - min;

	res.x = max - randFloat() * rng;
	res.y = max - randFloat() * rng;
	res.z = max - randFloat() * rng;
	return res;
}

GLfloat distance(vec3f v1, vec3f v2) {
	return sqrtf((v1.x - v2.x) * (v1.x - v2.x)
				  + (v1.y - v2.y) * (v1.y - v2.y)
				  + (v1.z - v2.z) * (v1.z - v2.z));
}