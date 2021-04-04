#include "spaceSnake.h"
#include "utils.h"

extern vec3f g_pos;
extern dirMat g_cam;
extern t_listSnake *g_snake;

static void calcCamStep(GLfloat step) {
	g_pos.x += g_cam.f.x * step;
	g_pos.y += g_cam.f.y * step;
	g_pos.z += g_cam.f.z * step;
}

static void calcSnakeStep(GLfloat step) {
	t_listSnake *body = g_snake;
	t_listSnake *prev;

	body->pos.x += g_cam.f.x * step;
	body->pos.y += g_cam.f.y * step;
	body->pos.z += g_cam.f.z * step;
	prev = body;
	body = body->next;

	vec3f dir;

	for (; body; body = body->next) {
		dir.x = body->pos.x - prev->pos.x;
		dir.y = body->pos.y - prev->pos.y;
		dir.z = body->pos.z - prev->pos.z;
		normalize(&dir);
		body->pos.x = prev->pos.x + dir.x * 1.5; // todo config distance between body parts
		body->pos.y = prev->pos.y + dir.y * 1.5;
		body->pos.z = prev->pos.z + dir.z * 1.5;
		prev = body;
	}
}

void calculateStep() {
	GLfloat step = 0.1f; // todo config
	calcCamStep(step);
	calcSnakeStep(step);
}
