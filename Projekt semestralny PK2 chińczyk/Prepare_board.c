#include "Prepare_board.h"

void init_board(_board *board, int num_of_players)
{
	//wyjscia z baz
	board->exits[0].x = 0; board->exits[0].y = 4; board->exits[0].color = 34;
	board->exits[1].x = 6; board->exits[1].y = 0; board->exits[1].color = 102;
	board->exits[2].x = 10; board->exits[2].y = 6; board->exits[2].color = 17;
	board->exits[3].x = 4; board->exits[3].y = 10; board->exits[3].color = 68;
	//kolory baz i ilosci pionkow na wyjsciach + mety
	for (int i = 0; i < 4; i++)
	{
		board->exits[i].how_many_pawns = 0;
		for (int j = 0; j < 4; j++)
		{
			if (i == 0)
				board->bases[i][j].color = 34;
			else if (i == 1)
				board->bases[i][j].color = 102;
			else if (i == 2)
				board->bases[i][j].color = 17;
			else if (i == 3)
				board->bases[i][j].color = 68;
		}
	}
	board->road = malloc(56 * sizeof(_field));
	prepare_road(board->road, num_of_players);
}

void prepare_bases(_board *board, _pawn *pawns, int num_of_players)
{
	int blue_pawn = 1, green_pawn = 1, yellow_pawn = 1, red_pawn = 1;
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{

			if (i < 2)
			{
				if (j < 2)
				{
					pawns[green_pawn - 1].id = green_pawn;
					pawns[green_pawn - 1].color = 32;
					pawns[green_pawn - 1].player = 0;
					pawns[green_pawn - 1].x = j;
					pawns[green_pawn - 1].y = i;
					pawns[green_pawn - 1].in_base = 1;
					pawns[green_pawn - 1].pos_on_road = 0;
					pawns[green_pawn - 1].on_meta = 0;
					pawns[green_pawn - 1].distance = 0;
					pawns[green_pawn - 1].next = NULL;

					board->bases[0][green_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[0][green_pawn - 1].pawns = NULL;
					push_back(&board->bases[0][green_pawn - 1].pawns, &pawns[green_pawn - 1]);
					board->bases[0][green_pawn - 1].x = j;
					board->bases[0][green_pawn - 1].y = i;
					board->bases[0][green_pawn - 1].how_many_pawns = 1;

					green_pawn++;
					continue;
				}
				if (j > 8)
				{
					pawns[yellow_pawn + 3].player = 1;
					pawns[yellow_pawn + 3].color = 96;
					pawns[yellow_pawn + 3].id = yellow_pawn;
					pawns[yellow_pawn + 3].x = j;
					pawns[yellow_pawn + 3].y = i;
					pawns[yellow_pawn + 3].in_base = 1;
					pawns[yellow_pawn + 3].pos_on_road = 0;
					pawns[yellow_pawn + 3].on_meta = 0;
					pawns[yellow_pawn + 3].distance = 0;
					pawns[yellow_pawn + 3].next = NULL;

					board->bases[1][yellow_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[1][yellow_pawn - 1].pawns = NULL;
					push_back(&board->bases[1][yellow_pawn - 1].pawns, &pawns[3 + yellow_pawn]);
					board->bases[1][yellow_pawn - 1].x = j;
					board->bases[1][yellow_pawn - 1].y = i;
					board->bases[1][yellow_pawn - 1].how_many_pawns = 1;

					yellow_pawn++;
					continue;
				}
			}
			if (i > 8)
			{
				if (j < 2 && num_of_players>3)
				{
					pawns[red_pawn + 11].player = 3;
					pawns[red_pawn + 11].color = 64;
					pawns[red_pawn + 11].id = red_pawn;
					pawns[red_pawn + 11].x = j;
					pawns[red_pawn + 11].y = i;
					pawns[red_pawn + 11].in_base = 1;
					pawns[red_pawn + 11].distance = 0;
					pawns[red_pawn + 11].pos_on_road = 0;
					pawns[red_pawn + 11].on_meta = 0;
					pawns[red_pawn + 11].next = NULL;

					board->bases[3][red_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[3][red_pawn - 1].pawns = NULL;
					push_back(&board->bases[3][red_pawn - 1].pawns, &pawns[11 + red_pawn]);
					board->bases[3][red_pawn - 1].x = j;
					board->bases[3][red_pawn - 1].y = i;
					board->bases[3][red_pawn - 1].how_many_pawns = 1;

					red_pawn++;
					continue;

				}
				if (j > 8 && num_of_players > 2)
				{
					pawns[blue_pawn + 7].player = 2;
					pawns[blue_pawn + 7].id = blue_pawn;
					pawns[blue_pawn + 7].color = 16;
					pawns[blue_pawn + 7].x = j;
					pawns[blue_pawn + 7].y = i;
					pawns[blue_pawn + 7].in_base = 1;
					pawns[blue_pawn + 7].pos_on_road = 0;
					pawns[blue_pawn + 7].on_meta = 0;
					pawns[blue_pawn + 7].distance = 0;
					pawns[blue_pawn + 7].next = NULL;

					board->bases[2][blue_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[2][blue_pawn - 1].pawns = NULL;
					push_back(&board->bases[2][blue_pawn - 1].pawns, &pawns[7 + blue_pawn]);
					board->bases[2][blue_pawn - 1].x = j;
					board->bases[2][blue_pawn - 1].y = i;
					board->bases[2][blue_pawn - 1].how_many_pawns = 1;

					blue_pawn++;
					continue;
				}
			}
		}
	}
}

void prepare_road(_field *road, int num_of_players)
{
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		road[j].y = 4;
		road[j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[j].x = 4;
		road[j].y = i;
		j++;
	}
	road[j].y = 0;
	road[j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[j].x = 6;
		road[j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[j].y = 4;
		road[j].x = i + 7;
		j++;
	}
	road[j].y = 5;
	road[j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[j].y = 6;
		road[j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[j].x = 6;
		road[j].y = i;
		j++;
	}
	road[j].y = 10;
	road[j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[j].x = 4;
		road[j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[j].y = 6;
		road[j].x = i;
		j++;
	}
	road[j].y = 5;
	road[j].x = 0;

	//kolory
	for (j = 0; j < 40; j++)
	{
		if (j % 2 == 1)
			road[j].color = 119;
		else
			road[j].color = 255;
	}
	//wyjscia z baz
	road[0].color = 34;
	road[10].color = 102;
	road[20].color = 17;
	road[30].color = 68;

	int k = 9;	//potrzebny do nadania wspolrzednych polom mety gracza czerwonego
	for (int i = 0; i < 4; i++)
	{
		//META ZIELONEGO
		road[40 + i].x = i + 1;
		road[40 + i].y = 5;
		road[40 + i].color = 34;
		//META ZOLTEGO
		road[44 + i].x = 5;
		road[44 + i].y = i + 1;
		road[44 + i].color = 102;
		//META NIEBIESKIEGO
		road[48 + i].x = k;
		road[48 + i].y = 5;
		road[48 + i].color = 17;
		//META CZERWONEGO
		road[52 + i].x = 5;
		road[52 + i].y = k;
		road[52 + i].color = 68;
		k--;
	}
	for (int i = 0; i < 56; i++)
	{
		road[i].pawns = NULL;
		road[i].how_many_pawns = 0;
	}
}

