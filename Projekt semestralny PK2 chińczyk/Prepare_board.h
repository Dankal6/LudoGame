#pragma once
#include <Windows.h>
#include "Header.h"
#include "Pawn.h"

void draw_board(struct _board*, HANDLE, _pawn[16]);

void prepare_board_of_ptr(_board*);

void draw_square(int, int, int, HANDLE);

void draw_field(_field field, _board*, HANDLE, int);
