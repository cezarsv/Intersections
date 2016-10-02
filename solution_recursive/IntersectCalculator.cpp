#include <iostream>
#include <fstream>
#include <exception>
#include "json/json.h"
#include "IntersectCalculator.h"

using namespace std;

Rectangle::Rectangle()
:m_x(0), m_y(0), m_w(0), m_h(0)
{
}

Rectangle::Rectangle(int x, int y, int w, int h)
:m_x(x), m_y(y), m_w(w), m_h(h)
{
}

void Rectangle::intersect(const Rectangle& rect)
{
	int x = max(m_x, rect.m_x);
	int y = max(m_y, rect.m_y);
	m_w = min(m_x + m_w, rect.m_x + rect.m_w) - x;
	m_h = min(m_y + m_h, rect.m_y + rect.m_h) - y;
	m_x = x;
	m_y = y;
}

bool Rectangle::valid() const
{
    return m_w >= 0 && m_h >=0;
}

Intersection::Intersection(const Rectangle& rect, unsigned int idx)
{
	m_value = rect;
	m_indexes.push_back(idx);
}

void Intersection::intersect(const Rectangle& rect, unsigned int idx)
{
    if (empty())
        return;

    m_value.intersect(rect);
	m_indexes.push_back(idx);
}

bool Intersection::empty() const
{
    return (m_indexes.empty() || (! m_value.valid()));
}

int Intersection::size() const
{
	return m_indexes.size();
}

int Intersection::lastIdx() const
{
	return *m_indexes.rbegin();
}

void Intersection::print(std::ostream& output) const
{
	output << "\tBetween rectangle ";
	unsigned int count = m_indexes.size() - 1;
	for (list<unsigned int>::const_iterator it = m_indexes.begin(); it != m_indexes.end(); ++it, --count)
	{
		if (it != m_indexes.begin())
			output << ((! count) ? " and " : ", ");
		output << (*it + 1);
	}
	output << " at (" << m_value.m_x << "," << m_value.m_y << "), w=" << m_value.m_w << ", h=" << m_value.m_h << "." << endl;
}

InputReader::InputReader(unsigned int maxNumOfRects)
:MAX_NUM_OF_RECTS((maxNumOfRects > 0) ? maxNumOfRects : 1000)
{
}

const std::vector<Rectangle>& InputReader::getRectangles() const
{
	return m_rectangles;
}

bool InputReader::readInput(const std::string& filename)
{
	ifstream jsonFile(filename.c_str());
	if (! jsonFile.is_open())
	{
		cerr << "ERROR: Cannot open file '" << filename << "'" << endl;
		return false;
	}

	string line;
	string fileContent;
	while (getline (jsonFile, line))
	{
		fileContent += line + "\n";
	}
	jsonFile.close();

//		cerr << "<" << fileContent << ">" << endl;
	Json::Reader reader;
	Json::Value jsonRects;
	if (! reader.parse(fileContent, jsonRects))
	{
		cerr << "ERROR: Cannot parse json file '" << filename << "'" << endl;
		return false;
	}

	unsigned int numOfRects = jsonRects["rects"].size();
	if (numOfRects > MAX_NUM_OF_RECTS)
		numOfRects = MAX_NUM_OF_RECTS;
	for (unsigned int i = 0; i < numOfRects;  ++i)
	{
		const Json::Value& r = jsonRects["rects"][i];
		Rectangle rect(r["x"].asInt(), r["y"].asInt(), r["w"].asInt(), r["h"].asInt());
		m_rectangles.push_back(rect);
	}
	return true;
}

IntersectCalculator::IntersectCalculator(const vector<Rectangle>& rectangles, ostream& output, int maxNumOfIntersect)
:m_rectangles(rectangles), m_output(output), MAX_NUM_OF_INTERSECT(maxNumOfIntersect)
{
}

bool IntersectCalculator::allIntersectionsIncluding(Intersection& intersection, int& numOfFoundIntersect) const
{
	if ((MAX_NUM_OF_INTERSECT >= 0) && (numOfFoundIntersect >= MAX_NUM_OF_INTERSECT))
	{
		m_output << "Reached the permitted number of found valid intersections: " << MAX_NUM_OF_INTERSECT
				 << ", abandon the calculations" << endl;
		return false;
	}

	if (intersection.empty())
		return true;

	if (intersection.size() > 1)
	{
		intersection.print(m_output);
		++numOfFoundIntersect;
	}

	for (unsigned int i = intersection.lastIdx() + 1; i < m_rectangles.size(); ++i)
	{
		Intersection nextIntersection = intersection;
		nextIntersection.intersect(m_rectangles[i], i);
		if (! allIntersectionsIncluding(nextIntersection, numOfFoundIntersect))
			return false;
	}

	return true;
}

int IntersectCalculator::calculateIntersections() const
{
	m_output << "Input:" << endl;
	for (unsigned int i = 1; i <= m_rectangles.size(); ++i)
	{
		const Rectangle& r = m_rectangles[i-1];
		m_output << "\t" << i << ": Rectangle at (" << r.m_x << "," << r.m_y << "), w=" << r.m_w << ", h=" << r.m_h << "." << endl;
	}

	int numOfFoundIntersect = 0;
	m_output << endl << "Intersections:" << endl;
	for (unsigned int i = 0; i < m_rectangles.size(); ++i)
	{
		Intersection intersect(m_rectangles[i], i);
		if (! allIntersectionsIncluding(intersect, numOfFoundIntersect))
			break;
	}

	return numOfFoundIntersect;
}

