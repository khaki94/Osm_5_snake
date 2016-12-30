/*
 * Player.cpp
 *
 *  Created on: 21.12.2016
 *      Author: admin
 */
#include "Player.h"

Player::Player(unsigned long *_graph, Map *_map) : speed(0), size(0), graph(_graph), dir(RIGHT), isFood(false), point(0),
pause(false), isAlive(false)
{
	map = _map;
//		Point *tmp = new Point(4,5);
//		wsp.push_back(tmp);
	sprites.push_back(new SnakeHead(8,8,graph));
	sprites.push_back(new SnakeTail(7,8,graph));
//	sprites.push_back(new SnakeTail(6,8,graph));
//	sprites.push_back(new SnakeTail(5,8,graph));

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
	sprites.insert(sprites.begin()+1,new SnakeTail(x,y,graph));
//	sprites.push_back();
	size++;
}
void Player::Draw()
{
	std::vector<Sprite*>::iterator it;
	for(it = sprites.begin(); it != sprites.end(); it++ )
	{
		(*it)->Draw();
	}
}
// true, jezeli nie ma kolizji
bool Player::CheckCollision(int x, int y)
{
	for(int i = 1; i < size; i++)
	{
		if( sprites[i]->GetX() == x && sprites[i]->GetY() == y)
			return false;
	}
	return true;
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

	speed = point/100;
	if(speed > 10)
		speed = 10;
}

void Player::MoveUp()
{
	if(map->GetCollision(y-1,x) == Map::WALL || !CheckCollision(x,y-1))
	{
		SetLive(false);
	}
	else if(map->GetCollision(y-1,x) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetY(sprites.front()->GetY()-1);
	}
	else if(map->GetCollision(y-1,x) == Map::FOOD)
	{
		Grow(sprites.front()->GetX(),sprites.front()->GetY());
		sprites.front()->SetY(sprites.front()->GetY()-1);
		map->EatFood();
		AddPoint(10);
	}
}
void Player::MoveLeft()
{
	if(map->GetCollision(y,x-1) == Map::WALL || !CheckCollision(x-1,y))
	{
		SetLive(false);
	}
	else if(map->GetCollision(y,x-1) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetX(sprites.front()->GetX()-1);
	}
	else if(map->GetCollision(y,x-1) == Map::FOOD)
	{
		Grow(sprites.front()->GetX(),sprites.front()->GetY());
		sprites.front()->SetX(sprites.front()->GetX()-1);
		map->EatFood();
		AddPoint(10);
	}
}
void Player::MoveDown()
{
	if(map->GetCollision(y+1,x) == Map::WALL || !CheckCollision(x,y+1))
	{
		SetLive(false);
	}
	else if(map->GetCollision(y+1,x) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetY(sprites.front()->GetY()+1);
	}
	else if(map->GetCollision(y+1,x) == Map::FOOD)
	{
		Grow(sprites.front()->GetX(),sprites.front()->GetY());
		sprites.front()->SetY(sprites.front()->GetY()+1);
		map->EatFood();
		AddPoint(10);
	}
}
void Player::MoveRight()
{
	if(map->GetCollision(y,x+1) == Map::WALL || !CheckCollision(x+1,y))
	{
		SetLive(false);
	}
	else if(map->GetCollision(y,x+1) == Map::BACKGROUND)
	{
		Move();
		sprites.front()->SetX(sprites.front()->GetX()+1);
	}
	else if(map->GetCollision(y,x+1) == Map::FOOD)
	{
		Grow(sprites.front()->GetX(),sprites.front()->GetY());
		sprites.front()->SetX(sprites.front()->GetX()+1);
		map->EatFood();
		AddPoint(10);
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

void Player::Reset()
{
	std::vector<Sprite*>::iterator it;
	for(it = sprites.begin()+2; it != sprites.end(); it++ )
	{
		delete *it;
	}
	for(int i = 2; i < size; i++)
	{
		sprites.pop_back();
	}
	sprites.front()->SetX(5);
	sprites.front()->SetY(5);
	sprites[1]->SetX(4);
	sprites[1]->SetY(5);
	point = 0;
	pause = false;
	isAlive = true;
	size = 2;
	dir = RIGHT;
	speed = 0;
}


