#include "Pawn.h"

void draw_pawn(int x, int y, int color, HANDLE h, _pawn *pawn)
{
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

void draw_2_pawns(int x, int y, int color, HANDLE h, _pawn *pawn)
{
	//zasadnicze rysowanie
	//lewa kolumna pionka
	{
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn->id);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn->id);
	}
	//prawa kolumna pionka
	{
		pawn = pawn->next;
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 2, y * 2 + 1, h);
		printf("%i", pawn->id);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn->id);
	}
	gotoxy(0, 30, h);
}

void draw_3_pawns(int x, int y, int color, HANDLE h, _pawn *pawn)
{
	//gorny wiersz pola
	{
		//lewa strona (pionek 1)
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn->id);
		//prawa strona	(pionek 2)
		pawn = pawn->next;
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn->id);
	}
	//dolny wiersz pola
	{
		//lewa strona	(pionek 3)
		pawn = pawn->next;
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn->id);;
	}
	gotoxy(0, 30, h);
}

void draw_4_pawns(int x, int y, int color, HANDLE h, _pawn *pawn)
{
	//gorny wiersz pola
	{
		//lewa strona (pionek 1)
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn->id);
		//prawa strona	(pionek 2)
		pawn = pawn->next;
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn->id);
	}
	//dolny wiersz pola
	{
		//lewa strona	(pionek 3)
		pawn = pawn->next;
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn->id);
		//prawa strona	(pionek 4)
		pawn = pawn->next;
		changeConsoleColor(pawn->color);
		gotoxy(x * 4 + 2, y * 2 + 1, h);
		printf("%i", pawn->id);
	}
	gotoxy(0, 30, h);
}

void return_to_base(_pawn *pawn, _board *board, HANDLE h)
{
	pawn->in_base = 1;
	pawn->pos_on_road = 0;

	pawn->x = board->bases[pawn->player][pawn->id - 1].x;
	pawn->y = board->bases[pawn->player][pawn->id - 1].y;
	board->bases[pawn->player][pawn->id - 1].pawns = pawn;	//ustawianie wskaznika na zbity pionek w bazie
	board->bases[pawn->player][pawn->id - 1].how_many_pawns++;	//inkrementacja ilosci pionkow na polu w bazie, na ktory wrocil pionek
	//rysowanie zbitego pionka w bazie
	draw_field(board->bases[pawn->player][pawn->id - 1], board, h, -1);
}

void pop_front(_pawn **head)
{
	_pawn * temp = malloc(sizeof(_pawn));
	if (*head != NULL)
	{
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
}

void pop_by_index(_pawn **head, int position)
{
	if (position == 0)
	{
		pop_front(head);
	}
	else
	{
		_pawn *current = *head;
		_pawn *temp;
		int i = 0;
		while (current->next != NULL && i < position - 1)
		{
			current = current->next;
			i++;
		}
		temp = current->next;
		current->next = temp->next;
		free(temp);
	}
}

void push_back(_pawn **head, _pawn *pawn)
{
	_pawn *temp = (_pawn*)malloc(sizeof(_pawn));
	temp->player = pawn->player;
	temp->color = pawn->color;
	temp->id = pawn->id;
	temp->in_base = pawn->in_base;
	temp->pos_on_road = pawn->pos_on_road;
	temp->x = pawn->x;
	temp->y = pawn->y;
	temp->next = NULL;

	if (*head == NULL)
	{
		*head = temp;
	}
	else
	{
		_pawn *current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = temp;
	}
}

void beat_enemy_pawns(_pawn *pawn, _board *board, HANDLE h)
{
	int i = 0;
	_pawn *temp = board->road[pawn->pos_on_road].pawns;
	for (int i = 0; i < board->road[pawn->pos_on_road].how_many_pawns; i++)
	{
		if (temp->color != pawn->color)	//porownuje po kolorach, bo czemu nie
		{
			return_to_base(board->road[pawn->pos_on_road].pawns, board, h);
			pop_front(&board->road[pawn->pos_on_road].pawns);	//usuwanie wskaznika na pionek, ktory wlasnie wrocil do bazy
			board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci pionkow na usunietym polu 
			temp = board->road[pawn->pos_on_road].pawns;
			continue;
		}
		temp = temp->next;
	}
}

int position_in_list(_pawn **head, _pawn *pawn)
{
	_pawn *temp = (*head);
	int i = 0;
	while (temp)
	{
		if (temp->id == pawn->id)
		{
			return i;
		}
		i++;
		temp = temp->next;
	}
}

void leave_the_base(_player *player, _pawn *pawn, _board *board, HANDLE h)
{
	pawn->in_base = 0;
	pawn->pos_on_road = player->begin;

	board->bases[player->id][pawn->id - 1].how_many_pawns--;
	pop_front(&board->bases[player->id][pawn->id - 1].pawns);	//pop_front, bo w bazie nie moze byc wiecej jak 1 pionek
	int x = board->exits[player->id].x;
	int y = board->exits[player->id].y;

	int color = board->bases[player->id][pawn->id - 1].color;
	int pawns = board->road[player->begin].how_many_pawns;

	if (pawns == 0)
	{
		board->road[player->begin].pawns = malloc(sizeof(_pawn));		//przydzielanie pamieci
		board->road[player->begin].pawns = NULL;
	}

	push_back(&board->road[player->begin].pawns, pawn);		//ustawiam wskaznik na nowego pionka
	board->road[player->begin].how_many_pawns++;		//inkrementuje ilosc pionkow na polu
	draw_square(pawn->x, pawn->y, color, h);	//usuwam pionka z bazy
	pawn->x = x;
	pawn->y = y;
	int i = board->road[player->begin].how_many_pawns;	//sprawdzam ilosc pionkow na nowym polu, jak wiecej niz 1, sprawdzam czy mozna cos zbic
	if (i > 1)
	{
		beat_enemy_pawns(pawn, board, h);
	}
	//rysuje go na polu wyjsciowym w zaleznosci od stanu tego pola (ilosci pionkow)
	if (i == 1)
	{
		draw_pawn(x, y, color, h, board->road[player->begin].pawns);
	}
	else if (i == 2)
	{
		draw_2_pawns(x, y, 32, h, board->road[player->begin].pawns);
	}
	else if (i == 3)
	{
		draw_3_pawns(x, y, 32, h, board->road[player->begin].pawns);
	}
	else if (i == 4)
	{
		draw_4_pawns(x, y, 32, h, board->road[player->begin].pawns);
	}
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
	}
	else
	{
		int temp = pawn->pos_on_road;
		int temp2 = temp;
		for (int i = 0; i < dice; i++)
		{
			if (i == 39)
			{
				i = 39;
			}
			int next_field = pawn->pos_on_road + 1;
			if (next_field == 40)
			{
				next_field = 0;
			}
			int x = board->road[next_field].x;
			int y = board->road[next_field].y;

			int pawns = board->road[next_field].how_many_pawns;
			if (pawns == 0)
			{
				board->road[next_field].pawns = malloc(sizeof(_pawn));		//przydzielanie pamieci
				board->road[next_field].pawns = NULL;
			}

			push_back(&board->road[next_field].pawns, pawn);		//dodaje wskazik na nowego pionka dla pola dalej
			int pos = position_in_list(&board->road[pawn->pos_on_road].pawns, pawn);
			pop_by_index(&board->road[pawn->pos_on_road].pawns, pos);

			//board->road[i].pawns[return_index_of_pawn(pawn, board)] = NULL;	//usuwam wskaznik na pionek ze starego pola, z ktorego odchodze
			//free(board->road[i].pawns[return_index_of_pawn(pawn, board)]);
			//free(board->road[i].pawns);

			board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
			board->road[next_field].how_many_pawns++;	//inkrementacja ilosci pionkow na nowym polu
			pawn->pos_on_road++;
			if (pawn->pos_on_road == 40)
			{
				pawn->pos_on_road = 0;
			}
			pawn->x = x;
			pawn->y = y;
			Sleep(20);
			if (i == (dice - 1) && board->road[next_field].how_many_pawns > 1)
			{
				beat_enemy_pawns(pawn, board, h);
			}
			//rysowanie nowego pola
			draw_field(board->road[next_field], board, h, next_field);
			//odtwarzanie starego pola
			if (next_field == 0)
			{
				draw_field(board->road[39], board, h, 39);
			}
			else
			{
				draw_field(board->road[next_field - 1], board, h, next_field - 1);
			}
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

int check_if_enemy(_pawn *head, _player *player)
{
	if (head == NULL)
	{
		return 0;
	}
	else
	{
		_pawn *current = head;
		while (current != NULL)
		{
			if (current->player != player->id)
			{
				return 1;
			}
			current = current->next;
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
			if (board->road[player->begin].how_many_pawns != 0)
			{
				if (check_if_enemy(board->road[player->begin].pawns, player) == 1)		//na wyjsciu stoi przeciwnik, bo rozne ID graczy
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
	//dla kazdego pionka spoza bazy sprawdzam, czy na koncu jego wedrowki nie stoi przecwiny pionek
	else
	{
		for (int i = 0; i < 4; i++)
		{
			_pawn toCheck = pawns[player->id * 4 + i];
			if (toCheck.in_base == 0)			//sprawdzam, czy ten pionek jest poza baza
			{
				for (int j = 0; j < 4; j++)
				{
					if (toCheck.pos_on_road + dice > 39)
					{
						toCheck.pos_on_road = dice - (39 - toCheck.pos_on_road);
					}
					if (check_if_enemy(board->road[toCheck.pos_on_road + dice - 1].pawns, player) == 1)
					{
						return i + 1;
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



