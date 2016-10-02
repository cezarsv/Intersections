#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "TestDriver.h"
#include "IntersectCalculator.h"

using namespace std;

// Helper, used to print a string both in ascii format and in hex
static std::string printHexAscii(const std::string& src)
{
	std::ostringstream os;
	std::ostringstream rt;

	for (std::string::size_type i = 0; i < src.length(); i++)
	{
		unsigned char out = src[i];
		char coutt = src[i];
		os << "0x" << std::setfill('0') << std::hex << std::setw(2) << (int)out << " ";
		if( out > 31 && out < 128 )
			rt << coutt;
		else
			rt << ".";
		if( (( (i+1) % 10) == 0) || i+1 == src.length()  )
		{
			os  << std::setfill(' ') << std::setw((10 - ((i) % 10)) * 5) << "[" << rt.str() << "]" << std::endl;
			rt.str("");
		}
	}

	return os.str();
}

std::ostream& operator<<(std::ostream& os, const Rectangle& r)
{
    os << "Rectangle(" << r.m_x << "," << r.m_y << "," << r.m_w << "," << r.m_h << ")";
    return os;
}

void setUp()
{
	system("rm -rf result.txt");
}

void tearDown()
{
	system("rm -rf result.txt");
}

BEGIN_TEST(Rectangle_IntersectOfTwo)
	Rectangle rect(100, 100, 250, 80);
	Rectangle rect1(140, 160, 250, 100);
	rect.intersect(rect1);
	Rectangle expected(140, 160, 210, 20);
	assertEquals(expected, rect);
}

BEGIN_TEST(Rectangle_OnePointIntersect)
    Rectangle rect(10, 10, 10, 10);
    Rectangle rect1(20, 20, 5, 5);
    rect.intersect(rect1);
    Rectangle expected(20, 20, 0, 0);
    assertEquals(expected, rect);
}

BEGIN_TEST(IntersectCalculator_DifferentRects)
	char expected[] =
		"Input:\n"
		"\t1: Rectangle at (100,100), w=250, h=80.\n"
		"\t2: Rectangle at (120,200), w=250, h=150.\n"
		"\t3: Rectangle at (140,160), w=250, h=100.\n"
		"\t4: Rectangle at (160,140), w=350, h=190.\n"
		"\n"
		"Intersections:\n"
		"\tBetween rectangle 1 and 3 at (140,160), w=210, h=20.\n"
		"\tBetween rectangle 1, 3 and 4 at (160,160), w=190, h=20.\n"
		"\tBetween rectangle 1 and 4 at (160,140), w=190, h=40.\n"
		"\tBetween rectangle 2 and 3 at (140,200), w=230, h=60.\n"
		"\tBetween rectangle 2, 3 and 4 at (160,200), w=210, h=60.\n"
		"\tBetween rectangle 2 and 4 at (160,200), w=210, h=130.\n"
		"\tBetween rectangle 3 and 4 at (160,160), w=230, h=100.\n"
		;

	vector<Rectangle> rectangles(4);
	rectangles[0] = Rectangle(100, 100, 250, 80);
	rectangles[1] = Rectangle(120, 200, 250, 150);
	rectangles[2] = Rectangle(140, 160, 250, 100);
	rectangles[3] = Rectangle(160, 140, 350, 190);

	ostringstream os;
	IntersectCalculator calc(rectangles, os);
	calc.calculateIntersections();
	//cerr << os.str() << endl;
	assertEquals(printHexAscii(expected), printHexAscii(os.str()));
}

BEGIN_TEST(IntersectCalculator_SimilarRects)
	char expected[] =
		"Input:\n"
		"\t1: Rectangle at (100,100), w=250, h=80.\n"
		"\t2: Rectangle at (100,100), w=250, h=80.\n"
		"\t3: Rectangle at (100,100), w=250, h=80.\n"
		"\t4: Rectangle at (100,100), w=250, h=80.\n"
		"\n"
		"Intersections:\n"
		"\tBetween rectangle 1 and 2 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 1, 2 and 3 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 1, 2, 3 and 4 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 1, 2 and 4 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 1 and 3 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 1, 3 and 4 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 1 and 4 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 2 and 3 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 2, 3 and 4 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 2 and 4 at (100,100), w=250, h=80.\n"
		"\tBetween rectangle 3 and 4 at (100,100), w=250, h=80.\n";

	vector<Rectangle> rectangles(4);
	rectangles[0] = Rectangle(100, 100, 250, 80);
	rectangles[1] = Rectangle(100, 100, 250, 80);
	rectangles[2] = Rectangle(100, 100, 250, 80);
	rectangles[3] = Rectangle(100, 100, 250, 80);

	ostringstream os;
	IntersectCalculator calc(rectangles, os);
	calc.calculateIntersections();
	//cerr << os.str() << endl;
	assertEquals(expected, os.str());
}

BEGIN_TEST(IntersectCalculator_EmptyIntersectWhenOneRect)
	char expected[] =
		"Input:\n"
		"\t1: Rectangle at (100,100), w=250, h=80.\n"
		"\n"
		"Intersections:\n"
		;

	vector<Rectangle> rectangles(1);
	rectangles[0] = Rectangle(100, 100, 250, 80);

	ostringstream os;
	IntersectCalculator calc(rectangles, os);
	calc.calculateIntersections();
	//cerr << os.str() << endl;
	assertEquals(expected, os.str());
}

BEGIN_TEST(IntersectCalculator_EmptyIntersectWhenNoRect)
	char expected[] =
		"Input:\n"
		"\n"
		"Intersections:\n"
		;

	vector<Rectangle> rectangles;

	ostringstream os;
	IntersectCalculator calc(rectangles, os);
	calc.calculateIntersections();
	//cerr << os.str() << endl;
	assertEquals(expected, os.str());
}

BEGIN_TEST(IntersectCalculator_EmptyIntersect)
	char expected[] =
		"Input:\n"
		"\t1: Rectangle at (10,10), w=10, h=10.\n"
		"\t2: Rectangle at (100,100), w=10, h=10.\n"
		"\n"
		"Intersections:\n"
		;

	vector<Rectangle> rectangles(2);
	rectangles[0] = Rectangle(10, 10, 10, 10);
	rectangles[1] = Rectangle(100, 100, 10, 10);

	ostringstream os;
	IntersectCalculator calc(rectangles, os);
	calc.calculateIntersections();
	//cerr << "\tExpected:" << endl << printHexAscii(expected) << endl << "\tGot:" << endl << printHexAscii(os.str()) << endl;
	assertEquals(expected, os.str());
}
 
BEGIN_TEST(IntersectCalculator_NumberOfFoundIntersect)
	vector<Rectangle> rectangles(4);
	rectangles[0] = Rectangle(100, 100, 250, 80);
	rectangles[1] = Rectangle(120, 200, 250, 150);
	rectangles[2] = Rectangle(140, 160, 250, 100);
	rectangles[3] = Rectangle(160, 140, 350, 190);

	ostringstream os;
	const int MaxNumOfFoundIntersect = 5;
	IntersectCalculator calc(rectangles, os, MaxNumOfFoundIntersect);
	int numOfIntersect = calc.calculateIntersections();
	//cerr << os.str() << endl;
	assertEquals(MaxNumOfFoundIntersect, numOfIntersect);
}

BEGIN_TEST(IntersectCalculator_LimitHugeNumberOfFoundIntersect)
	const int N = 1000;
	vector<Rectangle> rectangles;
	for (int i = 0; i < N; ++i)
		rectangles.push_back(Rectangle(100, 100, 250, 80));

	ostringstream os;
	const int MaxNumOfFoundIntersect = 1000;
	IntersectCalculator calc(rectangles, os, MaxNumOfFoundIntersect);
	int numOfIntersect = calc.calculateIntersections();
	//cerr << os.str() << endl;
	assertEquals(MaxNumOfFoundIntersect, numOfIntersect);
}

BEGIN_TEST(InputReader_NotExistingFile)
	InputReader inputReader;
	assertEquals(false, inputReader.readInput("NotExistingFile.txt"));
}

BEGIN_TEST(InputReader_BadFile)
	InputReader inputReader;
	assertEquals(false, inputReader.readInput("BadFile.txt"));
}
 
BEGIN_TEST(InputReader_GoodFile)
	InputReader inputReader;
	assertEquals(true, inputReader.readInput("GoodFile.txt"));
	assertEquals(4, inputReader.getRectangles().size());
}
 
BEGIN_TEST(InputReader_CheckMaxInput)
	InputReader inputReader(3);
	assertEquals(true, inputReader.readInput("GoodFile.txt"));
	assertEquals(3, inputReader.getRectangles().size());
}
 
BEGIN_TEST(IntersectCalculator_GoodFile)
	char expected[] =
		"Input:\n"
		"\t1: Rectangle at (100,100), w=250, h=80.\n"
		"\t2: Rectangle at (120,200), w=250, h=150.\n"
		"\t3: Rectangle at (140,160), w=250, h=100.\n"
		"\t4: Rectangle at (160,140), w=350, h=190.\n"
		"\n"
		"Intersections:\n"
		"\tBetween rectangle 1 and 3 at (140,160), w=210, h=20.\n"
		"\tBetween rectangle 1, 3 and 4 at (160,160), w=190, h=20.\n"
		"\tBetween rectangle 1 and 4 at (160,140), w=190, h=40.\n"
		"\tBetween rectangle 2 and 3 at (140,200), w=230, h=60.\n"
		"\tBetween rectangle 2, 3 and 4 at (160,200), w=210, h=60.\n"
		"\tBetween rectangle 2 and 4 at (160,200), w=210, h=130.\n"
		"\tBetween rectangle 3 and 4 at (160,160), w=230, h=100.\n"
		;

	InputReader inputReader;
	inputReader.readInput("GoodFile.txt");

	ostringstream os;
	IntersectCalculator calc(inputReader.getRectangles(), os);
	calc.calculateIntersections();
	//cerr << os.str() << endl;
	assertEquals(expected, os.str());
}

BEGIN_TEST(IntersectCalculator_VVManyIntersections)
	const int N = 10;
	vector<Rectangle> rectangles;
	for (int i = 0; i < N; ++i)
		rectangles.push_back(Rectangle(100, 100, 250, 80));

	int numOfIntersect = 0;

	fstream resultFile("result.txt", ios_base::in | ios_base::out | ios_base::trunc);
	assertEquals(true, resultFile.is_open());

	IntersectCalculator calc(rectangles, resultFile);
	calc.calculateIntersections();

	resultFile.seekg(ios_base::beg);
	string line;
	while (getline (resultFile, line))
	{
		if (line.find("Between rectangle") != string::npos)
			numOfIntersect++;
	}
	resultFile.close();

	assertEquals(1013, numOfIntersect);
}

int main()
{
	RUN_TEST(Rectangle_IntersectOfTwo);
	RUN_TEST(Rectangle_OnePointIntersect);
	RUN_TEST(IntersectCalculator_DifferentRects);
	RUN_TEST(IntersectCalculator_SimilarRects);
	RUN_TEST(IntersectCalculator_EmptyIntersectWhenOneRect);
	RUN_TEST(IntersectCalculator_EmptyIntersectWhenNoRect);
	RUN_TEST(IntersectCalculator_EmptyIntersect);
	RUN_TEST(IntersectCalculator_NumberOfFoundIntersect);
	RUN_TEST(IntersectCalculator_LimitHugeNumberOfFoundIntersect);
	RUN_TEST(InputReader_NotExistingFile);
	RUN_TEST(InputReader_BadFile);
	RUN_TEST(InputReader_GoodFile);
	RUN_TEST(InputReader_CheckMaxInput);
	RUN_TEST(IntersectCalculator_GoodFile);
	RUN_TEST(IntersectCalculator_VVManyIntersections);

	return 0;
}

