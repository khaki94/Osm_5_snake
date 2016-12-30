/*
 * Alfabet.cpp
 *
 *  Created on: 30.12.2016
 *      Author: admin
 */

#include "Alfabet.h"

Alfabet::Alfabet(unsigned long * _graph): graph(_graph)
{
	digit = new int*[10];
	digit[0] = LoadLeter("0.txt");
	digit[1] = LoadLeter("1.txt");
	digit[2] = LoadLeter("2.txt");
	digit[3] = LoadLeter("3.txt");
	digit[4] = LoadLeter("4.txt");
	digit[5] = LoadLeter("5.txt");
	digit[6] = LoadLeter("6.txt");
	digit[7] = LoadLeter("7.txt");
	digit[8] = LoadLeter("8.txt");
	digit[9] = LoadLeter("9.txt");

}

Alfabet::~Alfabet()
{
	for(int i = 0; i < 10; i++)
	{
			delete digit[i];
	}
	delete digit;
}

int * Alfabet::LoadLeter(std::string name)
{
	std::fstream file;
	name = "alfabet\\"+name;
	file.open(name.c_str(),std::ios::in);
	int *tmp = new int[32*32];
	for(int i = 0; i < 32*32; i++)
		file >> tmp[i];
	file.close();
	return tmp;
}

void Alfabet::SetScore(int _score)
{
	if( _score >= 1000)
	{
		int tmp[4];
		tmp[0] = _score/1000;
		tmp[1] = ( _score - tmp[0] * 1000 ) / 100;
		tmp[2] = ( _score - tmp[0] * 1000 - tmp[1] * 100 ) / 10;
		tmp[3] = ( _score - tmp[0] * 1000 - tmp[1] * 100 - tmp[2] * 10 );
		ChooseDigit(tmp[0],0);
		ChooseDigit(tmp[1],1);
		ChooseDigit(tmp[2],2);
		ChooseDigit(tmp[3],3);
		return;
	}
	if( _score >= 100)
	{
		int tmp[3];
		tmp[0] =   _score / 100;
		tmp[1] = ( _score - tmp[0] * 100 ) / 10;
		tmp[2] = ( _score - tmp[0] * 100 - tmp[1] * 10 );
		ChooseDigit(0,0);
		ChooseDigit(tmp[0],1);
		ChooseDigit(tmp[1],2);
		ChooseDigit(tmp[2],3);
		return;
	}
	if( _score >= 10)
	{
		int tmp[2];
		tmp[0] =   _score / 10;
		tmp[1] = ( _score - tmp[0] * 10 );
		ChooseDigit(0,0);
		ChooseDigit(0,1);
		ChooseDigit(tmp[0],2);
		ChooseDigit(tmp[1],3);
		return;
	}
	Draw(digit[0],0);
	Draw(digit[0],1);
	Draw(digit[0],2);
	Draw(digit[0],3);
}

void Alfabet::Draw(int *tab, int pos)
{
	for(int y = 0; y < 32; y++)
		for( int x = 0; x < 32; x++)
		{
			if(tab[y*32+x] == 1)
				SetPixel(graph,(x+(32*pos)),y,0xFF00FF);
		}
}

void Alfabet::ChooseDigit(int dig, int pos)
{
	switch(dig)
	{
	case(0):
		Draw(digit[0],pos);
			break;
	case(1):
		Draw(digit[1],pos);
			break;
	case(2):
		Draw(digit[2],pos);
			break;
	case(3):
		Draw(digit[3],pos);
			break;
	case(4):
		Draw(digit[4],pos);
			break;
	case(5):
		Draw(digit[5],pos);
			break;
	case(6):
		Draw(digit[6],pos);
			break;
	case(7):
		Draw(digit[7],pos);
			break;
	case(8):
		Draw(digit[8],pos);
			break;
	case(9):
		Draw(digit[9],pos);
				break;
	}
}
