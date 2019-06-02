#include "Pawn.h"

int move_pawn(_pawn *pawn, int dice, _board *board, HANDLE h, _pawn *pawns, _player *player)	//pawns zdaje sie byc zbedne
{
	//sprawdzam, czy wybrany pionek znajduje sie w bazie, oraz czy wyrzucona zostala 6stka
	if (pawn->in_base == 1 && dice == 6)
	{
		leave_the_base(player, pawn, board, h, pawns);
		return 1;
	}
	//sprawdzam, czy wybrany pionek jest na mecie, czy jeszcze w drodze
	else if (pawn->on_meta == 0 && pawn->in_base == 0)
	{
		int temp = pawn->pos_on_road;
		int temp2 = temp;
		for (int i = 0; i < dice; i++)
		{
			int next_field = pawn->pos_on_road + 1;
			if ((player->begin - pawn->pos_on_road == 1 && player->id != 0) || (player->id == 0 && pawn->pos_on_road == 39))	//wchodze na mete
			{
				int pos = position_in_list(&board->road[pawn->pos_on_road].pawns, pawn);
				pop_by_index(&board->road[pawn->pos_on_road].pawns, pos);
				board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
				pawn->on_meta = 1;
				draw_field(board->road[next_field - 1], board, h, next_field - 1);
				go_finish(pawn, dice - i, board, h, pawns, player);
				return;
			}
			if (next_field == 40)
			{
				next_field = 0;
			}
			int x = board->road[next_field].x;
			int y = board->road[next_field].y;

			int pawns = board->road[next_field].how_many_pawns;
			if (pawns == 0)
			{
				//board->road[next_field].pawns = malloc(sizeof(_pawn));		//przydzielanie pamieci
				board->road[next_field].pawns = NULL;
			}

			int pos = position_in_list(&board->road[pawn->pos_on_road].pawns, pawn);
			pop_by_index(&board->road[pawn->pos_on_road].pawns, pos);
			push_back(&board->road[next_field].pawns, pawn);		//dodaje wskazik na nowego pionka dla pola dalej

			board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
			board->road[next_field].how_many_pawns++;	//inkrementacja ilosci pionkow na nowym polu
			pawn->pos_on_road++;
			if (pawn->pos_on_road == 40)
			{
				pawn->pos_on_road = 0;
			}
			pawn->x = x;
			pawn->y = y;
			Sleep(50);
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
	else if (pawn->on_meta >= 1)
	{
		return go_finish(pawn, dice, board, h, pawns, player);
	}
	else
	{
		printf("You can't move that pawn!");
		Sleep(50);
		return 0;
	}

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

void beat_enemy_pawns(_pawn *pawn, _board *board, HANDLE h)
{
	int i = 0;
	int temp2 = board->road[pawn->pos_on_road].how_many_pawns;
	_pawn *temp = board->road[pawn->pos_on_road].pawns;
	for (int i = 0; i < temp2; i++)
	{
		if (temp->color != pawn->color)	//porownuje po kolorach, bo czemu nie
		{
			return_to_base(temp, board, h);
			pop_front(&board->road[pawn->pos_on_road].pawns);	//usuwanie wskaznika na pionek, ktory wlasnie wrocil do bazy
			board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci pionkow na usunietym polu 
			temp = board->road[pawn->pos_on_road].pawns;
			continue;
		}
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
		//board->road[player->begin].pawns = malloc(sizeof(_pawn));		//przydzielanie pamieci
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
	draw_field(board->road[player->begin], board, h, 0);
}

int go_finish(_pawn *pawn, int dice, _board *board, HANDLE h, _pawn *pawns, _player *player)
{
	if (pawn->on_meta == 5)
	{
		return 0;
	}
	for (int i = 0; i < dice; i++)
	{
		if (pawn->on_meta < 5)
		{
			int next_field = pawn->on_meta - 1;
			int x = board->meta[player->id][next_field].x;
			int y = board->meta[player->id][next_field].y;

			int pawns = board->meta[player->id][next_field].how_many_pawns;
			if (pawns == 0)
			{
				//board->meta[player->id][next_field].pawns = malloc(sizeof(_pawn));		//przydzielanie pamieci
				board->meta[player->id][next_field].pawns = NULL;
			}

			if (pawn->on_meta >= 2)
			{
				int pos = position_in_list(&board->meta[player->id][pawn->on_meta - 2].pawns, pawn);
				pop_by_index(&board->meta[player->id][pawn->on_meta - 2].pawns, pos);
				board->meta[player->id][pawn->on_meta - 2].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
			}

			push_back(&board->meta[player->id][next_field].pawns, pawn);		//dodaje wskazik na nowego pionka dla pola dalej


			board->meta[player->id][next_field].how_many_pawns++;	//inkrementacja ilosci pionkow na nowym polu

			pawn->x = x;
			pawn->y = y;
			Sleep(50);
			//rysowanie nowego pola
			draw_field(board->meta[player->id][next_field], board, h, next_field);
			//odtwarzanie starego pola
			if (next_field != 0)
			{
				draw_field(board->meta[player->id][next_field - 1], board, h, next_field - 1);
			}
			pawn->on_meta++;
		}
	}
	return 1;
}

int check_if_won(_player *player, _pawn *pawns)
{
	for (int i = 0; i < 4; i++)
	{
		if (pawns[player->id * 4 + i].on_meta == 0)
		{
			return 0;
		}
	}
	return 1;
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

int moveable(_player *player, int dice, _pawn *pawns)
{
	if (dice != 6)
	{
		for (int i = 0; i < 4; i++)
		{
			if (pawns[player->id * 4 + i].in_base == 0 && pawns[player->id * 4 + i].on_meta != 5)
			{
				return 1;
			}
		}
		return 0;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (pawns[player->id * 4 + i].on_meta != 5)
			{
				return 1;
			}
		}
	}
	return 0;
}

int choose_pawn(_player *player, int dice, _board *board, _pawn *pawns)
{
	//na poczatek sprawdzam, czy na wyjsciu z bazy nie stoi przecinik, ktorego moglbym zbic
	if (dice == 6)		//do testow zakomentowane
	{
		for (int i = 0; i < 4; i++)
		{
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
				if (toCheck.pos_on_road + dice > 39 && toCheck.on_meta == 0) //oznacza to, ze pionek moze wejsc do bazy, wiec go wybieram
				{
					return i + 1;	
				}
				//dodaje warunek toCheck.on_meta == 0, poniewaz jak pionek jest na mecie to nie bedzie nic zbijal
				if (toCheck.on_meta == 0 && check_if_enemy(board->road[toCheck.pos_on_road + dice].pawns, player) == 1)
				{
					return i + 1;
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



