#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include <stdlib.h>
#include <time.h>

//34,32 - ZIELONY ; 102,96 ZOLTY ; 68,64 CZERWONY ; 17,16 NIEBIESKI

typedef struct {
	char player[7];		//mozna by dynamicznie, do ewentualnej poprawki
	int id;
	int x, y;
	int pos_on_road;
	int in_base;
	char name[7];
	int color;
}_pawn;

typedef struct {

	char coords[11][11][10];
	int how_many_pawns[11][11];		//przechowuje informacje na temat ilosci pionkow na danym polu
	int pawns_on_that_field[11][11][4];	//przechowuje ID pionkow na danym polu, nie moze byc wiecej niz 4, wynika z zasad gry, docelowo zbedne z racji posiadania wskaznikow
	_pawn *pawn_ptr[11][11][4];		//przechowuje wskazniki na pionki znajdujace sie na danym polu
	int exit_coords[4][3];		//koordy wyjsc z baz + kolor pola
	int base_coords[4][4][2];		//koordy baz (gracz, 1 z 4 pol, koordy)
	int meta_coords[4][4][2];		//koordy mety dla kazdego z graczy (gracz[1-4], 1 z pol, wspolrzedne) jw
}_board;

//warto rozwazyc przerobienie na liste dwukierunkowa
typedef struct {
	int x;
	int y;
}_road;

typedef struct {
	char name[7];	//mozna by dynamicznie, do ewentualnej poprawki
}_player;

void changeConsoleColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void gotoxy(int x, int y, HANDLE h)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}

void draw_pawn(int x, int y, int color, HANDLE h, _pawn *pawn)
{
	//zmiana wspolrzednych pionka
	pawn->x = x;
	pawn->y = y;
	//zasadnicze rysowanie
	changeConsoleColor(pawn->color);
	for (int i = 1; i < 3; i++)
	{
		gotoxy(x * 4 + i, y * 2 + 1, h);
		printf("%i", pawn->id);
		gotoxy(x * 4 + i, y * 2, h);
		printf("%i", pawn->id);
	}
	gotoxy(0, 30, h);
}

void draw_2_pawns(int x, int y, int color, HANDLE h, _pawn *pawn1, _pawn *pawn2)
{
	//zasadnicze rysowanie
	//lewa kolumna pionka
	{
		changeConsoleColor(pawn1->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn1->id);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn1->id);
	}
	//prawa kolumna pionka
	{
		changeConsoleColor(pawn2->color);
		gotoxy(x * 4 + 2, y * 2 + 1, h);
		printf("%i", pawn2->id);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn2->id);
	}
	gotoxy(0, 30, h);
}

void draw_3_pawns(int x, int y, int color, HANDLE h, _pawn *pawn1, _pawn *pawn2, _pawn *pawn3)
{
	//gorny wiersz pola
	{
		//lewa strona (pionek 1)
		changeConsoleColor(pawn1->color);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn1->id);
		//prawa strona	(pionek 2)
		changeConsoleColor(pawn2->color);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn2->id);
	}
	//dolny wiersz pola
	{
		//lewa strona	(pionek 3)
		changeConsoleColor(pawn3->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn3->id);;
	}
	gotoxy(0, 30, h);
}

void draw_4_pawns(int x, int y, int color, HANDLE h, _pawn *pawn1, _pawn *pawn2, _pawn *pawn3, _pawn *pawn4)
{
	//gorny wiersz pola
	{
		//lewa strona (pionek 1)
		changeConsoleColor(pawn1->color);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn1->id);
		//prawa strona	(pionek 2)
		changeConsoleColor(pawn2->color);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn2->id);
	}
	//dolny wiersz pola
	{
		//lewa strona	(pionek 3)
		changeConsoleColor(pawn3->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn3->id);
		//prawa strona	(pionek 4)
		changeConsoleColor(pawn4->color);
		gotoxy(x * 4 + 2, y * 2 + 1, h);
		printf("%i", pawn4->id);
	}
	gotoxy(0, 30, h);
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

					board->pawn_ptr[j][i][yellow_pawn - 1] = &pawns[yellow_pawn - 1];
					board->base_coords[1][yellow_pawn - 1][0] = j; board->base_coords[1][yellow_pawn - 1][1] = i;

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

					board->pawn_ptr[j][i][red_pawn - 1] = &pawns[red_pawn - 1];
					board->base_coords[3][red_pawn - 1][0] = j; board->base_coords[3][red_pawn - 1][1] = i;

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

					board->pawn_ptr[j][i][blue_pawn - 1] = &pawns[blue_pawn - 1];
					board->base_coords[2][blue_pawn - 1][0] = j; board->base_coords[2][blue_pawn - 1][1] = i;

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

void show_board_as_strings(char(*board)[11][11][10])
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n");
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			printf("%s\t", (*board)[j][i]);
		}
		printf("\n");
	}
}

int throw_dice()
{
	srand(time(NULL));
	int dice = ((rand() % 6) + 1);
	return dice;
}

//zwraca indeks pionka w tablicy pionkow na danym polu (1 z max 4), potrzebne do usuwania wskaznika na pionek, ktory odszedl z pola
int return_index_of_pawn(int x, int y, _pawn *pawn, _board *board)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[x][y][i] != NULL)
		{
			if (strcmp(board->pawn_ptr[x][y][i]->name, pawn->name) == 0)
			{
				return i;
			}
		}
	}
}

//funkcja zwraca indeksy pawn_ptr z board, na ktorych jest pionek, a nie NULL
int *which_is_not_null(int x, int y, _board *board)
{
	int tab[4];
	int j = 0;
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[x][y][i] != NULL)
		{
			tab[j] = i;
			j++;
		}
	}
	return tab;
}

int which_is_null(int x, int y, _board *board)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[x][y][i] == NULL)
		{
			return i;
		}
	}
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
		if (i % 2 == 0)
		{
			draw_square(x, y, 119, h);
		}
		else
		{
			draw_square(x, y, 255, h);
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
	//rysowanie pionkow
	int pawns = board->how_many_pawns[x][y];
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
	//rysowanie baz

}

void return_to_base(_pawn *pawn, _board *board)
{
	pawn->in_base = 1;
	pawn->pos_on_road = 0;
	if (strcmp(pawn->player, "green") == 0)
	{
		pawn->x = board->base_coords[0][pawn->id][0];
		pawn->y = board->base_coords[0][pawn->id][1];
	}
	else if (strcmp(pawn->player, "yellow") == 0)
	{
		pawn->x = board->base_coords[1][pawn->id][0];
		pawn->y = board->base_coords[1][pawn->id][1];
	}
	else if (strcmp(pawn->player, "blue") == 0)
	{
		pawn->x = board->base_coords[2][pawn->id][0];
		pawn->y = board->base_coords[2][pawn->id][1];
	}
	else if (strcmp(pawn->player, "red") == 0)
	{
		pawn->x = board->base_coords[3][pawn->id][0];
		pawn->y = board->base_coords[3][pawn->id][1];
	}
	board->pawn_ptr[pawn->x][pawn->y][pawn->id] = pawn;
}

void beat_enemy_pawns(_pawn *pawn, _board *board)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[pawn->x][pawn->y][i] != NULL)
		{
			if (board->pawn_ptr[pawn->x][pawn->y][i]->color != pawn->color)	//porownuje po kolorach, bo czemu nie
			{
				return_to_base(board->pawn_ptr[pawn->x][pawn->y][i], board);	//RETURN COS NIE DZIALA
				board->pawn_ptr[pawn->x][pawn->y][i] = NULL;
				board->how_many_pawns[pawn->x][pawn->y]--;
			}
		}
	}
}

void leave_the_base(int player, _pawn *pawn, _board *board, HANDLE h)
{
	int x = board->exit_coords[player][0];
	int y = board->exit_coords[player][1];
	int color = board->exit_coords[player][2];
	int i = which_is_null(x, y, board);
	board->pawn_ptr[x][y][i] = pawn;
	i = board->how_many_pawns[x][y];
	draw_square(pawn->x, pawn->y, color, h);	//usuwam pionka z bazy
	pawn->x = x;
	pawn->y = y;
	if (i > 0)
	{
		beat_enemy_pawns(pawn, board);
	}
	i = board->how_many_pawns[x][y];
	//rysuje go na polu wyjsciowym w zaleznosci od stanu tego pola (ilosci pionkow)
	int *temp = which_is_not_null(x, y, board);
	if (i == 0)
	{
		draw_pawn(x, y, color, h, pawn);
		board->pawns_on_that_field[x][y][i] = pawn;
	}
	else if (i == 1)
	{
		draw_2_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]]);
		board->pawns_on_that_field[x][y][i] = pawn;
	}
	else if (i == 2)
	{
		draw_3_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]]);
		board->pawns_on_that_field[x][y][i] = pawn;
	}
	else if (i == 3)
	{
		draw_4_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]], board->pawn_ptr[x][y][temp[3]]);
		board->pawns_on_that_field[x][y][i] = pawn;
	}

	board->how_many_pawns[x][y]++;
}

void move_pawn(_pawn *pawn, int dice, _board *board, HANDLE h, _pawn *pawns, _road *road)
{

	//sprawdzam, czy wybrany pionek znajduje sie w bazie !! dodac jeszcze sprawdzenie, czy dice ==6 !! + ewentualnie koordy baz w strukturze
	if (pawn->in_base == 1)
	{
		if (strcmp(pawn->player, "green") == 0)	//pionek gracza ZIELONY
		{
			leave_the_base(0, pawn, board, h, pawns);
		}
		else if (strcmp(pawn->player, "yellow") == 0)	//pionek gracza ZOLTY
		{
			leave_the_base(1, pawn, board, h, pawns);
		}
		else if (strcmp(pawn->player, "blue") == 0)	//pionek gracza NIEBIESKI
		{
			leave_the_base(2, pawn, board, h, pawns);
		}
		else if (strcmp(pawn->player, "red") == 0)	//pionek gracza CZERWONY
		{
			leave_the_base(3, pawn, board, h, pawns);
		}
		pawn->in_base = 0;
		pawn->pos_on_road = 1;
	}
	else
	{
		int temp = pawn->pos_on_road;		//zaczyna sie od 1, takze pod i kryje sie nastepne pole
		if (temp + dice > 44)
		{
			//Printf("You can't move that pawn!");
			//Sleep(1000);
			return;
		}
		for (int i = temp; i < (temp + dice); i++)
		{
			int x = road[i].x;
			int y = road[i].y;
			int empty = which_is_null(x, y, board);

			board->pawn_ptr[x][y][empty] = pawn;	//dodaje wskazik na nowego pionka dla pola dalej
			board->pawn_ptr[road[i - 1].x][road[i - 1].y][return_index_of_pawn(road[i - 1].x, road[i - 1].y, pawn, board)] = NULL;	//usuwam wskaznik na pionek ze starego pola, z ktorego odchodze
			board->how_many_pawns[road[i - 1].x][road[i - 1].y]--;	//dekrementacja ilosci piokow ze starego pola
			board->how_many_pawns[x][y]++;	//inkrementacja ilosci pionkow na nowym polu
			pawn->pos_on_road++;
			pawn->x = x;
			pawn->y = y;
			Sleep(20);
			if (i == (temp + dice - 1))
			{
				beat_enemy_pawns(pawn, board);
			}
			//rysowanie nowego pola
			draw_field(road[i].x, road[i].y, board, h, i + 1);
			//odtwarzanie starego pola
			draw_field(road[i - 1].x, road[i - 1].y, board, h, i);
		}
	}
	return;
}

//czysci tekst pod plansza
void clear_text(HANDLE h)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	gotoxy(0, 22, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 23, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 24, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 25, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 26, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	return;
}

//zwraca numer pionka w tablicy [0-15]
_pawn *find_pawn_in_array(char *player, int id, _pawn *pawns)
{
	for (int i = 0; i < 16; i++)
	{
		if (strcmp(pawns[i].player, player) == 0)
		{
			if (pawns[i].id == id)
			{
				return &pawns[i];
			}
		}
	}
}

void prepare_green_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		road[0][j].y = 4;
		road[0][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[0][j].x = 4;
		road[0][j].y = i;
		j++;
	}
	road[0][j].y = 0;
	road[0][j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[0][j].x = 6;
		road[0][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[0][j].y = 4;
		road[0][j].x = i + 7;
		j++;
	}
	road[0][j].y = 5;
	road[0][j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[0][j].y = 6;
		road[0][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[0][j].x = 6;
		road[0][j].y = i;
		j++;
	}
	road[0][j].y = 10;
	road[0][j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[0][j].x = 4;
		road[0][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[0][j].y = 6;
		road[0][j].x = i;
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		road[0][j].y = 5;
		road[0][j].x = i;
		j++;
	}
}

void prepare_yellow_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		road[1][j].x = 6;
		road[1][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[1][j].y = 4;
		road[1][j].x = i + 7;
		j++;
	}
	road[1][j].y = 5;
	road[1][j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[1][j].y = 6;
		road[1][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[1][j].x = 6;
		road[1][j].y = i;
		j++;
	}
	road[1][j].y = 10;
	road[1][j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[1][j].x = 4;
		road[1][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[1][j].y = 6;
		road[1][j].x = i;
		j++;
	}
	road[1][j].y = 5;
	road[1][j].x = 0;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[1][j].y = 4;
		road[1][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[1][j].x = 4;
		road[1][j].y = i;
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		road[1][j].y = i;
		road[1][j].x = 5;
		j++;
	}
}

void prepare_blue_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 10; i >= 6; i--)
	{
		road[2][j].y = 6;
		road[2][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[2][j].x = 6;
		road[2][j].y = i;
		j++;
	}
	road[2][j].y = 10;
	road[2][j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[2][j].x = 4;
		road[2][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[2][j].y = 6;
		road[2][j].x = i;
		j++;
	}
	road[2][j].y = 5;
	road[2][j].x = 0;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[2][j].y = 4;
		road[2][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[2][j].x = 4;
		road[2][j].y = i;
		j++;
	}
	road[2][j].y = 0;
	road[2][j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[2][j].x = 6;
		road[2][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[2][j].y = 4;
		road[2][j].x = i + 7;
		j++;
	}
	for (i = 10; i > 5; i--)
	{
		road[2][j].y = 5;
		road[2][j].x = i;
		j++;
	}


}

void prepare_red_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 10; i >= 6; i--)
	{
		road[3][j].x = 4;
		road[3][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[3][j].y = 6;
		road[3][j].x = i;
		j++;
	}
	road[3][j].y = 5;
	road[3][j].x = 0;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[3][j].y = 4;
		road[3][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[3][j].x = 4;
		road[3][j].y = i;
		j++;
	}
	road[3][j].y = 0;
	road[3][j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[3][j].x = 6;
		road[3][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[3][j].y = 4;
		road[3][j].x = i + 7;
		j++;
	}
	road[3][j].y = 5;
	road[3][j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[3][j].y = 6;
		road[3][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[3][j].x = 6;
		road[3][j].y = i;
		j++;
	}
	for (i = 10; i >= 6; i--)
	{
		road[3][j].y = i;
		road[3][j].x = 5;
		j++;
	}

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

int main()
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;	//watpliwa uzytecznosc
	_board *board = malloc(sizeof*board);
	_pawn pawns[16];
	//do przemyslenia, wyjatkowo ³opatologiczne
	_road roads[4][44];
	prepare_green_road(roads);
	prepare_yellow_road(roads);
	prepare_blue_road(roads);
	prepare_red_road(roads);

	prepare_board_of_ptr(board);


	_player players[4] = { "green", "yellow", "blue", "red" };

	draw_board(board, h, pawns);

	//show_board_as_strings(board);
	/*for (int i = 0; i < 16; i++)
	{
		printf("%s", pawns[i].player);
	}*/

	int pawn_nr;
	_pawn *pawn = (_pawn*)malloc(sizeof(_pawn));;
	int i = 0; //tymczasowo robi za ID graczy

	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 22, h);

		srand(time(0));
		int dice = throw_dice();

		//printf("Dice: ");
		//scanf("%i", &dice);

		printf("\nDice: %i", dice);

		//printf("Player: ");
		//scanf("%i", &i);
		printf("\nPlayer: %s, dice: %i", players[i].name, dice);

		if (dice < 44)
		{
			pawn_nr = rand() % 4 + 1;

			//printf("\nChoose pawn: ");
			//scanf("%i", &pawn_nr);
			pawn = find_pawn_in_array(players[i].name, pawn_nr, pawns);
			move_pawn(pawn, dice, board, h, pawns, roads[i]);
		}
		if (i == 3)
		{
			i = 0;
		}
		else
		{
			i++;
		}
		Sleep(100);
		clear_text(h);
	}


	//wypisywanie dostepnych kolorow z calego zakresu
	/*
	for (int i = 0; i < 256; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		printf("%i. Kolor pod numerem: %i\n", i,i);
	}//*/

	getch();
	//system("pause");
	return 0;
}