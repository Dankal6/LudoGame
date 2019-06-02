#pragma once
#include "Header.h"

int move_pawn(_pawn*, int, _board*, HANDLE, _pawn*, _player*);

void return_to_base(_pawn*, _board*, HANDLE);

void beat_enemy_pawns(_pawn*, _board*, HANDLE);

void leave_the_base(_player*, _pawn*, _board*, HANDLE);

int go_finish(_pawn*, int, _board*, HANDLE, _pawn*, _player*);

int check_if_won(_player*, _pawn*);

int check_if_enemy(_pawn*, _player*);

int moveable(_player*, int, _pawn*);

int choose_pawn(_player*, int, _board*, _pawn*);	//dla gracza sterowanego przez komputer, aby "chetniej" zbijal gdy ma mozliwosc

