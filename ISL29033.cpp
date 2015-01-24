/*
 * ISL29033.cpp
 *
 *  Created on: 2014年11月25日
 *      Author: taoyuan
 */

#include "ISL29033.h"
#include "Wire.h"

#define ADDR 		0b1000100
#define CMD1 		0
#define CMD2 		1
#define DATALSB 	2
#define DATAMSB 	3

const float RANGES[] = { 125.0, 500.0, 2000.0, 8000.0 };
const float RESOLUTIONS[] = { 65536.0, 4096.0, 256.0, 16.0 };

ISL29033::ISL29033() {
	setAddress(ADDR);
}

//float ISL29033::range() {
//	if (_rangeIndex >= 0 && _rangeIndex < 4) {
//		return RANGES[_rangeIndex];
//	}
//	return RANGES[0];
//}
//
//uint16_t ISL29033::resolution() {
//	if (_resolutionIndex >= 0 && _resolutionIndex < 4) {
//		return RESOLUTIONS[_resolutionIndex];
//	}
//	return RESOLUTIONS[0];
//}

void ISL29033::setAddress(uint8_t addr) {
	_address = addr;
}

void ISL29033::setMode(uint8_t data) {
	delay(10);
	write(CMD1, data);
}

void ISL29033::setScale(uint8_t data) {
	delay(10);
	write(CMD2, data);

	_range = RANGES[data & 0x03];
	_resolution = RESOLUTIONS[(data >> 2) & 0x03];
}

void ISL29033::begin(void) {
	Wire.begin();
}

void ISL29033::sleep(void) {
	write(CMD1, 0b00000000);
}

void ISL29033::reset(void) {
}

uint32_t ISL29033::calcLux(uint16_t value) {
	return (_range * value) / _resolution;
}

uint16_t ISL29033::read(void) {
	uint16_t value = 0;

	write(DATAMSB);
	Wire.beginTransmission(_address);      // start transmission to device
	Wire.requestFrom(_address, 1);    		// send data n-bytes read/

	while (Wire.available()) {
		value = Wire.read();                	// receive DATA
	}
	Wire.endTransmission();                   // end transmission
	value <<= 8;

	write(DATALSB);
	Wire.beginTransmission(_address);      // start transmission to device
	Wire.requestFrom(_address, 1);

	while (Wire.available()) {
		value |= Wire.read();                // receive DATA
	}
	Wire.endTransmission();                   // end transmission

	return value;
}

uint32_t ISL29033::readLux(void) {
	return calcLux(read());
}

void ISL29033::write(uint8_t data) {
	Wire.beginTransmission(_address);
	Wire.write(data);
	Wire.endTransmission();
}

void ISL29033::write(uint8_t reg, uint8_t data) {
	Wire.beginTransmission(_address);
	Wire.write(reg);
	Wire.write(data);
	Wire.endTransmission();
}

