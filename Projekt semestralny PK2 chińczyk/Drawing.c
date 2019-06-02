#include "Drawing.h"

void draw_pawns(_field *field, HANDLE h)
{
	int x = field->x;
	int y = field->y;
	int amount = field->how_many_pawns;

	if (amount == 1)
	{
		changeConsoleColor(field->pawns->color);
		for (int i = 1; i < 3; i++)
		{
			gotoxy(x * 4 + i, y * 2 + 1, h);
			printf("%i", field->pawns->id);
			gotoxy(x * 4 + i, y * 2, h);
			printf("%i", field->pawns->id);
		}
	}
	else if (amount == 2)
	{
		//lewa kolumna pionka
		{
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 1, y * 2 + 1, h);
			printf("%i", field->pawns->id);
			gotoxy(x * 4 + 1, y * 2, h);
			printf("%i", field->pawns->id);
		}
		//prawa kolumna pionka
		{
			field->pawns = field->pawns->next;
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 2, y * 2 + 1, h);
			printf("%i", field->pawns->id);
			gotoxy(x * 4 + 2, y * 2, h);
			printf("%i", field->pawns->id);
		}
	}
	else if (amount == 3)
	{
		//gorny wiersz pola
		{
			//lewa strona (pionek 1)
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 1, y * 2, h);
			printf("%i", field->pawns->id);
			//prawa strona	(pionek 2)
			field->pawns = field->pawns->next;
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 2, y * 2, h);
			printf("%i", field->pawns->id);
		}
		//dolny wiersz pola
		{
			//lewa strona	(pionek 3)
			field->pawns = field->pawns->next;
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 1, y * 2 + 1, h);
			printf("%i", field->pawns->id);;
		}
	}
	else if (amount == 4)
	{
		//gorny wiersz pola
		{
			//lewa strona (pionek 1)
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 1, y * 2, h);
			printf("%i", field->pawns->id);
			//prawa strona	(pionek 2)
			field->pawns = field->pawns->next;
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 2, y * 2, h);
			printf("%i", field->pawns->id);
		}
		//dolny wiersz pola
		{
			//lewa strona	(pionek 3)
			field->pawns = field->pawns->next;
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 1, y * 2 + 1, h);
			printf("%i", field->pawns->id);
			//prawa strona	(pionek 4)
			field->pawns = field->pawns->next;
			changeConsoleColor(field->pawns->color);
			gotoxy(x * 4 + 2, y * 2 + 1, h);
			printf("%i", field->pawns->id);
		}
	}
	gotoxy(0, 30, h);
}

void draw_square(int x, int y, int color, HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		gotoxy(x * 4 + i, y * 2, h);
		changeConsoleColor(color);
		printf("%c", 219);
		gotoxy(x * 4 + i, y * 2 + 1, h);
		printf("%c", 219);
	}
	gotoxy(0, 30, h);
}

void draw_field(_field field, _board *board, HANDLE h, int i)
{
	//rysowanie wyjsc graczy
	int x = field.x;
	int y = field.y;
	if (x == board->exits[0].x && y == board->exits[0].y)
	{
		draw_square(x, y, 34, h);
	}
	else if (x == board->exits[1].x && y == board->exits[1].y)
	{
		draw_square(x, y, 102, h);
	}
	else if (x == board->exits[2].x && y == board->exits[2].y)
	{
		draw_square(x, y, 17, h);
	}
	else if (x == board->exits[3].x && y == board->exits[3].y)
	{
		draw_square(x, y, 68, h);
	}
	//rysowanie pol bialo-szarych
	else
	{
		if (i == -1)		//gdy pionek wraca po zbiciu do bazy i=-1 i nie rysuje pol bialo-szarych
		{
			draw_square(x, y, field.color, h);
		}
		else
		{
			if (i % 2 == 1)
			{
				draw_square(x, y, 119, h);
			}
			else
			{
				draw_square(x, y, 255, h);
			}
		}
	}
	//rysowanie mety graczy
	int it, j;
	for (it = 0; it < 4; it++)
	{
		for (j = 0; j < 4; j++)
		{
			if (x == board->meta[it][j].x && y == board->meta[it][j].y)
			{
				if (it == 0)
					draw_square(x, y, 34, h);
				else if (it == 1)
					draw_square(x, y, 102, h);
				else if (it == 2)
					draw_square(x, y, 17, h);
				else if (it == 3)
					draw_square(x, y, 68, h);
			}
		}
	}
	//rysowanie pionkow
	draw_pawns(&field, h);
}