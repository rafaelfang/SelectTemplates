/*
 * Utility.h
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#ifndef UTILITYINTERFACE_H_
#define UTILITYINTERFACE_H_

#include <string>
#include <vector>

class Point;

using namespace std;
class UtilityInterface {
public:
	UtilityInterface(char*);
	void loadConfigurationFile();
	virtual void makeDirectory()=0;
	virtual void populateResultVector()=0;
	virtual void write2Json()=0;
	virtual void setup3DCoords()=0;
	virtual void calculateDistanceMatrix()=0;

	virtual void findLocalAlign()=0;
	virtual void write2PDB()=0;
	virtual void findGlobalAlign()=0;
	virtual ~UtilityInterface();
	char* getRootName();
	void setRootName(char* rootName);
	void findProteinSeqLength();
	float findDistance(Point,Point);
	string convertResidueName(const char residueName);


protected:

	char* rootName;
	string inputFileLocation;
	string outputFileLocation;
	string DBInfoLocation;
	string proteinLocation;
	int proteinSeqLength;
	vector<char> originalProteinSeq;
};

#endif /* UTILITYINTERFACE_H_ */
