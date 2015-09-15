/*
 * AlignmentResult.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#include "AlignmentResult.h"

AlignmentResult::AlignmentResult() {

}

AlignmentResult::~AlignmentResult() {

}

vector<float>& AlignmentResult::getXCoords() {
	return XCoords;
}

void AlignmentResult::setXCoords(vector<float>& Xcoords) {
	XCoords = Xcoords;
}

vector<float>& AlignmentResult::getYCoords() {
	return YCoords;
}

void AlignmentResult::setYCoords(vector<float>& Ycoords) {
	YCoords = Ycoords;
}
vector<float>& AlignmentResult::getZCoords() {
	return ZCoords;
}

void AlignmentResult::setZCoords(vector<float>& Zcoords) {
	ZCoords = Zcoords;
}

vector<char>& AlignmentResult::getTemplateSeq() {
	return templateSeq;
}

void AlignmentResult::setTemplateSeq(vector<char>& templateSeq) {
	this->templateSeq = templateSeq;
}

vector<vector<float> >& AlignmentResult::getDistMat() {
	return distMat;
}

void AlignmentResult::setDistMat(vector<vector<float> >& distMat) {
	this->distMat = distMat;
}
