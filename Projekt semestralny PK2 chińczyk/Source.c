#include "Structures.h"
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
	gotoxy(0, x, h);
	return;
}

void init_game(_board **board, _pawn **pawns, _player **players, HANDLE h)
{
	(*board) = malloc(sizeof(_board));
	int choice = ask_for_load(h);
	if (choice == 2)
	{
		(*board)->num_of_players = load_players_from_file();
	}
	else
	{
		(*board)->num_of_players = ask_for_players(h);
	}
	(*pawns)= malloc(((*board)->num_of_players * 4) * sizeof(_pawn));
	(*players) = malloc((*board)->num_of_players * sizeof(_player));
	prepare_bases((*board), (*pawns), (*board)->num_of_players);
	init_players((*players), (*board)->num_of_players);
	init_board((*board), (*board)->num_of_players);

	if (choice == 2)
	{
		load_from_file((*pawns), (*board), (*players), h);
	}
	else
	{
		ask_for_AI_players((*players), h, (*board)->num_of_players);
	}
}

int main()
{
	int pawn_nr;
	int i = 0;		//ID graczy
	int place=1;		//miejsce na "podium"
	int play=1;			//warunek zakonczenia gry
	int moved, dice;

	//int choice=0;
	int autodice;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);

	_board *board;
	_pawn *pawns;
	_player *players;

	/*board = malloc(sizeof(_board));
	int choice = ask_for_load(h);
	if (choice == 2)
	{
		board->num_of_players = load_players_from_file();
	}
	else
	{
		board->num_of_players = ask_for_players(h);
	}
	pawns = malloc((board->num_of_players * 4) * sizeof(_pawn));
	players = malloc(board->num_of_players * sizeof(_player));
	prepare_bases(board, pawns, board->num_of_players);
	init_players(players, board->num_of_players);
	init_board(board, board->num_of_players);

	if (choice == 2)
	{
		load_from_file(pawns, board, players, h);
	}
	else
	{
		ask_for_AI_players(players, h, board->num_of_players);
	}*/

	init_game(&board,&pawns,&players,h);
	autodice = ask_for_auto_dice(h);
	draw_board(board, h);



	while (play)		//glowna petla gry
	{
		save_to_file(pawns,players, board->num_of_players);		//SAVE

		if (players[i].place != 0)	//mechanizm pomijania w kolejce graczy, ktorzy zakonczyli rozgrywke (4 pionki w bazie)
		{
			i++;
			if (i == board->num_of_players - 1)
				i = 0;
			continue;
		}

		moved = 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		clear_text(22, h);
		gotoxy(0, 22, h);
		printf("Player: ");
		scanf("%i", &i);

		clear_text(22, h);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(0, 22, h);

		if (autodice == 0)
		{
			printf("Dice: ");
			scanf("%i", &dice);
		}
		else
		{
			dice = throw_dice();
		}
		printf("\nPlayer: %s, dice: %i", players[i].name, dice);

		while (moved == 0)
		{
			if (players[i].AI == 1)
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
			clear_text(22, h);
		}
		Sleep(100);
		//sprawdzam, czy rozpatrywany gracz juz wygral
		if (check_if_won(&players[i], pawns) == 1 && players[i].place==0)
		{
			play = endgame(&players[i], &place, board->num_of_players);
		}
		i++;
		//warunek zapetlania sie ID graczy
		if (i == board->num_of_players)
		{
			i = 0;
		}
	}
	place_for_last_player(players, board->num_of_players);
	show_score(players, h, board->num_of_players);
	free(pawns);
	free(board);
	free(players);
	_getch();
	return 0;
}