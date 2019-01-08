/*
 * Battery.cpp
 *
 *  Created on: 5 gen 2019
 *      Author: dpatella
 */

#include "Battery.h"

Battery::Battery(uint8_t analogpin) {
	// TODO Auto-generated constructor stub

	_pin = analogpin;
	Kerr = 0.024017;
	Kcell = 0.203337;

}
void Battery::getVoltage() {


	float x = analogRead(_pin) / 1023;
	float calc = (x * 1.1) - 0.024017;
	DAC[0] = calc; // mV from DAC
	voltage[0] = calc / 0.203337;  //Cell voltage

}

