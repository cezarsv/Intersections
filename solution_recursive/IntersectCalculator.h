#include <string>
#include <list>
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
		Intersection(const Rectangle& r, unsigned int idx);
	
		void intersect(const Rectangle& rectangle, unsigned int idx);

		bool empty() const;
		int size() const;
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
		IntersectCalculator(const std::vector<Rectangle>& rects, std::ostream& output = std::cout, int maxNumOfIntersect = -1);
		int calculateIntersections() const; // find and print all the valid intersections

	private:
		// calculate all the non-empty Intersections that include the given one:
		bool allIntersectionsIncluding(Intersection& intersection, int& numOfFoundIntersect) const;

		const std::vector<Rectangle>& m_rectangles;
		std::ostream& m_output;
		const int MAX_NUM_OF_INTERSECT; // if positive, it will limit the number of found intersections.
};

