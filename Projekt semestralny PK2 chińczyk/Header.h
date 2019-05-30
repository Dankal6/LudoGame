#pragma once
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include <stdlib.h>
#include <time.h>

typedef struct {
	int x;
	int y;
	/*_road *next;
	_road *prev;
	_road *head;
	_road *tail;*/
}_road;

typedef struct {
	char name[7];	//mozna by dynamicznie, do ewentualnej poprawki
	int id;
	int random;
}_player;

typedef struct {
	int player;	
	int id;
	int x, y;
	int pos_on_road;
	int in_base;
	int color;
}_pawn;

typedef struct {
	int how_many_pawns[11][11];		//przechowuje informacje na temat ilosci pionkow na danym polu
	_pawn **pawn_ptr[11][11];		//przechowuje wskazniki na pionki znajdujace sie na danym polu
	int exit_coords[4][3];			//koordy wyjsc z baz dla kazdego z graczy + kolor pola
	int base_coords[4][4][2];		//koordy baz (gracz, 1 z 4 pol, koordy)
	int meta_coords[4][4][2];		//koordy mety dla kazdego z graczy (gracz[1-4], 1 z pol, wspolrzedne) jw
}_board;

