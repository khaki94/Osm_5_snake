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

	LoadLevel("level1.txt");

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

void Map::LoadLevel(std::string name)
{
	std::fstream file;
	int tmp;
	file.open(name.c_str(), std::ios::in);
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			file >> tmp;
			if( tmp == 0)
				map[y][x] = BACKGROUND;
			else if( tmp == 1)
				map[y][x] = WALL;

			}
	file.close();
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

