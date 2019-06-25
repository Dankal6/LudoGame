#pragma once
#include "Structures.h"

#ifndef _LIST_OF_PAWNS_H
#define _LIST_OF_PAWNS_H

void pop_front(_pawn **);

void pop_by_index(_pawn **, int);

void push_back(_pawn **, _pawn *);

int position_in_list(_pawn**, _pawn*);

#endif