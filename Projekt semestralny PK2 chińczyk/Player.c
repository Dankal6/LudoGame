#include "Player.h"

void init(_player *players)
{
	strcpy(players[0].name, "green");
	strcpy(players[1].name, "yellow");
	strcpy(players[2].name, "blue");
	strcpy(players[3].name, "red");

	for (int i = 0; i < 4; i++)
	{
		players[i].begin = 10 * i;
		players[i].id = i;
		players[i].random = 0;
	
	}
}