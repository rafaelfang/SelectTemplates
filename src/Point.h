/*
 * Point.h
 *
 *  Created on: Sep 8, 2015
 *      Author: rafae
 */

#ifndef POINT_H_
#define POINT_H_

class Point {
public:
	Point(float,float,float);
	virtual ~Point();
	float getX() ;
	void setX(float x);
	float getY() ;
	void setY(float y);
	float getZ() ;
	void setZ(float z);

private:
	float x;
	float y;
	float z;
};

#endif /* POINT_H_ */
