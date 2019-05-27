#pragma once
#include "Header.h"

void draw_pawn(int, int, int, HANDLE, _pawn*);

void draw_2_pawns(int, int, int, HANDLE, _pawn*, _pawn*);

void draw_3_pawns(int, int, int, HANDLE, _pawn*, _pawn*, _pawn*);

void draw_4_pawns(int, int, int, HANDLE, _pawn*, _pawn*, _pawn*, _pawn*);

int return_index_of_pawn(int, int, _pawn*, _board*);

void return_to_base(_pawn*, _board*, HANDLE);

void beat_enemy_pawns(_pawn*, _board*, HANDLE);

void leave_the_base(int, _pawn*, _board*, HANDLE);

void move_pawn(_pawn*, int, _board*, HANDLE, _pawn*, _road*);

_pawn *find_pawn_in_array(char*, int, _pawn*);

int *which_is_not_null(int, int, _board*);