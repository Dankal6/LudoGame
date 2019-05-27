#include "Header.h"
//34,32 - ZIELONY ; 102,96 ZOLTY ; 68,64 CZERWONY ; 17,16 NIEBIESKI


//warto rozwazyc przerobienie na liste dwukierunkowa
typedef struct {
	int x;
	int y;
}_road;

typedef struct {
	char name[7];	//mozna by dynamicznie, do ewentualnej poprawki
}_player;

void changeConsoleColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void gotoxy(int x, int y, HANDLE h)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}

void draw_pawn(int x, int y, int color, HANDLE h, _pawn *pawn)
{
	//zmiana wspolrzednych pionka
	pawn->x = x;
	pawn->y = y;
	//zasadnicze rysowanie
	changeConsoleColor(pawn->color);
	for (int i = 1; i < 3; i++)
	{
		gotoxy(x * 4 + i, y * 2 + 1, h);
		printf("%i", pawn->id);
		gotoxy(x * 4 + i, y * 2, h);
		printf("%i", pawn->id);
	}
	gotoxy(0, 30, h);
}

void draw_2_pawns(int x, int y, int color, HANDLE h, _pawn *pawn1, _pawn *pawn2)
{
	//zasadnicze rysowanie
	//lewa kolumna pionka
	{
		changeConsoleColor(pawn1->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn1->id);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn1->id);
	}
	//prawa kolumna pionka
	{
		changeConsoleColor(pawn2->color);
		gotoxy(x * 4 + 2, y * 2 + 1, h);
		printf("%i", pawn2->id);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn2->id);
	}
	gotoxy(0, 30, h);
}

void draw_3_pawns(int x, int y, int color, HANDLE h, _pawn *pawn1, _pawn *pawn2, _pawn *pawn3)
{
	//gorny wiersz pola
	{
		//lewa strona (pionek 1)
		changeConsoleColor(pawn1->color);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn1->id);
		//prawa strona	(pionek 2)
		changeConsoleColor(pawn2->color);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn2->id);
	}
	//dolny wiersz pola
	{
		//lewa strona	(pionek 3)
		changeConsoleColor(pawn3->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn3->id);;
	}
	gotoxy(0, 30, h);
}

void draw_4_pawns(int x, int y, int color, HANDLE h, _pawn *pawn1, _pawn *pawn2, _pawn *pawn3, _pawn *pawn4)
{
	//gorny wiersz pola
	{
		//lewa strona (pionek 1)
		changeConsoleColor(pawn1->color);
		gotoxy(x * 4 + 1, y * 2, h);
		printf("%i", pawn1->id);
		//prawa strona	(pionek 2)
		changeConsoleColor(pawn2->color);
		gotoxy(x * 4 + 2, y * 2, h);
		printf("%i", pawn2->id);
	}
	//dolny wiersz pola
	{
		//lewa strona	(pionek 3)
		changeConsoleColor(pawn3->color);
		gotoxy(x * 4 + 1, y * 2 + 1, h);
		printf("%i", pawn3->id);
		//prawa strona	(pionek 4)
		changeConsoleColor(pawn4->color);
		gotoxy(x * 4 + 2, y * 2 + 1, h);
		printf("%i", pawn4->id);
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

int throw_dice()
{
	srand(time(NULL));
	int dice = ((rand() % 6) + 1);
	return dice;
}

//zwraca indeks pionka w tablicy pionkow na danym polu (1 z max 4), potrzebne do usuwania wskaznika na pionek, ktory odszedl z pola
int return_index_of_pawn(int x, int y, _pawn *pawn, _board *board)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[x][y][i] != NULL)
		{
			if (strcmp(board->pawn_ptr[x][y][i]->name, pawn->name) == 0)
			{
				return i;
			}
		}
	}
}

//funkcja zwraca indeksy pawn_ptr z board, na ktorych jest pionek, a nie NULL
int *which_is_not_null(int x, int y, _board *board)
{
	int tab[4];
	int j = 0;
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[x][y][i] != NULL)
		{
			tab[j] = i;
			j++;
		}
	}
	return tab;
}

int which_is_null(int x, int y, _board *board)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[x][y][i] == NULL)
		{
			return i;
		}
	}
}

void draw_field(int x, int y, _board *board, HANDLE h, int i)
{
	//rysowanie wyjsc graczy
	if (x == board->exit_coords[0][0] && y == board->exit_coords[0][1])
	{
		draw_square(x, y, 34, h);
	}
	else if (x == board->exit_coords[1][0] && y == board->exit_coords[1][1])
	{
		draw_square(x, y, 102, h);
	}
	else if (x == board->exit_coords[2][0] && y == board->exit_coords[2][1])
	{
		draw_square(x, y, 17, h);
	}
	else if (x == board->exit_coords[3][0] && y == board->exit_coords[3][1])
	{
		draw_square(x, y, 68, h);
	}
	//rysowanie pol bialo-szarych
	else
	{
		if (i != -1)		//gdy pionek wraca po zbiciu do bazy i=-1 i nie rysuje pol bialo-szarych
		{
			if (i % 2 == 0)
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
			if (x == board->meta_coords[it][j][0] && y == board->meta_coords[it][j][1])
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
	int pawns = board->how_many_pawns[x][y];		//##ERROR
	int *temp = which_is_not_null(x, y, board);
	if (pawns == 1)
	{
		draw_pawn(x, y, 32, h, board->pawn_ptr[x][y][temp[0]]);
	}
	else if (pawns == 2)
	{
		draw_2_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]]);
	}
	else if (pawns == 3)
	{
		draw_3_pawns(x, y, 34, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]]);
	}
	else if (pawns == 4)
	{
		draw_4_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]], board->pawn_ptr[x][y][temp[3]]);
	}
}

void return_to_base(_pawn *pawn, _board *board, HANDLE h)
{
	pawn->in_base = 1;
	pawn->pos_on_road = 0;
	if (strcmp(pawn->player, "green") == 0)
	{
		pawn->x = board->base_coords[0][pawn->id - 1][0];
		pawn->y = board->base_coords[0][pawn->id - 1][1];
	}
	else if (strcmp(pawn->player, "yellow") == 0)
	{
		pawn->x = board->base_coords[1][pawn->id - 1][0];
		pawn->y = board->base_coords[1][pawn->id - 1][1];
	}
	else if (strcmp(pawn->player, "blue") == 0)
	{
		pawn->x = board->base_coords[2][pawn->id - 1][0];
		pawn->y = board->base_coords[2][pawn->id - 1][1];
	}
	else if (strcmp(pawn->player, "red") == 0)
	{
		pawn->x = board->base_coords[3][pawn->id - 1][0];
		pawn->y = board->base_coords[3][pawn->id - 1][1];
	}
	board->pawn_ptr[pawn->x][pawn->y][pawn->id - 1] = pawn;	//ustawianie wskaznika na zbity pionek w bazie
	board->how_many_pawns[pawn->x][pawn->y]++;	//inkrementacja ilosci pionkow na polu w bazie, na ktory wrocil pionek
	//rysowanie zbitego pionka w bazie
	draw_field(pawn->x, pawn->y, board, h, -1);
}

void beat_enemy_pawns(_pawn *pawn, _board *board, HANDLE h)
{
	for (int i = 0; i < 4; i++)
	{
		if (board->pawn_ptr[pawn->x][pawn->y][i] != NULL)
		{
			if (board->pawn_ptr[pawn->x][pawn->y][i]->color != pawn->color)	//porownuje po kolorach, bo czemu nie
			{
				return_to_base(board->pawn_ptr[pawn->x][pawn->y][i], board, h);	//RETURN COS NIE DZIALA
				board->pawn_ptr[pawn->x][pawn->y][i] = NULL;	//usuwanie wskaznika na pionek, ktory wlasnie wrocil do bazy
				board->how_many_pawns[pawn->x][pawn->y]--;	//dekrementacja ilosci pionkow na usunietym polu 
			}
		}
	}
}

void leave_the_base(int player, _pawn *pawn, _board *board, HANDLE h)
{
	board->how_many_pawns[pawn->x][pawn->y]--;
	board->pawn_ptr[pawn->x][pawn->y][return_index_of_pawn(pawn->x, pawn->y, pawn, board)] = NULL;
	int x = board->exit_coords[player][0];
	int y = board->exit_coords[player][1];
	int color = board->exit_coords[player][2];
	int i = which_is_null(x, y, board);
	board->pawn_ptr[x][y][i] = pawn;
	i = board->how_many_pawns[x][y];
	draw_square(pawn->x, pawn->y, color, h);	//usuwam pionka z bazy
	pawn->x = x;
	pawn->y = y;
	if (i > 0)
	{
		beat_enemy_pawns(pawn, board, h);
	}
	i = board->how_many_pawns[x][y];
	//rysuje go na polu wyjsciowym w zaleznosci od stanu tego pola (ilosci pionkow)
	int *temp = which_is_not_null(x, y, board);
	if (i == 0)
	{
		draw_pawn(x, y, color, h, pawn);
		board->pawns_on_that_field[x][y][i] = pawn;
	}
	else if (i == 1)
	{
		draw_2_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]]);
		board->pawns_on_that_field[x][y][i] = pawn;
	}
	else if (i == 2)
	{
		draw_3_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]]);
		board->pawns_on_that_field[x][y][i] = pawn;
	}
	else if (i == 3)
	{
		draw_4_pawns(x, y, 32, h, board->pawn_ptr[x][y][temp[0]], board->pawn_ptr[x][y][temp[1]], board->pawn_ptr[x][y][temp[2]], board->pawn_ptr[x][y][temp[3]]);
		board->pawns_on_that_field[x][y][i] = pawn;
	}

	board->how_many_pawns[x][y]++;
}

void move_pawn(_pawn *pawn, int dice, _board *board, HANDLE h, _pawn *pawns, _road *road)
{

	//sprawdzam, czy wybrany pionek znajduje sie w bazie !! dodac jeszcze sprawdzenie, czy dice ==6 !! + ewentualnie koordy baz w strukturze
	if (pawn->in_base == 1)
	{
		if (strcmp(pawn->player, "green") == 0)	//pionek gracza ZIELONY
		{
			leave_the_base(0, pawn, board, h, pawns);
		}
		else if (strcmp(pawn->player, "yellow") == 0)	//pionek gracza ZOLTY
		{
			leave_the_base(1, pawn, board, h, pawns);
		}
		else if (strcmp(pawn->player, "blue") == 0)	//pionek gracza NIEBIESKI
		{
			leave_the_base(2, pawn, board, h, pawns);
		}
		else if (strcmp(pawn->player, "red") == 0)	//pionek gracza CZERWONY
		{
			leave_the_base(3, pawn, board, h, pawns);
		}
		pawn->in_base = 0;
		pawn->pos_on_road = 1;
	}
	else
	{
		int temp = pawn->pos_on_road;		//zaczyna sie od 1, takze pod i kryje sie nastepne pole
		if (temp + dice > 44)
		{
			//Printf("You can't move that pawn!");
			//Sleep(1000);
			return;
		}
		for (int i = temp; i < (temp + dice); i++)
		{
			int x = road[i].x;
			int y = road[i].y;
			int empty = which_is_null(x, y, board);

			board->pawn_ptr[x][y][empty] = pawn;	//dodaje wskazik na nowego pionka dla pola dalej
			board->pawn_ptr[road[i - 1].x][road[i - 1].y][return_index_of_pawn(road[i - 1].x, road[i - 1].y, pawn, board)] = NULL;	//usuwam wskaznik na pionek ze starego pola, z ktorego odchodze
			board->how_many_pawns[road[i - 1].x][road[i - 1].y]--;	//dekrementacja ilosci piokow ze starego pola
			board->how_many_pawns[x][y]++;	//inkrementacja ilosci pionkow na nowym polu
			pawn->pos_on_road++;
			pawn->x = x;
			pawn->y = y;
			Sleep(20);
			if (i == (temp + dice - 1))
			{
				beat_enemy_pawns(pawn, board, h);
			}
			//rysowanie nowego pola
			draw_field(road[i].x, road[i].y, board, h, i + 1);
			//odtwarzanie starego pola
			draw_field(road[i - 1].x, road[i - 1].y, board, h, i);
		}
	}
	return;
}

//czysci tekst pod plansza
void clear_text(HANDLE h)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	gotoxy(0, 22, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 23, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 24, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 25, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 26, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 27, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, 28, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	return;
}

//zwraca numer pionka w tablicy [0-15]
_pawn *find_pawn_in_array(char *player, int id, _pawn *pawns)
{
	for (int i = 0; i < 16; i++)
	{
		if (strcmp(pawns[i].player, player) == 0)
		{
			if (pawns[i].id == id)
			{
				return &pawns[i];
			}
		}
	}
}

void prepare_green_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		road[0][j].y = 4;
		road[0][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[0][j].x = 4;
		road[0][j].y = i;
		j++;
	}
	road[0][j].y = 0;
	road[0][j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[0][j].x = 6;
		road[0][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[0][j].y = 4;
		road[0][j].x = i + 7;
		j++;
	}
	road[0][j].y = 5;
	road[0][j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[0][j].y = 6;
		road[0][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[0][j].x = 6;
		road[0][j].y = i;
		j++;
	}
	road[0][j].y = 10;
	road[0][j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[0][j].x = 4;
		road[0][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[0][j].y = 6;
		road[0][j].x = i;
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		road[0][j].y = 5;
		road[0][j].x = i;
		j++;
	}
}

void prepare_yellow_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		road[1][j].x = 6;
		road[1][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[1][j].y = 4;
		road[1][j].x = i + 7;
		j++;
	}
	road[1][j].y = 5;
	road[1][j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[1][j].y = 6;
		road[1][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[1][j].x = 6;
		road[1][j].y = i;
		j++;
	}
	road[1][j].y = 10;
	road[1][j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[1][j].x = 4;
		road[1][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[1][j].y = 6;
		road[1][j].x = i;
		j++;
	}
	road[1][j].y = 5;
	road[1][j].x = 0;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[1][j].y = 4;
		road[1][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[1][j].x = 4;
		road[1][j].y = i;
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		road[1][j].y = i;
		road[1][j].x = 5;
		j++;
	}
}

void prepare_blue_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 10; i >= 6; i--)
	{
		road[2][j].y = 6;
		road[2][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[2][j].x = 6;
		road[2][j].y = i;
		j++;
	}
	road[2][j].y = 10;
	road[2][j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[2][j].x = 4;
		road[2][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[2][j].y = 6;
		road[2][j].x = i;
		j++;
	}
	road[2][j].y = 5;
	road[2][j].x = 0;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[2][j].y = 4;
		road[2][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[2][j].x = 4;
		road[2][j].y = i;
		j++;
	}
	road[2][j].y = 0;
	road[2][j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[2][j].x = 6;
		road[2][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[2][j].y = 4;
		road[2][j].x = i + 7;
		j++;
	}
	for (i = 10; i > 5; i--)
	{
		road[2][j].y = 5;
		road[2][j].x = i;
		j++;
	}


}

void prepare_red_road(_road road[4][44])
{
	int i, j = 0;
	for (i = 10; i >= 6; i--)
	{
		road[3][j].x = 4;
		road[3][j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[3][j].y = 6;
		road[3][j].x = i;
		j++;
	}
	road[3][j].y = 5;
	road[3][j].x = 0;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[3][j].y = 4;
		road[3][j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[3][j].x = 4;
		road[3][j].y = i;
		j++;
	}
	road[3][j].y = 0;
	road[3][j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[3][j].x = 6;
		road[3][j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[3][j].y = 4;
		road[3][j].x = i + 7;
		j++;
	}
	road[3][j].y = 5;
	road[3][j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[3][j].y = 6;
		road[3][j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[3][j].x = 6;
		road[3][j].y = i;
		j++;
	}
	for (i = 10; i >= 6; i--)
	{
		road[3][j].y = i;
		road[3][j].x = 5;
		j++;
	}

}

//wypelniam NULLami
void prepare_board_of_ptr(_board *board)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				board->pawn_ptr[i][j][k] = NULL;
			}
		}
	}
}

int main()
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;	//watpliwa uzytecznosc
	 _board *board = malloc(sizeof*board);
	 _pawn pawns[16];
	//do przemyslenia, wyjatkowo ³opatologiczne
	_road roads[4][44];
	prepare_green_road(roads);
	prepare_yellow_road(roads);
	prepare_blue_road(roads);
	prepare_red_road(roads);

	prepare_board_of_ptr(board);


	_player players[4] = { "green", "yellow", "blue", "red" };

	draw_board(board, h, pawns);

	int pawn_nr;
	_pawn *pawn = (_pawn*)malloc(sizeof(_pawn));;
	int i = 0; //tymczasowo robi za ID graczy
	int moved,dice,moveable;

	while (1)		//glowna petla gry
	{
		if (i == 3)
		{
			i = 0;
		}
		else
		{
			i++;
		}

		moved = 0;
		moveable = 0;
		dice = throw_dice();

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 22, h);

		//printf("Dice: ");
		//scanf("%i", &dice);

		printf("\nDice: %i", dice);

		//printf("Player: ");
		//scanf("%i", &i);
		printf("\nPlayer: %s, dice: %i", players[i].name, dice);

		if (dice != 6)
		{
			for (int j = 0; j < 4; j++)
			{
				if (pawns[i * 4 + j].in_base == 0)
				{
					moveable = 1;
				}
			}
		}

		if (moveable==1 || dice ==6)
		{
			while (moved == 0)
			{
				pawn_nr = rand() % 4 + 1;
				printf("\nChoosed pawn: %i", pawn_nr);
				//scanf("%i", &pawn_nr);
				pawn = find_pawn_in_array(players[i].name, pawn_nr, pawns);
				if (pawn->in_base == 1 && dice != 6)
				{
					printf("You cant move that pawn!");
					continue;
				}
				move_pawn(pawn, dice, board, h, pawns, roads[i]);
				moved = 1;
			}
		}
		Sleep(100);
		clear_text(h);
	}
	//wypisywanie dostepnych kolorow z calego zakresu
	/*
	for (int i = 0; i < 256; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
		printf("%i. Kolor pod numerem: %i\n", i,i);
	}//*/
	getch();
	//system("pause");
	return 0;
}