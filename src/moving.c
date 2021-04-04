#include "spaceSnake.h"
#include "utils.h"

extern mat3f g_cam;
extern t_globalConfiguration cnf;

static void calcCamStep(GLfloat step) {
	cnf.snake->pos.x += g_cam.r1.x * step;
	cnf.snake->pos.y += g_cam.r1.y * step;
	cnf.snake->pos.z += g_cam.r1.z * step;
}

static void calcSnakeStep(GLfloat step) {
	t_listPos *body = cnf.snake;
	t_listPos *prev;

	body->pos.x += g_cam.r1.x * step;
	body->pos.y += g_cam.r1.y * step;
	body->pos.z += g_cam.r1.z * step;
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
	t_listPos *body = cnf.snake;

	for (; body->next; body = body->next);

	body->next = malloc(sizeof *body);
	body->next->next = NULL;
	body->next->pos.x = body->pos.x;
	body->next->pos.y = body->pos.y;
	body->next->pos.z = body->pos.z + 1.5; // todo config snake size
}

void fruitDelete(t_listPos *toDelete) { // todo optimize somehow
	t_listPos *fruit = cnf.fruits;

	if (!toDelete)
		return;

	if (toDelete == cnf.fruits) {
		cnf.fruits = toDelete->next;
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
		if (cnf.fruits) {
			fruit->next = cnf.fruits;
			cnf.fruits = fruit;
		} else {
			cnf.fruits = fruit;
		}
	}
}
void checkFruitEating() {
	t_listPos *fruit = cnf.fruits;

	for (; fruit; fruit = fruit->next) {
		if (distance(cnf.snake->pos, fruit->pos) < 1.5 + 0.6)  { // todo config fruit size and snake size
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
