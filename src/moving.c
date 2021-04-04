#include "spaceSnake.h"
#include "utils.h"

extern vec3f g_pos;
extern dirMat g_cam;
extern t_listPos *g_snake;
extern t_listPos *g_fruits;

static void calcCamStep(GLfloat step) {
	g_pos.x += g_cam.f.x * step;
	g_pos.y += g_cam.f.y * step;
	g_pos.z += g_cam.f.z * step;
}

static void calcSnakeStep(GLfloat step) {
	t_listPos *body = g_snake;
	t_listPos *prev;

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

static void snakeGrow() {	// todo add saving last snake part
	t_listPos *body = g_snake;

	for (; body->next; body = body->next);

	body->next = malloc(sizeof *body);
	body->next->next = NULL;
	body->next->pos.x = body->pos.x;
	body->next->pos.y = body->pos.y;
	body->next->pos.z = body->pos.z + 1.5; // todo config snake size
}

void fruitDelete(t_listPos *toDelete) { // todo optimize somehow
	t_listPos *fruit = g_fruits;

	if (!toDelete)
		return;

	if (toDelete == g_fruits) {
		g_fruits = toDelete->next;
		free(toDelete);
		return;
	}

	for (; fruit; fruit = fruit->next) {
		if (fruit->next == toDelete) {
			fruit->next = toDelete->next;
			free(toDelete);
			return;
		}
	}
}

void addFruits(GLint count) {
	t_listPos *fruit;

	for (int i = 0; i < count; ++i) {
		fruit = malloc(sizeof *fruit);
		fruit->next = NULL;
		fruit->pos = randVec3fRange(-40.f, 40.f); // todo config fruits depends on game field
		if (g_fruits) {
			fruit->next = g_fruits;
			g_fruits = fruit;
		} else {
			g_fruits = fruit;
		}
	}
}
void checkFruitEating() {
	t_listPos *fruit = g_fruits;

	for (; fruit; fruit = fruit->next) {
		if (distance(g_snake->pos, fruit->pos) < 1.5 + 0.6)  { // todo config fruit size and snake size
			snakeGrow();
			fruitDelete(fruit);
			addFruits(1);
			return;
		}
	}
}

void calculateStep() {
	GLfloat step = 0.1f; // todo config step size
	calcCamStep(step);
	calcSnakeStep(step);
	checkFruitEating();
}
