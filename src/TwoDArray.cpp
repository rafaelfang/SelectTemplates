/*
 * TwoDArray.cpp
 *
 *  Created on: Sep 14, 2015
 *      Author: rafae
 */

#include "TwoDArray.h"

#include <stdlib.h>

TwoDArray::TwoDArray(int theRow, int theCol) {
	array = (float*)malloc(theRow * theCol * sizeof(float));

}
int TwoDArray::getTotalSize(){
	if(row==col){
		return row*row;
	}else{
		return row*col;
	}
}
void TwoDArray::setArrayValue(int whichRow, int whichCol, float theValue) {
	array[whichRow * col + whichCol] = theValue;
}
float TwoDArray::returnArrayValue(int whichRow, int whichCol) {
	return array[whichRow * col + whichCol];
}

TwoDArray::~TwoDArray() {
	free(array);
}

int TwoDArray::getCol() {
	return col;
}

void TwoDArray::setCol(int col) {
	this->col = col;
}

int TwoDArray::getRow() {
	return row;
}

void TwoDArray::setRow(int row) {
	this->row = row;
}

float* TwoDArray::getArray() {
	return array;
}

void TwoDArray::setArray(float* array) {
	this->array = array;
}
