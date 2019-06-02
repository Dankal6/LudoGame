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
	FILE *fp;
	if ((fp = fopen("save.txt", "w")) == NULL) {
		printf("Can not open file!\n");
		return;
	}
	for (int i = 0; i < 16; i++)
	{
		//fprintf(fp, "Pawn: %i\n", pawn[i].id + (4* pawn[i].player));
		fprintf(fp, "%i\n", pawn[i].id);
		fprintf(fp, "%i\n", pawn[i].player);
		fprintf(fp, "%i\n", pawn[i].color);
		fprintf(fp, "%i\n", pawn[i].in_base);
		fprintf(fp, "%i\n", pawn[i].pos_on_road);
		fprintf(fp, "%i\n", pawn[i].x);
		fprintf(fp, "%i\n", pawn[i].y);
	}
	fclose(fp);
}

void load_from_file(_pawn *pawn, _board *board)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			board->bases[i][j].how_many_pawns = 0;
			pop_front(&board->bases[i][j].pawns);
		}
	}
	FILE *fp;
	if ((fp = fopen("save.txt", "r")) == NULL) {
		printf("Can not open file!\n");
		return;
	}
	for (int i = 0; i < 16; i++)
	{
		//fprintf(fp, "Pawn: %i\n", pawn[i].id + (4* pawn[i].player));
		fscanf(fp, "%i", &pawn[i].id);
		fscanf(fp, "%i", &pawn[i].player);
		fscanf(fp, "%i", &pawn[i].color);
		fscanf(fp, "%i", &pawn[i].in_base);
		fscanf(fp, "%i", &pawn[i].pos_on_road);
		fscanf(fp, "%i", &pawn[i].x);
		fscanf(fp, "%i", &pawn[i].y);
		if (pawn[i].pos_on_road == 0)
		{
			push_back(&board->bases[pawn[i].player][pawn[i].id - 1].pawns, &pawn[i]);		//ustawiam wskaznik na pionka w bazie
			board->bases[pawn[i].player][pawn[i].id - 1].how_many_pawns = 1;
		}
		else
		{
			push_back(&board->road[pawn[i].pos_on_road].pawns, &pawn[i]);		//ustawiam wskaznik na pionka w trasie
			board->road[pawn[i].pos_on_road].how_many_pawns++;
		}
	}
	fclose(fp);
}

int main()
{
	int pawn_nr;
	int i = 0;		//ID graczy
	int moved, dice;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	_pawn pawns[16];
	_board *board = malloc(sizeof(_board));
	_player players[4];


	prepare_road(board->road);
	init(players);

	init_board(board);
	prepare_bases(board, pawns);
	draw_bases(board, h);
	prepare_goals(board);
	draw_goals(board, h);
	prepare_road(board->road);
	draw_road(board->road,h);

	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//ustawia kolor na czarne tlo i biala czcionke
	printf("1. Play.\n2. Load from file.\nChoice: ");
	scanf("%i", &choice);
	if (choice == 2)
	{
		load_from_file(pawns, board);
		for (int i = 0; i < 40; i++)
		{
			draw_field(board->road[i], board, h, i);
		}
		for (i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				draw_field(board->bases[i][j], board, h, -1);
			}
		}
	}

	while (1)		//glowna petla gry
	{
		//save_to_file(pawns);		//SAVE

		moved = 0;
		dice = throw_dice();
		int manual = 0;								//MANUAL

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 22, h);

		/*printf("Dice: ");
		scanf("%i", &dice);*/

		if (manual == 1)
		{
			printf("Dice: ");
			scanf("%i", &dice);
			printf("\nPlayer: ");
			scanf("%i", &i);
		}
		printf("\nDice: %i", dice);
		printf(", random move: %i", players[i].random);
		printf("\nPlayer: %s, dice: %i", players[i].name, dice);


		while (moved == 0)
		{
			if (manual == 0)
			{
				pawn_nr = choose_pawn(&players[i], dice, board, pawns);
			}
			else
			{
				printf("\nPawn: ");
				scanf("%i", &pawn_nr);
			}
			gotoxy(0, 24, h);
			printf("\nChoosed pawn: %i", pawn_nr);
			if (moveable(&players[i], dice, pawns) == 0)
			{
				break;
			}
			moved = move_pawn(&pawns[4 * i + pawn_nr - 1], dice, board, h, pawns, &players[i]);
		}

		//debug
		/*
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		for (int i = 0; i < 11; i++)
		{
			gotoxy(50, i, h);
			printf("aaaaaaaaaaaaaaaaa");
		}
		for (int j = 0; j < 16; j++)
		{
			gotoxy(50 + pawns[j].x, pawns[j].y, h);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), pawns[j].color);
			printf("%i", pawns[j].id);
		}
		*/
		Sleep(100);
		clear_text(h);

		//warunek zapetlania sie ID graczy
		if (i == 3)
		{
			i = 0;
		}
		else
		{
			i++;
		}
		if (check_if_won(&players[i], pawns) == 1)
		{
			continue;
		}
	}
	free(board);
	return 0;
}