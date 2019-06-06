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
//czysci tekst pod plansza
void clear_text(int x,HANDLE h)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	gotoxy(0, x, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, x+1, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, x+2, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, x+3, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, x + 4, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	gotoxy(0, x + 5, h);
	printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	return;
}

int main()
{
	int pawn_nr;
	int i = 0;		//ID graczy
	int place=1;		//miejsce na "podium"
	int play=1;			//warunek zakonczenia gry
	int moved, dice;
	int num_of_players;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	int choice = ask_for_load(h);
	if (choice == 2)
	{
		num_of_players = load_players_from_file();
	}
	else
	{
		num_of_players = ask_for_players(h);
	}

	_board *board = malloc(sizeof(_board));
	_pawn *pawns = malloc((num_of_players*4) * sizeof(_pawn));
	_player *players = malloc(num_of_players * sizeof(_player));

	prepare_bases(board, pawns, num_of_players);
	init_players(players, num_of_players);

	init_board(board, num_of_players);
	draw_board(board, h);

	if (choice == 2)
	{
		load_from_file(pawns, board,players,h);
	}

	while (play)		//glowna petla gry
	{
		//save_to_file(pawns,players,num_of_players);		//SAVE
		if (players[i].place != 0)
		{
			i++;
			if (i == num_of_players - 1)
				i = 0;
			continue;
		}

		moved = 0;
		dice = throw_dice();
		int manual = 0;								//MANUAL

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 22, h);

		if (manual == 1)
		{
			printf("Dice: ");
			scanf("%i", &dice);
			printf("Player: ");
			scanf("%i", &i);
		}
		printf("Dice: %i", dice);
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
			printf("Choosed pawn: %i", pawn_nr);
			if (moveable(&players[i], dice, pawns,board) == 0)
			{
				clear_text(22, h);
				break;
			}
			moved = move_pawn(&pawns[4 * i + pawn_nr - 1], dice, board, h, pawns, &players[i]);
		}
		Sleep(100);

		//sprawdzam, czy rozpatrywany gracz juz wygral
		if (check_if_won(&players[i], pawns) == 1 && players[i].place==0)
		{
			play = endgame(&players[i], &place, num_of_players);
		}
		i++;
		//warunek zapetlania sie ID graczy
		if (i == num_of_players)
		{
			i = 0;
		}

		//debug
		/*
		for (int i = 0; i < 56; i++)
		{
			gotoxy(50, i, h);
			printf("Road[%i]x,y,pawn = %i, %i, %p", i, board->road[i].x, board->road[i].y, board->road[i].pawns);
		}*/
	}
	place_for_last_player(players, num_of_players);
	show_score(players, h, num_of_players);
	free(pawns);
	free(board);
	free(players);
	_getch();
	return 0;
}