#include "List_of_pawns.h"

void pop_front(_pawn **head)
{
	_pawn * temp = (*head);
	if (*head != NULL)
	{
		(*head) = (*head)->next;
		temp = NULL;
	}
}

void pop_by_index(_pawn **head, int position)
{
	if (position == 0)
	{
		pop_front(head);
	}
	else
	{
		_pawn *current = *head;
		_pawn *temp;
		int i = 0;
		while (current->next != NULL && i < position - 1)
		{
			current = current->next;
			i++;
		}
		temp = current->next;
		current->next = temp->next;
		temp = NULL;
	}
}

void push_back(_pawn **head, _pawn *pawn)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	_pawn *temp = pawn;
	pawn->next = NULL;
	if (*head == NULL)
	{
		*head = temp;
	}
	else
	{
		_pawn *current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = temp;
	}
}

int position_in_list(_pawn **head, _pawn *pawn)
{
	_pawn *temp = (*head);
	int i = 0;
	while (temp)
	{
		if ((temp->id == pawn->id) && (temp->player == pawn->player))
		{
			return i;
		}
		i++;
		temp = temp->next;
	}
	return 0;
}
