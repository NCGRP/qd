#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "main.hpp"
using namespace std;


/***************GLOBAL VARIABLES*****************/


/***************SUBROUTINES*****************/


/***************MAIN*****************/
int main( int argc, char* argv[] )
{
	//declare initial variables
	std::string DoNorm = "no"; //normalize or not
	std::string DoQ = "no"; //calculate q-distance or not
	std::string DoP = "no"; //calculate partition distance or not
	const char* e; //partition 1 from command line
	const char* g; //partition 2 from command line
	const char* QMat1; //path to q-matrix 1 from command line
	const char* QMat2; //path to q-matrix 2 from command line
	
	//parse the command line for options
	for (int i=0;i<argc;i++)
	{
		if ( string(argv[i]) == "-q" )
			{
			    DoQ = "yes"; //calculate q-distance or not
        		QMat1 = argv[i+1];
        		QMat2 = argv[i+2];
			} 
 		if ( string(argv[i]) == "-p" )
			{
				DoP = "yes"; //calculate partition distance or not
				e = argv[i+1];
				g = argv[i+2];
			}
 		if ( string(argv[i]) == "-n" )
			{
        		DoNorm = "yes"; //normalize or not
			}
	}
	
	//compute distances
	if ( DoQ == "yes" )
		{
			qdist(QMat1,QMat2);
		}
	
	if ( DoP == "yes" )
		{
			partdist(e,g,DoNorm);
		}

	return 0;
}
