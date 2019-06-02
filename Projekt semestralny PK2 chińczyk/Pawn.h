#pragma once
#include "Header.h"

void draw_pawns(_field, HANDLE);

int return_index_of_pawn(_pawn*, _board*);

void return_to_base(_pawn*, _board*, HANDLE);

void beat_enemy_pawns(_pawn*, _board*, HANDLE);

void leave_the_base(_player*, _pawn*, _board*, HANDLE);

int move_pawn(_pawn*, int, _board*, HANDLE, _pawn*, _player*);

int go_finish(_pawn*, int, _board*, HANDLE, _pawn*, _player*);

int moveable(_player*, int, _pawn*);

int check_if_won(_player*, _pawn*);

int choose_pawn(_player*, int, _board*, _pawn*);	//dla gracza sterowanego przez komputer, aby "chetniej" zbijal gdy ma mozliwosc

void draw_field(_field field, _board*, HANDLE, int);

void pop_front(_pawn **);

void pop_by_index(_pawn **, int);

void push_back(_pawn **, _pawn *);
