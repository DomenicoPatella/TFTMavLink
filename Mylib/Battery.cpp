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

/**
 * @brief Get individual cell voltage from analog input
 * A0 Cell 1
 * A1 Cell 2
 * A2 Cell 3
 * A3 Cell 4
 * A4 Cell 5
 * A5 Cell 6
 */
void Battery::getVoltage() {


	float raw = analogRead(_pin);
	float x=raw/1023;
	float calc = (x * 1.1) - 0.024017;
	DAC[0] = calc; // mV from DAC
	voltage[0] = calc / 0.203337;  //1Cell voltage
	voltage[1] = (calc / 0.203337) +0.1;  //2Cell voltage
	voltage[2] = (calc / 0.203337) -0.1;  //3Cell voltage

	if(voltage[0]<0.0) voltage[0]=0.0;
}

