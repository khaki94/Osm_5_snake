/*
 * Sprite.h
 *
 *  Created on: 18.12.2016
 *      Author: admin
 */

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include "peripherals.h"

class Sprite {
protected:
	enum Color
	{
		BLACK = 0x000000,
		BLUE = 0x0000FF,
		GREEN = 0x00FF00,
		CYAN = 0x00FFFF,
		RED = 0xFF0000,
		PURPLE = 0xFF00FF,
		YELLOW = 0xFFFF00,
		WHITE = 0x0FFFFFF
	};
	int x,y;   // punkt poczatkowy kazdego sprite( gorny, prawy rog)
	Color color;  // kolor figury
	unsigned long * graph;  // wskaznik do ekranu

public:
	virtual void Draw() = 0;
	Sprite(unsigned long * _graph);
	Sprite(int _x, int _y, unsigned long * _graph);
	virtual ~Sprite();
	int GetX() { return x; }
	int GetY() { return y; }
};

class Background : public Sprite
{
	const int size;
public:
	Background(unsigned long * _graph);
	Background(int _x, int _y,unsigned long * _graph);
	virtual ~Background();
	void Draw();
};



class Wall : public Sprite
{
	const int size;
public:
	Wall(unsigned long * _graph);
	Wall(int _x, int _y,unsigned long * _graph);
	virtual ~Wall();
	void Draw();
};

class Food : public Sprite
{
	const int radius;
public:
	Food(unsigned long * _graph);
	Food(int _x, int _y,unsigned long * _graph);
	virtual ~Food();
	void Draw();
};

class SnakeHead : public Sprite
{
	const int size;
public:
	SnakeHead(unsigned long * _graph);
	SnakeHead(int _x, int _y,unsigned long * _graph);
	virtual ~SnakeHead();
	void Draw();
};

class SnakeTail : public Sprite
{
	const int size;
public:
	SnakeTail(unsigned long * _graph);
	SnakeTail(int _x, int _y,unsigned long * _graph);
	virtual ~SnakeTail();
	void Draw();
};
#endif /* SRC_SPRITE_H_ */
