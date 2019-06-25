#include"Save_load.h"

void save_to_file(_pawn * pawn, _player *players, int num_of_players)
{
	FILE *fp;
	if ((fp = fopen("save.txt", "w")) == NULL) {
		printf("Can not open file!\n");
		return;
	}
	fprintf(fp, "%i\n", num_of_players);
	for (int i = 0; i < num_of_players; i++)
	{
		fprintf(fp, "%i\n", players[i].won);
		fprintf(fp, "%i\n", players[i].place);
		fprintf(fp, "%i\n", players[i].random);
		fprintf(fp, "%i\n", players[i].AI);
	}
	for (int i = 0; i < num_of_players*4; i++)
	{
		fprintf(fp, "%i\n", pawn[i].id);
		fprintf(fp, "%i\n", pawn[i].player);
		fprintf(fp, "%i\n", pawn[i].color);
		fprintf(fp, "%i\n", pawn[i].in_base);
		fprintf(fp, "%i\n", pawn[i].pos_on_road);
		fprintf(fp, "%i\n", pawn[i].distance);
		fprintf(fp, "%i\n", pawn[i].x);
		fprintf(fp, "%i\n", pawn[i].y);
		fprintf(fp, "%i\n", pawn[i].on_meta);
	}
	fclose(fp);
}

int load_players_from_file()
{
	int num_of_players;
	FILE *fp;
	if ((fp = fopen("save.txt", "r")) == NULL) {
		printf("Can not open save.txt file!\n");
		Sleep(1000);
		exit(0);
	}
	fscanf(fp, "%i", &num_of_players);
	return num_of_players;
}

void load_from_file(_pawn *pawn, _board *board,_player *players,HANDLE h)
{
	FILE *fp;
	if ((fp = fopen("save.txt", "r")) == NULL) {
		printf("Can not open save.txt file!\n");
		Sleep(1000);
		exit(0);
	}
	for (int i = 0; i < board->num_of_players; i++)
	{
		for (int j = 0; j < board->num_of_players; j++)
		{
			board->bases[i][j].how_many_pawns = 0;
			pop_front(&board->bases[i][j].pawns);
		}
	}
	int num_of_players;
	fscanf(fp, "%i", &num_of_players);
	for (int i = 0; i < num_of_players; i++)
	{
		fscanf(fp, "%i\n", &players[i].won);
		fscanf(fp, "%i\n", &players[i].place);
		fscanf(fp, "%i\n", &players[i].random);
		fscanf(fp, "%i\n", &players[i].AI);
	}
	for (int i = 0; i < num_of_players*4; i++)
	{
		fscanf(fp, "%i", &pawn[i].id);
		fscanf(fp, "%i", &pawn[i].player);
		fscanf(fp, "%i", &pawn[i].color);
		fscanf(fp, "%i", &pawn[i].in_base);
		fscanf(fp, "%i", &pawn[i].pos_on_road);
		fscanf(fp, "%i", &pawn[i].distance);
		fscanf(fp, "%i", &pawn[i].x);
		fscanf(fp, "%i", &pawn[i].y);
		fscanf(fp, "%i", &pawn[i].on_meta);
		if (pawn[i].in_base == 1)
		{
			push_back(&board->bases[pawn[i].player][pawn[i].id - 1].pawns, &pawn[i]);		//ustawiam wskaznik na pionka w bazie
			board->bases[pawn[i].player][pawn[i].id - 1].how_many_pawns = 1;
		}
		else
		{
			push_back(&board->road[pawn[i].distance+(4*pawn[i].player)-1].pawns, &pawn[i]);		//ustawiam wskaznik na pionka w trasie
			board->road[pawn[i].distance + (4*pawn[i].player)-1].how_many_pawns++;
		}
	}
	fclose(fp);
}
