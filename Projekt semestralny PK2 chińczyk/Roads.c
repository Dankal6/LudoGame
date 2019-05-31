#include "Roads.h"

void prepare_green_road(_field road[40])
{
	int i, j = 0;
	for (i = 0; i < 5; i++)
	{
		road[j].y = 4;
		road[j].x = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[j].x = 4;
		road[j].y = i;
		j++;
	}
	road[j].y = 0;
	road[j].x = 5;
	j++;
	for (i = 0; i < 5; i++)
	{
		road[j].x = 6;
		road[j].y = i;
		j++;
	}
	for (i = 0; i < 4; i++)
	{
		road[j].y = 4;
		road[j].x = i + 7;
		j++;
	}
	road[j].y = 5;
	road[j].x = 10;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[j].y = 6;
		road[j].x = i;
		j++;
	}
	for (i = 7; i < 11; i++)
	{
		road[j].x = 6;
		road[j].y = i;
		j++;
	}
	road[j].y = 10;
	road[j].x = 5;
	j++;
	for (i = 10; i >= 6; i--)
	{
		road[j].x = 4;
		road[j].y = i;
		j++;
	}
	for (i = 3; i >= 0; i--)
	{
		road[j].y = 6;
		road[j].x = i;
		j++;
	}
	for (int i = 0; i < 5; i++)
	{
		road[j].y = 5;
		road[j].x = i;
		j++;
	}
	for (j = 0; j < 40; j++)
	{
		road[j].pawns = NULL;
	}
}

