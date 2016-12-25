/*
 * Player.cpp
 *
 *  Created on: 21.12.2016
 *      Author: admin
 */
#include "Player.h"

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
	 std::vector<Sprite*>::iterator it;
	 for(it = sprites.end(); it != sprites.begin()+1; it-- )
	 {
//		 (*it)->
	 }
	 sprites.push_back(new SnakeTail((*sprites.end())->GetX(),(*sprites.end())->GetY(),graph));
	 //sprites.front()->SetX(sprites.front()->GetX()+1);
	 sprites.front()->SetX(6);
}


