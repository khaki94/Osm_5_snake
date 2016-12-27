/*
 * Player.cpp
 *
 *  Created on: 21.12.2016
 *      Author: admin
 */
#include "Player.h"

Player::Player(unsigned long *_graph) : speed(0), size(16), graph(_graph), dir(RIGHT)
{
//		Point *tmp = new Point(4,5);
//		wsp.push_back(tmp);
	sprites.push_back(new SnakeHead(8,8,graph));
	sprites.push_back(new SnakeTail(7,8,graph));
	sprites.push_back(new SnakeTail(6,8,graph));
	sprites.push_back(new SnakeTail(5,8,graph));
}

Player::~Player()
{
	std::vector<Sprite*>::iterator it;
	for(it = sprites.begin(); it != sprites.end(); it++ )
	{
		delete *it;
	}

}
void Player::Grow(int x, int y)
{
	sprites.push_back(new SnakeHead(x,y,graph));
}
void Player::Draw()
{
	std::vector<Sprite*>::iterator it;
	for(it = sprites.begin(); it != sprites.end(); it++ )
	{
		(*it)->Draw();
	}
}
void Player::CheckCollision()
{
	// sprawdza kolizje
}

void Player::Move(Direction _dir)
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
		// do nothing, but compliler is annoying with warnings;
		break;
	}
}

void Player::MoveUp()
{
	//if()
}
void Player::MoveLeft()
{

}
void Player::MoveDown()
{

}
void Player::MoveRight()
{

}


