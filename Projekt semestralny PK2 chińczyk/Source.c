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
void clear_text(int x,int y,HANDLE h)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
	for (int i = 0; i < y; i++)
	{
		gotoxy(0, x+i, h);
		printf("aaaaaaaaaaaaaaaaa/taaaaaaaaaaaaaaaaaaaaa");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(0, x, h);
	return;
}

void init_game(_board **board, _pawn **pawns, _player **players, HANDLE h, char* argv)
{
	(*board) = malloc(sizeof(_board));
	int choice = atoi(argv);

	if (choice == 2)
	{
		(*board)->num_of_players = load_players_from_file();
	}
	else if(choice ==1)
	{
		(*board)->num_of_players = ask_for_players(h);
	}
	else
	{
		printf("\nIncorrect value! (1 or 2)");
		Sleep(1000);
		exit(0);
	}
	(*pawns)= malloc(((*board)->num_of_players * 4) * sizeof(_pawn));
	(*players) = malloc(((*board)->num_of_players) * sizeof(_player));
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

int get_number_from_user(int a, int b)
{
	int correct = -1;
	int num;
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &cbsi);
	cbsi.dwCursorPosition;
	
	while(correct=-1)
	{
		fseek(stdin, 0, SEEK_END);

		scanf("%i", &num);
		if (num >= a && num <= b)
		{
			clear_text(cbsi.dwCursorPosition.Y + 1, 1, h);
			return num;
		}
		else
		{
			clear_text(cbsi.dwCursorPosition.Y + 1, 1, h);
			gotoxy(0, cbsi.dwCursorPosition.Y, h);
			printf("\nIncorrect value! Try again: ");
		}
	}
}

void move(int *moved, int i, _player *players, int dice, _pawn *pawns, _board *board)
{
	int pawn_nr;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	while ((*moved) == 0)
	{
		if (moveable(&players[i], dice, pawns, board) == 0)
		{
			printf("\nNo move to make!");
			//Sleep(1000);
			clear_text(22, 4, h);
			break;
		}
		if (players[i].AI == 1)
		{
			pawn_nr = choose_pawn(&players[i], dice, board, pawns);
		}
		else
		{
			printf("Pawn: ");
			pawn_nr = get_number_from_user(1, 4);
		}
		printf("Choosed pawn: %i", pawn_nr);
		(*moved) = move_pawn(&pawns[4 * i + pawn_nr - 1], dice, board, h, &players[i]);
		if ((*moved) == 0)
		{
			gotoxy(0, 25, h);
			printf("You can't move that pawn!");
		}
		//Sleep(1000);
		clear_text(22, 4, h);
	}
	Sleep(100);
}

void game(_pawn *pawns, _player *players, _board *board, int autodice)
{
	int moved, dice, pawn_nr;;
	int i = 0;		//ID graczy
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int place = 1;		//miejsce na "podium"
	int play = 1;			//warunek zakonczenia gry

	while (play)		//glowna petla gry
	{
		save_to_file(pawns, players, board->num_of_players);		//SAVE

		if (players[i].place != 0)	//mechanizm pomijania w kolejce graczy, ktorzy zakonczyli rozgrywke (4 pionki w bazie)
		{
			if (i == board->num_of_players - 1)
				i = 0;
			else
				i++;
			continue;
		}

		moved = 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		clear_text(22, 1, h);
		if (autodice == 0)
		{
			printf("Dice: ");
			dice = get_number_from_user(1, 6);
		}
		else
		{
			dice = throw_dice();
		}
		printf("Player: %s, dice: %i\n", players[i].name, dice);
		move(&moved, i, players, dice, pawns, board);
		//sprawdzam, czy rozpatrywany gracz juz wygral
		if (check_if_won(&players[i], pawns) == 1 && players[i].place == 0)
		{
			play = endgame(&players[i], &place, board->num_of_players);
		}
		i++;
		if (moved == 2)
		{
			i--;
		}
		//warunek zapetlania sie ID graczy
		if (i == board->num_of_players)
		{
			i = 0;
		}
	}
	printf("\nGAME OVER");
}



int main(int argc, char* argv[])
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int autodice;

	_board *board;
	_pawn *pawns;
	_player *players;

	init_game(&board,&pawns,&players,h, argv[1]);
	autodice = ask_for_auto_dice(h);
	draw_board(board, h);
	game(pawns, players, board, autodice);
	place_for_last_player(players, board->num_of_players);
	show_score(players, h, board->num_of_players);
	free(pawns);
	free(board);
	free(players);
	_getch();
	return 0;
}