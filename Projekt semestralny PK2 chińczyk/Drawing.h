#pragma once
#include "Structures.h"

#ifndef _DRAWING_H
#define _DRAWING_H

void draw_board(_board*, HANDLE);

void draw_pawns(_field, HANDLE);

void draw_field(_field, HANDLE);

void draw_bases(_board*, HANDLE h);

void draw_raod(_field*, HANDLE);

void draw_exits(_field*, HANDLE);

void draw_the_center(HANDLE);

void draw_prev_next_field(_board *, int, HANDLE);

#endif