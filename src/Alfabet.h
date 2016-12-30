/*
 * Alfabet.h
 *
 *  Created on: 30.12.2016
 *      Author: admin
 */

#ifndef SRC_ALFABET_H_
#define SRC_ALFABET_H_

#include <string>
#include <fstream>
#include "peripherals.h"

class Alfabet {
private:
	unsigned long *graph;
	int **digit;
private:
	int *LoadLeter(std::string name);
	void Draw(int *, int);
	void ChooseDigit(int, int);
public:
	Alfabet(unsigned long * _graph);
	virtual ~Alfabet();
	void SetScore( int _score);
};

#endif /* SRC_ALFABET_H_ */
