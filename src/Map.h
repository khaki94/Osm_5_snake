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

class Map {
public:
enum Walk
{
	GO_FORWARD,
	GO_LEFT,
	GO_RIGHT
};
private:
	int height;
	int width;
	int playerX, playerY;
	unsigned long * graph;
enum Area
{
	WALL,
	FOOD,
	SNAKE_HEAD,
	SNAKE_TAIL,
	BACKGROUND
};
enum Direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,

};
Direction dir;
Area **map;
Sprite ***sprite;
public:
	Map(unsigned long*);
	virtual ~Map();
	void Square();
	void DrawMap();
	void LoadLevel(std::string name);
	void UpdateMap(Walk);
	void UpdateSprite();
private:
	void Move();
	void MoveDown();
	void MoveUp();
	void MoveLeft();
	void MoveRight();
};

#endif /* SRC_MAP_H_ */
