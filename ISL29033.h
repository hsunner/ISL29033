/*
 * ALS.h
 *
 *  Created on: 2014年11月25日
 *      Author: taoyuan
 */

#ifndef ISL29033_H_
#define ISL29033_H_

#include "Arduino.h"

// Command Register I
#define MODE_ALS_CONTINUOUS 	0b10100000
#define MODE_IR_CONTINUOUS 		0b11000000

// Command Register II
#define SCALE_RESOLUTION_16		0b00000000
#define SCALE_RESOLUTION_12		0b00000100
#define SCALE_RESOLUTION_8		0b00001000
#define SCALE_RESOLUTION_4		0b00001100

#define SCALE_RANGE_1			0b00000000
#define SCALE_RANGE_2			0b00000001
#define SCALE_RANGE_3			0b00000010
#define SCALE_RANGE_4			0b00000011

class ISL29033 {
public:
	ISL29033();
	void setAddress(uint8_t addr);
	void setMode(uint8_t data);
	void setScale(uint8_t data);
	void begin(void);
	void sleep(void);
	void reset(void);

	uint16_t read(void);
	uint32_t readLux(void);
	uint32_t calcLux(uint16_t value);
protected:
	int _address;
	float _range;
	float _resolution;
	void write(uint8_t data);
	void write(uint8_t reg, uint8_t data);
};

#endif /* ISL29033_H_ */
