/*
 * Sprite.cpp
 *
 *  Created on: 18.12.2016
 *      Author: admin
 */

#include "Sprite.h"

// klasa Sprite
Sprite::Sprite(unsigned long * _graph): x(0), y(0), color(BLACK), graph(_graph) {}
Sprite::Sprite(int _x, int _y,unsigned long * _graph) : x(_x*16), y(_y*16), color(BLACK), graph(_graph) {}
Sprite::~Sprite() { }

// klasa Background
Background::Background(unsigned long * _graph) : Sprite(_graph), size(16) { color = WHITE; }
Background::Background(int _x, int _y,unsigned long * _graph) : Sprite(_x, _y,_graph), size(16) { color = WHITE; }
Background::~Background() {}
void Background::Draw()
{
	for( int _y = 0; _y < size; _y++ )
		for(int _x = 0; _x < size; _x++)
			SetPixel(graph,(_x+x),(_y+y),color);
}

// klasa Wall
Wall::Wall(unsigned long * _graph) : Sprite(_graph), size(16) { color = BLACK;}
Wall::Wall(int _x, int _y,unsigned long * _graph) : Sprite(_x, _y,_graph), size(16) { color = BLACK;}
Wall::~Wall() {}
void Wall::Draw()
{
	for( int _y = 0; _y < size; _y++ )
		for(int _x = 0; _x < size; _x++)
			SetPixel(graph,(_x+x),(_y+y),color);
}

// klasa Food
Food::Food(unsigned long * _graph) : Sprite(_graph), radius(8) { color = BLUE;}
Food::Food(int _x, int _y,unsigned long * _graph) : Sprite(_x, _y,_graph), radius(8) { color = BLUE;}
Food::~Food() {}
void Food::Draw()
{
	for( int _y = 0; _y < radius*2; _y++ )
		for(int _x = 0; _x < radius*2; _x++)
		{
			if((_x-radius)*(_x-radius)+(_y-radius)*(_y-radius) < radius*radius)
				SetPixel(graph,(x+_x),(y+_y),color);
		}

}


