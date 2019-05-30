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
		if (board->road[pawn->pos_on_road].pawns[i] != NULL)
		{
			if ((board->road[pawn->pos_on_road].pawns[i]->id == pawn->id) && (board->road[pawn->pos_on_road].pawns[i]->player == pawn->player))
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

	pawn->x = board->bases[pawn->player][pawn->id - 1].x;
	pawn->y = board->bases[pawn->player][pawn->id - 1].y;
	board->bases[pawn->x][pawn->y].pawns[pawn->id - 1] = pawn;	//ustawianie wskaznika na zbity pionek w bazie
	board->bases[pawn->x][pawn->y].how_many_pawns++;	//inkrementacja ilosci pionkow na polu w bazie, na ktory wrocil pionek
	//rysowanie zbitego pionka w bazie
	draw_field(pawn->x, pawn->y, board, h, -1);
}

void beat_enemy_pawns(_pawn *pawn, _board *board, HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->road[pawn->pos_on_road].pawns[i] != NULL)
		{
			if (board->road[pawn->pos_on_road].pawns[i]->color != pawn->color)	//porownuje po kolorach, bo czemu nie
			{
				return_to_base(board->road[pawn->pos_on_road].pawns[i], board, h);
				board->road[pawn->pos_on_road].pawns[i] = NULL;	//usuwanie wskaznika na pionek, ktory wlasnie wrocil do bazy
				board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci pionkow na usunietym polu 
			}
		}
	}
}

//funkcja zwraca indeksy pawn_ptr z board, na ktorych jest pionek, a nie NULL
int *which_is_not_null(_board *board, int x)
{
	int tab[4];
	int j = 0;
	for (int i = 0; i < 4; i++)
	{
		if (board->road[x].pawns[i] != NULL)
		{
			tab[j] = i;
			j++;
		}
	}
	return tab;
}

void leave_the_base(_player *player, _pawn *pawn, _board *board, HANDLE h)		//player int na strukture do zmiany
{
	board->bases[player->id][pawn->id].how_many_pawns--;
	board->bases[player->id][pawn->id].pawns[0] = NULL;
	int x = board->exits[player->id].x;
	int y = board->exits[player->id].y;

	int i = which_is_null(board, player->begin);
	int color = board->bases[player->id][pawn->id].color;
	board->road[player->begin].pawns[i] = pawn;
	i = board->road[player->begin].how_many_pawns;
	draw_square(pawn->x, pawn->y, color, h);	//usuwam pionka z bazy
	pawn->x = x;
	pawn->y = y;
	if (i > 0)
	{
		beat_enemy_pawns(pawn, board, h);
	}
	i = board->exits[player->id].how_many_pawns;
	//rysuje go na polu wyjsciowym w zaleznosci od stanu tego pola (ilosci pionkow)
	int *temp = which_is_not_null(board,player->begin);
	if (i == 0)
	{
		draw_pawn(x, y, color, h, pawn);
	}
	else if (i == 1)
	{
		draw_2_pawns(x, y, 32, h, board->exits[player->id].pawns[temp[0]], board->exits[player->id].pawns[temp[1]]);
	}
	else if (i == 2)
	{
		draw_3_pawns(x, y, 32, h, board->exits[player->id].pawns[temp[0]], board->exits[player->id].pawns[temp[1]], board->exits[player->id].pawns[temp[2]]);
	}
	else if (i == 3)
	{
		draw_4_pawns(x, y, 32, h, board->exits[player->id].pawns[temp[0]], board->exits[player->id].pawns[temp[1]], board->exits[player->id].pawns[temp[2]], board->exits[player->id].pawns[temp[4]]);
	}

	board->exits[player->id].how_many_pawns++;
}

void move_pawn(_pawn *pawn, int dice, _board *board, HANDLE h, _pawn *pawns, _player *player)	//pawns zdaje sie byc zbedne
{
	//sprawdzam, czy wybrany pionek znajduje sie w bazie
	if (pawn->in_base == 1)
	{
		if (player->id == 0)	//pionek gracza ZIELONY
		{

			leave_the_base(player, pawn, board, h, pawns);
		}
		else if (player->id == 1)	//pionek gracza ZOLTY
		{
			leave_the_base(player, pawn, board, h, pawns);
		}
		else if (player->id == 2)	//pionek gracza NIEBIESKI
		{
			leave_the_base(player, pawn, board, h, pawns);
		}
		else if (player->id == 3)	//pionek gracza CZERWONY
		{
			leave_the_base(player, pawn, board, h, pawns);
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
			int x = board->road[i].x;
			int y = board->road[i].y;
			int empty = which_is_null(x, y, board);

			board->road[i].pawns[empty] = pawn;		//dodaje wskazik na nowego pionka dla pola dalej
			board->road[i - 1].pawns[return_index_of_pawn(board->road[i - 1].x, board->road[i - 1].y, pawn, board)] = NULL;	//usuwam wskaznik na pionek ze starego pola, z ktorego odchodze
			board->road[i - 1].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
			board->road[i].how_many_pawns++;	//inkrementacja ilosci pionkow na nowym polu
			pawn->pos_on_road++;
			pawn->x = x;
			pawn->y = y;
			Sleep(20);
			if (i == (temp + dice - 1))
			{
				beat_enemy_pawns(pawn, board, h);
			}
			//rysowanie nowego pola
			draw_field(board->road[i].x, board->road[i].y, board, h, i + 1);
			//odtwarzanie starego pola
			draw_field(board->road[i - 1].x, board->road[i - 1].y, board, h, i);
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
int which_is_null(_board *board, int x)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->road[x].pawns[i] == NULL)
		{
			return i;
		}
	}
}

int choose_pawn(_player *player, int dice, _board *board, _pawn *pawns)
{
	//na poczatek sprawdzam, czy na wyjsciu z bazy nie stoi przecinik, ktorego moglbym zbic
	if (dice == 6)		//do testow zakomentowane
	{
		for (int i = 0; i < 4; i++)
		{
			//if (board->pawn_ptr[board->exit_coords[player->id][0]][board->exit_coords[player->id][1]][i] != NULL)
			if (board->exits[player->id].how_many_pawns != 0)
			{
				if (board->exits[player->id].pawns[i] != NULL)
				{
					if (board->exits[player->id].pawns[i]->player != player->id)		//na wyjsciu stoi przeciwnik, bo rozne ID graczy
					{
						for (int i = 0; i < 4; i++)
						{
							if (pawns[player->id * 4 + i].in_base == 1)			//sprawdzam, czy mam pionka w bazie
							{
								return i + 1;		//wychodze pionkiem, ktory jest w bazie i moze zbic czekajacego na wyjsciu przeciwnika
							}
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
			_pawn toCheck = pawns[player->id * 4 + i];
			if (toCheck.in_base == 0)			//sprawdzam, czy jest jakis pionek poza baza
			{
				for (int j = 0; j < 4; j++)
				{
					if (toCheck.pos_on_road + dice < 44)
					{
						if (board->road[toCheck.pos_on_road + dice - 1].pawns[j] != NULL)
						{
							if (board->road[toCheck.pos_on_road + dice - 1].pawns[j]->player != player->id)
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



