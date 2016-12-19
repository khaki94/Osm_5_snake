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
private:
	int height;
	int width;
	unsigned long * graph;
enum Area
{
	WALL,
	FOOD,
	SNAKE_HEAD,
	SNAKE_TAIL,
	BACKGROUND
};
Area **map;
Sprite ***sprite;
public:
	Map(unsigned long*);
	virtual ~Map();
	void Square();
	void DrawMap();
	void LoadLevel(std::string name);
	void UpdateMap();
	void UpdateSprite();
};

#endif /* SRC_MAP_H_ */
