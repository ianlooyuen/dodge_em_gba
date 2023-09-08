#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

#define MAX_ENTITIES 8
#define PLAYER_SIZE 8
#define ENEMY_SIZE 5
// TODO: Create any necessary structs

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

struct entity {
	int row;
	int col;
	int rd;
	int cd;
	u16 color;
};

struct state {
	int nentities;
	struct entity player;
	struct entity entities[MAX_ENTITIES];
};

#endif
