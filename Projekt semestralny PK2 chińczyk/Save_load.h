#pragma once
#include "Structures.h"

#ifndef _SAVE_LOAD_H
#define _SAVE_LOAD_H

void save_to_file(_pawn*,_player*,int);

int load_players_from_file();

void load_from_file(_pawn*, _board*, _player*, HANDLE);

#endif