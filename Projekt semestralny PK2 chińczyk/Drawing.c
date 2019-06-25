#include "Drawing.h"

void draw_pawns(_field field, HANDLE h)
{
	int x = field.x;
	int y = field.y;
	int amount = field.how_many_pawns;

	if (amount == 1)
	{
		changeConsoleColor(field.pawns->color);
		for (int i = 1; i < 3; i++)
		{
			gotoxy(x * 4 + i, y * 2 + 1, h);
			printf("%i", field.pawns->id);
			gotoxy(x * 4 + i, y * 2, h);
			printf("%i", field.pawns->id);
		}
	}
	else if (amount == 2)
	{
		//lewa kolumna pionka
		{
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 1, y * 2 + 1, h);
			printf("%i", field.pawns->id);
			gotoxy(x * 4 + 1, y * 2, h);
			printf("%i", field.pawns->id);
		}
		//prawa kolumna pionka
		{
			field.pawns = field.pawns->next;
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 2, y * 2 + 1, h);
			printf("%i", field.pawns->id);
			gotoxy(x * 4 + 2, y * 2, h);
			printf("%i", field.pawns->id);
		}
	}
	else if (amount == 3)
	{
		//gorny wiersz pola
		{
			//lewa strona (pionek 1)
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 1, y * 2, h);
			printf("%i", field.pawns->id);
			//prawa strona	(pionek 2)
			field.pawns = field.pawns->next;
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 2, y * 2, h);
			printf("%i", field.pawns->id);
		}
		//dolny wiersz pola
		{
			//lewa strona	(pionek 3)
			field.pawns = field.pawns->next;
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 1, y * 2 + 1, h);
			printf("%i", field.pawns->id);;
		}
	}
	else if (amount == 4)
	{
		//gorny wiersz pola
		{
			//lewa strona (pionek 1)
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 1, y * 2, h);
			printf("%i", field.pawns->id);
			//prawa strona	(pionek 2)
			field.pawns = field.pawns->next;
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 2, y * 2, h);
			printf("%i", field.pawns->id);
		}
		//dolny wiersz pola
		{
			//lewa strona	(pionek 3)
			field.pawns = field.pawns->next;
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 1, y * 2 + 1, h);
			printf("%i", field.pawns->id);
			//prawa strona	(pionek 4)
			field.pawns = field.pawns->next;
			changeConsoleColor(field.pawns->color);
			gotoxy(x * 4 + 2, y * 2 + 1, h);
			printf("%i", field.pawns->id);
		}
	}
	gotoxy(0, 30, h);
}

void draw_field(_field field, HANDLE h)
{
	int x= field.x;
	int y= field.y;
	for (int i = 0; i < 4; i++)
	{
		gotoxy(x * 4 + i, y * 2, h);
		changeConsoleColor(field.color);
		printf("%c", 219);
		gotoxy(x * 4 + i, y * 2 + 1, h);
		printf("%c", 219);
	}
	//rysowanie pionkow
	draw_pawns(field, h);
	gotoxy(0, 30, h);
}

void draw_bases(_board *board, HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			draw_field(board->bases[i][j], h);
		}
	}
}

void draw_road(_field *road,HANDLE h)
{
	for (int i = 0; i < 56; i++)
	{
		draw_field(road[i], h);
	}
}

void draw_exits(_field *exit, HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		draw_field(exit[i], h);
	}
}

void draw_the_center(HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(5 * 4 + i, 5 * 2, h);
		changeConsoleColor(119);
		printf("%c", 219);
		gotoxy(5 * 4 + i, 5 * 2 + 1, h);
		printf("%c", 219);
	}
}

void draw_board(_board *board, HANDLE h)
{
	draw_bases(board, h);
	draw_exits(board->exits, h);
	draw_road(board->road, h);
	draw_the_center(h);
}

void draw_prev_next_field(_board *board, int next_field, HANDLE h)
{
	//rysowanie nowego pola
	draw_field(board->road[next_field], h);
	//odtwarzanie starego pola
	if (next_field == 0)
	{
		draw_field(board->road[39], h);
	}
	else
	{
		draw_field(board->road[next_field - 1], h);
	}
}