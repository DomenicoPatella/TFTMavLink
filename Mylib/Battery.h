/*
 * Battery.h
 *
 *  Created on: 5 gen 2019
 *      Author: dpatella
 */

#ifndef FRSKYTELEMETRYMAVLINK_MYLIB_BATTERY_H_
#define FRSKYTELEMETRYMAVLINK_MYLIB_BATTERY_H_
#include "Arduino.h"

class Battery {
public:

	Battery(uint8_t  analogpin);
    void getVoltage();
    float voltage[4];
    float DAC[4];

private:
    uint8_t _pin;
	float Kcell,Kerr;


};

#endif /* FRSKYTELEMETRYMAVLINK_MYLIB_BATTERY_H_ */
