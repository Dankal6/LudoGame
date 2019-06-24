#pragma once
#include "Structures.h"

int move_pawn(_pawn*, int, _board*, HANDLE, _pawn*, _player*);

void return_to_base(_pawn*, _board*, HANDLE);

void beat_enemy_pawns(_pawn*, _board*, HANDLE);

void leave_the_base(_player*, _pawn*, _board*, HANDLE);

int go_finish(_pawn*, int, int, _board*, HANDLE, _pawn*, _player*);