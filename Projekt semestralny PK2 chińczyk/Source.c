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

void save_to_file(_pawn * pawn)
{
	FILE *fp; /* u¿ywamy metody wysokopoziomowej - musimy mieæ zatem identyfikator pliku, uwaga na gwiazdkê! */
	if ((fp = fopen("save.txt", "w")) == NULL) {
		printf("Can not open file!\n");
		return;
	}
	for (int i = 0; i < 16; i++)
	{
		fprintf(fp, "Pawn: %i\n", pawn[i].id + (4* pawn[i].player));
		fprintf(fp, "%i\n", pawn[i].id);
		fprintf(fp, "%i\n", pawn[i].player);
		fprintf(fp, "%i\n", pawn[i].color);
		fprintf(fp, "%i\n", pawn[i].in_base);
		fprintf(fp, "%i\n", pawn[i].pos_on_road);
		fprintf(fp, "%i\n", pawn[i].x);
		fprintf(fp, "%i\n", pawn[i].y);
		fprintf(fp, "\n");
	}
	fclose(fp);
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
	prepare_green_road(board->road);

	//prepare_board_of_ptr(board);

	_player players[4] = { "green", "yellow", "blue", "red" };
	strcpy(players[0].name, "green");
	strcpy(players[1].name, "yellow");
	strcpy(players[2].name, "blue");
	strcpy(players[3].name, "red");
	players[0].begin = 1;
	players[1].begin = 11;
	players[2].begin = 21;
	players[3].begin = 31;

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

		save_to_file(pawns);

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
				pawn_nr = choose_pawn(&players[i], dice, board, pawns);
				printf("\nChoosed pawn: %i", pawn_nr);
				//scanf("%i", &pawn_nr);
				if (pawns[4*i+pawn_nr-1].in_base == 1 && dice > 6)
				{
					printf("You cant move that pawn!");
					continue;
				}
				move_pawn(&pawns[4*i + pawn_nr-1], dice, board, h, pawns,players[i]);
				moved = 1;
			}
		}
		Sleep(100);
		clear_text(h);
	}
	return 0;
}