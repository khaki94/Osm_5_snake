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

	std::vector<Sprite*> sprites;

	// METODY
public:
	Player(unsigned long *_graph);
	virtual ~Player();
	int GetSize() { return size; }
	void Grow(int x, int y);
	void Draw();
	int GetX() { return sprites.front()->GetX(); }
	int GetY() { return sprites.front()->GetY(); }

	void CheckCollision();
	int GetSpeed() { return speed; }

	void Move(Direction _dir);

private:
	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
};

#endif /* SRC_PLAYER_H_ */
