#include "spaceSnake.h"
#include "utils.h"

extern t_globalConfiguration cnf;

static void calcCamStep(GLfloat step) {
	cnf.snake->pos.x += cnf.cam.r1.x * step;
	cnf.snake->pos.y += cnf.cam.r1.y * step;
	cnf.snake->pos.z += cnf.cam.r1.z * step;
}

static void calcSnakeStep(GLfloat step) {
	t_listPos *body = cnf.snake;
	t_listPos *prev;

	body->pos.x += cnf.cam.r1.x * step;
	body->pos.y += cnf.cam.r1.y * step;
	body->pos.z += cnf.cam.r1.z * step;
	prev = body;
	body = body->next;

	vec3f dir;

	for (; body; body = body->next) {
		dir.x = body->pos.x - prev->pos.x;
		dir.y = body->pos.y - prev->pos.y;
		dir.z = body->pos.z - prev->pos.z;
		normalize(&dir);
		body->pos.x = prev->pos.x + dir.x * cnf.game.snakeDefault.bodyDistance;
		body->pos.y = prev->pos.y + dir.y * cnf.game.snakeDefault.bodyDistance;
		body->pos.z = prev->pos.z + dir.z * cnf.game.snakeDefault.bodyDistance;
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
	body->next->pos.z = body->pos.z + cnf.game.snakeDefault.bodyDistance;
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
		fruit->pos = randVec3fRange(-cnf.game.cell.radius / 1.8, cnf.game.cell.radius / 1.8);
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
		if (distance(cnf.snake->pos, fruit->pos) < cnf.game.snakeDefault.size + cnf.game.fruitDefault.size)  {
			snakeGrow();
			fruitDelete(fruit);
			addFruits(1);
			return;
		}
	}
}

void calculateStep() {
	GLfloat step = cnf.game.snakeDefault.movSpeed;
	calcCamStep(step);
	calcSnakeStep(step);
	checkFruitEating();
}
