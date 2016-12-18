/*
 * main.h
 *
 *  Created on: 28.10.2016
 *      Author: AR
 */

#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "settings.h"
#ifdef RPiLAB_RPi
#include <uspienv.h>
#include <uspi.h>
#include <uspios.h>
#include <uspienv/synchronize.h>
#include <uspienv/memio.h>
#else
#define EXIT_HALT 0
#endif

#include "utilities.h"
#include "peripherals.h"

// moje klasy
#include "Map.h"

extern struct JoY JoYAct;
int UpdateIO();
int SystemInit();
void DataPrepare();
void ClearScreen();
void DrawObjects();
void PrintDiagnosticInfo();
#endif /* SRC_MAIN_H_ */
