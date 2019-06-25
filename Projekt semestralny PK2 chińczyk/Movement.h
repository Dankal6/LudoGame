#pragma once
#include "Structures.h"

#ifndef _MOVEMENT_H
#define _MOVEMENT_H

int move_pawn(_pawn*, int, _board*, HANDLE, _player*);

int go_road(int, _pawn *, _board *, _player *, HANDLE);

void return_to_base(_pawn*, _board*, HANDLE);

void beat_enemy_pawns(_pawn*, _board*, HANDLE);

void leave_the_base(_player*, _pawn*, _board*, HANDLE);

int go_finish(_pawn*, int, int, _board*, HANDLE, _player*);

void update_pawn(_pawn*, _field);

#endif