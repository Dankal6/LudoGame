#include "Movement.h"

int throw_dice()
{
	srand(time(NULL));
	int dice = ((rand() % 6) + 1);
	return dice;
}

int move_pawn(_pawn *pawn, int dice, _board *board, HANDLE h, _pawn *pawns, _player *player)	//pawns zdaje sie byc zbedne
{
	if (pawn->distance + dice > 45 || board->road[pawn->distance + (4 * pawn->player) + dice - 1].pawns != NULL)
	{
		return 0;
	}
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
			//if ((player->begin - pawn->pos_on_road == 1 && player->id != 0) || (player->id == 0 && pawn->pos_on_road == 39))	//wchodze na mete
			if(pawn->distance==40)
			{
				return go_finish(pawn, dice - (i), dice, board, h, pawns, player);
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
				board->road[next_field].pawns = NULL;
			}

			int pos = position_in_list(&board->road[pawn->pos_on_road].pawns, pawn);
			pop_by_index(&board->road[pawn->pos_on_road].pawns, pos);
			push_back(&board->road[next_field].pawns, pawn);		//dodaje wskazik na nowego pionka dla pola dalej

			board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
			board->road[next_field].how_many_pawns++;	//inkrementacja ilosci pionkow na nowym polu
			pawn->pos_on_road++;
			pawn->distance++;
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
			draw_field(board->road[next_field], h);
			//odtwarzanie starego pola
			if (next_field == 0)
			{
				draw_field(board->road[39], h);
			}
			else
			{
				draw_field(board->road[next_field - 1], h);
			}
		}
		if (dice == 6)
		{
			return 0;
		}
	}
	else if (pawn->distance >= 41)
	{
		return go_finish(pawn, dice, dice, board, h, pawns, player);
	}
	else
	{
		return 0;
	}

}

void return_to_base(_pawn *pawn, _board *board, HANDLE h)
{
	pawn->in_base = 1;
	pawn->pos_on_road = 0;
	pawn->distance = 0;

	pawn->x = board->bases[pawn->player][pawn->id - 1].x;
	pawn->y = board->bases[pawn->player][pawn->id - 1].y;
	board->bases[pawn->player][pawn->id - 1].pawns = pawn;	//ustawianie wskaznika na zbity pionek w bazie
	board->bases[pawn->player][pawn->id - 1].how_many_pawns++;	//inkrementacja ilosci pionkow na polu w bazie, na ktory wrocil pionek
	//rysowanie zbitego pionka w bazie
	draw_field(board->bases[pawn->player][pawn->id - 1], h);
}

void beat_enemy_pawns(_pawn *pawn, _board *board, HANDLE h)
{
	int i = 0;
	int pawns_on_field = board->road[pawn->pos_on_road].how_many_pawns;
	_pawn *to_beat = board->road[pawn->pos_on_road].pawns;
	for (int i = 0; i < pawns_on_field; i++)
	{
		if (to_beat->color != pawn->color)	//porownuje po kolorach, bo czemu nie
		{
			return_to_base(to_beat, board, h);
			pop_front(&board->road[pawn->pos_on_road].pawns);	//usuwanie wskaznika na pionek, ktory wlasnie wrocil do bazy
			board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci pionkow na usunietym polu 
			to_beat = board->road[pawn->pos_on_road].pawns;
			continue;
		}
		to_beat = to_beat->next;
	}
}

void leave_the_base(_player *player, _pawn *pawn, _board *board, HANDLE h)
{
	pawn->in_base = 0;
	pawn->pos_on_road = player->begin;
	pawn->distance = 1;

	board->bases[player->id][pawn->id - 1].how_many_pawns--;
	pop_front(&board->bases[player->id][pawn->id - 1].pawns);	//pop_front, bo w bazie nie moze byc wiecej jak 1 pionek
	int x = board->exits[player->id].x;
	int y = board->exits[player->id].y;

	int color = board->bases[player->id][pawn->id - 1].color;
	int pawns = board->road[player->begin].how_many_pawns;

	if (pawns == 0)
	{
		board->road[player->begin].pawns = NULL;
	}

	push_back(&board->road[player->begin].pawns, pawn);		//ustawiam wskaznik na nowego pionka
	board->road[player->begin].how_many_pawns++;		//inkrementuje ilosc pionkow na polu
	draw_field(board->bases[player->id][pawn->id - 1], h);	//usuwam pionka z bazy
	pawn->x = x;
	pawn->y = y;
	int i = board->road[player->begin].how_many_pawns;	//sprawdzam ilosc pionkow na nowym polu, jak wiecej niz 1, sprawdzam czy mozna cos zbic
	if (i > 1)
	{
		beat_enemy_pawns(pawn, board, h);
	}
	draw_field(board->road[player->begin], h);
}

int go_finish(_pawn *pawn, int dice_left, int dice, _board *board, HANDLE h, _pawn *pawns, _player *player)
{
	if (pawn->distance + dice_left > 44)
	{
		return 0;
	}
	if (board->road[pawn->distance + (4 * pawn->player) + dice_left - 1].pawns != NULL)	//to oznacza, iz na polu, na ktore zmierza pionek jakis pionek juz jest, a na mecie pionki grupowaæ siê nie mog¹
	{
		return 0;
	}
	for (int i = 0; i < dice_left; i++)
	{
		if (pawn->on_meta < 5)
		{
			pawn->x = board->road[pawn->distance + (4 * pawn->player)].x;
			pawn->y = board->road[pawn->distance + (4 * pawn->player)].y;
			int pawns = board->road[pawn->distance + (4 * pawn->player)].how_many_pawns;
			if (pawns == 0)
			{
				board->road[pawn->distance + (4 * pawn->player)].pawns = NULL;
			}

			if (pawn->distance >= 41)
			{
				int pos = position_in_list(&board->road[pawn->distance + (4 * pawn->player) - 1].pawns, pawn);
				pop_by_index(&board->road[pawn->distance + (4 * pawn->player) - 1].pawns, pos);
				board->road[pawn->distance + (4 * pawn->player) - 1].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
			}
			else
			{
				int pos = position_in_list(&board->road[pawn->pos_on_road].pawns, pawn);
				pop_by_index(&board->road[pawn->pos_on_road].pawns, pos);	//usuwanie z pola przed meta
				board->road[pawn->pos_on_road].how_many_pawns--;	//dekrementacja ilosci piokow ze starego pola
				pawn->on_meta = 1;
				draw_field(board->road[pawn->pos_on_road], h);		//rysowanie pola przed meta juz bez pionka
			}

			push_back(&board->road[pawn->distance + (4 * pawn->player)].pawns, pawn);		//dodaje wskazik na nowego pionka dla pola dalej
			board->road[pawn->distance + (4 * pawn->player)].how_many_pawns++;	//inkrementacja ilosci pionkow na nowym polu

			Sleep(50);
			//rysowanie nowego pola
			draw_field(board->road[pawn->distance + (4 * pawn->player)], h);
			//odtwarzanie starego pola
			draw_field(board->road[pawn->distance + (4 * pawn->player) - 1], h);
			pawn->distance++;
		}
	}
	if (dice == 6)
	{
		return 0;
	}
	return 1;
}



