/*
 * BlaPDBResult.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Chao
 */

#include "BLAPDBResult.h"

#include <string>

BLAPDBResult::BLAPDBResult() :
		AlignmentResult() {

}

BLAPDBResult::~BLAPDBResult() {

}

string& BLAPDBResult::getAlignment() {
	return alignment;
}

void BLAPDBResult::setAlignment(string& alignment) {
	this->alignment = alignment;
}

float BLAPDBResult::getExpect() {
	return expect;
}

void BLAPDBResult::setExpect(float expect) {
	this->expect = expect;
}

bool BLAPDBResult::isFirstStateReached() {
	return firstStateReached;
}

void BLAPDBResult::setFirstStateReached(bool firstStateReached = false) {
	this->firstStateReached = firstStateReached;
}

int BLAPDBResult::getGaps() {
	return gaps;
}

void BLAPDBResult::setGaps(int gaps) {
	this->gaps = gaps;
}

int BLAPDBResult::getIdentities() {
	return identities;
}

void BLAPDBResult::setIdentities(int identities) {
	this->identities = identities;
}

int BLAPDBResult::getLength() {
	return length;
}

void BLAPDBResult::setLength(int length) {
	this->length = length;
}

int BLAPDBResult::getPositives() {
	return positives;
}

void BLAPDBResult::setPositives(int positives) {
	this->positives = positives;
}

string& BLAPDBResult::getQuery() {
	return query;
}

void BLAPDBResult::setQuery(string& query) {
	this->query = query;
}

int BLAPDBResult::getQueryEnd() {
	return queryEnd;
}

void BLAPDBResult::setQueryEnd(int queryEnd) {
	this->queryEnd = queryEnd;
}

int BLAPDBResult::getQueryStart() {
	return queryStart;
}

void BLAPDBResult::setQueryStart(int queryStart) {
	this->queryStart = queryStart;
}

float BLAPDBResult::getScore() {
	return score;
}

void BLAPDBResult::setScore(float score) {
	this->score = score;
}

bool BLAPDBResult::isSecondStateReached() {
	return secondStateReached;
}

void BLAPDBResult::setSecondStateReached(bool secondStateReached = false) {
	this->secondStateReached = secondStateReached;
}

string& BLAPDBResult::getSubject() {
	return subject;
}

void BLAPDBResult::setSubject(string& subject) {
	this->subject = subject;
}

int BLAPDBResult::getSubjectEnd() {
	return subjectEnd;
}

void BLAPDBResult::setSubjectEnd(int subjectEnd) {
	this->subjectEnd = subjectEnd;
}

int BLAPDBResult::getSubjectStart() {
	return subjectStart;
}

void BLAPDBResult::setSubjectStart(int subjectStart) {
	this->subjectStart = subjectStart;
}

bool BLAPDBResult::isThirdStateReached() {
	return thirdStateReached;
}

void BLAPDBResult::setThirdStateReached(bool thirdStateReached = false) {
	this->thirdStateReached = thirdStateReached;
}

string& BLAPDBResult::getProteinName() {
	return proteinName;
}

void BLAPDBResult::setProteinName(string& proteinName) {
	this->proteinName = proteinName;
}

int BLAPDBResult::getGapNum() {
	return gapNum;
}

void BLAPDBResult::setGapNum(int gapNum) {
	this->gapNum = gapNum;
}

float BLAPDBResult::getCoverageRate() {
	return coverageRate;
}

void BLAPDBResult::setCoverageRate(float coverageRate) {
	this->coverageRate = coverageRate;
}
