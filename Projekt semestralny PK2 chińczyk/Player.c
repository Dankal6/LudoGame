#include "Player.h"

void init(_player *players, int num_of_players)
{
	players[0].name = malloc(6 * sizeof(char));
	strcpy(players[0].name, "green");
	players[1].name = malloc(7 * sizeof(char));
	strcpy(players[1].name, "yellow");
	if (num_of_players > 2)
	{
		players[2].name = malloc(5 * sizeof(char));
		strcpy(players[2].name, "blue");
	}
	if (num_of_players > 3)
	{
		players[3].name = malloc(4 * sizeof(char));
		strcpy(players[3].name, "red");
	}


	for (int i = 0; i < num_of_players; i++)
	{
		players[i].begin = 10 * i;
		players[i].id = i;
		players[i].random = 0;

	}
}