#pragma once
#include "Structures.h"

void save_to_file(_pawn*,_player*,int);

int load_players_from_file();

void load_from_file(_pawn*, _board*, _player*, HANDLE);