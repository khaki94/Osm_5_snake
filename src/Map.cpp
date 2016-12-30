/*
 * Map.cpp
 *
 *  Created on: 18.12.2016
 *      Author: admin
 */

#include "Map.h"

Map::Map(unsigned long *_graph): height(30), width(40), graph(_graph), isFood(false)
{
	// tworzenie Area
	map = new Area *[height];
	for( int i = 0; i < height; i++)
	{
		map[i] = new Area[width];
	}

	// Wczytanie mapy kafelkowej
	LoadLevel("level1.txt");

	// tworzenie sprite'ow
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
			else if (map[y][x] == BACKGROUND)
				sprite[y][x] = new Background(x,y,graph);
			else if (map[y][x] == FOOD)
				sprite[y][x] = new Food(x,y,graph);
		}
}
Map::~Map()
{
	for( int i = 0; i < height; i++)
	{
		delete[] map[i];
	}
	delete[] map;

	for( int i = 0; i < height; i++)
	{
		for( int x = 0; x < width; x++)
			delete sprite[i][x];
		delete[] sprite[i];
	}
	delete[] sprite;

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
			else if( tmp == 2)
				map[y][x] = FOOD;
		}
	file.close();
}

void Map::DrawMap()
{
	for(int y = 0; y <height; y++)
		for(int x = 0; x < width; x++)
		{
			sprite[y][x]->Draw();
		}
}

void Map::UpdateSprite(bool gameOver)
{
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			delete sprite[y][x];
			if(!gameOver)
			{
				sprite[y][x] = new Wall(x,y,graph);
				continue;
			}
			if(map[y][x] == WALL)
				sprite[y][x] = new Wall(x,y,graph);
			else if (map[y][x] == BACKGROUND)
				sprite[y][x] = new Background(x,y,graph);
			else if (map[y][x] == FOOD)
				sprite[y][x] = new Food(x,y,graph);
		}
}

Map::Area Map::GetCollision(int y, int x)
{
	return map[y][x];
}

void Map::SetFood()
{
	if(!isFood)
	{
		do
		{
			foodX = (time(NULL)%60 + foodY)%38+1;
			foodY = (time(NULL)%40 + foodX)%26+3;
		}while(GetCollision(foodY,foodX) != BACKGROUND);
		map[foodY][foodX] = FOOD;
		isFood = true;
	}
}
