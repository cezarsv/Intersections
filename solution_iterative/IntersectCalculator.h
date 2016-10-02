#include <string>
#include <list>
#include <queue>
#include <vector>
#include <iostream>

struct Rectangle
{
	Rectangle();
	Rectangle(int x, int y, int w, int h);

	void intersect(const Rectangle& r);
	bool valid() const;

	int m_x;
	int m_y;
	int m_w;
	int m_h;
};

// This class maintains the result of the intersection from many rectangles:
class Intersection
{
	public:
		Intersection(const Rectangle& rect, unsigned int idx);
	
		void intersect(const Rectangle& rect, unsigned int idx);

		bool empty() const;
		int lastIdx() const;
		void print(std::ostream& output) const;

	private:
		std::list<unsigned int> m_indexes;	// each index will refer a rectangle from an indexed collection of all rectangles
		Rectangle m_value;
};

class InputReader
{
	public:
		InputReader(unsigned int maxNumOfRects = 1000);
		bool readInput(const std::string& filename);
		const std::vector<Rectangle>& getRectangles() const;

	private:
		std::vector<Rectangle> m_rectangles;
		const unsigned int MAX_NUM_OF_RECTS;
};

class IntersectCalculator
{
	public:
		typedef std::queue<Intersection> IntersectionsLevel; // level K contains all non-empty Comb(N,K)

		IntersectCalculator(const std::vector<Rectangle>& rects, std::ostream& output = std::cout, int maxNumOfIntersect = -1);
		int calculateIntersections(); // find and print all the valid intersections 

	private:
		// Build the next level of non-empty intersections by adding to each 
		// intersection of the crt level each of the remaining Rectangles:
		bool buildNextLevel(int& numOfFoundIntersect);

		const std::vector<Rectangle>& m_rectangles;
		std::ostream& m_output;

		IntersectionsLevel m_levels[2];
		int m_crtLevel;		// m_levels[m_crtLevel] contains all combinations Comb(N, l).
		int m_nextLevel;	// m_levels[m_nextLevel] contains all combinations Comb(N, l+1), built from m_levels[m_crtLevel].

		const int MAX_NUM_OF_INTERSECT; // if positive, it will limit the number of found intersections.
};

