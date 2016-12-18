/*
 * Map.cpp
 *
 *  Created on: 18.12.2016
 *      Author: admin
 */

#include "Map.h"

Map::Map(): height(32), width(24)
{
	map = new Area *[height];
	for( int i = 0; i < height; i++)
	{
		map[i] = new Area[width];
	}
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			if( (x*y == 0) || (y == (height-1)) || (x = (width-1))  )
				map[y][x] = WALL;
			else
				map[y][x] = EMPTY;
		}
	//GRAPH = SCREENBUF;
}

Map::~Map()
{
	for( int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

void Map::Square(unsigned long *graph)
{
	static int i = 0;
	for(int x = 0; x < 20;x++)
		for(int y = 0; y < 20; y++)
			SetPixel(graph,x+(20*i),y,0xFFF);
	if( i++ > 31)
		i = 0;
}

void Map::DrawMap(unsigned long *graph)
{
	for(int y = 0; y <height; y++)
		for(int x = 0; x < width; x++)
		{
			if(map[y][x] == WALL)
				int a; //square.Draw();
			else
				continue;
		}
}

