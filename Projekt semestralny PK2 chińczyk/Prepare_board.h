#pragma once
#include "Structures.h"

#ifndef _PREPARE_BOARD_H
#define _PREPARE_BOARD_H

void init_board(_board*);

void prepare_bases(_board*, _pawn*, int);

void prepare_road(_field*);

#endif


