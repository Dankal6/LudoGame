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
	board->exit_coords[0][0] = 0; board->exit_coords[0][1] = 4; board->exit_coords[0][2] = 34;
	board->exit_coords[1][0] = 6; board->exit_coords[1][1] = 0; board->exit_coords[1][2] = 102;
	board->exit_coords[2][0] = 10; board->exit_coords[2][1] = 6; board->exit_coords[2][2] = 17;
	board->exit_coords[3][0] = 4; board->exit_coords[3][1] = 10; board->exit_coords[3][2] = 68;

	//char (*board)[11][11][10];
	int i = 4, j;
	int white = 1;
	int licznik = 0;

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			//strcpy(*board->coords[j][i], "0");
			strcpy(board->coords[j][i], "0");
			board->how_many_pawns[i][j] = 0;
		}
	}

	/*for (i = 0; i < 22; i++)
	{
		for (j = 0; j < 44; j++)
		{
			if (i < 4 || i>17)
			{
				if (j < 8 || j>35)
				{
					(*board)[i][j] = 177;
					continue;
				}
			}
			(*board)[i][j] = 219;
		}
	}*/
	//RYSOWANIE
#pragma region pas_poziomy
	for (int j = 0; j < 11; j++)
	{
		if (white == 1)
		{
			draw_square(j, i, 255, h);
			sprintf((board->coords)[j][i], "empty");
			draw_square(j, i + 2, 255, h);
			sprintf((board->coords)[j][i + 2], "empty");
			white = 0;
		}
		else if (white == 0)
		{
			draw_square(j, i, 119, h);
			sprintf((board->coords)[j][i], "empty");
			draw_square(j, i + 2, 119, h);
			sprintf((board->coords)[j][i + 2], "empty");
			white = 1;
		}
		if (j == 0 || j == 10)
		{
			if (j == 0)
			{
				draw_square(j, i, 34, h); //WYJSCIE Z BAZY ZIELONEGO
				sprintf((board->coords)[j][i], "gexit");
			}
			else
			{
				draw_square(j, i + 2, 17, h); //WYJSCIE Z BAZY NIEBIESKIEGO
				sprintf((board->coords)[j][i + 2], "bexit");
			}
			draw_square(j, i + 1, 119, h);
			sprintf((board->coords)[j][i + 1], "empty");
		}
		else if (j > 0 && j < 5)
		{
			draw_square(j, i + 1, 34, h);	//META ZIELONEGO
			sprintf((board->coords)[j][i + 1], "gend");
			board->meta_coords[0][j - 1][0] = j;
			board->meta_coords[0][j - 1][1] = i + 1;
		}
		else if (j < 10 && j>5)
		{
			draw_square(j, i + 1, 17, h);	//META NIEBIESKIEGO
			sprintf((board->coords)[j][i + 1], "bend");
			board->meta_coords[2][j - 6][0] = j;
			board->meta_coords[2][j - 6][1] = i + 1;
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
				sprintf((board->coords)[j][i], "yexit");
				white = 0;
				continue;
			}
			if (i == 10 && j == 4)
			{
				draw_square(j, i, 68, h); //WYJSCIE Z BAZY CZERWONEGO
				sprintf((board->coords)[j][i], "rexit");
				white = 0;
				continue;
			}
			if (white == 1)
			{
				draw_square(j, i, 255, h);
				sprintf((board->coords)[j][i], "empty");
				white = 0;
			}
			else if (white == 0)
			{
				draw_square(j, i, 119, h);
				sprintf((board->coords)[j][i], "empty");;
				white = 1;
			}
			if (i > 0 && i < 5)
			{
				if (j > 4 && j < 6)
				{
					draw_square(j, i, 102, h);	//META ZOLTEGO
					sprintf((board->coords)[j][i], "yend");
					board->meta_coords[1][i - 1][0] = j;
					board->meta_coords[1][i - 1][1] = i;
					continue;
				}
			}
			else if (i > 5 && i < 10)
			{
				if (j > 4 && j < 6)
				{
					draw_square(j, i, 68, h);	//META CZERWONEGO
					sprintf((board->coords)[j][i], "rend");
					board->meta_coords[3][i - 6][0] = j;
					board->meta_coords[3][i - 6][1] = i;
					continue;
				}
			}
			else if (j < 5 && (i == 5))
			{
				draw_square(j, i, 34, h); //META ZIELONEGO
				sprintf((board->coords)[j][i], "gend");
				continue;
			}
			else if (j > 5 && (i == 5))
			{
				draw_square(j, i, 17, h);	//META NIEBIESKIEGO
				sprintf((board->coords)[j][i], "bend");
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
					sprintf(pawns[green_pawn - 1].player, "green");
					pawns[green_pawn - 1].x = j;
					sprintf(pawns[green_pawn - 1].name, "gpawn%i", green_pawn);
					pawns[green_pawn - 1].y = i;
					pawns[green_pawn - 1].in_base = 1;

					board->pawn_ptr[j][i][green_pawn - 1] = &pawns[green_pawn - 1];
					board->base_coords[0][green_pawn - 1][0] = j; board->base_coords[0][green_pawn - 1][1] = i;
					board->how_many_pawns[j][i] = 1;


					draw_pawn(j, i, 32, h, &pawns[green_pawn - 1]);

					sprintf((board->coords)[j][i], "gpawn%i", green_pawn);

					green_pawn++;
					continue;
				}
				if (j > 8)
				{

					draw_square(j, i, 102, h);	//ZOLTY

					sprintf(pawns[yellow_pawn + 3].player, "yellow");
					pawns[yellow_pawn + 3].color = 96;
					pawns[yellow_pawn + 3].id = yellow_pawn;
					sprintf(pawns[yellow_pawn + 3].name, "ypawn%i", yellow_pawn);
					pawns[yellow_pawn + 3].x = j;
					pawns[yellow_pawn + 3].y = i;
					pawns[yellow_pawn + 3].in_base = 1;

					board->pawn_ptr[j][i][yellow_pawn - 1] = &pawns[4 + yellow_pawn - 1];
					board->base_coords[1][yellow_pawn - 1][0] = j; board->base_coords[1][yellow_pawn - 1][1] = i;
					board->how_many_pawns[j][i] = 1;

					draw_pawn(j, i, 96, h, &pawns[yellow_pawn + 3]);

					sprintf((board->coords)[j][i], "ypawn%i", yellow_pawn);

					yellow_pawn++;
					continue;
				}
			}
			if (i > 8)
			{
				if (j < 2)
				{
					draw_square(j, i, 68, h);	//CZERWONY

					sprintf(pawns[red_pawn + 11].player, "red");
					pawns[red_pawn + 11].color = 64;
					pawns[red_pawn + 11].id = red_pawn;
					sprintf(pawns[red_pawn + 11].name, "rpawn%i", red_pawn);
					pawns[red_pawn + 11].x = j;
					pawns[red_pawn + 11].y = i;
					pawns[red_pawn + 11].in_base = 1;

					board->pawn_ptr[j][i][red_pawn - 1] = &pawns[12 + red_pawn - 1];
					board->base_coords[3][red_pawn - 1][0] = j; board->base_coords[3][red_pawn - 1][1] = i;
					board->how_many_pawns[j][i] = 1;

					draw_pawn(j, i, 64, h, &pawns[red_pawn + 11]);

					sprintf((board->coords)[j][i], "rpawn%i", red_pawn);

					red_pawn++;
					continue;

				}
				if (j > 8)
				{

					draw_square(j, i, 17, h);	//NIEBIESKI

					sprintf(pawns[blue_pawn + 7].player, "blue");
					pawns[blue_pawn + 7].id = blue_pawn;
					pawns[blue_pawn + 7].color = 16;
					sprintf(pawns[blue_pawn + 7].name, "bpawn%i", blue_pawn);
					pawns[blue_pawn + 7].x = j;
					pawns[blue_pawn + 7].y = i;
					pawns[blue_pawn + 7].in_base = 1;

					board->pawn_ptr[j][i][blue_pawn - 1] = &pawns[8 + blue_pawn - 1];
					board->base_coords[2][blue_pawn - 1][0] = j; board->base_coords[2][blue_pawn - 1][1] = i;
					board->how_many_pawns[j][i] = 1;

					draw_pawn(j, i, 16, h, &pawns[blue_pawn + 7]);

					sprintf((board->coords)[j][i], "bpawn%i", blue_pawn);

					blue_pawn++;
					continue;
				}
			}
		}
	}
#pragma endregion 

}

//wypelniam NULLami
void prepare_board_of_ptr(_board *board)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				board->pawn_ptr[i][j][k] = NULL;
			}
		}
	}
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

void draw_field(int x, int y, _board *board, HANDLE h, int i)
{
	//rysowanie wyjsc graczy
	if (x == board->exit_coords[0][0] && y == board->exit_coords[0][1])
	{
		draw_square(x, y, 34, h);
	}
	else if (x == board->exit_coords[1][0] && y == board->exit_coords[1][1])
	{
		draw_square(x, y, 102, h);
	}
	else if (x == board->exit_coords[2][0] && y == board->exit_coords[2][1])
	{
		draw_square(x, y, 17, h);
	}
	else if (x == board->exit_coords[3][0] && y == board->exit_coords[3][1])
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
			if (x == board->meta_coords[it][j][0] && y == board->meta_coords[it][j][1])
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
	int pawns = board->how_many_pawns[x][y];		//##ERROR
	int *temp = which_is_not_null(x, y, board);
	if (pawns == 1)
	{
		draw_pawn(x, y, 32, h, board->pawn_ptr[x][y][temp[0]]);
	}
	else if (pawns == 2)
	{
		draw_2_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]]);
	}
	else if (pawns == 3)
	{
		draw_3_pawns(x, y, 34, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]]);
	}
	else if (pawns == 4)
	{
		draw_4_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]], board->pawn_ptr[x][y][temp[3]]);
	}
}
