/*
 * TwoDArray.h
 *
 *  Created on: Sep 14, 2015
 *      Author: rafae
 */

#ifndef TWODARRAY_H_
#define TWODARRAY_H_

class TwoDArray {
public:
	TwoDArray(int, int);
	virtual ~TwoDArray();
	int getTotalSize();
	int getCol();
	void setCol(int col);
	int getRow();
	void setRow(int row);
	float* getArray();
	void setArray(float*);
	void setArrayValue(int, int, float);
	float returnArrayValue(int, int);

private:
	int row;
	int col;
	float* array;
};

#endif /* TWODARRAY_H_ */
