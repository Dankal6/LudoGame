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
	char *name;
	int id;
	int random;
	int begin;
	int won;
}_player;

typedef struct{
	int player;
	int id;
	int x, y;
	int pos_on_road;
	int in_base;
	int on_meta;
	int color;
	struct _pawn *next;
}_pawn;

typedef struct {
	_pawn *pawns;				//przechowuje wskazniki na pionki znajdujace sie na danym polu
	int x, y, how_many_pawns,color;	//koordy + przechowuje informacje na temat ilosci pionkow na danym polu
}_field;

typedef struct {	
	_field road[40];	
	_field exits[4];
	_field bases[4][4];
	_field meta[4][4];
}_board;