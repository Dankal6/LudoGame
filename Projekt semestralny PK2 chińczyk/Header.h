#pragma once
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include <stdlib.h>
#include <time.h>


typedef struct {
	char player[7];		//mozna by dynamicznie, do ewentualnej poprawki
	int id;
	int x, y;
	int pos_on_road;
	int in_base;
	char name[7];
	int color;
}_pawn;

typedef struct {

	char coords[11][11][10];
	int how_many_pawns[11][11];		//przechowuje informacje na temat ilosci pionkow na danym polu
	int pawns_on_that_field[11][11][4];	//przechowuje ID pionkow na danym polu, nie moze byc wiecej niz 4, wynika z zasad gry, docelowo zbedne z racji posiadania wskaznikow
	_pawn *pawn_ptr[11][11][4];		//przechowuje wskazniki na pionki znajdujace sie na danym polu
	int exit_coords[4][3];		//koordy wyjsc z baz + kolor pola
	int base_coords[4][4][2];		//koordy baz (gracz, 1 z 4 pol, koordy)
	int meta_coords[4][4][2];		//koordy mety dla kazdego z graczy (gracz[1-4], 1 z pol, wspolrzedne) jw
}_board;

