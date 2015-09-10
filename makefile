selectTopTemplate: jsoncpp.o AlignmentResult.o Point.o BLAPDBImpl.o BLAPDBResult.o Driver.o UtilityInterface.o 
	g++ jsoncpp.o AlignmentResult.o Point.o BLAPDBImpl.o BLAPDBResult.o Driver.o UtilityInterface.o  -o selectTopTemplate

jsoncpp.o: jsoncpp.cpp
	g++ -c jsoncpp.cpp
	
AlignmentResult.o: AlignmentResult.cpp
	g++ -c AlignmentResult.cpp
	
Point.o: Point.cpp
	g++ -c Point.cpp
			
BLAPDBImpl.o: BLAPDBImpl.cpp
	g++ -c BLAPDBImpl.cpp
	
BLAPDBResult.o: BLAPDBResult.cpp
	g++ -c BLAPDBResult.cpp

		
Driver.o: Driver.cpp
	g++ -c Driver.cpp
	
UtilityInterface.o: UtilityInterface.cpp
	g++ -c UtilityInterface.cpp

clean:
	rm *.o selectTopTemplate