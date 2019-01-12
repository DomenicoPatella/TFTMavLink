/*
 * Battery.cpp
 *
 *  Created on: 5 gen 2019
 *      Author: dpatella
 */

#include "Battery.h"

Battery::Battery() {
	// TODO Auto-generated constructor stub

	_pin[0] = A0;
	_pin[1] = A1;
	_pin[2] = A2;
	_pin[3] = A3;

	Kerr = 0.024017;
	Kcell = 0.203337;

}

/**
 * @brief Get individual cell voltage from analog input
 * A0 Cell 1
 * A1 Cell 2
 * A2 Cell 3
 * A3 Cell 4
 */
void Battery::getVoltage() {

	float raw[4];

	for (int var = 0; var < 4; var++) {
		raw[var] = analogRead(_pin[var]);
		float x = raw[var] / 1023;
		float calc = (x * 1.1) - 0.024017;
		DAC[var] = calc; // mV from DAC
		voltage[var] = calc / 0.203337;  //  Cell voltage
		if (voltage[var] < 0.0)
				voltage[var] = 0.0;

	}



}

