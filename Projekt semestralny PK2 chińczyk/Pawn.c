#include "Pawn.h"

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

void return_to_base(_pawn *pawn, _board *board, HANDLE h)
{
	pawn->in_base = 1;
	pawn->pos_on_road = 0;
	pawn->x = board->base_coords[pawn->player][pawn->id - 1][0];
	pawn->y = board->base_coords[pawn->player][pawn->id - 1][1];
	board->pawn_ptr[pawn->x][pawn->y][pawn->id - 1] = pawn;	//ustawianie wskaznika na zbity pionek w bazie
	board->how_many_pawns[pawn->x][pawn->y]++;	//inkrementacja ilosci pionkow na polu w bazie, na ktory wrocil pionek
	//rysowanie zbitego pionka w bazie
	draw_field(pawn->x, pawn->y, board, h, -1);
}

void beat_enemy_pawns(_pawn *pawn, _board *board, HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[pawn->x][pawn->y][i] != NULL)
		{
			if (board->pawn_ptr[pawn->x][pawn->y][i]->color != pawn->color)	//porownuje po kolorach, bo czemu nie
			{
				return_to_base(board->pawn_ptr[pawn->x][pawn->y][i], board, h);	//RETURN COS NIE DZIALA
				board->pawn_ptr[pawn->x][pawn->y][i] = NULL;	//usuwanie wskaznika na pionek, ktory wlasnie wrocil do bazy
				board->how_many_pawns[pawn->x][pawn->y]--;	//dekrementacja ilosci pionkow na usunietym polu 
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

void leave_the_base(int player, _pawn *pawn, _board *board, HANDLE h)
{
	board->how_many_pawns[pawn->x][pawn->y]--;
	board->pawn_ptr[pawn->x][pawn->y][return_index_of_pawn(pawn->x, pawn->y, pawn, board)] = NULL;
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
		beat_enemy_pawns(pawn, board, h);
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

void move_pawn(_pawn *pawn, int dice, _board *board, HANDLE h, _pawn *pawns, _road *road)	//pawns zdaje sie byc zbedne
{
	//sprawdzam, czy wybrany pionek znajduje sie w bazie
	if (pawn->in_base == 1)
	{
		if (pawn->player == 0)	//pionek gracza ZIELONY
		{

			leave_the_base(0, pawn, board, h, pawns);
		}
		else if (pawn->player == 1)	//pionek gracza ZOLTY
		{
			leave_the_base(1, pawn, board, h, pawns);
		}
		else if (pawn->player == 2)	//pionek gracza NIEBIESKI
		{
			leave_the_base(2, pawn, board, h, pawns);
		}
		else if (pawn->player == 3)	//pionek gracza CZERWONY
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
				beat_enemy_pawns(pawn, board, h);
			}
			//rysowanie nowego pola
			draw_field(road[i].x, road[i].y, board, h, i + 1);
			//odtwarzanie starego pola
			draw_field(road[i - 1].x, road[i - 1].y, board, h, i);
		}
	}
	return;
}

//zwraca numer pionka w tablicy [0-15] //po wywaleniu tego z Source.c przestalo dzialac, tutaj niby ok, ale wskaznik w mainie wskazuje na smieci, porzucam do wyjasnienia
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
//zwraca indeks wskazujacy na nulla w tablicy pawn_ptr, aby tam ustawic wskaznik na nowoprzybylego pionka
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

int choose_pawn(_player *player, int dice, _board *board, _pawn *pawns, _road road[4][44])
{
	//na poczatek sprawdzam, czy na wyjsciu z bazy nie stoi przecinik, ktorego moglbym zbic
	if (dice == 6)		//do testow zakomentowane
	{
		for (int i = 0; i < 4; i++)
		{
			if (board->pawn_ptr[board->exit_coords[player->id][0]][board->exit_coords[player->id][1]][i] != NULL)
			{
				if (board->pawn_ptr[board->exit_coords[player->id][0]][board->exit_coords[player->id][1]][i]->player != player->id)		//na wyjsciu stoi przeciwnik
				{
					for (int i = 0; i < 4; i++)
					{
						if (pawns[player->id * 4 + i].in_base == 1)
						{
							//leave_the_base(player->id, &pawns[player->id * 4 + i], board, h);
							return i+1;
						}
					}
				}
			}
		}
	}
	else
	//dla kazdego pionka spoza bazy sprawdzam, czy na koncu jego wedrowki nie stoi przecwiny pionek
	{
		for (int i = 0; i < 4; i++)
		{
			if (pawns[player->id * 4 + i].in_base == 0)
			{
				for (int j = 0; j < 4; j++)
				{
					if (pawns[player->id * 4 + i].pos_on_road + dice < 44)
					{
						if (board->pawn_ptr[road[player->id][pawns[player->id * 4 + i].pos_on_road + dice - 1].x]
							[road[player->id][pawns[player->id * 4 + i].pos_on_road + dice - 1].y][j] != NULL)
						{
							if (board->pawn_ptr[road[player->id][pawns[player->id * 4 + i].pos_on_road + dice - 1].x]
								[road[player->id][pawns[player->id * 4 + i].pos_on_road + dice - 1].y][j]->player != player->id)
							{
								return i + 1;
							}
						}
					}
				}
			}
		}
	}
	if (player->random == 0)
	{
		int farthest = 1;
		int temp = 0;
		for (int i = 0; i < 4; i++)
		{
			if (pawns[player->id * 4 + i].pos_on_road > temp)
			{
				temp = pawns[player->id * 4 + i].pos_on_road;
				farthest = i + 1;
			}
		}
		player->random++;
		return farthest;
	}
	else
	{
		player->random++;
		if (player->random == 3)
			player->random = 0;
		return rand() % 4 + 1;
	}

}



