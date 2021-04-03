#include "spaceSnake.h"

extern vec3f g_pos;
extern dirMat g_cam;

void calculateStep() {
	GLfloat step = 0.1f; // todo config
	g_pos.x += g_cam.f.x * step;
	g_pos.y += g_cam.f.y * step;
	g_pos.z += g_cam.f.z * step;
}
