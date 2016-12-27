/*
 * Player.cpp
 *
 *  Created on: 21.12.2016
 *      Author: admin
 */
#include "Player.h"

Player::Player(unsigned long *_graph, Map *_map) : speed(0), size(0), graph(_graph), dir(RIGHT)
{
	map = _map;
//		Point *tmp = new Point(4,5);
//		wsp.push_back(tmp);
	sprites.push_back(new SnakeHead(8,8,graph));
	sprites.push_back(new SnakeTail(7,8,graph));
	sprites.push_back(new SnakeTail(6,8,graph));
	sprites.push_back(new SnakeTail(5,8,graph));

	size = sprites.size();

	x = sprites.front()->GetX();
	y = sprites.front()->GetY();
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
	x = sprites.front()->GetX();
	y = sprites.front()->GetY();

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
	if(map->GetCollision(y-1,x) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetY(sprites.front()->GetY()-1);
	}
	else if(map->GetCollision(y-1,x) == Map::WALL)
	{

	}
	else if(map->GetCollision(y-1,x) == Map::FOOD)
	{
		Grow(sprites.front()->GetX(),sprites.front()->GetY());
		sprites.front()->SetY(sprites.front()->GetY()-1);
	}
}
void Player::MoveLeft()
{
	if(map->GetCollision(y,x-1) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetX(sprites.front()->GetX()-1);
	}
	else if(map->GetCollision(y,x-1) == Map::WALL)
	{

	}
	else if(map->GetCollision(y,x-1) == Map::FOOD)
	{
		Grow(sprites.front()->GetX(),sprites.front()->GetX());
		sprites.front()->SetX(sprites.front()->GetX()-1);
	}
}
void Player::MoveDown()
{
	if(map->GetCollision(y+1,x) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetY(sprites.front()->GetY()+1);
	}
	else if(map->GetCollision(y+1,x) == Map::WALL)
	{

	}
	else if(map->GetCollision(y+1,x) == Map::FOOD)
	{
		Grow(sprites.front()->GetY(),sprites.front()->GetY());
		sprites.front()->SetY(sprites.front()->GetY()+1);
	}
}
void Player::MoveRight()
{
	if(map->GetCollision(y,x+1) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetX(sprites.front()->GetX()+1);
	}
	else if(map->GetCollision(y,x+1) == Map::WALL)
	{

	}
	else if(map->GetCollision(y,x+1) == Map::FOOD)
	{
		Grow(sprites.front()->GetX(),sprites.front()->GetX());
		sprites.front()->SetX(sprites.front()->GetX()+1);
	}
}

void Player::Move()
{
	int x = sprites.front()->GetX();
	int y = sprites.front()->GetY();
	for( int i = 1; i < size; i++)
	{
//		sprites.push_back(new SnakeHead(sprites.front()->GetX(),sprites.front()->GetY(),graph));
		int tmpX = sprites[i]->GetX();
		int tmpY = sprites[i]->GetY();
		sprites[i]->SetX(x);//(new SnakeHead(,sprites.front()->GetY(),graph));
		sprites[i]->SetY(y);
		x = tmpX;
		y = tmpY;
	}
}


