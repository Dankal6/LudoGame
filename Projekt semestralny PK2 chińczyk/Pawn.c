#include "Pawn.h"

typedef struct {
	char player[7];		//mozna by dynamicznie, do ewentualnej poprawki
	int id;
	int x, y;
	int pos_on_road;
	int in_base;
	char name[7];
	int color;
}_pawn;
