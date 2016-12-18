/*
 * Map.h
 *
 *  Created on: 18.12.2016
 *      Author: admin
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include "main.h"
#include "peripherals.h"

class Map {
private:
	int height;
	int width;
enum Area
{
	WALL,
	EMPTY
};
Area **map;
public:
	Map();
	virtual ~Map();
	void Square(unsigned long*);
	void DrawMap(unsigned long*);
};

#endif /* SRC_MAP_H_ */
