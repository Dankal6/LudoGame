#include "Roads.h"

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
