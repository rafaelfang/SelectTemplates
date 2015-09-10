/*
 * BLAPDBImpl.h
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#ifndef BLAPDBIMPL_H_
#define BLAPDBIMPL_H_

#include <vector>

#include "BLAPDBResult.h"
#include "UtilityInterface.h"

class BLAPDBImpl: public UtilityInterface {
public:
	BLAPDBImpl(char*);
	void makeDirectory();
	void populateResultVector();
	void write2Json();
	void setup3DCoords();
	void calculateDistanceMatrix();
	void findLocalAlign();
	void write2PDB();
	void findGlobalAlign();
	virtual ~BLAPDBImpl();
private:
	vector<BLAPDBResult> blaPDBResultVector;

};

#endif /* BLAPDBIMPL_H_ */
