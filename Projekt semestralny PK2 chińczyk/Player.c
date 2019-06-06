#include "Player.h"

void init_players(_player *players, int num_of_players)
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
		players[i].place = 0;

	}
}

int endgame(_player *player, int *place, int num_of_players)
{
	player->place = (*place);
	if ((*place) == num_of_players - 1)
	{
		return 0;
	}
	(*place)++;
	return 1;
}

void place_for_last_player(_player *players, int num_of_players)
{
	for (int i = 0; i < num_of_players; i++)
	{
		if (players[i].place == 0)
		{
			players[i].place = num_of_players;
			return;
		}
	}
}

void show_score(_player*players, HANDLE h, int num_of_players)
{
	gotoxy(0, 24, h);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (int i = 0; i < num_of_players; i++)
	{
		printf("\nPlayer: %s, place: %i.", players[i].name, players[i].place);
	}
}

int ask_for_players(HANDLE h)
{
	int num_of_players;
	gotoxy(0, 0, h);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("How many players? ");
	scanf("%i", &num_of_players);
	clear_text(0, h);
	return num_of_players;
}

int ask_for_load(HANDLE h)
{ 
	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("1. Play.\n2. Load from file.\nChoice: ");
	scanf("%i", &choice);
	clear_text(0, h);
	return choice;
}