/*
 * Map.h
 *
 *  Created on: 18.12.2016
 *      Author: admin
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "peripherals.h"
#include "Sprite.h"
#include <fstream>
#include <string>
#include <ctime>

class Map {
public:
	enum Area
	{
		WALL,
		FOOD,
		BACKGROUND
	};
private:
	int height;
	int width;
	unsigned long * graph;

Area **map;
Sprite ***sprite;
bool isFood;
int foodX,foodY;
public:
	Map(unsigned long*);
	virtual ~Map();
	void Square();
	void DrawMap();
	void LoadLevel(std::string name);
	void UpdateSprite(bool);
	void SetFood();
	void EatFood() { isFood = false; map[foodY][foodX] = BACKGROUND; }
    Area GetCollision(int y, int x);
    void GameOver();
    void Reset() { map[foodY][foodX] = BACKGROUND; isFood = false;}
};

#endif /* SRC_MAP_H_ */
