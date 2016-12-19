/*
 * Map.cpp
 *
 *  Created on: 18.12.2016
 *      Author: admin
 */

#include "Map.h"

Map::Map(unsigned long *_graph): height(30), width(40), graph(_graph)
{
	map = new Area *[height];
	for( int i = 0; i < height; i++)
	{
		map[i] = new Area[width];
	}
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			if( (x*y == 0) || (y == (height-1)) || (x == (width-1))  )
				map[y][x] = WALL;
			else
				map[y][x] = BACKGROUND;
		}

	sprite = new Sprite **[height];
	for( int i = 0; i < height; i++)
	{
		sprite[i] = new Sprite *[width];
	}
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			if(map[y][x] == WALL)
				sprite[y][x] = new Wall(x,y,graph);
			else
				sprite[y][x] = new Background(x,y,graph);
		}
}

Map::~Map()
{
	for( int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

void Map::DrawMap()
{
//	Sprite *sprite = new Background(10,10,graph);
//	sprite->Draw();
	for(int y = 0; y <height; y++)
		for(int x = 0; x < width; x++)
		{
			sprite[y][x]->Draw();
		}
}

