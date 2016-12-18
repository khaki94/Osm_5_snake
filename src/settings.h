/*
 * settings.h
 *
 *  Created on: 26.10.2016
 *      Author: AR
 */

#ifndef SRC_SETTINGS_H_
#define SRC_SETTINGS_H_

#define SIMULATOR

#ifdef SIMULATOR
#define RPiLAB_WIN
#undef RPiLAB_RPi
#else
#define RPiLAB_RPi
#undef RPiLAB_WIN
#endif

#endif /* SRC_SETTINGS_H_ */
