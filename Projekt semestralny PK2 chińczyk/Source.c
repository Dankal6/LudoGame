#include "Header.h"
//34,32 - ZIELONY ; 102,96 ZOLTY ; 68,64 CZERWONY ; 17,16 NIEBIESKI

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

int throw_dice()
{
	srand(time(NULL));
	int dice = ((rand() % 6) + 1);
	return dice;
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

int main()
{
	int pawn_nr;
	int i = 0; //tymczasowo robi za ID graczy
	int moved, dice, moveable;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
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
	strcpy(players[0].name, "green");
	strcpy(players[1].name, "yellow");
	strcpy(players[2].name, "blue");
	strcpy(players[3].name, "red");
	for (int i = 0; i < 4; i++)
	{
		players[i].id = i;
		players[i].random = 0;
	}

	draw_board(board, h, pawns);

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
		printf(", random move: %i", players[i].random);

		//printf("Player: ");
		//scanf("%i", &i);
		printf("\nPlayer: %s, dice: %i", players[i].name, dice);

		if (dice != 7)
		{
			for (int j = 0; j < 4; j++)
			{
				if (pawns[i * 4 + j].in_base == 0)
				{
					moveable = 1;
				}
			}
		}

		if (moveable==1 || dice <=6)
		{
			while (moved == 0)
			{
				pawn_nr = choose_pawn(&players[i], dice, board, pawns, roads);
				printf("\nChoosed pawn: %i", pawn_nr);
				//scanf("%i", &pawn_nr);
				if (pawns[4*i+pawn_nr-1].in_base == 1 && dice > 6)
				{
					printf("You cant move that pawn!");
					continue;
				}
				move_pawn(&pawns[4*i + pawn_nr-1], dice, board, h, pawns, roads[i]);
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