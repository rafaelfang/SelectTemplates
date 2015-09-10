/*
 * Utility.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#include "UtilityInterface.h"

#include <stdio.h>
#include <cmath>
#include <cstring>
#include <cwchar>
#include <fstream>
#include <iostream>

#include "json/json.h"
#include "Point.h"

UtilityInterface::UtilityInterface(char* rootName) {
	setRootName(rootName);
	loadConfigurationFile();
	findProteinSeqLength();

}
void UtilityInterface::loadConfigurationFile() {
	Json::Reader reader;
	Json::Value root;

	//read from file
	ifstream is;
	is.open("configuration.json", ios::binary);

	if (reader.parse(is, root)) {
		DBInfoLocation = root["DBInfoLocation"].asString();
		inputFileLocation = root["inputFileLocation"].asString();
		outputFileLocation = root["outputFileLocation"].asString();
		proteinLocation = root["proteinLocation"].asString();
	}

	is.close();
}

UtilityInterface::~UtilityInterface() {
	// TODO Auto-generated destructor stub
}

char* UtilityInterface::getRootName() {
	return rootName;
}

void UtilityInterface::setRootName(char* rootName) {
	this->rootName = rootName;
}

void UtilityInterface::findProteinSeqLength() {
	string inFilename(proteinLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += ".fasta";
	//cout<<inFilename<<endl;

	FILE* fptr = fopen((char*) inFilename.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}
	char line[500];
	fgets(line, 500, fptr);
	fgets(line, 500, fptr);
	char *pos;
	if ((pos = strchr(line, '\n')) != NULL) {
		*pos = '\0';
	}

	proteinSeqLength = strlen(line);

	originalProteinSeq.resize(proteinSeqLength);
	for (int j = 0; j < proteinSeqLength; j++) {
		originalProteinSeq[j] = line[j];
	}
	//cout<<"proteinSeqLength"<<proteinSeqLength<<endl;

	fclose(fptr);
}

float UtilityInterface::findDistance(Point A, Point B) {
	float xSqr = (A.getX() - B.getX()) * (A.getX() - B.getX());
	float ySqr = (A.getY() - B.getY()) * (A.getY() - B.getY());
	float zSqr = (A.getZ() - B.getZ()) * (A.getZ() - B.getZ());

	float mySqr = xSqr + ySqr + zSqr;

	return sqrt(mySqr);
}

string UtilityInterface::convertResidueName(const char residueName) {
	if (residueName == 'A') {
		return "ALA";
	}

	if (residueName == 'R') {
		return "ARG";
	}

	if (residueName == 'N') {
		return "ASN";
	}
	if (residueName == 'D') {
		return "ASP";
	}
	if (residueName == 'B') {
		return "ASX";
	}
	if (residueName == 'C') {
		return "CYS";
	}
	if (residueName == 'Q') {
		return "GLN";
	}
	if (residueName == 'E') {
		return "GLU";
	}
	if (residueName == 'Z') {
		return "GLX";
	}
	if (residueName == 'G') {
		return "GLY";
	}
	if (residueName == 'H') {
		return "HIS";
	}
	if (residueName == 'I') {
		return "ILE";
	}
	if (residueName == 'L') {
		return "LEU";
	}
	if (residueName == 'K') {
		return "LYS";
	}
	if (residueName == 'M') {
		return "MET";
	}
	if (residueName == 'F') {
		return "PHE";
	}
	if (residueName == 'P') {
		return "PRO";
	}
	if (residueName == 'S') {
		return "SER";
	}
	if (residueName == 'T') {
		return "THR";
	}
	if (residueName == 'W') {
		return "TRP";
	}
	if (residueName == 'Y') {
		return "TYR";
	}
	if (residueName == 'V') {
		return "VAL";
	}
	return "INVALID NAME";
}

