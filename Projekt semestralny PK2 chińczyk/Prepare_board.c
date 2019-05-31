#include "Prepare_board.h"

void draw_board(_board *board, HANDLE h, _pawn pawns[16])
{
	//INICJOWANIE
	int blue_pawn = 1, green_pawn = 1, yellow_pawn = 1, red_pawn = 1;
	char cgreen_pawn[7];
	char cred_pawn[7];
	char cblue_pawn[7];
	char cyellow_pawn[7];

	//wyjscia z baz
	board->exits[0].x = 0; board->exits[0].y = 4; board->exits[0].color = 34;
	board->exits[1].x = 6; board->exits[1].y = 0; board->exits[1].color = 102;
	board->exits[2].x = 10; board->exits[2].y = 6; board->exits[2].color = 17;
	board->exits[3].x = 4; board->exits[3].y = 10; board->exits[3].color = 68;

	//char (*board)[11][11][10];
	int i = 4, j;
	int white = 1;
	int licznik = 0;

	for (int i = 0; i < 40; i++)
	{
		board->road[i].how_many_pawns = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			board->meta[i][j].how_many_pawns = 0;
		}
		board->exits[i].how_many_pawns = 0;
	}

	//RYSOWANIE
#pragma region pas_poziomy
	for (int j = 0; j < 11; j++)
	{
		if (white == 1)
		{
			draw_square(j, i, 255, h);
			draw_square(j, i + 2, 255, h);
			white = 0;
		}
		else if (white == 0)
		{
			draw_square(j, i, 119, h);
			draw_square(j, i + 2, 119, h);
			white = 1;
		}
		if (j == 0 || j == 10)
		{
			if (j == 0)
			{
				draw_square(j, i, 34, h); //WYJSCIE Z BAZY ZIELONEGO
			}
			else
			{
				draw_square(j, i + 2, 17, h); //WYJSCIE Z BAZY NIEBIESKIEGO
			}
			draw_square(j, i + 1, 119, h);
		}
		else if (j > 0 && j < 5)
		{
			draw_square(j, i + 1, 34, h);	//META ZIELONEGO
			board->meta[0][j - 1].x = j;
			board->meta[0][j - 1].y = i + 1;
		}
		else if (j < 10 && j>5)
		{
			draw_square(j, i + 1, 17, h);	//META NIEBIESKIEGO
			board->meta[2][j - 6].x = j;
			board->meta[2][j - 6].y = i + 1;
		}
	}

#pragma endregion
	white = 1;
#pragma region pas_pionowy_+_bazy
	for (int i = 0; i < 11; i++)
	{
		for (int j = 4; j < 7; j++)
		{
			if (i == 0 && j == 6) //WYJSCIE Z BAZY ZOLTEGO
			{
				draw_square(j, i, 102, h);
				white = 0;
				continue;
			}
			if (i == 10 && j == 4)
			{
				draw_square(j, i, 68, h); //WYJSCIE Z BAZY CZERWONEGO
				white = 0;
				continue;
			}
			if (white == 1)
			{
				draw_square(j, i, 255, h);
				white = 0;
			}
			else if (white == 0)
			{
				draw_square(j, i, 119, h);
				white = 1;
			}
			if (i > 0 && i < 5)
			{
				if (j > 4 && j < 6)
				{
					draw_square(j, i, 102, h);	//META ZOLTEGO
					board->meta[1][i - 1].x = j;
					board->meta[1][i - 1].y = i;
					continue;
				}
			}
			else if (i > 5 && i < 10)
			{
				if (j > 4 && j < 6)
				{
					draw_square(j, i, 68, h);	//META CZERWONEGO
					board->meta[3][i - 6].x = j;
					board->meta[3][i - 6].y = i;
					continue;
				}
			}
			else if (j < 5 && (i == 5))
			{
				draw_square(j, i, 34, h); //META ZIELONEGO
				continue;
			}
			else if (j > 5 && (i == 5))
			{
				draw_square(j, i, 17, h);	//META NIEBIESKIEGO
				continue;
			}
		}
		//BAZY
		for (int j = 0; j < 11; j++)
		{

			if (i < 2)
			{
				if (j < 2)
				{
					draw_square(j, i, 34, h); //ZIELONY

					pawns[green_pawn - 1].id = green_pawn;
					pawns[green_pawn - 1].color = 32;
					pawns[green_pawn - 1].player = 0;
					pawns[green_pawn - 1].x = j;
					pawns[green_pawn - 1].y = i;
					pawns[green_pawn - 1].in_base = 1;
					pawns[green_pawn - 1].pos_on_road = 0;
					pawns[green_pawn - 1].next = NULL;

					board->bases[0][green_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[0][green_pawn - 1].pawns = NULL;
					push_back(&board->bases[0][green_pawn - 1].pawns, &pawns[green_pawn - 1]);

					board->bases[0][green_pawn - 1].x = j; 
					board->bases[0][green_pawn - 1].y = i;
					board->bases[0][green_pawn - 1].how_many_pawns = 1;

					draw_pawn(j, i, 32, h, &pawns[green_pawn - 1]);


					green_pawn++;
					continue;
				}
				if (j > 8)
				{

					draw_square(j, i, 102, h);	//ZOLTY

					pawns[yellow_pawn + 3].player = 1;
					pawns[yellow_pawn + 3].color = 96;
					pawns[yellow_pawn + 3].id = yellow_pawn;
					pawns[yellow_pawn + 3].x = j;
					pawns[yellow_pawn + 3].y = i;
					pawns[yellow_pawn + 3].in_base = 1;
					pawns[yellow_pawn + 3].pos_on_road = 0;
					pawns[yellow_pawn + 3].next = NULL;

					board->bases[1][yellow_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[1][yellow_pawn - 1].pawns = NULL;
					push_back(&board->bases[1][yellow_pawn - 1].pawns, &pawns[3 + yellow_pawn]);
					board->bases[1][yellow_pawn - 1].x = j; 
					board->bases[1][yellow_pawn - 1].y = i;
					board->bases[1][yellow_pawn - 1].how_many_pawns = 1;

					draw_pawn(j, i, 96, h, &pawns[yellow_pawn + 3]);

					yellow_pawn++;
					continue;
				}
			}
			if (i > 8)
			{
				if (j < 2)
				{
					draw_square(j, i, 68, h);	//CZERWONY

					pawns[red_pawn + 11].player = 3;
					pawns[red_pawn + 11].color = 64;
					pawns[red_pawn + 11].id = red_pawn;
					pawns[red_pawn + 11].x = j;
					pawns[red_pawn + 11].y = i;
					pawns[red_pawn + 11].in_base = 1;
					pawns[red_pawn + 11].pos_on_road = 0;
					pawns[red_pawn + 11].next = NULL;

					board->bases[3][red_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[3][red_pawn - 1].pawns = NULL;
					push_back(&board->bases[3][red_pawn - 1].pawns, &pawns[11 + red_pawn]);
					board->bases[3][red_pawn - 1].x = j; 
					board->bases[3][red_pawn - 1].y = i;
					board->bases[3][red_pawn - 1].how_many_pawns = 1;

					draw_pawn(j, i, 64, h, &pawns[red_pawn + 11]);


					red_pawn++;
					continue;

				}
				if (j > 8)
				{

					draw_square(j, i, 17, h);	//NIEBIESKI

					pawns[blue_pawn + 7].player = 2;
					pawns[blue_pawn + 7].id = blue_pawn;
					pawns[blue_pawn + 7].color = 16;
					pawns[blue_pawn + 7].x = j;
					pawns[blue_pawn + 7].y = i;
					pawns[blue_pawn + 7].in_base = 1;
					pawns[blue_pawn + 7].pos_on_road = 0;
					pawns[blue_pawn + 7].next = NULL;

					board->bases[2][blue_pawn - 1].pawns = (_pawn*)malloc(sizeof(_pawn));
					board->bases[2][blue_pawn - 1].pawns = NULL;
					push_back(&board->bases[2][blue_pawn - 1].pawns, &pawns[7 + blue_pawn]);
					board->bases[2][blue_pawn - 1].x = j; 
					board->bases[2][blue_pawn - 1].y = i;
					board->bases[2][blue_pawn - 1].how_many_pawns = 1;

					draw_pawn(j, i, 16, h, &pawns[blue_pawn + 7]);

					
					blue_pawn++;
					continue;
				}
			}
		}
	}
#pragma endregion 

}

void draw_square(int x, int y, int color, HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(x * 4 + i, y * 2, h);
		changeConsoleColor(color);
		printf("%c", 219);
		gotoxy(x * 4 + i, y * 2 + 1, h);
		printf("%c", 219);
	}
	gotoxy(0, 30, h);
}

void draw_field(_field *field, _board *board, HANDLE h, int i)
{
	//rysowanie wyjsc graczy
	int x = field->x;
	int y = field->y;
	if (x == board->exits[0].x && y == board->exits[0].y)
	{
		draw_square(x, y, 34, h);
	}
	else if (x == board->exits[1].x && y == board->exits[1].y)
	{
		draw_square(x, y, 102, h);
	}
	else if (x == board->exits[2].x && y == board->exits[2].y)
	{
		draw_square(x, y, 17, h);
	}
	else if (x == board->exits[3].x && y == board->exits[3].y)
	{
		draw_square(x, y, 68, h);
	}
	//rysowanie pol bialo-szarych
	else
	{
		if (i != -1)		//gdy pionek wraca po zbiciu do bazy i=-1 i nie rysuje pol bialo-szarych
		{
			if (i % 2 == 0)
			{
				draw_square(x, y, 119, h);
			}
			else
			{
				draw_square(x, y, 255, h);
			}
		}
	}
	//rysowanie mety graczy
	int it, j;
	for (it = 0; it < 4; it++)
	{
		for (j = 0; j < 4; j++)
		{
			if (x == board->meta[it][j].x && y == board->meta[it][j].y)
			{
				if (it == 0)
					draw_square(x, y, 34, h);
				else if (it == 1)
					draw_square(x, y, 102, h);
				else if (it == 2)
					draw_square(x, y, 17, h);
				else if (it == 3)
					draw_square(x, y, 68, h);
			}
		}
	}
	//rysowanie pionkow
	int pawns = field->how_many_pawns;
	if (pawns == 1)
	{
		draw_pawn(x, y, 32, h, field->pawns);
	}
	else if (pawns == 2)
	{
		draw_2_pawns(x, y, 32, h, board->road[i].pawns);
	}
	else if (pawns == 3)
	{
		draw_3_pawns(x, y, 32, h, board->road[i].pawns);
	}
	else if (pawns == 4)
	{
		draw_4_pawns(x, y, 32, h, board->road[i].pawns);
	}
}
