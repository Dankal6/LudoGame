#pragma once
#include "Structures.h"

int choose_pawn(_player*, int, _board*, _pawn*);	//dla gracza sterowanego przez komputer, aby "chetniej" zbijal gdy ma mozliwosc

int moveable(_player*, int, _pawn*,_board*);

int check_if_won(_player*, _pawn*);

int check_if_enemy(_pawn*, _player*);





