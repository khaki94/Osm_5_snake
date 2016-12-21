/*
 * Player.h
 *
 *  Created on: 20.12.2016
 *      Author: admin
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

#include <vector>
#include "Sprite.h"
#include "Map.h"

class Player {
public:
	enum Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE
	};
	struct Point
	{
		Point(int _x, int _y): x(_x), y(_y) {};
		int x;
		int y;
	};

private:
	int speed;
	int size;
	unsigned long* graph;
	Direction dir;

//	std::vector<Point*> wsp;
	std::vector<Sprite*> sprites;

	// METODY
public:
	Player(unsigned long *_graph) : speed(0), size(16), graph(_graph), dir(RIGHT)
	{
//		Point *tmp = new Point(4,5);
//		wsp.push_back(tmp);
		sprites.push_back(new SnakeHead(4,5,graph));
	}

	virtual ~Player()
	{
		 std::vector<Sprite*>::iterator it;
		 for(it = sprites.begin(); it != sprites.end(); it++ )
		 {
			 delete *it;
		 }

	}
	int GetSize() { return size; }
	void Grow(int x, int y)
	{
		sprites.push_back(new SnakeHead(x,y,graph));
	}
	void Draw()
	{
		 std::vector<Sprite*>::iterator it;
		 for(it = sprites.begin(); it != sprites.end(); it++ )
		 {
			 (*it)->Draw();
		}
	}
	int GetX() { return sprites.front()->GetX(); }
	int GetY() { return sprites.front()->GetY(); }

	void CheckCollision()
	{

	}
	int GetSpeed() { return speed; }

	void Move(Direction _dir)
	{
		if( _dir != NONE)
			dir = _dir;
		switch(dir)
		{
		case(UP):
				MoveUp();
				break;
		case(LEFT):
				MoveLeft();
				break;
		case(DOWN):
				 MoveDown();
				break;
		case(RIGHT):
				MoveRight();
				break;
		case(NONE):
				// do nothing, but compliler is annoying with it warning;
				break;
		}
	}
private:
	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
};

#endif /* SRC_PLAYER_H_ */
