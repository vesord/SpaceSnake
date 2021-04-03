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

void doKeysActions();
void keyPressed(unsigned char key, int x, int y);
void keyReleased(unsigned char key, int x, int y);

#endif //SPACESNAKE_KEYS_H
