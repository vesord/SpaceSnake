//
// Created by vesord on 03.04.2021.
//

#ifndef SPACESNAKE_KEYS_H
#define SPACESNAKE_KEYS_H

typedef struct	s_pressedKeys {
	char a;
	char d;
	char w;
	char s;
	char q;
	char e;
}				t_pressedKeys;

typedef struct	s_pressedMouse {
	char left;
	char right;
}				t_pressedMouse;

void doKeysActions();
void keyPressed(unsigned char key, int x, int y);
void keyReleased(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mouseMove(int x, int y);

#endif //SPACESNAKE_KEYS_H
