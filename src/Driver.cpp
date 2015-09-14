//============================================================================
// Name        : Utility.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstring>
#include <iostream>


#include "BLAPDBImpl.h"


using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "not enough arguments" << endl;
		cout << "<executable> <type> <proteinName>" << endl;

	}

	// -blaPDB T0837
	if (strcmp(argv[1], "-blaPDB") == 0) {
		BLAPDBImpl blaPDBImpl(argv[2]);
		blaPDBImpl.populateResultVector();
		blaPDBImpl.makeDirectory();
		blaPDBImpl.write2Json();
		blaPDBImpl.setup3DCoords();
		blaPDBImpl.calculateDistanceMatrix();
		//blaPDBImpl.calculateSimilarityMatrix();
	}




	return 0;
}
