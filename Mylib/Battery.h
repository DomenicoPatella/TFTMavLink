/*
 * Battery.h
 *
 *  Created on: 5 gen 2019
 *      Author: dpatella
 */

#ifndef MYLIB_BATTERY_H_
#define MYLIB_BATTERY_H_
#include "Arduino.h"

class Battery {
public:

	Battery();
    void getVoltage();
    float voltage[3];
    float DAC[3];

private:
    uint8_t _pin[3];
	float Kcell,Kerr;


};

#endif /* MYLIB_BATTERY_H_ */
