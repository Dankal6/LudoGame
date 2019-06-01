#pragma once
#include "Header.h"

void draw_pawn(int, int, int, HANDLE, _pawn*);

void draw_2_pawns(int, int, int, HANDLE, _pawn*);

void draw_3_pawns(int, int, int, HANDLE, _pawn*);

void draw_4_pawns(int, int, int, HANDLE, _pawn*);

int return_index_of_pawn(_pawn*, _board*);

void return_to_base(_pawn*, _board*, HANDLE);

void beat_enemy_pawns(_pawn*, _board*, HANDLE);

void leave_the_base(_player*, _pawn*, _board*, HANDLE);

void move_pawn(_pawn*, int, _board*, HANDLE, _pawn*, _player*);

_pawn *find_pawn_in_array(char*, int, _pawn*);

int choose_pawn(_player*,int,_board*,_pawn*);	//dla gracza sterowanego przez komputer, aby "chetniej" zbijal gdy ma mozliwosc

void draw_field(_field field, _board*, HANDLE, int);

void pop_front(_pawn **);

void pop_by_index(_pawn **, int);

void push_back(_pawn **, _pawn *);
