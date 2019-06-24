#pragma once
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#include <stdlib.h>
#include <time.h>

typedef struct {
	char *name;	//nazwa gracza: green, yellow, blue, red
	int id;		//id gracza 0-3;
	int AI;		//czy graczem steruje komputer, 0-1
	int random;	//informacja o tym, czy komputer wykonuje losowy ruch
	int begin;	//miejsce rozpoczecia na planszy
	int won;	//informacja o tym, czy gracz jest 4 pionkami na mecie, 0-1
	int place;	//informacja o kolejnosci konczenia gry, miejscu
}_player;

typedef struct{
	int player;	//odpowiednik ID z _player, 0-3
	int id;		//id pionka, wartosc 1-4
	int x, y;	//wspolrzedne na planszy
	int pos_on_road;	//pozycja na trasie, 0-39
	int distance;		//dystans od poczatku
	int in_base;	//informacja o tym, czy pionek jest w bazie, 0-1
	int on_meta;	//informacja o tym, czy pionek jest na mecie, 0-4
	int color;		//przechowuje kolor pionka
	struct _pawn *next;	//przechowuje wskaznik na nastepnego pionka w liscie, jezeli na 1 polu jest wiecej niz 1 pionek
}_pawn;

typedef struct {
	_pawn *pawns;				//przechowuje wskazniki na pionki znajdujace sie na danym polu
	int x, y, how_many_pawns,color;	//koordy + przechowuje informacje na temat ilosci pionkow na danym polu
}_field;

typedef struct {	
	int num_of_players;
	_field *road;	
	_field exits[4];
	_field bases[4][4];
	//_field meta[4][4];	//testowo przerzucam do road[56]
}_board;