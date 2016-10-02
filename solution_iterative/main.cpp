#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <exception>
#include "IntersectCalculator.h"

using namespace std;

int main(int argc, char *argv[])
{
	try
	{
		if (argc < 2)
		{
			cerr << "Please enter the json file name: " << argv[0] << " filename [max_num_of_intersect]" << endl;
			return -1;
		}
		string filename = argv[1];
		
		int maxNumOfIntersect = -1;
		if (argc > 2)
			maxNumOfIntersect = atoi(argv[2]);
			
		InputReader inputReader;
		if (! inputReader.readInput(filename))
		{
			return -2;
		}

		IntersectCalculator intersectCalc(inputReader.getRectangles(), cout, maxNumOfIntersect);
		intersectCalc.calculateIntersections();
		return 0;
	}
	catch (const exception& e)
	{
		cerr << "Exception: " << e.what() << endl;
	}
	catch (...)
	{ 
		cerr << "Unknown Exception" << endl;
	}

	return -3;
}
