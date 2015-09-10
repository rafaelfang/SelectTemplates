/*
 * Point.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: rafae
 */

#include "Point.h"

Point::Point(float theX,float theY, float theZ) {
	// TODO Auto-generated constructor stub
	this->setX(theX);
	this->setY(theY);
	this->setZ(theZ);
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

float Point::getX() {
	return x;
}

void Point::setX(float x) {
	this->x = x;
}

float Point::getY() {
	return y;
}

void Point::setY(float y) {
	this->y = y;
}

float Point::getZ() {
	return z;
}

void Point::setZ(float z) {
	this->z = z;
}
