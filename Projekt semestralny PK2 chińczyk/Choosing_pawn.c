#include "Choosing_pawn.h"

int check_if_won(_player *player, _pawn *pawns, int num_of_players)
{
	for (int i = 0; i < num_of_players; i++)
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