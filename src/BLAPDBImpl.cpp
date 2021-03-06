/*
 * BLAPDBImpl.cpp
 *
 *  Created on: Apr 21, 2015
 *      Author: cf797
 */

#include "BLAPDBImpl.h"

#include <stdio.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "Point.h"

BLAPDBImpl::BLAPDBImpl(char* theRootName) :
		UtilityInterface(theRootName) {
	// TODO Auto-generated constructor stub

}
void BLAPDBImpl::makeDirectory() {
	char cmd1[500];
	string outputFileFoldername(outputFileLocation);
	outputFileFoldername += "/";
	outputFileFoldername += rootName;
	outputFileFoldername += "/BLAPDB/";
	sprintf(cmd1, "mkdir -p %s", (char*) outputFileFoldername.c_str());
	//cout << cmd << endl;
	system(cmd1);

	char cmd2[500];
	string outputFileLocal3DFoldername(outputFileLocation);
	outputFileLocal3DFoldername += "/";
	outputFileLocal3DFoldername += rootName;
	outputFileLocal3DFoldername += "/BLAPDB/local/";
	sprintf(cmd2, "mkdir -p %s", (char*) outputFileLocal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd2);

	char cmd3[500];
	string outputFileGlobal3DFoldername(outputFileLocation);
	outputFileGlobal3DFoldername += "/";
	outputFileGlobal3DFoldername += rootName;
	outputFileGlobal3DFoldername += "/BLAPDB/FullyExtended/";
	sprintf(cmd3, "mkdir -p %s", (char*) outputFileGlobal3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd3);

	char cmd4[500];
	string outputFilePdb3DFoldername(outputFileLocation);
	outputFilePdb3DFoldername += "/";
	outputFilePdb3DFoldername += rootName;
	outputFilePdb3DFoldername += "/BLAPDB/pdbFiles/";
	sprintf(cmd4, "mkdir -p %s", (char*) outputFilePdb3DFoldername.c_str());
	//cout << cmd << endl;
	system(cmd4);

	char cmd5[500];
	string outputFileDistMatFoldername(outputFileLocation);
	outputFileDistMatFoldername += "/";
	outputFileDistMatFoldername += rootName;
	outputFileDistMatFoldername += "/BLAPDB/distanceMatrix/";
	sprintf(cmd5, "mkdir -p %s", (char*) outputFileDistMatFoldername.c_str());
	//cout << cmd << endl;
	system(cmd5);
}
void BLAPDBImpl::populateResultVector() {

	char line[500];
	int counter = 0;
	string inFilename(inputFileLocation);
	inFilename += "/";
	inFilename += rootName;
	inFilename += "/";
	inFilename += "/query.blaPDB";

	FILE* fptr = fopen((char*) inFilename.c_str(), "r");
	if (fptr == NULL) {
		cout << "input file: " << inFilename << " can't open" << endl;
	}
	BLAPDBResult result;

	while (fgets(line, 500, fptr) != NULL) {
		if ((strstr(line, ">") != NULL) && !result.isFirstStateReached()) {
			//set first block information
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);
			while (strstr(line, "Length =") == NULL) {
				fgets(line, 500, fptr); //skip long name
			}
			char temp[10];
			int seqLen;
			sscanf(line, "%s = %d", temp, &seqLen);
			result.setLength(seqLen);
			//set first state reached
			result.setFirstStateReached(true);
		}
		if ((strstr(line, "Score =") != NULL)
				&& !result.isSecondStateReached()) {
			//set second block information
			float score;
			char* pos1 = strstr(line, "=");
			sscanf(pos1 + 1, "%f", &score);
			result.setScore(score);
			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);
			fgets(line, 500, fptr);
			pos1 = strstr(line, "(");
			int identities;
			sscanf(pos1 + 1, "%d", &identities);
			result.setIdentities(identities);
			pos2 = strstr(pos1 + 1, "(");
			int positives;
			sscanf(pos2 + 1, "%d", &positives);
			result.setPositives(positives);

			char* pos3 = strstr(pos2 + 1, "=");
			if (pos3 == NULL) {
				result.setGapNum(0);
				result.setGaps(0);
			} else {
				int gapNum;
				sscanf(pos3 + 1, "%d", &gapNum);
				result.setGapNum(gapNum);
				int gaps;
				char* pos4 = strstr(pos3 + 1, "(");
				sscanf(pos4 + 1, "%d", &gaps);
				result.setGaps(gaps);
			}

			//set second state reached
			result.setSecondStateReached(true);
		}

		if ((strstr(line, "Query:") != NULL) && !result.isThirdStateReached()) {
			//set third block information
			int nInt1, nInt2;
			char var1[20], var2[20];
			char tmpQuery[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpQuery, &nInt2);
			result.setQueryStart(nInt1);
			string tmpQueryStr(tmpQuery);
			result.setQuery(tmpQueryStr);
			result.setQueryEnd(nInt2);
			fgets(line, 500, fptr);
			string tmpLineStr(line);
			result.setAlignment(tmpLineStr);
			fgets(line, 500, fptr);
			char tmpSubject[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpSubject, &nInt2);
			result.setSubjectStart(nInt1);
			string tmpSubjectStr(tmpSubject);
			result.setSubject(tmpSubjectStr);
			result.setSubjectEnd(nInt2);
			//set third state reached
			result.setThirdStateReached(true);
		}

		if ((strstr(line, "Query:") != NULL) && result.isThirdStateReached()) {
			//update third block information, so in this case
			//query, alignment and subject should be long string
			//the queryEnd and subjectEnd should also be updated
			int nInt1, nInt2;
			char var1[20], var2[20];
			char tmpQuery[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpQuery, &nInt2);
			string newQuery = result.getQuery();
			newQuery += tmpQuery;
			result.setQuery(newQuery);
			result.setQueryEnd(nInt2);
			fgets(line, 500, fptr);
			string newAlignment = result.getAlignment();
			newAlignment += line;
			result.setAlignment(newAlignment);
			fgets(line, 500, fptr);
			char tmpSubject[200];
			sscanf(line, "%s %d %s %d", var1, &nInt1, tmpSubject, &nInt2);
			string newSubject = result.getSubject();
			newSubject += tmpSubject;
			result.setSubject(newSubject);
			result.setSubjectEnd(nInt2);

		}

		if ((strstr(line, "Score =") != NULL)
				&& result.isSecondStateReached()) {

			//first write the protein information to json
			string searchDBFilename(DBInfoLocation);
			searchDBFilename += result.getProteinName();
			searchDBFilename += ".db";
			//find the local alignment
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			float theCoverageRate = float(
					(result.getSubjectEnd() - result.getSubjectStart() + 1
							- result.getGapNum())) / (proteinSeqLength);
			result.setCoverageRate(theCoverageRate);
			blaPDBResultVector.push_back(result);
			counter++;
			//then update the information and set the second state flag
			float score;
			char* pos1 = strstr(line, "=");
			sscanf(pos1 + 1, "%f", &score);
			result.setScore(score);
			char* pos2 = strstr(pos1 + 1, "=");
			float eValue;
			sscanf(pos2 + 1, "%f", &eValue);
			result.setExpect(eValue);
			fgets(line, 500, fptr);
			pos1 = strstr(line, "(");
			int identities;
			sscanf(pos1 + 1, "%d", &identities);
			result.setIdentities(identities);
			pos2 = strstr(pos1 + 1, "(");
			int positives;
			sscanf(pos2 + 1, "%d", &positives);
			result.setPositives(positives);
			char* pos3 = strstr(pos2 + 1, "(");
			if (pos3 == NULL) {
				//there is no gaps
				result.setGaps(0);
			} else {
				int gaps;
				sscanf(pos3 + 1, "%d", &gaps);
				result.setGaps(gaps);
			}

			result.setSecondStateReached(true);
			//unset the third block flag
			result.setThirdStateReached(false);

		}
		if ((strstr(line, ">") != NULL) && result.isFirstStateReached()) {

			//first write the protein information to json
			string searchDBFilename(DBInfoLocation);
			searchDBFilename += result.getProteinName();
			searchDBFilename += ".db";
			//find the local alignment
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			//aaaaaaaaaaaaaa
			float theCoverageRate = float(
					(result.getSubjectEnd() - result.getSubjectStart() + 1
							- result.getGapNum())) / (proteinSeqLength);
			result.setCoverageRate(theCoverageRate);

			blaPDBResultVector.push_back(result);
			counter++;
			//then update the information set the first state flag
			char proteinName[7];
			char* pos1 = strstr(line, ">");
			sscanf(pos1 + 1, "%s", proteinName);
			string proteinNameStr(proteinName);
			result.setProteinName(proteinNameStr);
			while (strstr(line, "Length =") == NULL) {
				fgets(line, 500, fptr); //skip long name
			}
			char temp[10];
			int seqLen;
			sscanf(line, "%s = %d", temp, &seqLen);
			result.setLength(seqLen);
			//unset second block flag and third block flag
			result.setSecondStateReached(false);
			result.setThirdStateReached(false);
		}

	}
	string searchDBFilename(DBInfoLocation);
	searchDBFilename += result.getProteinName();
	searchDBFilename += ".db";
	//find the local alignment
	//aaaaaaaaaaaaaa
	//aaaaaaaaaaaaaa
	//aaaaaaaaaaaaaa
	float theCoverageRate = float(
			(result.getSubjectEnd() - result.getSubjectStart() + 1
					- result.getGapNum())) / (proteinSeqLength);
	result.setCoverageRate(theCoverageRate);

	blaPDBResultVector.push_back(result);

	fclose(fptr);

}
void BLAPDBImpl::write2Json() {

	string outFilename(outputFileLocation);
	outFilename += rootName;
	outFilename += "/BLAPDB/";
	outFilename += "blaPDB.json";
	//cout<<outFilename<<endl;
	ofstream outputFile(outFilename.c_str());

	outputFile << "{" << "\n";

	for (int i = 0; i < blaPDBResultVector.size(); i++) {

		outputFile << "\"protein" << i << "\":{\n";
		outputFile << "\t\"proteinName\":\""
				<< blaPDBResultVector[i].getProteinName() << "\",\n";
		outputFile << "\t\"OriginalSequenceLength\":\"" << proteinSeqLength
				<< "\",\n";
		outputFile << "\t\"Length\":\"" << blaPDBResultVector[i].getLength()
				<< "\",\n";
		outputFile << "\t\"Score\":\"" << blaPDBResultVector[i].getScore()
				<< "\",\n";
		outputFile << "\t\"Expect\":\"" << blaPDBResultVector[i].getExpect()
				<< "\",\n";
		outputFile << "\t\"Identities\":\""
				<< blaPDBResultVector[i].getIdentities() << "%\",\n";
		outputFile << "\t\"Positives\":\""
				<< blaPDBResultVector[i].getPositives() << "%\",\n";
		outputFile << "\t\"Gaps\":\"" << blaPDBResultVector[i].getGaps()
				<< "\",\n";
		outputFile << "\t\"CoveragePercentage\":\""
				<< (blaPDBResultVector[i].getCoverageRate()) * 100 << "%\",\n";
		outputFile << "\t\"QueyStart\":\""
				<< blaPDBResultVector[i].getQueryStart() << "\",\n";
		outputFile << "\t\"Query\":\"" << blaPDBResultVector[i].getQuery()
				<< "\",\n";
		outputFile << "\t\"QueryEnd\":\"" << blaPDBResultVector[i].getQueryEnd()
				<< "\",\n";
		outputFile << "\t\"Alignment\":\""
				<< blaPDBResultVector[i].getAlignment() << "\",\n";
		outputFile << "\t\"SubjectStart\":\""
				<< blaPDBResultVector[i].getSubjectStart() << "\",\n";
		outputFile << "\t\"Subject\":\"" << blaPDBResultVector[i].getSubject()
				<< "\",\n";
		outputFile << "\t\"SubjectEnd\":\""
				<< blaPDBResultVector[i].getSubjectEnd() << "\"\n";
		outputFile << "},\n";
	}
	outputFile << "\"finish\":\"end\"" << "\n";
	outputFile << "}" << "\n";

	outputFile.close();

}

void BLAPDBImpl::setup3DCoords() {
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		string proteinDBFilename(DBInfoLocation);
		proteinDBFilename += "/";
		proteinDBFilename += blaPDBResultVector[i].getProteinName();
		proteinDBFilename += ".db";
		FILE* fptr = fopen((char*) proteinDBFilename.c_str(), "r");
		if (fptr == NULL) {
			cout << proteinDBFilename << " can't open!" << endl;
		}
		char line[3000];
		char proteinSeq[3000];
		int seqLength;
		vector<float> Xs;
		vector<float> Ys;
		vector<float> Zs;
		vector<char> templateSeq;
		while (fgets(line, 3000, fptr) != NULL) {
			if (strstr(line, ">Reference Sequence Info:") != NULL) {
				fgets(line, 3000, fptr);
				sscanf(line, "%s", proteinSeq);
				string s(proteinSeq);
				seqLength = s.size();
				templateSeq.resize(seqLength);
				for (int j = 0; j < seqLength; j++) {
					templateSeq[j] = s[j];
				}
				//cout<<seqLength<<endl;
				continue;
			}
			if (strstr(line, ">Ca XYZ:") != NULL) {
				Xs.resize(seqLength);
				Ys.resize(seqLength);
				Zs.resize(seqLength);

				float temp;
				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Xs[j] = temp;
					//cout<<Xs[j];
				}

				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Ys[j] = temp;
					//cout<<Ys[j];
				}

				for (int j = 0; j < seqLength; j++) {
					fscanf(fptr, "%f", &temp);
					Zs[j] = temp;
					//cout<<Zs[j];
				}

				break;
			}
		}
		fclose(fptr);
		blaPDBResultVector[i].setTemplateSeq(templateSeq);
		blaPDBResultVector[i].setXCoords(Xs);
		blaPDBResultVector[i].setYCoords(Ys);
		blaPDBResultVector[i].setZCoords(Zs);

	}
}

float** BLAPDBImpl::loadDistanceMatrix(string fileName) {

	vector<float> arr;
	string a;
	int counter = 0;
	ifstream inputStream(fileName.c_str());
	while (!inputStream.eof())

	{

		inputStream >> a;
		counter++;
		arr.push_back(atof(a.c_str()));

	}
	int row = sqrt(counter);
	float** array2D = (float**) malloc(row * sizeof(float*));
	for (int i = 0; i < row; i++) {
		array2D[i] = (float *) malloc(row * sizeof(float));
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			array2D[i][j] = arr[i * row + j];
		}
	}
	displayDistMat(array2D, row);
	return array2D;

}

void BLAPDBImpl::displayDistMat(float** distMat, int row) {
	cout << "distMat is" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < row; j++) {
			cout << " " << distMat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << endl;
	cout << endl;

}
void BLAPDBImpl::calculateSimilarityMatrix() {
	//cout<<"similaritymatrix start"<<endl;

	int theSize = blaPDBResultVector.size();
	float theSimilarityMatrix[theSize][theSize];

	string distanceMatFilename(outputFileLocation);
	distanceMatFilename += "/";
	distanceMatFilename += rootName;
	distanceMatFilename += "/BLAPDB/distanceMatrix/protein";
	for (int m = 0; m < theSize; m++) {
		stringstream ss1;
		ss1 << m;
		string distanceMatFilenameA = distanceMatFilename + ss1.str();
		distanceMatFilenameA += ".txt";
		cout << "distanceMatFilenameA is " << distanceMatFilenameA << endl;
		float** distMatrixA = loadDistanceMatrix(distanceMatFilenameA.c_str());

		for (int n = 0; n < theSize; n++) {

			stringstream ss2;
			ss2 << n;

			string distanceMatFilenameB = distanceMatFilename + ss2.str();
			distanceMatFilenameB += ".txt";
			cout << "distanceMatFilenameB is " << distanceMatFilenameB << endl;
			float** distMatrixB = loadDistanceMatrix(
					distanceMatFilenameB.c_str());

			break;
			int queryStartA = blaPDBResultVector[m].getQueryStart();
			int queryEndA = blaPDBResultVector[m].getQueryEnd();

			int queryStartB = blaPDBResultVector[n].getQueryStart();
			int queryEndB = blaPDBResultVector[n].getQueryEnd();
			cout << "queryStartA " << queryStartA << "queryEndA " << queryEndA
					<< endl;
			cout << "queryStartB " << queryStartB << "queryEndB " << queryEndB
					<< endl;

			if (queryStartA <= queryStartB && queryStartB <= queryEndA
					&& queryEndA <= queryEndB) {
				cout << "case 1 begin" << endl;
				int overlapLength = queryEndA - queryStartB + 1;

				float temp1;
				float temp2;
				float rmsd;

				for (int i = 0; i < overlapLength; i++) {

					for (int j = 0; j < overlapLength; j++) {

						temp1 =
								distMatrixA[queryStartB - queryStartA + i][queryStartB
										- queryStartA + j];

						temp2 = distMatrixB[i][j];

						rmsd += (temp1 - temp2) * (temp1 - temp2);
					}

				}

				rmsd = sqrt(rmsd / (overlapLength * overlapLength));
				cout << "case 1 rmsd is: " << rmsd << endl;
				theSimilarityMatrix[m][n] = rmsd;
			} else if (queryStartA <= queryStartB && queryStartB <= queryEndB
					&& queryEndB <= queryEndA) {
				cout << "case 2 begin" << endl;
				int overlapLength = queryEndB - queryStartB + 1;
				float temp1;
				float temp2;
				float rmsd;
				for (int i = 0; i < overlapLength; i++) {

					for (int j = 0; j < overlapLength; j++) {

						temp1 =
								distMatrixA[queryStartB - queryStartA + i][queryStartB
										- queryStartA + j];
						temp2 = distMatrixB[i][j];
						rmsd += (temp1 - temp2) * (temp1 - temp2);
					}

				}

				rmsd = sqrt(rmsd / (overlapLength * overlapLength));
				cout << "case 2 rmsd:" << rmsd << endl;
				theSimilarityMatrix[m][n] = rmsd;
			} else if (queryStartB <= queryStartA && queryStartA <= queryEndB
					&& queryEndB <= queryEndA) {
				cout << "case 3 begin" << endl;
				int overlapLength = queryEndB - queryStartA + 1;
				float temp1;
				float temp2;
				float rmsd;
				for (int i = 0; i < overlapLength; i++) {

					for (int j = 0; j < overlapLength; j++) {

						temp1 =
								distMatrixA[queryStartA - queryStartB + i][queryStartA
										- queryStartB + j];
						temp2 = distMatrixB[i][j];
						rmsd += (temp1 - temp2) * (temp1 - temp2);
					}

				}

				rmsd = sqrt(rmsd / (overlapLength * overlapLength));
				cout << "case 3 " << rmsd << endl;
				theSimilarityMatrix[m][n] = rmsd;
			} else if (queryStartB <= queryStartA && queryStartA <= queryEndA
					&& queryEndA <= queryEndB) {
				cout << "case 4 begin " << endl;
				int overlapLength = queryEndA - queryStartA + 1;
				float temp1;
				float temp2;
				float rmsd;
				for (int i = 0; i < overlapLength; i++) {

					for (int j = 0; j < overlapLength; j++) {

						temp1 =
								distMatrixA[queryStartA - queryStartB + i][queryStartA
										- queryStartB + j];
						temp2 = distMatrixB[i][j];
						rmsd += (temp1 - temp2) * (temp1 - temp2);
					}

				}

				rmsd = sqrt(rmsd / (overlapLength * overlapLength));
				cout << "case 4 " << rmsd << endl;
				theSimilarityMatrix[m][n] = rmsd;
			} else {
				cout << "case 5 " << 0.0 << endl;
				theSimilarityMatrix[m][n] = 0.0;//no overlapping between the two distance Matrix
			}

			free(distMatrixB);

		}
		free(distMatrixA);
	}
	cout << "write to files" << endl;
	//write the similarity matrix into files for debugging

	string proteinSimilarityMatFilename(outputFileLocation);
	proteinSimilarityMatFilename += "/";
	proteinSimilarityMatFilename += rootName;
	proteinSimilarityMatFilename += "/BLAPDB/similarityMatrix.txt";

	ofstream outSimilarityMatFile((char*) proteinSimilarityMatFilename.c_str(),
			ios::out);

	for (int i = 0; i < theSize; i++) {

		for (int j = 0; j < theSize; j++) {
			outSimilarityMatFile << " " << theSimilarityMatrix[i][j] << " ";
		}
		outSimilarityMatFile << "\n";
	}
	outSimilarityMatFile << "\n";
	outSimilarityMatFile.close();

}

void BLAPDBImpl::calculateDistanceMatrix() {

	for (int k = 0; k < blaPDBResultVector.size(); k++) {
		vector<float> Xs = blaPDBResultVector[k].getXCoords();
		vector<float> Ys = blaPDBResultVector[k].getYCoords();
		vector<float> Zs = blaPDBResultVector[k].getZCoords();
		int subjectStart = blaPDBResultVector[k].getSubjectStart();
		string subject = blaPDBResultVector[k].getSubject();
		int subjectEnd = blaPDBResultVector[k].getSubjectEnd();

		int theSize = subject.size();
		cout << "asdasdfasdfdsaf" << theSize << endl;
		vector<float> extendedXs;
		extendedXs.resize(theSize);
		vector<float> extendedYs;
		extendedYs.resize(theSize);
		vector<float> extendedZs;
		extendedZs.resize(theSize);

		int count = 0;
		for (int i = 0; i < theSize; i++) {
			if (subject[i] == '-') {
				extendedXs[i] = 10000;
				extendedYs[i] = 10000;
				extendedZs[i] = 10000;

				count++;
			} else {
				extendedXs[i] = Xs[i + subjectStart - 1 - count];
				extendedYs[i] = Ys[i + subjectStart - 1 - count];
				extendedZs[i] = Zs[i + subjectStart - 1 - count];
			}
		}

		for (int i = 0; i < theSize; i++) {
			cout << " " << extendedXs[i];
		}
		cout << endl;
		for (int i = 0; i < theSize; i++) {
			cout << " " << extendedYs[i];
		}
		cout << endl;
		for (int i = 0; i < theSize; i++) {
			cout << " " << extendedZs[i];
		}
		cout << endl;
		vector<vector<float> > distMatrix;
		distMatrix.resize(theSize);
		//extended is the subject length from 0 to the length of it
		for (int i = 0; i < theSize; i++) {
			Point A(extendedXs[i], extendedYs[i], extendedZs[i]);

			for (int j = 0; j < theSize; j++) {
				Point B(extendedXs[j], extendedYs[j], extendedZs[j]);

				distMatrix[i][j] = findDistance(A, B); // Add an element (column) to the row
			}

		}
		blaPDBResultVector[k].setDistMat(distMatrix);
	}

//write the distance matrix into files for debugging

	for (int k = 0; k < blaPDBResultVector.size(); k++) {
		string proteinDistMatFilename(outputFileLocation);
		proteinDistMatFilename += "/";
		proteinDistMatFilename += rootName;
		proteinDistMatFilename += "/BLAPDB/distanceMatrix/";
		proteinDistMatFilename += "protein";
		proteinDistMatFilename += convertInt(k);
		proteinDistMatFilename += ".txt";
		vector<vector<float> > distanceMatrix =
				blaPDBResultVector[k].getDistMat();
		ofstream outDistMatFile((char*) proteinDistMatFilename.c_str(),
				ios::out);

		for (int i = 0; i < distanceMatrix.size(); i++) {

			for (int j = 0; j < distanceMatrix.size(); j++) {
				outDistMatFile << " " << distanceMatrix[i][j] << " ";
			}
			outDistMatFile << "\n";
		}
		outDistMatFile << "\n";
		outDistMatFile.close();
	}
	/*
	 int similaritySize = blaPDBResultVector.size();

	 vector<vector<float> > similairtyMatrix;
	 similairtyMatrix.resize(similaritySize);
	 for (int i = 0; i < similaritySize; i++) {
	 similairtyMatrix[i].resize(similaritySize);
	 }
	 //start finding the similarity matrix
	 for (int i = 0; i < similaritySize; i++) {
	 //int i = 1;
	 //int j = 0;
	 vector<vector<float> > distanceMatrixA =
	 blaPDBResultVector[i].getDistMat();
	 int queryAStart = blaPDBResultVector[i].getQueryStart();
	 int queryAEnd = blaPDBResultVector[i].getQueryEnd();
	 for (int j = 0; j < similaritySize; j++) {
	 vector<vector<float> > distanceMatrixB =
	 blaPDBResultVector[j].getDistMat();
	 int queryBStart = blaPDBResultVector[j].getQueryStart();
	 int queryBEnd = blaPDBResultVector[j].getQueryEnd();

	 //find overlapping area
	 if (queryAStart == queryBStart && queryAEnd == queryBEnd) {
	 similairtyMatrix[i][j] = 0.0;
	 } else if (queryAStart < queryBEnd && queryBStart < queryAEnd) {
	 int arr[4] = { queryAStart, queryAEnd, queryBStart, queryBEnd };
	 sort(arr, arr + 4);
	 int overlapSize = arr[2] - arr[1] + 1;

	 int temp = 0;

	 for (int m = 0; m < overlapSize; m++) {

	 for (int n = 0; n < overlapSize; n++) {
	 cout << " m " << m << " n " << n << "overlapSize"
	 << overlapSize << endl;
	 temp +=
	 (distanceMatrixA[arr[1] - queryAStart + m][arr[1]
	 - queryAStart + n]
	 - distanceMatrixB[arr[1] - queryBStart
	 + m][arr[1] - queryBStart + n])
	 * (distanceMatrixA[arr[1] - queryAStart
	 + m][arr[1] - queryAStart + n]
	 - distanceMatrixB[arr[1]
	 - queryBStart + m][arr[1]
	 - queryBStart + n]);

	 }

	 }

	 temp = temp / (overlapSize * overlapSize);
	 similairtyMatrix[i][j] = temp;

	 } else {
	 similairtyMatrix[i][j] = 1;
	 }

	 }
	 }
	 */
	//write similarity matrix to files
	/*
	 string proteinSimilarityMatFilename(outputFileLocation);
	 proteinSimilarityMatFilename += "/";
	 proteinSimilarityMatFilename += rootName;
	 proteinSimilarityMatFilename += "/BLAPDB/similarityMatrix.txt/";

	 //ofstream outSimilarityMatFile((char*) proteinSimilarityMatFilename.c_str(),
	 //		ios::out);
	 cout << "begin printing similarityMatrix" << endl;
	 for (int i = 0; i < blaPDBResultVector.size(); i++) {

	 for (int j = 0; j < blaPDBResultVector.size(); j++) {
	 //outSimilarityMatFile << " " << similairtyMatrix[i][j] << " ";
	 cout << " " << similairtyMatrix[i][j] << " ";
	 }
	 //outSimilarityMatFile << "\n";
	 cout << endl;
	 }
	 //outSimilarityMatFile << "\n";
	 //outSimilarityMatFile.close();
	 */
}

string BLAPDBImpl::convertInt(int number) {
	stringstream ss; //create a stringstream
	ss << number; //add number to the stream
	return ss.str(); //return a string with the contents of the stream
}

void BLAPDBImpl::findLocalAlign() {
	string proteinName;
	int subjectStart;
	string subject;
	string query;
	int subjectEnd;
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		proteinName = blaPDBResultVector[i].getProteinName();
		subjectStart = blaPDBResultVector[i].getSubjectStart();
		subject = blaPDBResultVector[i].getSubject();
		query = blaPDBResultVector[i].getQuery();
		subjectEnd = blaPDBResultVector[i].getSubjectEnd();
		vector<float> Xs = blaPDBResultVector[i].getXCoords();
		vector<float> Ys = blaPDBResultVector[i].getYCoords();
		vector<float> Zs = blaPDBResultVector[i].getZCoords();
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/BLAPDB/local/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += query;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		int offset = 0;
		for (int j = 0; j < subject.size(); j++) {
			if (subject[j] == '-' || query[j] != '-') {
				continue;
				//outJsonFile << "\"" << subject[j - 1] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else if (subject[j] != '-' || query[j] == '-') {
				offset++;
				continue;
			} else if (subject[j] == '-' || query[j] == '-') {
				continue;

			} else {

				outJsonFile << "\"" << query[j] << "\":\""
						<< Xs[subjectStart + offset - 1] << ","
						<< Ys[subjectStart + offset - 1] << ","
						<< Zs[subjectStart + offset - 1] << "\"\n";
				offset++;
			}

		}
		outJsonFile << "}\n";
		outJsonFile.close();

	}
}

void BLAPDBImpl::write2PDB() {
	string proteinName;
	int subjectStart;
	string subject;
	int subjectEnd;
	int queryStart;
	string query;
	int queryEnd;
	int length;
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		proteinName = blaPDBResultVector[i].getProteinName();
		queryStart = blaPDBResultVector[i].getQueryStart();
		query = blaPDBResultVector[i].getQuery();
		queryEnd = blaPDBResultVector[i].getQueryEnd();
		subjectStart = blaPDBResultVector[i].getSubjectStart();
		subject = blaPDBResultVector[i].getSubject();
		subjectEnd = blaPDBResultVector[i].getSubjectEnd();
		int queryHeadMore = queryStart - 1;
		int queryTailMore = proteinSeqLength - queryEnd;
		vector<float> Xs = blaPDBResultVector[i].getXCoords();
		vector<float> Ys = blaPDBResultVector[i].getYCoords();
		vector<float> Zs = blaPDBResultVector[i].getZCoords();
		vector<char> templateSeq = blaPDBResultVector[i].getTemplateSeq();
		length = blaPDBResultVector[i].getLength();
		int subjectHeadMore = subjectStart - 1;
		int subjectTailMore = length - subjectEnd;
		int headMore = 0;

		if (queryHeadMore > subjectHeadMore) {
			headMore = subjectHeadMore;
		} else {
			headMore = queryHeadMore;
		}

		int tailMore = 0;
		if (queryTailMore > subjectTailMore) {
			tailMore = subjectTailMore;
		} else {
			tailMore = queryTailMore;
		}
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/BLAPDB/pdbFiles/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += subject;
		protein3DCorrdsFilename += ".pdb";
		ofstream pdbFile((char*) protein3DCorrdsFilename.c_str(), ios::out);

		while (headMore > 0) {
			if (Xs[subjectStart - headMore - 1] != 10000
					&& Ys[subjectStart - headMore - 1] != 10000
					&& Zs[subjectStart - headMore - 1] != 10000) {
				pdbFile << "ATOM  ";				//record name
				pdbFile << right << setw(5) << subjectStart - headMore;	// atom serial number
				pdbFile << "  CA  ";				//atom name
				pdbFile << setw(3)
						<< convertResidueName(
								originalProteinSeq[queryStart - headMore - 1]);
				//pdbFile<<templateSeq[subjectStart - headMore];//for debug
				pdbFile << right << setw(6) << subjectStart - headMore;	// atom serial number
				pdbFile << "    ";
				pdbFile << right << setw(8.3)
						<< Xs[subjectStart - headMore - 1];
				pdbFile << right << setw(8.3)
						<< Ys[subjectStart - headMore - 1];
				pdbFile << right << setw(8.3)
						<< Zs[subjectStart - headMore - 1];
				pdbFile << "  1.00  0.00\n";
			}

			headMore--;
		}

		int queryPos = 1;
		int subjectPos = 1;
		for (int j = 0; j < subject.size(); j++) {
			if (subject[j] == '-' || query[j] != '-') {
				queryPos++;
				continue;
				//outJsonFile << "\"" << subject[j] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else if (subject[j] != '-' || query[j] == '-') {
				subjectPos++;
				continue;
			} else if (subject[j] == '-' || query[j] == '-') {
				continue;
			} else {
				if (Xs[subjectStart + subjectPos - 2] != 10000
						&& Ys[subjectStart + subjectPos - 2] != 10000
						&& Zs[subjectStart + subjectPos - 2] != 10000) {
					pdbFile << "ATOM  ";				//record name
					pdbFile << right << setw(5)
							<< subjectStart + subjectPos - 1;// atom serial number
					pdbFile << "  CA  ";				//atom name
					pdbFile << setw(3) << convertResidueName(query[j]);
					//pdbFile<<query[ j - 1]; //for dubug
					pdbFile << right << setw(6)
							<< subjectStart + subjectPos - 1;// atom serial number
					pdbFile << "    ";
					pdbFile << right << setw(8.3)
							<< Xs[subjectStart + subjectPos - 2];
					pdbFile << right << setw(8.3)
							<< Ys[subjectStart + subjectPos - 2];
					pdbFile << right << setw(8.3)
							<< Zs[subjectStart + subjectPos - 2];
					pdbFile << "  1.00  0.00\n";
				}
				subjectPos++;
				queryPos++;

			}

		}
//cout<<"Tailmore"<<tailMore<<endl;;
		if (tailMore > 0) {
			for (int k = 0; k < tailMore; k++) {
				if (Xs[subjectEnd + k] != 10000 && Ys[subjectEnd + k] != 10000
						&& Zs[subjectEnd + k] != 10000) {
					pdbFile << "ATOM  ";				//record name
					pdbFile << right << setw(5) << subjectEnd + k;// atom serial number
					pdbFile << "  CA  ";				//atom name
					pdbFile << setw(3)
							<< convertResidueName(
									originalProteinSeq[queryEnd + k]);
					pdbFile << right << setw(6) << subjectEnd + k;// atom serial number
					pdbFile << "    ";
					pdbFile << right << setw(8.3) << Xs[subjectEnd + k];
					pdbFile << right << setw(8.3) << Ys[subjectEnd + k];
					pdbFile << right << setw(8.3) << Zs[subjectEnd + k];
					pdbFile << "  1.00  0.00\n";
				}

			}

		}
		pdbFile << "TER\n";
		pdbFile.close();
	}

}

void BLAPDBImpl::findGlobalAlign() {
	string proteinName;
	int subjectStart;
	string subject;
	int subjectEnd;
	int queryStart;
	string query;
	int queryEnd;
	int length;
	for (int i = 0; i < blaPDBResultVector.size(); i++) {
		proteinName = blaPDBResultVector[i].getProteinName();
		queryStart = blaPDBResultVector[i].getQueryStart();
		query = blaPDBResultVector[i].getQuery();
		queryEnd = blaPDBResultVector[i].getQueryEnd();
		subjectStart = blaPDBResultVector[i].getSubjectStart();
		subject = blaPDBResultVector[i].getSubject();
		subjectEnd = blaPDBResultVector[i].getSubjectEnd();
		int queryHeadMore = queryStart - 1;
		int queryTailMore = proteinSeqLength - queryEnd;
		vector<float> Xs = blaPDBResultVector[i].getXCoords();
		vector<float> Ys = blaPDBResultVector[i].getYCoords();
		vector<float> Zs = blaPDBResultVector[i].getZCoords();
		vector<char> templateSeq = blaPDBResultVector[i].getTemplateSeq();
		length = blaPDBResultVector[i].getLength();
		int subjectHeadMore = subjectStart - 1;
		int subjectTailMore = length - subjectEnd;
//cout << proteinName << "---" << subjectTailMore << endl;
		int headMore = 0;

		if (queryHeadMore > subjectHeadMore) {
			headMore = subjectHeadMore;
		} else {
			headMore = queryHeadMore;
		}

		int tailMore = 0;
		if (queryTailMore > subjectTailMore) {
			tailMore = subjectTailMore;
		} else {
			tailMore = queryTailMore;
		}
		string protein3DCorrdsFilename(outputFileLocation);
		protein3DCorrdsFilename += "/";
		protein3DCorrdsFilename += rootName;
		protein3DCorrdsFilename += "/BLAPDB/FullyExtended/";
		protein3DCorrdsFilename += proteinName;
		protein3DCorrdsFilename += "_";
		protein3DCorrdsFilename += subject;
		protein3DCorrdsFilename += ".json";
		ofstream outJsonFile((char*) protein3DCorrdsFilename.c_str(), ios::out);
		outJsonFile << "{\n";
		outJsonFile << "\"proteinName\":\"" << proteinName << "\"\n";
		while (headMore > 0) {

			outJsonFile << "\"" << originalProteinSeq[queryStart - headMore - 1]
					<< "\":\"" << Xs[subjectStart - headMore - 1] << ","
					<< Ys[subjectStart - headMore - 1] << ","
					<< Zs[subjectStart - headMore - 1] << "\"\n";

			headMore--;
		}
		int offset = 0;
		for (int j = 0; j < subject.size(); j++) {
			if (subject[j] == '-' || query[j] != '-') {
				continue;
				//outJsonFile << "\"" << subject[j] << "\":\""
				//	<< "10000,10000,10000\"\n";
			} else if (subject[j] != '-' || query[j] == '-') {
				offset++;
				continue;
			} else if (subject[j] == '-' || query[j] == '-') {
				continue;
			} else {

				outJsonFile << "\"" << query[j] << "\":\""
						<< Xs[subjectStart + offset - 1] << ","
						<< Ys[subjectStart + offset - 1] << ","
						<< Zs[subjectStart + offset - 1] << "\"\n";
				offset++;

			}

		}
//cout<<"Tailmore"<<tailMore<<endl;;
		if (tailMore > 0) {
			for (int k = 0; k < tailMore; k++) {

				outJsonFile << "\"" << originalProteinSeq[queryEnd + k]
						<< "\":\"" << Xs[subjectEnd + k] << ","
						<< Ys[subjectEnd + k] << "," << Zs[subjectEnd + k]
						<< "\"\n";

			}

		}
		outJsonFile << "}\n";
		outJsonFile.close();
	}

}

BLAPDBImpl::~BLAPDBImpl() {
// TODO Auto-generated destructor stub
}

