#pragma once
#include "Structures.h"

void draw_board(_board*, HANDLE);

void draw_pawns(_field, HANDLE);

void draw_field(_field, HANDLE);

void draw_bases(_board*, HANDLE h);

void draw_raod(_field*, HANDLE);

void draw_exits(_field*, HANDLE);

void draw_the_center(HANDLE);